#include "character_p.h"
#include "physicsutils_p.h"

#include <Jolt/Physics/Collision/Shape/ScaledShape.h>
#include <Jolt/Physics/Collision/Shape/RotatedTranslatedShape.h>

Character::Character(QQuick3DNode *parent) : AbstractPhysicsCharacter(parent)
{
}

Character::~Character()
{
    Character::cleanup();
}

int Character::layer() const
{
    return m_characterSettings.mLayer;
}

void Character::setLayer(int layer)
{
    if (m_characterSettings.mLayer == layer)
        return;

    m_characterSettings.mLayer = layer;
    if (m_character)
        m_character->SetLayer(layer);

    emit layerChanged(layer);
}

float Character::mass() const
{
    return m_characterSettings.mMass;
}

void Character::setMass(float mass)
{
    if (qFuzzyCompare(m_characterSettings.mMass, mass))
        return;

    if (m_character) {
        qWarning() << "Warning: Changing 'mass' after character is initialized will have "
                      "no effect";
        return;
    }

    m_characterSettings.mMass = mass;
    emit massChanged(mass);
}

float Character::friction() const
{
    return m_characterSettings.mFriction;
}

void Character::setFriction(float friction)
{
    if (qFuzzyCompare(m_characterSettings.mFriction, friction))
        return;

    if (m_character) {
        qWarning() << "Warning: Changing 'friction' after character is initialized will have "
                      "no effect";
        return;
    }

    m_characterSettings.mFriction = friction;
    emit frictionChanged(friction);
}

float Character::gravityFactor() const
{
    return m_characterSettings.mGravityFactor;
}

void Character::setGravityFactor(float gravityFactor)
{
    if (qFuzzyCompare(m_characterSettings.mGravityFactor, gravityFactor))
        return;

    if (m_character) {
        qWarning() << "Warning: Changing 'gravityFactor' after character is initialized will have "
                      "no effect";
        return;
    }

    m_characterSettings.mGravityFactor = gravityFactor;
    emit gravityFactorChanged(gravityFactor);
}

QVector3D Character::getLinearVelocity() const
{
    if (m_character == nullptr)
        return QVector3D();

    return PhysicsUtils::toQtType(m_character->GetLinearVelocity());
}

void Character::setLinearVelocity(const QVector3D &linearVelocity)
{
    if (m_character == nullptr) {
        qWarning() << "Warning: Invoking 'setLinearVelocity' before character is initialized will have no effect";
        return;
    }

    m_character->SetLinearVelocity(PhysicsUtils::toJoltType(linearVelocity));
}

void Character::postSimulation(float maxSeparationDistance)
{
    if (m_character == nullptr)
        return;

    m_character->PostSimulation(maxSeparationDistance);
}

bool Character::setShape(float maxPenetrationDepth)
{
    auto shape = m_shape->getJoltShape();

    if (shape->MustBeStatic()) {
        qWarning() << "Character: Cannot make character containing static shape.";
        return false;
    }

    return m_character->SetShape(shape, maxPenetrationDepth);
}

JPH::CharacterBase *Character::character() const
{
    return m_character;
}

void Character::updateJoltObject()
{
    if (m_character || m_jolt == nullptr || m_shape == nullptr)
        return;

    auto shape = m_shape->getJoltShape();

    if (shape->MustBeStatic()) {
        qWarning() << "Character: Cannot make character containing static shape.";
        return;
    }

    m_characterSettings.mShape = shape;
    m_characterSettings.mSupportingVolume = JPH::Plane(PhysicsUtils::toJoltType(supportingVolume().toVector3D()), supportingVolume().w());
    m_characterSettings.mMaxSlopeAngle = qDegreesToRadians(maxSlopeAngle());

    m_character = new JPH::Character(
            &m_characterSettings,
            PhysicsUtils::toJoltType(scenePosition()),
            PhysicsUtils::toJoltType(sceneRotation()),
            reinterpret_cast<JPH::uint64>(this),
            m_jolt);

    m_character->AddToPhysicsSystem(static_cast<JPH::EActivation>(m_activation));

    m_bodyID = static_cast<int>(m_character->GetBodyID().GetIndexAndSequenceNumber());
    emit bodyIDChanged(m_bodyID);
}

void Character::cleanup()
{
    if (m_character) {
        m_character->RemoveFromPhysicsSystem();
        delete m_character;
    }

    m_character = nullptr;
}

void Character::sync()
{
    if (m_character == nullptr)
        return;

    QVector3D position = PhysicsUtils::toQtType(m_character->GetCenterOfMassPosition());
    const QQuick3DNode *parentNode = static_cast<QQuick3DNode *>(parentItem());

    if (!parentNode) {
        setPosition(position);
    } else {
        setPosition(parentNode->mapPositionFromScene(position));
    }
}
