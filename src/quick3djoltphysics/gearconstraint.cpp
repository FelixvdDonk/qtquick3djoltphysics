#include "gearconstraint_p.h"
#include "hingeconstraint_p.h"
#include "physicsutils_p.h"

#include <Jolt/Physics/PhysicsSystem.h>

GearConstraint::GearConstraint(QQuick3DNode *parent) : AbstractPhysicsConstraint(parent)
{
}

GearConstraint::~GearConstraint() = default;

Body *GearConstraint::body1() const
{
    return m_body1;
}

void GearConstraint::setBody1(Body *body)
{
    if (m_body1 == body)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'body1' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_body1 = body;
    emit body1Changed(m_body1);
}

Body *GearConstraint::body2() const
{
    return m_body2;
}

void GearConstraint::setBody2(Body *body)
{
    if (m_body2 == body)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'body2' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_body2 = body;
    emit body2Changed(m_body2);
}

QVector3D GearConstraint::hingeAxis1() const
{
    return m_hingeAxis1;
}

void GearConstraint::setHingeAxis1(const QVector3D &hingeAxis1)
{
    if (m_hingeAxis1 == hingeAxis1)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'hingeAxis1' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_hingeAxis1 = hingeAxis1;
    emit hingeAxis1Changed(m_hingeAxis1);
}

QVector3D GearConstraint::hingeAxis2() const
{
    return m_hingeAxis2;
}

void GearConstraint::setHingeAxis2(const QVector3D &hingeAxis2)
{
    if (m_hingeAxis2 == hingeAxis2)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'hingeAxis2' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_hingeAxis2 = hingeAxis2;
    emit hingeAxis2Changed(m_hingeAxis2);
}

float GearConstraint::ratio() const
{
    return m_ratio;
}

void GearConstraint::setRatio(float ratio)
{
    if (qFuzzyCompare(m_ratio, ratio))
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'ratio' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_ratio = ratio;
    emit ratioChanged(m_ratio);
}

HingeConstraint *GearConstraint::gear1Constraint() const
{
    return m_gear1Constraint;
}

void GearConstraint::setGear1Constraint(HingeConstraint *constraint)
{
    if (m_gear1Constraint == constraint)
        return;

    m_gear1Constraint = constraint;

    if (m_constraint && m_gear1Constraint && m_gear2Constraint) {
        static_cast<JPH::GearConstraint *>(m_constraint)->SetConstraints(
            m_gear1Constraint->m_constraint, m_gear2Constraint->m_constraint);
    }

    emit gear1ConstraintChanged(m_gear1Constraint);
}

void GearConstraint::setGear2Constraint(HingeConstraint *constraint)
{
    if (m_gear2Constraint == constraint)
        return;

    m_gear2Constraint = constraint;

    if (m_constraint && m_gear1Constraint && m_gear2Constraint) {
        static_cast<JPH::GearConstraint *>(m_constraint)->SetConstraints(
            m_gear1Constraint->m_constraint, m_gear2Constraint->m_constraint);
    }

    emit gear2ConstraintChanged(m_gear2Constraint);
}

HingeConstraint *GearConstraint::gear2Constraint() const
{
    return m_gear2Constraint;
}

float GearConstraint::getTotalLambda() const
{
    if (!m_constraint)
        return 0.0f;
    return static_cast<const JPH::GearConstraint *>(m_constraint)->GetTotalLambda();
}

void GearConstraint::updateJoltObject()
{
    if (m_jolt == nullptr || m_body1 == nullptr || m_body2 == nullptr || m_constraint)
        return;

    m_constraintSettings.mSpace = JPH::EConstraintSpace::WorldSpace;
    m_constraintSettings.mHingeAxis1 = PhysicsUtils::toJoltType(m_hingeAxis1);
    m_constraintSettings.mHingeAxis2 = PhysicsUtils::toJoltType(m_hingeAxis2);
    m_constraintSettings.mRatio = m_ratio;

    m_constraint = m_constraintSettings.Create(*m_body1->m_body, *m_body2->m_body);

    if (m_gear1Constraint && m_gear2Constraint
        && m_gear1Constraint->m_constraint && m_gear2Constraint->m_constraint) {
        static_cast<JPH::GearConstraint *>(m_constraint)->SetConstraints(
            m_gear1Constraint->m_constraint, m_gear2Constraint->m_constraint);
    }

    m_jolt->AddConstraint(m_constraint);
}
