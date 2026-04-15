#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/swingtwistconstraint_p.h>
#include <QtQuick3DJoltPhysics/private/motorsettings_p.h>

class tst_SwingTwistConstraintMotor : public QObject
{
    Q_OBJECT
private slots:
    void defaults();
    void motorSettingsProperties();
    void motorStateProperties();
    void targetProperties();
    void angleProperties();
};

void tst_SwingTwistConstraintMotor::defaults()
{
    SwingTwistConstraint stc;
    QCOMPARE(stc.swingMotorSettings(), nullptr);
    QCOMPARE(stc.twistMotorSettings(), nullptr);
    QCOMPARE(stc.swingMotorState(), SwingTwistConstraint::MotorState::Off);
    QCOMPARE(stc.twistMotorState(), SwingTwistConstraint::MotorState::Off);
    QCOMPARE(stc.targetAngularVelocityCS(), QVector3D());
    QCOMPARE(stc.targetOrientationCS(), QQuaternion());
    QCOMPARE(stc.normalHalfConeAngle(), 0.0f);
    QCOMPARE(stc.planeHalfConeAngle(), 0.0f);
    QCOMPARE(stc.twistMinAngle(), 0.0f);
    QCOMPARE(stc.twistMaxAngle(), 0.0f);
    QCOMPARE(stc.swingType(), SwingTwistConstraint::SwingType::Cone);
}

void tst_SwingTwistConstraintMotor::motorSettingsProperties()
{
    SwingTwistConstraint stc;

    QSignalSpy swingSpy(&stc, &SwingTwistConstraint::swingMotorSettingsChanged);
    QSignalSpy twistSpy(&stc, &SwingTwistConstraint::twistMotorSettingsChanged);

    auto *swingMs = new MotorSettings(&stc);
    auto *twistMs = new MotorSettings(&stc);

    stc.setSwingMotorSettings(swingMs);
    QCOMPARE(stc.swingMotorSettings(), swingMs);
    QCOMPARE(swingSpy.count(), 1);

    stc.setTwistMotorSettings(twistMs);
    QCOMPARE(stc.twistMotorSettings(), twistMs);
    QCOMPARE(twistSpy.count(), 1);
}

void tst_SwingTwistConstraintMotor::motorStateProperties()
{
    SwingTwistConstraint stc;

    QSignalSpy swingSpy(&stc, &SwingTwistConstraint::swingMotorStateChanged);
    QSignalSpy twistSpy(&stc, &SwingTwistConstraint::twistMotorStateChanged);

    stc.setSwingMotorState(SwingTwistConstraint::MotorState::Position);
    QCOMPARE(stc.swingMotorState(), SwingTwistConstraint::MotorState::Position);
    QCOMPARE(swingSpy.count(), 1);

    stc.setTwistMotorState(SwingTwistConstraint::MotorState::Velocity);
    QCOMPARE(stc.twistMotorState(), SwingTwistConstraint::MotorState::Velocity);
    QCOMPARE(twistSpy.count(), 1);
}

void tst_SwingTwistConstraintMotor::targetProperties()
{
    SwingTwistConstraint stc;

    QSignalSpy angVelSpy(&stc, &SwingTwistConstraint::targetAngularVelocityCSChanged);
    QSignalSpy oriSpy(&stc, &SwingTwistConstraint::targetOrientationCSChanged);

    QVector3D vel(10, 20, 30);
    stc.setTargetAngularVelocityCS(vel);
    QCOMPARE(stc.targetAngularVelocityCS(), vel);
    QCOMPARE(angVelSpy.count(), 1);

    QQuaternion ori = QQuaternion::fromEulerAngles(30, 0, 0);
    stc.setTargetOrientationCS(ori);
    QCOMPARE(stc.targetOrientationCS(), ori);
    QCOMPARE(oriSpy.count(), 1);
}

void tst_SwingTwistConstraintMotor::angleProperties()
{
    SwingTwistConstraint stc;

    QSignalSpy normalSpy(&stc, &SwingTwistConstraint::normalHalfConeAngleChanged);
    QSignalSpy planeSpy(&stc, &SwingTwistConstraint::planeHalfConeAngleChanged);
    QSignalSpy twistMinSpy(&stc, &SwingTwistConstraint::twistMinAngleChanged);
    QSignalSpy twistMaxSpy(&stc, &SwingTwistConstraint::twistMaxAngleChanged);

    stc.setNormalHalfConeAngle(45.0f);
    QCOMPARE(stc.normalHalfConeAngle(), 45.0f);
    QCOMPARE(normalSpy.count(), 1);

    stc.setPlaneHalfConeAngle(30.0f);
    QCOMPARE(stc.planeHalfConeAngle(), 30.0f);
    QCOMPARE(planeSpy.count(), 1);

    stc.setTwistMinAngle(-45.0f);
    QCOMPARE(stc.twistMinAngle(), -45.0f);
    QCOMPARE(twistMinSpy.count(), 1);

    stc.setTwistMaxAngle(45.0f);
    QCOMPARE(stc.twistMaxAngle(), 45.0f);
    QCOMPARE(twistMaxSpy.count(), 1);
}

QTEST_GUILESS_MAIN(tst_SwingTwistConstraintMotor)
#include "tst_swingtwistconstraint_motor.moc"
