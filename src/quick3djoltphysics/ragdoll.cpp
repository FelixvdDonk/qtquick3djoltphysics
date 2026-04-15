#include "ragdoll_p.h"
#include "abstractshape_p.h"
#include "abstractphysicsconstraint_p.h"
#include "physicsutils_p.h"

#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Body/BodyLock.h>
#include <Jolt/Physics/Constraints/SwingTwistConstraint.h>
#include <Jolt/Physics/Constraints/HingeConstraint.h>

Ragdoll::Ragdoll(QQuick3DNode *parent) : AbstractPhysicsNode(parent)
{
}

Ragdoll::~Ragdoll()
{
    Ragdoll::cleanup();
}

PhysicsSkeleton *Ragdoll::skeleton() const
{
    return m_skeleton;
}

void Ragdoll::setSkeleton(PhysicsSkeleton *skeleton)
{
    if (m_skeleton == skeleton)
        return;

    if (m_ragdoll) {
        qWarning() << "Warning: Changing 'skeleton' after ragdoll is created will have no effect";
        return;
    }

    m_skeleton = skeleton;
    emit skeletonChanged(m_skeleton);
}

QQmlListProperty<RagdollPart> Ragdoll::parts()
{
    return QQmlListProperty<RagdollPart>(this, nullptr,
                                         &Ragdoll::appendPart,
                                         &Ragdoll::partCount,
                                         &Ragdoll::partAt,
                                         &Ragdoll::clearParts);
}

int Ragdoll::collisionGroupId() const
{
    return m_collisionGroupId;
}

void Ragdoll::setCollisionGroupId(int collisionGroupId)
{
    if (m_collisionGroupId == collisionGroupId)
        return;

    m_collisionGroupId = collisionGroupId;
    if (m_ragdoll)
        m_ragdoll->SetGroupID(static_cast<JPH::CollisionGroup::GroupID>(m_collisionGroupId));

    emit collisionGroupIdChanged(m_collisionGroupId);
}

bool Ragdoll::autoDisableParentChildCollisions() const
{
    return m_autoDisableParentChildCollisions;
}

void Ragdoll::setAutoDisableParentChildCollisions(bool autoDisable)
{
    if (m_autoDisableParentChildCollisions == autoDisable)
        return;

    if (m_ragdoll) {
        qWarning() << "Warning: Changing 'autoDisableParentChildCollisions' after ragdoll is "
                      "created will have no effect";
        return;
    }

    m_autoDisableParentChildCollisions = autoDisable;
    emit autoDisableParentChildCollisionsChanged(m_autoDisableParentChildCollisions);
}

void Ragdoll::addToPhysicsSystem()
{
    if (!m_jolt || !m_skeleton || m_ragdoll)
        return;

    // Build Jolt skeleton
    JPH::Ref<JPH::Skeleton> joltSkeleton = m_skeleton->createJoltSkeleton();
    const int jointCount = joltSkeleton->GetJointCount();

    if (jointCount == 0) {
        qWarning() << "Ragdoll: skeleton has no joints";
        return;
    }

    // Build name → index map
    m_nameToIndex.clear();
    m_nameToIndex.reserve(jointCount);
    for (int i = 0; i < jointCount; ++i) {
        const auto &joint = joltSkeleton->GetJoint(i);
        m_nameToIndex[QString::fromStdString(std::string(joint.mName.c_str()))] = i;
    }

    // Build ragdoll settings
    m_ragdollSettings = new JPH::RagdollSettings();
    m_ragdollSettings->mSkeleton = joltSkeleton;
    m_ragdollSettings->mParts.resize(static_cast<size_t>(jointCount));

    // Fill parts from QML
    for (auto *part : std::as_const(m_parts)) {
        auto it = m_nameToIndex.constFind(part->jointName());
        if (it == m_nameToIndex.constEnd()) {
            qWarning() << "Ragdoll: unknown joint name" << part->jointName();
            continue;
        }
        const int idx = it.value();
        auto &joltPart = m_ragdollSettings->mParts[static_cast<size_t>(idx)];

        // Shape
        if (part->shape()) {
            auto joltShape = part->shape()->getJoltShape();
            if (joltShape)
                joltPart.SetShape(joltShape);
        }

        // Motion type
        joltPart.mMotionType = static_cast<JPH::EMotionType>(part->motionType());

        // Mass
        if (part->mass() > 0.0f) {
            joltPart.mOverrideMassProperties = JPH::EOverrideMassProperties::CalculateInertia;
            joltPart.mMassPropertiesOverride.mMass = part->mass();
        }

        // Object layer
        joltPart.mObjectLayer = static_cast<JPH::ObjectLayer>(part->objectLayer());

        // Position and rotation
        joltPart.mPosition = JPH::RVec3(static_cast<JPH::Real>(part->position().x()),
                                         static_cast<JPH::Real>(part->position().y()),
                                         static_cast<JPH::Real>(part->position().z()));
        joltPart.mRotation = PhysicsUtils::toJoltType(part->rotation());

        // Constraint to parent
        if (part->constraintToParent()) {
            auto constraintSettings = part->constraintToParent()->createJoltConstraintSettings();
            if (constraintSettings)
                joltPart.mToParent = constraintSettings;
        }
    }

    // Disable parent-child collisions
    if (m_autoDisableParentChildCollisions)
        m_ragdollSettings->DisableParentChildCollisions();

    // Build index maps
    m_ragdollSettings->CalculateBodyIndexToConstraintIndex();

    // Create the runtime ragdoll
    m_ragdoll = m_ragdollSettings->CreateRagdoll(
        static_cast<JPH::CollisionGroup::GroupID>(m_collisionGroupId), 0, m_jolt);

    if (!m_ragdoll) {
        qWarning() << "Ragdoll: failed to create ragdoll (out of bodies?)";
        m_ragdollSettings = nullptr;
        return;
    }

    m_ragdoll->AddToPhysicsSystem(JPH::EActivation::Activate);
}

void Ragdoll::removeFromPhysicsSystem()
{
    if (!m_ragdoll)
        return;

    m_ragdoll->RemoveFromPhysicsSystem();
    delete m_ragdoll;
    m_ragdoll = nullptr;
    m_ragdollSettings = nullptr;
    m_nameToIndex.clear();
}

void Ragdoll::activate()
{
    if (m_ragdoll)
        m_ragdoll->Activate();
}

void Ragdoll::driveToPose(const QVariantMap &jointOrientations)
{
    if (!m_ragdoll || !m_ragdollSettings)
        return;

    for (auto it = jointOrientations.constBegin(); it != jointOrientations.constEnd(); ++it) {
        const int idx = jointIndexForName(it.key());
        if (idx < 0)
            continue;

        const int constraintIdx = m_ragdollSettings->GetConstraintIndexForBodyIndex(idx);
        if (constraintIdx < 0)
            continue;

        JPH::TwoBodyConstraint *constraint = m_ragdoll->GetConstraint(constraintIdx);
        if (!constraint)
            continue;

        const QQuaternion quat = it.value().value<QQuaternion>();
        const JPH::Quat joltQuat = PhysicsUtils::toJoltType(quat);

        JPH::EConstraintSubType subType = constraint->GetSubType();
        if (subType == JPH::EConstraintSubType::SwingTwist) {
            auto *st = static_cast<JPH::SwingTwistConstraint *>(constraint);
            st->SetSwingMotorState(JPH::EMotorState::Position);
            st->SetTwistMotorState(JPH::EMotorState::Position);
            st->SetTargetOrientationBS(joltQuat);
        } else if (subType == JPH::EConstraintSubType::Hinge) {
            auto *hinge = static_cast<JPH::HingeConstraint *>(constraint);
            hinge->SetMotorState(JPH::EMotorState::Position);
            // Extract angle from quaternion around hinge axis
            float angle = 2.0f * std::atan2(
                JPH::Vec3(joltQuat.GetX(), joltQuat.GetY(), joltQuat.GetZ()).Length(),
                joltQuat.GetW());
            hinge->SetTargetAngle(angle);
        }
    }
}

void Ragdoll::driveJointToAngle(const QString &jointName, float angleDegrees)
{
    if (!m_ragdoll || !m_ragdollSettings)
        return;

    const int idx = jointIndexForName(jointName);
    if (idx < 0)
        return;

    const int constraintIdx = m_ragdollSettings->GetConstraintIndexForBodyIndex(idx);
    if (constraintIdx < 0)
        return;

    JPH::TwoBodyConstraint *constraint = m_ragdoll->GetConstraint(constraintIdx);
    if (!constraint)
        return;

    if (constraint->GetSubType() == JPH::EConstraintSubType::Hinge) {
        auto *hinge = static_cast<JPH::HingeConstraint *>(constraint);
        hinge->SetMotorState(JPH::EMotorState::Position);
        hinge->SetTargetAngle(qDegreesToRadians(angleDegrees));
    }
}

QVector3D Ragdoll::getJointPosition(const QString &jointName) const
{
    if (!m_ragdoll || !m_jolt)
        return QVector3D();

    const int idx = jointIndexForName(jointName);
    if (idx < 0)
        return QVector3D();

    JPH::BodyID bodyId = m_ragdoll->GetBodyID(idx);
    JPH::BodyInterface &bi = m_jolt->GetBodyInterface();
    JPH::RVec3 pos = bi.GetPosition(bodyId);
    return QVector3D(static_cast<float>(pos.GetX()),
                     static_cast<float>(pos.GetY()),
                     static_cast<float>(pos.GetZ()));
}

QQuaternion Ragdoll::getJointRotation(const QString &jointName) const
{
    if (!m_ragdoll || !m_jolt)
        return QQuaternion();

    const int idx = jointIndexForName(jointName);
    if (idx < 0)
        return QQuaternion();

    JPH::BodyID bodyId = m_ragdoll->GetBodyID(idx);
    JPH::BodyInterface &bi = m_jolt->GetBodyInterface();
    JPH::Quat rot = bi.GetRotation(bodyId);
    return PhysicsUtils::toQtType(rot);
}

int Ragdoll::getJointCount() const
{
    if (m_ragdoll)
        return static_cast<int>(m_ragdoll->GetBodyCount());
    return 0;
}

void Ragdoll::updateJoltObject()
{
    // Ragdoll creation is deferred to addToPhysicsSystem() invocable
}

void Ragdoll::cleanup()
{
    if (m_ragdoll) {
        m_ragdoll->RemoveFromPhysicsSystem();
        delete m_ragdoll;
        m_ragdoll = nullptr;
    }
    m_ragdollSettings = nullptr;
    m_nameToIndex.clear();
}

void Ragdoll::appendPart(QQmlListProperty<RagdollPart> *list, RagdollPart *part)
{
    auto *self = static_cast<Ragdoll *>(list->object);
    self->m_parts.append(part);
}

qsizetype Ragdoll::partCount(QQmlListProperty<RagdollPart> *list)
{
    auto *self = static_cast<Ragdoll *>(list->object);
    return self->m_parts.size();
}

RagdollPart *Ragdoll::partAt(QQmlListProperty<RagdollPart> *list, qsizetype index)
{
    auto *self = static_cast<Ragdoll *>(list->object);
    return self->m_parts.at(index);
}

void Ragdoll::clearParts(QQmlListProperty<RagdollPart> *list)
{
    auto *self = static_cast<Ragdoll *>(list->object);
    self->m_parts.clear();
}

int Ragdoll::jointIndexForName(const QString &name) const
{
    auto it = m_nameToIndex.constFind(name);
    if (it == m_nameToIndex.constEnd()) {
        qWarning() << "Ragdoll: unknown joint name" << name;
        return -1;
    }
    return it.value();
}
