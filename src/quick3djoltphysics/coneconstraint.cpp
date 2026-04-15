#include "coneconstraint_p.h"
#include "physicsutils_p.h"

#include <Jolt/Physics/PhysicsSystem.h>

ConeConstraint::ConeConstraint(QQuick3DNode *parent) : AbstractPhysicsConstraint(parent)
{
}

ConeConstraint::~ConeConstraint() = default;

QVector3D ConeConstraint::point1() const
{
    return m_point1;
}

void ConeConstraint::setPoint1(const QVector3D &point)
{
    if (m_point1 == point)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'point1' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_point1 = point;
    emit point1Changed(m_point1);
}

QVector3D ConeConstraint::point2() const
{
    return m_point2;
}

void ConeConstraint::setPoint2(const QVector3D &point)
{
    if (m_point2 == point)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'point2' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_point2 = point;
    emit point2Changed(m_point2);
}

Body *ConeConstraint::body1() const
{
    return m_body1;
}

void ConeConstraint::setBody1(Body *body)
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

Body *ConeConstraint::body2() const
{
    return m_body2;
}

void ConeConstraint::setBody2(Body *body)
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

QVector3D ConeConstraint::twistAxis1() const
{
    return m_twistAxis1;
}

void ConeConstraint::setTwistAxis1(const QVector3D &twistAxis1)
{
    if (m_twistAxis1 == twistAxis1)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'twistAxis1' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_twistAxis1 = twistAxis1;
    emit twistAxis1Changed(m_twistAxis1);
}

QVector3D ConeConstraint::twistAxis2() const
{
    return m_twistAxis2;
}

void ConeConstraint::setTwistAxis2(const QVector3D &twistAxis2)
{
    if (m_twistAxis2 == twistAxis2)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'twistAxis2' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_twistAxis2 = twistAxis2;
    emit twistAxis2Changed(m_twistAxis2);
}

float ConeConstraint::halfConeAngle() const
{
    return m_halfConeAngle;
}

void ConeConstraint::setHalfConeAngle(float halfConeAngle)
{
    if (qFuzzyCompare(m_halfConeAngle, halfConeAngle))
        return;

    m_halfConeAngle = halfConeAngle;

    if (m_constraint)
        static_cast<JPH::ConeConstraint *>(m_constraint)->SetHalfConeAngle(qDegreesToRadians(m_halfConeAngle));

    emit halfConeAngleChanged(m_halfConeAngle);
}

QVector3D ConeConstraint::getTotalLambdaPosition() const
{
    if (m_constraint == nullptr)
        return QVector3D();

    return PhysicsUtils::toQtType(static_cast<JPH::ConeConstraint *>(m_constraint)->GetTotalLambdaPosition());
}

float ConeConstraint::getTotalLambdaRotation() const
{
    if (m_constraint == nullptr)
        return 0.0f;

    return static_cast<JPH::ConeConstraint *>(m_constraint)->GetTotalLambdaRotation();
}

void ConeConstraint::updateJoltObject()
{
    if (m_jolt == nullptr || m_body1 == nullptr || m_body2 == nullptr || m_constraint)
        return;

    m_constraintSettings.mPoint1 = PhysicsUtils::toJoltType(m_point1);
    m_constraintSettings.mPoint2 = PhysicsUtils::toJoltType(m_point2);
    m_constraintSettings.mTwistAxis1 = PhysicsUtils::toJoltType(m_twistAxis1);
    m_constraintSettings.mTwistAxis2 = PhysicsUtils::toJoltType(m_twistAxis2);
    m_constraintSettings.mHalfConeAngle = qDegreesToRadians(m_halfConeAngle);

    m_constraint = m_constraintSettings.Create(*m_body1->m_body, *m_body2->m_body);
    m_jolt->AddConstraint(m_constraint);
}

JPH::Ref<JPH::TwoBodyConstraintSettings> ConeConstraint::createJoltConstraintSettings() const
{
    auto *s = new JPH::ConeConstraintSettings();
    s->mPoint1 = PhysicsUtils::toJoltType(m_point1);
    s->mPoint2 = PhysicsUtils::toJoltType(m_point2);
    s->mTwistAxis1 = PhysicsUtils::toJoltType(m_twistAxis1);
    s->mTwistAxis2 = PhysicsUtils::toJoltType(m_twistAxis2);
    s->mHalfConeAngle = qDegreesToRadians(m_halfConeAngle);
    return s;
}
