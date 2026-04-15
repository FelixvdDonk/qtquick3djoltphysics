#include "softbody_p.h"
#include "physicsutils_p.h"

#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/SoftBody/SoftBodyMotionProperties.h>

SoftBody::SoftBody(QQuick3DNode *parent)
    : AbstractPhysicsNode(parent)
{
}

SoftBody::~SoftBody()
{
    cleanup();
}

SoftBodySharedSettings *SoftBody::sharedSettings() const
{
    return m_sharedSettings;
}

void SoftBody::setSharedSettings(SoftBodySharedSettings *settings)
{
    if (m_sharedSettings == settings)
        return;
    m_sharedSettings = settings;
    emit sharedSettingsChanged(m_sharedSettings);
}

quint32 SoftBody::objectLayer() const
{
    return m_objectLayer;
}

void SoftBody::setObjectLayer(quint32 objectLayer)
{
    if (m_objectLayer == objectLayer)
        return;
    m_objectLayer = objectLayer;
    emit objectLayerChanged(m_objectLayer);
}

int SoftBody::numIterations() const
{
    return m_numIterations;
}

void SoftBody::setNumIterations(int numIterations)
{
    if (m_numIterations == numIterations)
        return;
    m_numIterations = numIterations;
    emit numIterationsChanged(m_numIterations);
}

float SoftBody::linearDamping() const
{
    return m_linearDamping;
}

void SoftBody::setLinearDamping(float linearDamping)
{
    if (qFuzzyCompare(m_linearDamping, linearDamping))
        return;
    m_linearDamping = linearDamping;
    emit linearDampingChanged(m_linearDamping);
}

float SoftBody::maxLinearVelocity() const
{
    return m_maxLinearVelocity;
}

void SoftBody::setMaxLinearVelocity(float maxLinearVelocity)
{
    if (qFuzzyCompare(m_maxLinearVelocity, maxLinearVelocity))
        return;
    m_maxLinearVelocity = maxLinearVelocity;
    emit maxLinearVelocityChanged(m_maxLinearVelocity);
}

float SoftBody::restitution() const
{
    return m_restitution;
}

void SoftBody::setRestitution(float restitution)
{
    if (qFuzzyCompare(m_restitution, restitution))
        return;
    m_restitution = restitution;
    emit restitutionChanged(m_restitution);
}

float SoftBody::friction() const
{
    return m_friction;
}

void SoftBody::setFriction(float friction)
{
    if (qFuzzyCompare(m_friction, friction))
        return;
    m_friction = friction;
    emit frictionChanged(m_friction);
}

float SoftBody::pressure() const
{
    return m_pressure;
}

void SoftBody::setPressure(float pressure)
{
    if (qFuzzyCompare(m_pressure, pressure))
        return;
    m_pressure = pressure;
    emit pressureChanged(m_pressure);
}

float SoftBody::gravityFactor() const
{
    return m_gravityFactor;
}

void SoftBody::setGravityFactor(float gravityFactor)
{
    if (qFuzzyCompare(m_gravityFactor, gravityFactor))
        return;
    m_gravityFactor = gravityFactor;
    emit gravityFactorChanged(m_gravityFactor);
}

bool SoftBody::allowSleeping() const
{
    return m_allowSleeping;
}

void SoftBody::setAllowSleeping(bool allowSleeping)
{
    if (m_allowSleeping == allowSleeping)
        return;
    m_allowSleeping = allowSleeping;
    emit allowSleepingChanged(m_allowSleeping);
}

quint32 SoftBody::bodyID() const
{
    return m_bodyID;
}

int SoftBody::getNumVertices() const
{
    if (!m_body || !m_body->IsSoftBody())
        return 0;
    auto *mp = static_cast<JPH::SoftBodyMotionProperties *>(m_body->GetMotionProperties());
    return static_cast<int>(mp->GetVertices().size());
}

QVector3D SoftBody::getVertexPosition(int index) const
{
    if (!m_body || !m_body->IsSoftBody())
        return QVector3D();
    auto *mp = static_cast<JPH::SoftBodyMotionProperties *>(m_body->GetMotionProperties());
    const auto &vertices = mp->GetVertices();
    if (index < 0 || index >= static_cast<int>(vertices.size()))
        return QVector3D();
    // Vertex positions are local to body center of mass, convert to world then to cm
    JPH::RVec3 worldPos = m_body->GetCenterOfMassTransform() * vertices[index].mPosition;
    return QVector3D(static_cast<float>(worldPos.GetX()) * 100.0f,
                     static_cast<float>(worldPos.GetY()) * 100.0f,
                     static_cast<float>(worldPos.GetZ()) * 100.0f);
}

QVector3D SoftBody::getVertexVelocity(int index) const
{
    if (!m_body || !m_body->IsSoftBody())
        return QVector3D();
    auto *mp = static_cast<JPH::SoftBodyMotionProperties *>(m_body->GetMotionProperties());
    const auto &vertices = mp->GetVertices();
    if (index < 0 || index >= static_cast<int>(vertices.size()))
        return QVector3D();
    const JPH::Vec3 &vel = vertices[index].mVelocity;
    return QVector3D(vel.GetX() * 100.0f, vel.GetY() * 100.0f, vel.GetZ() * 100.0f);
}

float SoftBody::getVolume() const
{
    if (!m_body || !m_body->IsSoftBody())
        return 0.0f;
    auto *mp = static_cast<JPH::SoftBodyMotionProperties *>(m_body->GetMotionProperties());
    // Jolt volume in m³, convert to cm³ (× 1e6)
    return mp->GetVolume() * 1000000.0f;
}

void SoftBody::setPressureRuntime(float pressure)
{
    if (!m_body || !m_body->IsSoftBody())
        return;
    auto *mp = static_cast<JPH::SoftBodyMotionProperties *>(m_body->GetMotionProperties());
    mp->SetPressure(pressure);
    m_pressure = pressure;
}

void SoftBody::setNumIterationsRuntime(int numIterations)
{
    if (!m_body || !m_body->IsSoftBody())
        return;
    auto *mp = static_cast<JPH::SoftBodyMotionProperties *>(m_body->GetMotionProperties());
    mp->SetNumIterations(static_cast<uint32_t>(numIterations));
    m_numIterations = numIterations;
}

void SoftBody::updateJoltObject()
{
    if (!m_sharedSettings) {
        qWarning() << "SoftBody: sharedSettings is required";
        return;
    }

    JPH::Ref<JPH::SoftBodySharedSettings> joltSettings = m_sharedSettings->createJoltSettings();
    if (joltSettings == nullptr)
        return;

    JPH::SoftBodyCreationSettings creationSettings(
        joltSettings,
        PhysicsUtils::toJoltType(scenePosition()),
        PhysicsUtils::toJoltType(sceneRotation()),
        static_cast<JPH::ObjectLayer>(m_objectLayer));

    creationSettings.mNumIterations = static_cast<uint32_t>(m_numIterations);
    creationSettings.mLinearDamping = m_linearDamping;
    creationSettings.mMaxLinearVelocity = m_maxLinearVelocity / 100.0f; // cm/s -> m/s
    creationSettings.mRestitution = m_restitution;
    creationSettings.mFriction = m_friction;
    creationSettings.mPressure = m_pressure;
    creationSettings.mGravityFactor = m_gravityFactor;
    creationSettings.mAllowSleeping = m_allowSleeping;

    m_body = m_bodyInterface->CreateSoftBody(creationSettings);
    if (!m_body) {
        qWarning() << "SoftBody: failed to create Jolt soft body";
        return;
    }

    m_body->SetUserData(reinterpret_cast<JPH::uint64>(this));
    m_bodyInterface->AddBody(m_body->GetID(), JPH::EActivation::Activate);

    m_bodyID = m_body->GetID().GetIndexAndSequenceNumber();
    emit bodyIDChanged(m_bodyID);
}

void SoftBody::cleanup()
{
    if (m_body) {
        m_bodyInterface->RemoveBody(m_body->GetID());
        m_bodyInterface->DestroyBody(m_body->GetID());
        m_body = nullptr;
    }
}

void SoftBody::preSync(float deltaTime, QHash<QQuick3DNode *, QMatrix4x4> &transformCache)
{
    Q_UNUSED(deltaTime)
    Q_UNUSED(transformCache)

    if (!m_body)
        return;

    // Sync the QQuick3DNode position/rotation to match the Jolt body center of mass
    JPH::RVec3 pos = m_body->GetPosition();
    JPH::Quat rot = m_body->GetRotation();

    setPosition(QVector3D(static_cast<float>(pos.GetX()) * 100.0f,
                          static_cast<float>(pos.GetY()) * 100.0f,
                          static_cast<float>(pos.GetZ()) * 100.0f));
    setRotation(QQuaternion(rot.GetW(), rot.GetX(), rot.GetY(), rot.GetZ()));
}
