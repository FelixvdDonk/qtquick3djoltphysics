#include "ragdollpart_p.h"
#include "abstractshape_p.h"
#include "abstractphysicsconstraint_p.h"

RagdollPart::RagdollPart(QObject *parent) : QObject(parent)
{
}

RagdollPart::~RagdollPart() = default;

QString RagdollPart::jointName() const
{
    return m_jointName;
}

void RagdollPart::setJointName(const QString &jointName)
{
    if (m_jointName == jointName)
        return;

    m_jointName = jointName;
    emit jointNameChanged(m_jointName);
}

AbstractShape *RagdollPart::shape() const
{
    return m_shape;
}

void RagdollPart::setShape(AbstractShape *shape)
{
    if (m_shape == shape)
        return;

    m_shape = shape;
    emit shapeChanged(m_shape);
}

Body::MotionType RagdollPart::motionType() const
{
    return m_motionType;
}

void RagdollPart::setMotionType(Body::MotionType motionType)
{
    if (m_motionType == motionType)
        return;

    m_motionType = motionType;
    emit motionTypeChanged(m_motionType);
}

float RagdollPart::mass() const
{
    return m_mass;
}

void RagdollPart::setMass(float mass)
{
    if (qFuzzyCompare(m_mass, mass))
        return;

    m_mass = mass;
    emit massChanged(m_mass);
}

int RagdollPart::objectLayer() const
{
    return m_objectLayer;
}

void RagdollPart::setObjectLayer(int objectLayer)
{
    if (m_objectLayer == objectLayer)
        return;

    m_objectLayer = objectLayer;
    emit objectLayerChanged(m_objectLayer);
}

AbstractPhysicsConstraint *RagdollPart::constraintToParent() const
{
    return m_constraintToParent;
}

void RagdollPart::setConstraintToParent(AbstractPhysicsConstraint *constraint)
{
    if (m_constraintToParent == constraint)
        return;

    m_constraintToParent = constraint;
    emit constraintToParentChanged(m_constraintToParent);
}

QVector3D RagdollPart::position() const
{
    return m_position;
}

void RagdollPart::setPosition(const QVector3D &position)
{
    if (m_position == position)
        return;

    m_position = position;
    emit positionChanged(m_position);
}

QQuaternion RagdollPart::rotation() const
{
    return m_rotation;
}

void RagdollPart::setRotation(const QQuaternion &rotation)
{
    if (m_rotation == rotation)
        return;

    m_rotation = rotation;
    emit rotationChanged(m_rotation);
}
