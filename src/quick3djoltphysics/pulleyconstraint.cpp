#include "pulleyconstraint_p.h"
#include "physicsutils_p.h"

#include <Jolt/Physics/PhysicsSystem.h>

PulleyConstraint::PulleyConstraint(QQuick3DNode *parent) : AbstractPhysicsConstraint(parent)
{
}

PulleyConstraint::~PulleyConstraint() = default;

Body *PulleyConstraint::body1() const
{
    return m_body1;
}

void PulleyConstraint::setBody1(Body *body)
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

Body *PulleyConstraint::body2() const
{
    return m_body2;
}

void PulleyConstraint::setBody2(Body *body)
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

QVector3D PulleyConstraint::bodyPoint1() const
{
    return m_bodyPoint1;
}

void PulleyConstraint::setBodyPoint1(const QVector3D &point)
{
    if (m_bodyPoint1 == point)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'bodyPoint1' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_bodyPoint1 = point;
    emit bodyPoint1Changed(m_bodyPoint1);
}

QVector3D PulleyConstraint::fixedPoint1() const
{
    return m_fixedPoint1;
}

void PulleyConstraint::setFixedPoint1(const QVector3D &point)
{
    if (m_fixedPoint1 == point)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'fixedPoint1' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_fixedPoint1 = point;
    emit fixedPoint1Changed(m_fixedPoint1);
}

QVector3D PulleyConstraint::bodyPoint2() const
{
    return m_bodyPoint2;
}

void PulleyConstraint::setBodyPoint2(const QVector3D &point)
{
    if (m_bodyPoint2 == point)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'bodyPoint2' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_bodyPoint2 = point;
    emit bodyPoint2Changed(m_bodyPoint2);
}

QVector3D PulleyConstraint::fixedPoint2() const
{
    return m_fixedPoint2;
}

void PulleyConstraint::setFixedPoint2(const QVector3D &point)
{
    if (m_fixedPoint2 == point)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'fixedPoint2' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_fixedPoint2 = point;
    emit fixedPoint2Changed(m_fixedPoint2);
}

float PulleyConstraint::ratio() const
{
    return m_ratio;
}

void PulleyConstraint::setRatio(float ratio)
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

float PulleyConstraint::minLength() const
{
    return m_minLength;
}

void PulleyConstraint::setMinLength(float minLength)
{
    if (qFuzzyCompare(m_minLength, minLength))
        return;

    m_minLength = minLength;

    if (m_constraint)
        static_cast<JPH::PulleyConstraint *>(m_constraint)->SetLength(m_minLength / 100.0f, m_maxLength / 100.0f);

    emit minLengthChanged(m_minLength);
}

float PulleyConstraint::maxLength() const
{
    return m_maxLength;
}

void PulleyConstraint::setMaxLength(float maxLength)
{
    if (qFuzzyCompare(m_maxLength, maxLength))
        return;

    m_maxLength = maxLength;

    if (m_constraint)
        static_cast<JPH::PulleyConstraint *>(m_constraint)->SetLength(m_minLength / 100.0f, m_maxLength / 100.0f);

    emit maxLengthChanged(m_maxLength);
}

float PulleyConstraint::getCurrentLength() const
{
    if (!m_constraint)
        return 0.0f;
    return static_cast<const JPH::PulleyConstraint *>(m_constraint)->GetCurrentLength() * 100.0f;
}

float PulleyConstraint::getTotalLambdaPosition() const
{
    if (!m_constraint)
        return 0.0f;
    return static_cast<const JPH::PulleyConstraint *>(m_constraint)->GetTotalLambdaPosition();
}

void PulleyConstraint::updateJoltObject()
{
    if (m_jolt == nullptr || m_body1 == nullptr || m_body2 == nullptr || m_constraint)
        return;

    m_constraintSettings.mSpace = JPH::EConstraintSpace::WorldSpace;
    m_constraintSettings.mBodyPoint1 = JPH::RVec3(m_bodyPoint1.x() / 100.0f,
                                                    m_bodyPoint1.y() / 100.0f,
                                                    m_bodyPoint1.z() / 100.0f);
    m_constraintSettings.mFixedPoint1 = JPH::RVec3(m_fixedPoint1.x() / 100.0f,
                                                     m_fixedPoint1.y() / 100.0f,
                                                     m_fixedPoint1.z() / 100.0f);
    m_constraintSettings.mBodyPoint2 = JPH::RVec3(m_bodyPoint2.x() / 100.0f,
                                                    m_bodyPoint2.y() / 100.0f,
                                                    m_bodyPoint2.z() / 100.0f);
    m_constraintSettings.mFixedPoint2 = JPH::RVec3(m_fixedPoint2.x() / 100.0f,
                                                     m_fixedPoint2.y() / 100.0f,
                                                     m_fixedPoint2.z() / 100.0f);
    m_constraintSettings.mRatio = m_ratio;
    m_constraintSettings.mMinLength = m_minLength / 100.0f;
    m_constraintSettings.mMaxLength = m_maxLength < 0.0f ? -1.0f : m_maxLength / 100.0f;

    m_constraint = m_constraintSettings.Create(*m_body1->m_body, *m_body2->m_body);
    m_jolt->AddConstraint(m_constraint);
}
