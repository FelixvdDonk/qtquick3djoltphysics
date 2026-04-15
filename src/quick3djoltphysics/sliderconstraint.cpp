#include "sliderconstraint_p.h"
#include "physicsutils_p.h"

#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Constraints/MotorSettings.h>

SliderConstraint::SliderConstraint(QQuick3DNode *parent) : AbstractPhysicsConstraint(parent)
{
}

SliderConstraint::~SliderConstraint() = default;

QVector3D SliderConstraint::point1() const
{
    return m_point1;
}

void SliderConstraint::setPoint1(const QVector3D &point)
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

QVector3D SliderConstraint::point2() const
{
    return m_point2;
}

void SliderConstraint::setPoint2(const QVector3D &point)
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

Body *SliderConstraint::body1() const
{
    return m_body1;
}

void SliderConstraint::setBody1(Body *body)
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

Body *SliderConstraint::body2() const
{
    return m_body2;
}

void SliderConstraint::setBody2(Body *body)
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

QVector3D SliderConstraint::sliderAxis1() const
{
    return m_sliderAxis1;
}

void SliderConstraint::setSliderAxis1(const QVector3D &sliderAxis1)
{
    if (m_sliderAxis1 == sliderAxis1)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'sliderAxis1' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_sliderAxis1 = sliderAxis1;
    emit sliderAxis1Changed(m_sliderAxis1);
}

QVector3D SliderConstraint::sliderAxis2() const
{
    return m_sliderAxis2;
}

void SliderConstraint::setSliderAxis2(const QVector3D &sliderAxis2)
{
    if (m_sliderAxis2 == sliderAxis2)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'sliderAxis2' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_sliderAxis2 = sliderAxis2;
    emit sliderAxis2Changed(m_sliderAxis2);
}

QVector3D SliderConstraint::normalAxis1() const
{
    return m_normalAxis1;
}

void SliderConstraint::setNormalAxis1(const QVector3D &normalAxis1)
{
    if (m_normalAxis1 == normalAxis1)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'normalAxis1' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_normalAxis1 = normalAxis1;
    emit normalAxis1Changed(m_normalAxis1);
}

QVector3D SliderConstraint::normalAxis2() const
{
    return m_normalAxis2;
}

void SliderConstraint::setNormalAxis2(const QVector3D &normalAxis2)
{
    if (m_normalAxis2 == normalAxis2)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'normalAxis2' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_normalAxis2 = normalAxis2;
    emit normalAxis2Changed(m_normalAxis2);
}

float SliderConstraint::limitsMin() const
{
    return m_limitsMin;
}

void SliderConstraint::setLimitsMin(float limitsMin)
{
    if (qFuzzyCompare(m_limitsMin, limitsMin))
        return;

    m_limitsMin = limitsMin;
    if (m_constraint)
        static_cast<JPH::SliderConstraint *>(m_constraint)->SetLimits(m_limitsMin / 100.0f, m_limitsMax / 100.0f);

    emit limitsMinChanged(m_limitsMin);
}

float SliderConstraint::limitsMax() const
{
    return m_limitsMax;
}

void SliderConstraint::setLimitsMax(float limitsMax)
{
    if (qFuzzyCompare(m_limitsMax, limitsMax))
        return;

    m_limitsMax = limitsMax;
    if (m_constraint)
        static_cast<JPH::SliderConstraint *>(m_constraint)->SetLimits(m_limitsMin / 100.0f, m_limitsMax / 100.0f);

    emit limitsMaxChanged(m_limitsMax);
}

SpringSettings *SliderConstraint::limitsSpringSettings() const
{
    return m_limitsSpringSettings;
}

void SliderConstraint::setLimitsSpringSettings(SpringSettings *limitsSpringSettings)
{
    if (m_limitsSpringSettings == limitsSpringSettings)
        return;

    if (m_limitsSpringSettings)
        m_limitsSpringSettings->disconnect(m_limitsSpringSettingsConnection);

    m_limitsSpringSettings = limitsSpringSettings;

    m_limitsSpringSettingsConnection = QObject::connect(m_limitsSpringSettings, &SpringSettings::changed, this,
                    [this]
    {
        if (m_constraint != nullptr)
            static_cast<JPH::SliderConstraint *>(m_constraint)->SetLimitsSpringSettings(m_limitsSpringSettings->getJoltSpringSettings());
    });
    QObject::connect(m_limitsSpringSettings, &QObject::destroyed, this,
                     [this](QObject *obj)
    {
        if (m_limitsSpringSettings == obj) {
            m_limitsSpringSettings = nullptr;
            if (m_constraint != nullptr)
                static_cast<JPH::SliderConstraint *>(m_constraint)->SetLimitsSpringSettings(JPH::SpringSettings());
        }
    });

    if (m_constraint != nullptr)
        static_cast<JPH::SliderConstraint *>(m_constraint)->SetLimitsSpringSettings(m_limitsSpringSettings->getJoltSpringSettings());

    emit limitsSpringSettingsChanged(m_limitsSpringSettings);
}

float SliderConstraint::maxFrictionForce() const
{
    return m_maxFrictionForce;
}

void SliderConstraint::setMaxFrictionForce(float maxFrictionForce)
{
    if (qFuzzyCompare(m_maxFrictionForce, maxFrictionForce))
        return;

    m_maxFrictionForce = maxFrictionForce;

    if (m_constraint)
        static_cast<JPH::SliderConstraint *>(m_constraint)->SetMaxFrictionForce(maxFrictionForce);

    emit maxFrictionForceChanged(maxFrictionForce);
}

MotorSettings *SliderConstraint::motorSettings() const
{
    return m_motorSettings;
}

void SliderConstraint::setMotorSettings(MotorSettings *motorSettings)
{
    if (m_motorSettings == motorSettings)
        return;

    if (m_motorSettings)
        m_motorSettings->disconnect(m_motorSettingsConnection);

    m_motorSettings = motorSettings;

    m_motorSettingsConnection = QObject::connect(m_motorSettings, &MotorSettings::changed, this,
                    [this]
    {
        if (m_constraint != nullptr)
            static_cast<JPH::SliderConstraint *>(m_constraint)->GetMotorSettings() = m_motorSettings->getJoltMotorSettings();
    });
    QObject::connect(m_motorSettings, &QObject::destroyed, this,
                     [this](QObject *obj)
    {
        if (m_motorSettings == obj) {
            m_motorSettings = nullptr;
            if (m_constraint != nullptr)
                static_cast<JPH::SliderConstraint *>(m_constraint)->GetMotorSettings() = JPH::MotorSettings();
        }
    });

    if (m_constraint != nullptr)
        static_cast<JPH::SliderConstraint *>(m_constraint)->GetMotorSettings() = m_motorSettings->getJoltMotorSettings();

    emit motorSettingsChanged(m_motorSettings);
}

SliderConstraint::MotorState SliderConstraint::motorState() const
{
    return m_motorState;
}

void SliderConstraint::setMotorState(MotorState motorState)
{
    if (m_motorState == motorState)
        return;

    m_motorState = motorState;

    if (m_constraint)
        static_cast<JPH::SliderConstraint *>(m_constraint)->SetMotorState(static_cast<JPH::EMotorState>(m_motorState));

    emit motorStateChanged(m_motorState);
}

float SliderConstraint::targetVelocity() const
{
    return m_targetVelocity;
}

void SliderConstraint::setTargetVelocity(float targetVelocity)
{
    if (qFuzzyCompare(m_targetVelocity, targetVelocity))
        return;

    m_targetVelocity = targetVelocity;

    if (m_constraint)
        static_cast<JPH::SliderConstraint *>(m_constraint)->SetTargetVelocity(m_targetVelocity / 100.0f);

    emit targetVelocityChanged(m_targetVelocity);
}

float SliderConstraint::targetPosition() const
{
    return m_targetPosition;
}

void SliderConstraint::setTargetPosition(float targetPosition)
{
    if (qFuzzyCompare(m_targetPosition, targetPosition))
        return;

    m_targetPosition = targetPosition;

    if (m_constraint)
        static_cast<JPH::SliderConstraint *>(m_constraint)->SetTargetPosition(m_targetPosition / 100.0f);

    emit targetPositionChanged(m_targetPosition);
}

float SliderConstraint::getCurrentPosition() const
{
    if (m_constraint == nullptr)
        return 0.0f;

    return static_cast<JPH::SliderConstraint *>(m_constraint)->GetCurrentPosition() * 100.0f;
}

float SliderConstraint::getTotalLambdaMotor() const
{
    if (m_constraint == nullptr)
        return 0.0f;

    return static_cast<JPH::SliderConstraint *>(m_constraint)->GetTotalLambdaMotor();
}

float SliderConstraint::getTotalLambdaPositionLimits() const
{
    if (m_constraint == nullptr)
        return 0.0f;

    return static_cast<JPH::SliderConstraint *>(m_constraint)->GetTotalLambdaPositionLimits();
}

void SliderConstraint::updateJoltObject()
{
    if (m_jolt == nullptr || m_body1 == nullptr || m_body2 == nullptr || m_constraint)
        return;

    m_constraintSettings.mPoint1 = PhysicsUtils::toJoltType(m_point1);
    m_constraintSettings.mPoint2 = PhysicsUtils::toJoltType(m_point2);
    m_constraintSettings.mSliderAxis1 = PhysicsUtils::toJoltType(m_sliderAxis1);
    m_constraintSettings.mSliderAxis2 = PhysicsUtils::toJoltType(m_sliderAxis2);
    m_constraintSettings.mNormalAxis1 = PhysicsUtils::toJoltType(m_normalAxis1);
    m_constraintSettings.mNormalAxis2 = PhysicsUtils::toJoltType(m_normalAxis2);
    m_constraintSettings.mLimitsMin = m_limitsMin / 100.0f;
    m_constraintSettings.mLimitsMax = m_limitsMax / 100.0f;
    m_constraintSettings.mMaxFrictionForce = m_maxFrictionForce;

    if (m_limitsSpringSettings)
        m_constraintSettings.mLimitsSpringSettings = m_limitsSpringSettings->getJoltSpringSettings();

    if (m_motorSettings)
        m_constraintSettings.mMotorSettings = m_motorSettings->getJoltMotorSettings();

    m_constraint = m_constraintSettings.Create(*m_body1->m_body, *m_body2->m_body);

    auto *slider = static_cast<JPH::SliderConstraint *>(m_constraint);

    if (m_motorState != MotorState::Off)
        slider->SetMotorState(static_cast<JPH::EMotorState>(m_motorState));

    if (m_motorState == MotorState::Velocity)
        slider->SetTargetVelocity(m_targetVelocity / 100.0f);
    else if (m_motorState == MotorState::Position)
        slider->SetTargetPosition(m_targetPosition / 100.0f);

    m_jolt->AddConstraint(m_constraint);
}
