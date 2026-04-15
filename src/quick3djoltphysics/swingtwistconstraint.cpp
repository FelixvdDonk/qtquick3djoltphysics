#include "swingtwistconstraint_p.h"
#include "physicsutils_p.h"

#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Constraints/MotorSettings.h>

SwingTwistConstraint::SwingTwistConstraint(QQuick3DNode *parent) : AbstractPhysicsConstraint(parent)
{
}

SwingTwistConstraint::~SwingTwistConstraint() = default;

Body *SwingTwistConstraint::body1() const
{
    return m_body1;
}

void SwingTwistConstraint::setBody1(Body *body)
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

Body *SwingTwistConstraint::body2() const
{
    return m_body2;
}

void SwingTwistConstraint::setBody2(Body *body)
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

QVector3D SwingTwistConstraint::position1() const
{
    return m_position1;
}

void SwingTwistConstraint::setPosition1(const QVector3D &position1)
{
    if (m_position1 == position1)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'position1' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_position1 = position1;
    emit position1Changed(m_position1);
}

QVector3D SwingTwistConstraint::position2() const
{
    return m_position2;
}

void SwingTwistConstraint::setPosition2(const QVector3D &position2)
{
    if (m_position2 == position2)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'position2' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_position2 = position2;
    emit position2Changed(m_position2);
}

QVector3D SwingTwistConstraint::twistAxis1() const
{
    return m_twistAxis1;
}

void SwingTwistConstraint::setTwistAxis1(const QVector3D &twistAxis1)
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

QVector3D SwingTwistConstraint::twistAxis2() const
{
    return m_twistAxis2;
}

void SwingTwistConstraint::setTwistAxis2(const QVector3D &twistAxis2)
{
    if (m_twistAxis2 == twistAxis2)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'twistAxis2' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_twistAxis2 = twistAxis2;
    emit twistAxis1Changed(m_twistAxis2);
}

QVector3D SwingTwistConstraint::planeAxis1() const
{
    return m_planeAxis1;
}

void SwingTwistConstraint::setPlaneAxis1(const QVector3D &planeAxis1)
{
    if (m_planeAxis1 == planeAxis1)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'planeAxis1' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_planeAxis1 = planeAxis1;
    emit planeAxis1Changed(m_planeAxis1);
}

QVector3D SwingTwistConstraint::planeAxis2() const
{
    return m_planeAxis2;
}

void SwingTwistConstraint::setPlaneAxis2(const QVector3D &planeAxis2)
{
    if (m_planeAxis2 == planeAxis2)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'planeAxis2' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_planeAxis2 = planeAxis2;
    emit planeAxis2Changed(m_planeAxis1);
}

SwingTwistConstraint::SwingType SwingTwistConstraint::swingType() const
{
    return static_cast<SwingType>(m_constraintSettings.mSwingType);
}

void SwingTwistConstraint::setSwingType(SwingType swingType)
{
    if (static_cast<SwingType>(m_constraintSettings.mSwingType) == swingType)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'swingType' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_constraintSettings.mSwingType = static_cast<JPH::ESwingType>(swingType);
    emit swingTypeChanged(swingType);
}

float SwingTwistConstraint::normalHalfConeAngle() const
{
    return m_normalHalfConeAngle;
}

void SwingTwistConstraint::setNormalHalfConeAngle(float normalHalfConeAngle)
{
    if (qFuzzyCompare(m_normalHalfConeAngle, normalHalfConeAngle))
        return;

    if (m_constraint)
        static_cast<JPH::SwingTwistConstraint *>(m_constraint)->SetNormalHalfConeAngle(qDegreesToRadians(normalHalfConeAngle));

    m_normalHalfConeAngle = normalHalfConeAngle;
    emit normalHalfConeAngleChanged(normalHalfConeAngle);
}

float SwingTwistConstraint::planeHalfConeAngle() const
{
    return m_planeHalfConeAngle;
}

void SwingTwistConstraint::setPlaneHalfConeAngle(float planeHalfConeAngle)
{
    if (qFuzzyCompare(m_planeHalfConeAngle, planeHalfConeAngle))
        return;

    if (m_constraint)
        static_cast<JPH::SwingTwistConstraint *>(m_constraint)->SetPlaneHalfConeAngle(qDegreesToRadians(m_planeHalfConeAngle));

    m_planeHalfConeAngle = planeHalfConeAngle;
    emit planeHalfConeAngleChanged(planeHalfConeAngle);
}

float SwingTwistConstraint::twistMinAngle() const
{
    return m_twistMinAngle;
}

void SwingTwistConstraint::setTwistMinAngle(float twistMinAngle)
{
    if (qFuzzyCompare(m_twistMinAngle, twistMinAngle))
        return;

    if (m_constraint)
        static_cast<JPH::SwingTwistConstraint *>(m_constraint)->SetTwistMinAngle(qDegreesToRadians(m_twistMinAngle));

    m_twistMinAngle = twistMinAngle;
    emit twistMinAngleChanged(twistMinAngle);
}

float SwingTwistConstraint::twistMaxAngle() const
{
    return m_twistMaxAngle;
}

void SwingTwistConstraint::setTwistMaxAngle(float twistMaxAngle)
{
    if (qFuzzyCompare(m_twistMaxAngle, twistMaxAngle))
        return;

    if (m_constraint)
        static_cast<JPH::SwingTwistConstraint *>(m_constraint)->SetTwistMaxAngle(qDegreesToRadians(m_twistMaxAngle));

    m_twistMaxAngle = twistMaxAngle;
    emit twistMaxAngleChanged(twistMaxAngle);
}

float SwingTwistConstraint::maxFrictionTorque() const
{
    return m_constraintSettings.mMaxFrictionTorque;
}

void SwingTwistConstraint::setMaxFrictionTorque(float maxFrictionTorque)
{
    if (qFuzzyCompare(m_constraintSettings.mMaxFrictionTorque, maxFrictionTorque))
        return;

    if (m_constraint)
        static_cast<JPH::SwingTwistConstraint *>(m_constraint)->SetMaxFrictionTorque(maxFrictionTorque);

    m_constraintSettings.mMaxFrictionTorque = maxFrictionTorque;
    emit maxFrictionTorqueChanged(maxFrictionTorque);
}

MotorSettings *SwingTwistConstraint::swingMotorSettings() const
{
    return m_swingMotorSettings;
}

void SwingTwistConstraint::setSwingMotorSettings(MotorSettings *swingMotorSettings)
{
    if (m_swingMotorSettings == swingMotorSettings)
        return;

    if (m_swingMotorSettings)
        m_swingMotorSettings->disconnect(m_swingMotorSettingsConnection);

    m_swingMotorSettings = swingMotorSettings;

    m_swingMotorSettingsConnection = QObject::connect(m_swingMotorSettings, &MotorSettings::changed, this,
                    [this]
    {
        if (m_constraint != nullptr)
            static_cast<JPH::SwingTwistConstraint *>(m_constraint)->GetSwingMotorSettings() = m_swingMotorSettings->getJoltMotorSettings();
    });
    QObject::connect(m_swingMotorSettings, &QObject::destroyed, this,
                     [this](QObject *obj)
    {
        if (m_swingMotorSettings == obj) {
            m_swingMotorSettings = nullptr;
            if (m_constraint != nullptr)
                static_cast<JPH::SwingTwistConstraint *>(m_constraint)->GetSwingMotorSettings() = JPH::MotorSettings();
        }
    });

    if (m_constraint != nullptr)
        static_cast<JPH::SwingTwistConstraint *>(m_constraint)->GetSwingMotorSettings() = m_swingMotorSettings->getJoltMotorSettings();

    emit swingMotorSettingsChanged(m_swingMotorSettings);
}

MotorSettings *SwingTwistConstraint::twistMotorSettings() const
{
    return m_twistMotorSettings;
}

void SwingTwistConstraint::setTwistMotorSettings(MotorSettings *twistMotorSettings)
{
    if (m_twistMotorSettings == twistMotorSettings)
        return;

    if (m_twistMotorSettings)
        m_twistMotorSettings->disconnect(m_twistMotorSettingsConnection);

    m_twistMotorSettings = twistMotorSettings;

    m_twistMotorSettingsConnection = QObject::connect(m_twistMotorSettings, &MotorSettings::changed, this,
                    [this]
    {
        if (m_constraint != nullptr)
            static_cast<JPH::SwingTwistConstraint *>(m_constraint)->GetTwistMotorSettings() = m_twistMotorSettings->getJoltMotorSettings();
    });
    QObject::connect(m_twistMotorSettings, &QObject::destroyed, this,
                     [this](QObject *obj)
    {
        if (m_twistMotorSettings == obj) {
            m_twistMotorSettings = nullptr;
            if (m_constraint != nullptr)
                static_cast<JPH::SwingTwistConstraint *>(m_constraint)->GetTwistMotorSettings() = JPH::MotorSettings();
        }
    });

    if (m_constraint != nullptr)
        static_cast<JPH::SwingTwistConstraint *>(m_constraint)->GetTwistMotorSettings() = m_twistMotorSettings->getJoltMotorSettings();

    emit twistMotorSettingsChanged(m_twistMotorSettings);
}

SwingTwistConstraint::MotorState SwingTwistConstraint::swingMotorState() const
{
    return m_swingMotorState;
}

void SwingTwistConstraint::setSwingMotorState(MotorState swingMotorState)
{
    if (m_swingMotorState == swingMotorState)
        return;

    m_swingMotorState = swingMotorState;

    if (m_constraint)
        static_cast<JPH::SwingTwistConstraint *>(m_constraint)->SetSwingMotorState(static_cast<JPH::EMotorState>(m_swingMotorState));

    emit swingMotorStateChanged(m_swingMotorState);
}

SwingTwistConstraint::MotorState SwingTwistConstraint::twistMotorState() const
{
    return m_twistMotorState;
}

void SwingTwistConstraint::setTwistMotorState(MotorState twistMotorState)
{
    if (m_twistMotorState == twistMotorState)
        return;

    m_twistMotorState = twistMotorState;

    if (m_constraint)
        static_cast<JPH::SwingTwistConstraint *>(m_constraint)->SetTwistMotorState(static_cast<JPH::EMotorState>(m_twistMotorState));

    emit twistMotorStateChanged(m_twistMotorState);
}

QVector3D SwingTwistConstraint::targetAngularVelocityCS() const
{
    return m_targetAngularVelocityCS;
}

void SwingTwistConstraint::setTargetAngularVelocityCS(const QVector3D &targetAngularVelocityCS)
{
    if (m_targetAngularVelocityCS == targetAngularVelocityCS)
        return;

    m_targetAngularVelocityCS = targetAngularVelocityCS;

    if (m_constraint) {
        const JPH::Vec3 radPerSec(qDegreesToRadians(m_targetAngularVelocityCS.x()),
                                  qDegreesToRadians(m_targetAngularVelocityCS.y()),
                                  qDegreesToRadians(m_targetAngularVelocityCS.z()));
        static_cast<JPH::SwingTwistConstraint *>(m_constraint)->SetTargetAngularVelocityCS(radPerSec);
    }

    emit targetAngularVelocityCSChanged(m_targetAngularVelocityCS);
}

QQuaternion SwingTwistConstraint::targetOrientationCS() const
{
    return m_targetOrientationCS;
}

void SwingTwistConstraint::setTargetOrientationCS(const QQuaternion &targetOrientationCS)
{
    if (m_targetOrientationCS == targetOrientationCS)
        return;

    m_targetOrientationCS = targetOrientationCS;

    if (m_constraint)
        static_cast<JPH::SwingTwistConstraint *>(m_constraint)->SetTargetOrientationCS(PhysicsUtils::toJoltType(m_targetOrientationCS));

    emit targetOrientationCSChanged(m_targetOrientationCS);
}

QQuaternion SwingTwistConstraint::getRotationInConstraintSpace() const
{
    if (m_constraint == nullptr)
        return QQuaternion();

    return PhysicsUtils::toQtType(static_cast<JPH::SwingTwistConstraint *>(m_constraint)->GetRotationInConstraintSpace());
}

void SwingTwistConstraint::setTargetOrientationBS(const QQuaternion &orientation)
{
    if (m_constraint == nullptr) {
        qWarning() << "Warning: Cannot call setTargetOrientationBS before constraint is initialized";
        return;
    }

    static_cast<JPH::SwingTwistConstraint *>(m_constraint)->SetTargetOrientationBS(PhysicsUtils::toJoltType(orientation));
}

QVector3D SwingTwistConstraint::getTotalLambdaPosition() const
{
    if (m_constraint == nullptr)
        return QVector3D();

    return PhysicsUtils::toQtType(static_cast<JPH::SwingTwistConstraint *>(m_constraint)->GetTotalLambdaPosition());
}

float SwingTwistConstraint::getTotalLambdaTwist() const
{
    if (m_constraint == nullptr)
        return 0.0f;

    return static_cast<JPH::SwingTwistConstraint *>(m_constraint)->GetTotalLambdaTwist();
}

float SwingTwistConstraint::getTotalLambdaSwingY() const
{
    if (m_constraint == nullptr)
        return 0.0f;

    return static_cast<JPH::SwingTwistConstraint *>(m_constraint)->GetTotalLambdaSwingY();
}

float SwingTwistConstraint::getTotalLambdaSwingZ() const
{
    if (m_constraint == nullptr)
        return 0.0f;

    return static_cast<JPH::SwingTwistConstraint *>(m_constraint)->GetTotalLambdaSwingZ();
}

QVector3D SwingTwistConstraint::getTotalLambdaMotor() const
{
    if (m_constraint == nullptr)
        return QVector3D();

    return PhysicsUtils::toQtType(static_cast<JPH::SwingTwistConstraint *>(m_constraint)->GetTotalLambdaMotor());
}

void SwingTwistConstraint::updateJoltObject()
{
    if (m_jolt == nullptr || m_body1 == nullptr || m_body2 == nullptr || m_constraint)
        return;

    m_constraintSettings.mPosition1 = PhysicsUtils::toJoltType(m_position1);
    m_constraintSettings.mPosition2 = PhysicsUtils::toJoltType(m_position2);
    m_constraintSettings.mTwistAxis1 = PhysicsUtils::toJoltType(m_twistAxis1);
    m_constraintSettings.mTwistAxis2 = PhysicsUtils::toJoltType(m_twistAxis2);
    m_constraintSettings.mPlaneAxis1 = PhysicsUtils::toJoltType(m_planeAxis1);
    m_constraintSettings.mPlaneAxis2 = PhysicsUtils::toJoltType(m_planeAxis2);
    m_constraintSettings.mNormalHalfConeAngle = qDegreesToRadians(m_normalHalfConeAngle);
    m_constraintSettings.mPlaneHalfConeAngle = qDegreesToRadians(m_planeHalfConeAngle);
    m_constraintSettings.mTwistMinAngle = qDegreesToRadians(m_twistMinAngle);
    m_constraintSettings.mTwistMaxAngle = qDegreesToRadians(m_twistMaxAngle);

    if (m_swingMotorSettings)
        m_constraintSettings.mSwingMotorSettings = m_swingMotorSettings->getJoltMotorSettings();
    if (m_twistMotorSettings)
        m_constraintSettings.mTwistMotorSettings = m_twistMotorSettings->getJoltMotorSettings();

    m_constraint = m_constraintSettings.Create(*m_body1->m_body, *m_body2->m_body);

    auto *st = static_cast<JPH::SwingTwistConstraint *>(m_constraint);

    if (m_swingMotorState != MotorState::Off)
        st->SetSwingMotorState(static_cast<JPH::EMotorState>(m_swingMotorState));
    if (m_twistMotorState != MotorState::Off)
        st->SetTwistMotorState(static_cast<JPH::EMotorState>(m_twistMotorState));

    if (m_swingMotorState == MotorState::Velocity || m_twistMotorState == MotorState::Velocity) {
        const JPH::Vec3 radPerSec(qDegreesToRadians(m_targetAngularVelocityCS.x()),
                                  qDegreesToRadians(m_targetAngularVelocityCS.y()),
                                  qDegreesToRadians(m_targetAngularVelocityCS.z()));
        st->SetTargetAngularVelocityCS(radPerSec);
    }

    if (m_swingMotorState == MotorState::Position || m_twistMotorState == MotorState::Position)
        st->SetTargetOrientationCS(PhysicsUtils::toJoltType(m_targetOrientationCS));

    m_jolt->AddConstraint(m_constraint);
}

JPH::Ref<JPH::TwoBodyConstraintSettings> SwingTwistConstraint::createJoltConstraintSettings() const
{
    auto *s = new JPH::SwingTwistConstraintSettings();
    s->mPosition1 = PhysicsUtils::toJoltType(m_position1);
    s->mPosition2 = PhysicsUtils::toJoltType(m_position2);
    s->mTwistAxis1 = PhysicsUtils::toJoltType(m_twistAxis1);
    s->mTwistAxis2 = PhysicsUtils::toJoltType(m_twistAxis2);
    s->mPlaneAxis1 = PhysicsUtils::toJoltType(m_planeAxis1);
    s->mPlaneAxis2 = PhysicsUtils::toJoltType(m_planeAxis2);
    s->mNormalHalfConeAngle = qDegreesToRadians(m_normalHalfConeAngle);
    s->mPlaneHalfConeAngle = qDegreesToRadians(m_planeHalfConeAngle);
    s->mTwistMinAngle = qDegreesToRadians(m_twistMinAngle);
    s->mTwistMaxAngle = qDegreesToRadians(m_twistMaxAngle);
    s->mMaxFrictionTorque = m_constraintSettings.mMaxFrictionTorque;

    if (m_swingMotorSettings)
        s->mSwingMotorSettings = m_swingMotorSettings->getJoltMotorSettings();
    if (m_twistMotorSettings)
        s->mTwistMotorSettings = m_twistMotorSettings->getJoltMotorSettings();

    return s;
}
