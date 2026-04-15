#include "rackandpinionconstraint_p.h"
#include "hingeconstraint_p.h"
#include "sliderconstraint_p.h"
#include "physicsutils_p.h"

#include <Jolt/Physics/PhysicsSystem.h>

RackAndPinionConstraint::RackAndPinionConstraint(QQuick3DNode *parent)
    : AbstractPhysicsConstraint(parent)
{
}

RackAndPinionConstraint::~RackAndPinionConstraint() = default;

Body *RackAndPinionConstraint::body1() const
{
    return m_body1;
}

void RackAndPinionConstraint::setBody1(Body *body)
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

Body *RackAndPinionConstraint::body2() const
{
    return m_body2;
}

void RackAndPinionConstraint::setBody2(Body *body)
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

QVector3D RackAndPinionConstraint::hingeAxis() const
{
    return m_hingeAxis;
}

void RackAndPinionConstraint::setHingeAxis(const QVector3D &hingeAxis)
{
    if (m_hingeAxis == hingeAxis)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'hingeAxis' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_hingeAxis = hingeAxis;
    emit hingeAxisChanged(m_hingeAxis);
}

QVector3D RackAndPinionConstraint::sliderAxis() const
{
    return m_sliderAxis;
}

void RackAndPinionConstraint::setSliderAxis(const QVector3D &sliderAxis)
{
    if (m_sliderAxis == sliderAxis)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'sliderAxis' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_sliderAxis = sliderAxis;
    emit sliderAxisChanged(m_sliderAxis);
}

float RackAndPinionConstraint::ratio() const
{
    return m_ratio;
}

void RackAndPinionConstraint::setRatio(float ratio)
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

HingeConstraint *RackAndPinionConstraint::pinionConstraint() const
{
    return m_pinionConstraint;
}

void RackAndPinionConstraint::setPinionConstraint(HingeConstraint *constraint)
{
    if (m_pinionConstraint == constraint)
        return;

    m_pinionConstraint = constraint;

    if (m_constraint && m_pinionConstraint && m_rackConstraint) {
        static_cast<JPH::RackAndPinionConstraint *>(m_constraint)->SetConstraints(
            m_pinionConstraint->m_constraint, m_rackConstraint->m_constraint);
    }

    emit pinionConstraintChanged(m_pinionConstraint);
}

SliderConstraint *RackAndPinionConstraint::rackConstraint() const
{
    return m_rackConstraint;
}

void RackAndPinionConstraint::setRackConstraint(SliderConstraint *constraint)
{
    if (m_rackConstraint == constraint)
        return;

    m_rackConstraint = constraint;

    if (m_constraint && m_pinionConstraint && m_rackConstraint) {
        static_cast<JPH::RackAndPinionConstraint *>(m_constraint)->SetConstraints(
            m_pinionConstraint->m_constraint, m_rackConstraint->m_constraint);
    }

    emit rackConstraintChanged(m_rackConstraint);
}

float RackAndPinionConstraint::getTotalLambda() const
{
    if (!m_constraint)
        return 0.0f;
    return static_cast<const JPH::RackAndPinionConstraint *>(m_constraint)->GetTotalLambda();
}

void RackAndPinionConstraint::updateJoltObject()
{
    if (m_jolt == nullptr || m_body1 == nullptr || m_body2 == nullptr || m_constraint)
        return;

    m_constraintSettings.mSpace = JPH::EConstraintSpace::WorldSpace;
    m_constraintSettings.mHingeAxis = PhysicsUtils::toJoltType(m_hingeAxis);
    m_constraintSettings.mSliderAxis = PhysicsUtils::toJoltType(m_sliderAxis);
    m_constraintSettings.mRatio = m_ratio;

    m_constraint = m_constraintSettings.Create(*m_body1->m_body, *m_body2->m_body);

    if (m_pinionConstraint && m_rackConstraint
        && m_pinionConstraint->m_constraint && m_rackConstraint->m_constraint) {
        static_cast<JPH::RackAndPinionConstraint *>(m_constraint)->SetConstraints(
            m_pinionConstraint->m_constraint, m_rackConstraint->m_constraint);
    }

    m_jolt->AddConstraint(m_constraint);
}
