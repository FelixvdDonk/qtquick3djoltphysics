#include "sixdofconstraint_p.h"
#include "physicsutils_p.h"

#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Constraints/MotorSettings.h>

SixDOFConstraint::SixDOFConstraint(QQuick3DNode *parent) : AbstractPhysicsConstraint(parent)
{
}

SixDOFConstraint::~SixDOFConstraint() = default;

QVector3D SixDOFConstraint::position1() const
{
    return m_position1;
}

void SixDOFConstraint::setPosition1(const QVector3D &position)
{
    if (m_position1 == position)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'position1' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_position1 = position;
    emit position1Changed(m_position1);
}

QVector3D SixDOFConstraint::position2() const
{
    return m_position2;
}

void SixDOFConstraint::setPosition2(const QVector3D &position)
{
    if (m_position2 == position)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'position2' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_position2 = position;
    emit position2Changed(m_position2);
}

Body *SixDOFConstraint::body1() const
{
    return m_body1;
}

void SixDOFConstraint::setBody1(Body *body)
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

Body *SixDOFConstraint::body2() const
{
    return m_body2;
}

void SixDOFConstraint::setBody2(Body *body)
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

QVector3D SixDOFConstraint::axisX1() const
{
    return m_axisX1;
}

void SixDOFConstraint::setAxisX1(const QVector3D &axis)
{
    if (m_axisX1 == axis)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'axisX1' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_axisX1 = axis;
    emit axisX1Changed(m_axisX1);
}

QVector3D SixDOFConstraint::axisY1() const
{
    return m_axisY1;
}

void SixDOFConstraint::setAxisY1(const QVector3D &axis)
{
    if (m_axisY1 == axis)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'axisY1' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_axisY1 = axis;
    emit axisY1Changed(m_axisY1);
}

QVector3D SixDOFConstraint::axisX2() const
{
    return m_axisX2;
}

void SixDOFConstraint::setAxisX2(const QVector3D &axis)
{
    if (m_axisX2 == axis)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'axisX2' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_axisX2 = axis;
    emit axisX2Changed(m_axisX2);
}

QVector3D SixDOFConstraint::axisY2() const
{
    return m_axisY2;
}

void SixDOFConstraint::setAxisY2(const QVector3D &axis)
{
    if (m_axisY2 == axis)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'axisY2' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_axisY2 = axis;
    emit axisY2Changed(m_axisY2);
}

SixDOFConstraint::SwingType SixDOFConstraint::swingType() const
{
    return m_swingType;
}

void SixDOFConstraint::setSwingType(SwingType swingType)
{
    if (m_swingType == swingType)
        return;

    if (m_constraint) {
        qWarning() << "Warning: Changing 'swingType' after constraint is initialized will have "
                      "no effect";
        return;
    }

    m_swingType = swingType;
    emit swingTypeChanged(m_swingType);
}

QVector3D SixDOFConstraint::targetPositionCS() const
{
    return m_targetPositionCS;
}

void SixDOFConstraint::setTargetPositionCS(const QVector3D &targetPositionCS)
{
    if (m_targetPositionCS == targetPositionCS)
        return;

    m_targetPositionCS = targetPositionCS;

    if (m_constraint)
        static_cast<JPH::SixDOFConstraint *>(m_constraint)->SetTargetPositionCS(
            PhysicsUtils::toJoltType(m_targetPositionCS) / 100.0f);

    emit targetPositionCSChanged(m_targetPositionCS);
}

QQuaternion SixDOFConstraint::targetOrientationCS() const
{
    return m_targetOrientationCS;
}

void SixDOFConstraint::setTargetOrientationCS(const QQuaternion &targetOrientationCS)
{
    if (m_targetOrientationCS == targetOrientationCS)
        return;

    m_targetOrientationCS = targetOrientationCS;

    if (m_constraint)
        static_cast<JPH::SixDOFConstraint *>(m_constraint)->SetTargetOrientationCS(
            PhysicsUtils::toJoltType(m_targetOrientationCS));

    emit targetOrientationCSChanged(m_targetOrientationCS);
}

QVector3D SixDOFConstraint::targetVelocityCS() const
{
    return m_targetVelocityCS;
}

void SixDOFConstraint::setTargetVelocityCS(const QVector3D &targetVelocityCS)
{
    if (m_targetVelocityCS == targetVelocityCS)
        return;

    m_targetVelocityCS = targetVelocityCS;

    if (m_constraint)
        static_cast<JPH::SixDOFConstraint *>(m_constraint)->SetTargetVelocityCS(
            PhysicsUtils::toJoltType(m_targetVelocityCS) / 100.0f);

    emit targetVelocityCSChanged(m_targetVelocityCS);
}

QVector3D SixDOFConstraint::targetAngularVelocityCS() const
{
    return m_targetAngularVelocityCS;
}

void SixDOFConstraint::setTargetAngularVelocityCS(const QVector3D &targetAngularVelocityCS)
{
    if (m_targetAngularVelocityCS == targetAngularVelocityCS)
        return;

    m_targetAngularVelocityCS = targetAngularVelocityCS;

    if (m_constraint) {
        JPH::Vec3 radPerSec(qDegreesToRadians(m_targetAngularVelocityCS.x()),
                            qDegreesToRadians(m_targetAngularVelocityCS.y()),
                            qDegreesToRadians(m_targetAngularVelocityCS.z()));
        static_cast<JPH::SixDOFConstraint *>(m_constraint)->SetTargetAngularVelocityCS(radPerSec);
    }

    emit targetAngularVelocityCSChanged(m_targetAngularVelocityCS);
}

QQmlListProperty<MotorSettings> SixDOFConstraint::motorSettings()
{
    return QQmlListProperty<MotorSettings>(this, nullptr,
                                           &SixDOFConstraint::appendMotorSettings,
                                           &SixDOFConstraint::motorSettingsCount,
                                           &SixDOFConstraint::motorSettingsAt,
                                           &SixDOFConstraint::clearMotorSettings);
}

void SixDOFConstraint::appendMotorSettings(QQmlListProperty<MotorSettings> *list, MotorSettings *ms)
{
    auto *self = static_cast<SixDOFConstraint *>(list->object);
    if (self->m_motorSettingsList.size() >= 6) {
        qWarning() << "SixDOFConstraint: motorSettings list accepts exactly 6 elements (one per axis)";
        return;
    }
    const int index = self->m_motorSettingsList.size();
    self->m_motorSettingsList.append(ms);
    self->m_motorSettingsConnections.append(QMetaObject::Connection());
    self->connectMotorSettings(index, ms);
}

qsizetype SixDOFConstraint::motorSettingsCount(QQmlListProperty<MotorSettings> *list)
{
    return static_cast<SixDOFConstraint *>(list->object)->m_motorSettingsList.size();
}

MotorSettings *SixDOFConstraint::motorSettingsAt(QQmlListProperty<MotorSettings> *list, qsizetype index)
{
    return static_cast<SixDOFConstraint *>(list->object)->m_motorSettingsList.at(index);
}

void SixDOFConstraint::clearMotorSettings(QQmlListProperty<MotorSettings> *list)
{
    auto *self = static_cast<SixDOFConstraint *>(list->object);
    for (int i = 0; i < self->m_motorSettingsConnections.size(); ++i) {
        if (self->m_motorSettingsList[i])
            QObject::disconnect(self->m_motorSettingsConnections[i]);
    }
    self->m_motorSettingsList.clear();
    self->m_motorSettingsConnections.clear();
}

void SixDOFConstraint::connectMotorSettings(int index, MotorSettings *ms)
{
    m_motorSettingsConnections[index] = QObject::connect(ms, &MotorSettings::changed, this,
                    [this, index]
    {
        if (m_constraint != nullptr && index < m_motorSettingsList.size() && m_motorSettingsList[index]) {
            auto axis = static_cast<JPH::SixDOFConstraintSettings::EAxis>(index);
            static_cast<JPH::SixDOFConstraint *>(m_constraint)->GetMotorSettings(axis) =
                m_motorSettingsList[index]->getJoltMotorSettings();
        }
    });
    QObject::connect(ms, &QObject::destroyed, this,
                     [this, index](QObject *obj)
    {
        if (index < m_motorSettingsList.size() && m_motorSettingsList[index] == obj) {
            m_motorSettingsList[index] = nullptr;
        }
    });
}

void SixDOFConstraint::setAxisFree(Axis axis)
{
    const int idx = static_cast<int>(axis);
    if (idx < 0 || idx >= 6)
        return;

    if (m_constraint) {
        // Runtime: need to set limits to free range
        auto joltAxis = static_cast<JPH::SixDOFConstraintSettings::EAxis>(idx);
        if (idx < 3)
            static_cast<JPH::SixDOFConstraint *>(m_constraint)->SetTranslationLimits(
                JPH::Vec3::sReplicate(-FLT_MAX), JPH::Vec3::sReplicate(FLT_MAX));
        else
            static_cast<JPH::SixDOFConstraint *>(m_constraint)->SetRotationLimits(
                JPH::Vec3::sReplicate(-FLT_MAX), JPH::Vec3::sReplicate(FLT_MAX));
        return;
    }

    m_axisConfigs[idx].type = AxisConfig::Free;
    m_axisConfigs[idx].min = -FLT_MAX;
    m_axisConfigs[idx].max = FLT_MAX;
}

void SixDOFConstraint::setAxisFixed(Axis axis)
{
    const int idx = static_cast<int>(axis);
    if (idx < 0 || idx >= 6)
        return;

    if (m_constraint) {
        auto joltAxis = static_cast<JPH::SixDOFConstraintSettings::EAxis>(idx);
        if (idx < 3) {
            JPH::Vec3 limMin = static_cast<JPH::SixDOFConstraint *>(m_constraint)->GetTranslationLimitsMin();
            JPH::Vec3 limMax = static_cast<JPH::SixDOFConstraint *>(m_constraint)->GetTranslationLimitsMax();
            limMin.SetComponent(idx, FLT_MAX);
            limMax.SetComponent(idx, -FLT_MAX);
            static_cast<JPH::SixDOFConstraint *>(m_constraint)->SetTranslationLimits(limMin, limMax);
        } else {
            JPH::Vec3 limMin = static_cast<JPH::SixDOFConstraint *>(m_constraint)->GetRotationLimitsMin();
            JPH::Vec3 limMax = static_cast<JPH::SixDOFConstraint *>(m_constraint)->GetRotationLimitsMax();
            limMin.SetComponent(idx - 3, FLT_MAX);
            limMax.SetComponent(idx - 3, -FLT_MAX);
            static_cast<JPH::SixDOFConstraint *>(m_constraint)->SetRotationLimits(limMin, limMax);
        }
        return;
    }

    m_axisConfigs[idx].type = AxisConfig::Fixed;
    m_axisConfigs[idx].min = FLT_MAX;
    m_axisConfigs[idx].max = -FLT_MAX;
}

void SixDOFConstraint::setAxisLimits(Axis axis, float min, float max)
{
    const int idx = static_cast<int>(axis);
    if (idx < 0 || idx >= 6)
        return;

    // Convert: translation limits from cm to m, rotation limits from deg to rad
    float joltMin, joltMax;
    if (idx < 3) {
        joltMin = min / 100.0f;
        joltMax = max / 100.0f;
    } else {
        joltMin = qDegreesToRadians(min);
        joltMax = qDegreesToRadians(max);
    }

    if (m_constraint) {
        if (idx < 3) {
            JPH::Vec3 limMin = static_cast<JPH::SixDOFConstraint *>(m_constraint)->GetTranslationLimitsMin();
            JPH::Vec3 limMax = static_cast<JPH::SixDOFConstraint *>(m_constraint)->GetTranslationLimitsMax();
            limMin.SetComponent(idx, joltMin);
            limMax.SetComponent(idx, joltMax);
            static_cast<JPH::SixDOFConstraint *>(m_constraint)->SetTranslationLimits(limMin, limMax);
        } else {
            JPH::Vec3 limMin = static_cast<JPH::SixDOFConstraint *>(m_constraint)->GetRotationLimitsMin();
            JPH::Vec3 limMax = static_cast<JPH::SixDOFConstraint *>(m_constraint)->GetRotationLimitsMax();
            limMin.SetComponent(idx - 3, joltMin);
            limMax.SetComponent(idx - 3, joltMax);
            static_cast<JPH::SixDOFConstraint *>(m_constraint)->SetRotationLimits(limMin, limMax);
        }
        return;
    }

    m_axisConfigs[idx].type = AxisConfig::Limited;
    m_axisConfigs[idx].min = joltMin;
    m_axisConfigs[idx].max = joltMax;
}

void SixDOFConstraint::setMaxFriction(Axis axis, float value)
{
    const int idx = static_cast<int>(axis);
    if (idx < 0 || idx >= 6)
        return;

    m_maxFriction[idx] = value;

    if (m_constraint)
        static_cast<JPH::SixDOFConstraint *>(m_constraint)->SetMaxFriction(
            static_cast<JPH::SixDOFConstraintSettings::EAxis>(idx), value);
}

void SixDOFConstraint::setMotorState(Axis axis, MotorState state)
{
    const int idx = static_cast<int>(axis);
    if (idx < 0 || idx >= 6)
        return;

    m_motorStates[idx] = state;

    if (m_constraint)
        static_cast<JPH::SixDOFConstraint *>(m_constraint)->SetMotorState(
            static_cast<JPH::SixDOFConstraintSettings::EAxis>(idx),
            static_cast<JPH::EMotorState>(state));
}

void SixDOFConstraint::setTranslationLimits(const QVector3D &min, const QVector3D &max)
{
    if (m_constraint) {
        static_cast<JPH::SixDOFConstraint *>(m_constraint)->SetTranslationLimits(
            PhysicsUtils::toJoltType(min) / 100.0f,
            PhysicsUtils::toJoltType(max) / 100.0f);
    } else {
        for (int i = 0; i < 3; ++i) {
            m_axisConfigs[i].type = AxisConfig::Limited;
            m_axisConfigs[i].min = min[i] / 100.0f;
            m_axisConfigs[i].max = max[i] / 100.0f;
        }
    }
}

void SixDOFConstraint::setRotationLimits(const QVector3D &min, const QVector3D &max)
{
    if (m_constraint) {
        JPH::Vec3 joltMin(qDegreesToRadians(min.x()), qDegreesToRadians(min.y()), qDegreesToRadians(min.z()));
        JPH::Vec3 joltMax(qDegreesToRadians(max.x()), qDegreesToRadians(max.y()), qDegreesToRadians(max.z()));
        static_cast<JPH::SixDOFConstraint *>(m_constraint)->SetRotationLimits(joltMin, joltMax);
    } else {
        for (int i = 0; i < 3; ++i) {
            m_axisConfigs[3 + i].type = AxisConfig::Limited;
            m_axisConfigs[3 + i].min = qDegreesToRadians(min[i]);
            m_axisConfigs[3 + i].max = qDegreesToRadians(max[i]);
        }
    }
}

void SixDOFConstraint::setTargetOrientationBS(const QQuaternion &orientation)
{
    if (m_constraint == nullptr)
        return;

    static_cast<JPH::SixDOFConstraint *>(m_constraint)->SetTargetOrientationBS(
        PhysicsUtils::toJoltType(orientation));
}

QQuaternion SixDOFConstraint::getRotationInConstraintSpace() const
{
    if (m_constraint == nullptr)
        return QQuaternion();

    return PhysicsUtils::toQtType(
        static_cast<JPH::SixDOFConstraint *>(m_constraint)->GetRotationInConstraintSpace());
}

QVector3D SixDOFConstraint::getTotalLambdaPosition() const
{
    if (m_constraint == nullptr)
        return QVector3D();

    return PhysicsUtils::toQtType(
        static_cast<JPH::SixDOFConstraint *>(m_constraint)->GetTotalLambdaPosition());
}

QVector3D SixDOFConstraint::getTotalLambdaRotation() const
{
    if (m_constraint == nullptr)
        return QVector3D();

    return PhysicsUtils::toQtType(
        static_cast<JPH::SixDOFConstraint *>(m_constraint)->GetTotalLambdaRotation());
}

QVector3D SixDOFConstraint::getTotalLambdaMotorTranslation() const
{
    if (m_constraint == nullptr)
        return QVector3D();

    return PhysicsUtils::toQtType(
        static_cast<JPH::SixDOFConstraint *>(m_constraint)->GetTotalLambdaMotorTranslation());
}

QVector3D SixDOFConstraint::getTotalLambdaMotorRotation() const
{
    if (m_constraint == nullptr)
        return QVector3D();

    return PhysicsUtils::toQtType(
        static_cast<JPH::SixDOFConstraint *>(m_constraint)->GetTotalLambdaMotorRotation());
}

void SixDOFConstraint::updateJoltObject()
{
    if (m_jolt == nullptr || m_body1 == nullptr || m_body2 == nullptr || m_constraint)
        return;

    m_constraintSettings.mPosition1 = PhysicsUtils::toJoltType(m_position1);
    m_constraintSettings.mPosition2 = PhysicsUtils::toJoltType(m_position2);
    m_constraintSettings.mAxisX1 = PhysicsUtils::toJoltType(m_axisX1);
    m_constraintSettings.mAxisY1 = PhysicsUtils::toJoltType(m_axisY1);
    m_constraintSettings.mAxisX2 = PhysicsUtils::toJoltType(m_axisX2);
    m_constraintSettings.mAxisY2 = PhysicsUtils::toJoltType(m_axisY2);
    m_constraintSettings.mSwingType = static_cast<JPH::ESwingType>(m_swingType);

    // Apply axis configurations
    for (int i = 0; i < 6; ++i) {
        auto axis = static_cast<JPH::SixDOFConstraintSettings::EAxis>(i);
        switch (m_axisConfigs[i].type) {
        case AxisConfig::Free:
            m_constraintSettings.MakeFreeAxis(axis);
            break;
        case AxisConfig::Fixed:
            m_constraintSettings.MakeFixedAxis(axis);
            break;
        case AxisConfig::Limited:
            m_constraintSettings.SetLimitedAxis(axis, m_axisConfigs[i].min, m_axisConfigs[i].max);
            break;
        }
        m_constraintSettings.mMaxFriction[i] = m_maxFriction[i];
    }

    // Apply motor settings from the QML list
    for (int i = 0; i < m_motorSettingsList.size() && i < 6; ++i) {
        if (m_motorSettingsList[i])
            m_constraintSettings.mMotorSettings[i] = m_motorSettingsList[i]->getJoltMotorSettings();
    }

    m_constraint = m_constraintSettings.Create(*m_body1->m_body, *m_body2->m_body);

    auto *sixdof = static_cast<JPH::SixDOFConstraint *>(m_constraint);

    // Apply motor states
    for (int i = 0; i < 6; ++i) {
        if (m_motorStates[i] != MotorState::Off)
            sixdof->SetMotorState(static_cast<JPH::SixDOFConstraintSettings::EAxis>(i),
                                  static_cast<JPH::EMotorState>(m_motorStates[i]));
    }

    // Apply targets
    if (m_targetPositionCS != QVector3D())
        sixdof->SetTargetPositionCS(PhysicsUtils::toJoltType(m_targetPositionCS) / 100.0f);

    if (m_targetOrientationCS != QQuaternion())
        sixdof->SetTargetOrientationCS(PhysicsUtils::toJoltType(m_targetOrientationCS));

    if (m_targetVelocityCS != QVector3D())
        sixdof->SetTargetVelocityCS(PhysicsUtils::toJoltType(m_targetVelocityCS) / 100.0f);

    if (m_targetAngularVelocityCS != QVector3D()) {
        JPH::Vec3 radPerSec(qDegreesToRadians(m_targetAngularVelocityCS.x()),
                            qDegreesToRadians(m_targetAngularVelocityCS.y()),
                            qDegreesToRadians(m_targetAngularVelocityCS.z()));
        sixdof->SetTargetAngularVelocityCS(radPerSec);
    }

    m_jolt->AddConstraint(m_constraint);
}
