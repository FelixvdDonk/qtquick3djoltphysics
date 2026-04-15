#ifndef SIXDOFCONSTRAINT_P_H
#define SIXDOFCONSTRAINT_P_H

#include "abstractphysicsconstraint_p.h"
#include "body_p.h"
#include "motorsettings_p.h"

#include <QtQuick3DJoltPhysics/qtquick3djoltphysicsglobal.h>
#include <QtQuick3D/private/qquick3dnode_p.h>
#include <QtQml/QQmlEngine>

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Constraints/SixDOFConstraint.h>

#include <QVector3D>
#include <QQuaternion>
#include <QQmlListProperty>

class Q_QUICK3DJOLTPHYSICS_EXPORT SixDOFConstraint : public AbstractPhysicsConstraint
{
    Q_OBJECT
    Q_PROPERTY(QVector3D position1 READ position1 WRITE setPosition1 NOTIFY position1Changed)
    Q_PROPERTY(QVector3D position2 READ position2 WRITE setPosition2 NOTIFY position2Changed)
    Q_PROPERTY(Body *body1 READ body1 WRITE setBody1 NOTIFY body1Changed)
    Q_PROPERTY(Body *body2 READ body2 WRITE setBody2 NOTIFY body2Changed)
    Q_PROPERTY(QVector3D axisX1 READ axisX1 WRITE setAxisX1 NOTIFY axisX1Changed)
    Q_PROPERTY(QVector3D axisY1 READ axisY1 WRITE setAxisY1 NOTIFY axisY1Changed)
    Q_PROPERTY(QVector3D axisX2 READ axisX2 WRITE setAxisX2 NOTIFY axisX2Changed)
    Q_PROPERTY(QVector3D axisY2 READ axisY2 WRITE setAxisY2 NOTIFY axisY2Changed)
    Q_PROPERTY(SwingType swingType READ swingType WRITE setSwingType NOTIFY swingTypeChanged)
    Q_PROPERTY(QVector3D targetPositionCS READ targetPositionCS WRITE setTargetPositionCS NOTIFY targetPositionCSChanged)
    Q_PROPERTY(QQuaternion targetOrientationCS READ targetOrientationCS WRITE setTargetOrientationCS NOTIFY targetOrientationCSChanged)
    Q_PROPERTY(QVector3D targetVelocityCS READ targetVelocityCS WRITE setTargetVelocityCS NOTIFY targetVelocityCSChanged)
    Q_PROPERTY(QVector3D targetAngularVelocityCS READ targetAngularVelocityCS WRITE setTargetAngularVelocityCS NOTIFY targetAngularVelocityCSChanged)
    Q_PROPERTY(QQmlListProperty<MotorSettings> motorSettings READ motorSettings CONSTANT)
    QML_NAMED_ELEMENT(SixDOFConstraint)
public:
    explicit SixDOFConstraint(QQuick3DNode *parent = nullptr);
    ~SixDOFConstraint() override;

    enum class Axis {
        TranslationX,
        TranslationY,
        TranslationZ,
        RotationX,
        RotationY,
        RotationZ,
        Num,
    };
    Q_ENUM(Axis)

    enum class MotorState {
        Off,
        Velocity,
        Position,
    };
    Q_ENUM(MotorState)

    enum class SwingType {
        Cone,
        Pyramid,
    };
    Q_ENUM(SwingType)

    QVector3D position1() const;
    void setPosition1(const QVector3D &position);

    QVector3D position2() const;
    void setPosition2(const QVector3D &position);

    Body *body1() const;
    void setBody1(Body *body);

    Body *body2() const;
    void setBody2(Body *body);

    QVector3D axisX1() const;
    void setAxisX1(const QVector3D &axis);

    QVector3D axisY1() const;
    void setAxisY1(const QVector3D &axis);

    QVector3D axisX2() const;
    void setAxisX2(const QVector3D &axis);

    QVector3D axisY2() const;
    void setAxisY2(const QVector3D &axis);

    SwingType swingType() const;
    void setSwingType(SwingType swingType);

    QVector3D targetPositionCS() const;
    void setTargetPositionCS(const QVector3D &targetPositionCS);

    QQuaternion targetOrientationCS() const;
    void setTargetOrientationCS(const QQuaternion &targetOrientationCS);

    QVector3D targetVelocityCS() const;
    void setTargetVelocityCS(const QVector3D &targetVelocityCS);

    QVector3D targetAngularVelocityCS() const;
    void setTargetAngularVelocityCS(const QVector3D &targetAngularVelocityCS);

    QQmlListProperty<MotorSettings> motorSettings();

    Q_INVOKABLE void setAxisFree(Axis axis);
    Q_INVOKABLE void setAxisFixed(Axis axis);
    Q_INVOKABLE void setAxisLimits(Axis axis, float min, float max);
    Q_INVOKABLE void setMaxFriction(Axis axis, float value);
    Q_INVOKABLE void setMotorState(Axis axis, MotorState state);
    Q_INVOKABLE void setTranslationLimits(const QVector3D &min, const QVector3D &max);
    Q_INVOKABLE void setRotationLimits(const QVector3D &min, const QVector3D &max);
    Q_INVOKABLE void setTargetOrientationBS(const QQuaternion &orientation);

    Q_INVOKABLE QQuaternion getRotationInConstraintSpace() const;
    Q_INVOKABLE QVector3D getTotalLambdaPosition() const;
    Q_INVOKABLE QVector3D getTotalLambdaRotation() const;
    Q_INVOKABLE QVector3D getTotalLambdaMotorTranslation() const;
    Q_INVOKABLE QVector3D getTotalLambdaMotorRotation() const;

signals:
    void position1Changed(const QVector3D &position);
    void position2Changed(const QVector3D &position);
    void body1Changed(Body *body1);
    void body2Changed(Body *body2);
    void axisX1Changed(const QVector3D &axis);
    void axisY1Changed(const QVector3D &axis);
    void axisX2Changed(const QVector3D &axis);
    void axisY2Changed(const QVector3D &axis);
    void swingTypeChanged(SwingType swingType);
    void targetPositionCSChanged(const QVector3D &targetPositionCS);
    void targetOrientationCSChanged(const QQuaternion &targetOrientationCS);
    void targetVelocityCSChanged(const QVector3D &targetVelocityCS);
    void targetAngularVelocityCSChanged(const QVector3D &targetAngularVelocityCS);

protected:
    void updateJoltObject() override;

private:
    static void appendMotorSettings(QQmlListProperty<MotorSettings> *list, MotorSettings *ms);
    static qsizetype motorSettingsCount(QQmlListProperty<MotorSettings> *list);
    static MotorSettings *motorSettingsAt(QQmlListProperty<MotorSettings> *list, qsizetype index);
    static void clearMotorSettings(QQmlListProperty<MotorSettings> *list);

    void connectMotorSettings(int index, MotorSettings *ms);

    QVector3D m_position1;
    QVector3D m_position2;
    Body *m_body1 = nullptr;
    Body *m_body2 = nullptr;
    QVector3D m_axisX1 = QVector3D(1, 0, 0);
    QVector3D m_axisY1 = QVector3D(0, 1, 0);
    QVector3D m_axisX2 = QVector3D(1, 0, 0);
    QVector3D m_axisY2 = QVector3D(0, 1, 0);
    SwingType m_swingType = SwingType::Cone;
    QVector3D m_targetPositionCS;
    QQuaternion m_targetOrientationCS;
    QVector3D m_targetVelocityCS;
    QVector3D m_targetAngularVelocityCS;

    QList<MotorSettings *> m_motorSettingsList;
    QList<QMetaObject::Connection> m_motorSettingsConnections;

    // Deferred axis configuration (applied in updateJoltObject)
    struct AxisConfig {
        enum Type { Free, Fixed, Limited };
        Type type = Free;
        float min = -FLT_MAX;
        float max = FLT_MAX;
    };
    AxisConfig m_axisConfigs[6];
    float m_maxFriction[6] = { 0, 0, 0, 0, 0, 0 };
    MotorState m_motorStates[6] = { MotorState::Off, MotorState::Off, MotorState::Off, MotorState::Off, MotorState::Off, MotorState::Off };

    JPH::SixDOFConstraintSettings m_constraintSettings;
};

#endif // SIXDOFCONSTRAINT_P_H
