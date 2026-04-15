#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/hingeconstraint_p.h>
#include <QtQuick3DJoltPhysics/private/motorsettings_p.h>
#include <QtQuick3DJoltPhysics/private/body_p.h>
#include <QtQuick3DJoltPhysics/private/boxshape_p.h>

class tst_HingeConstraintMotor : public QObject
{
    Q_OBJECT
private slots:
    void defaults();
    void motorSettingsProperty();
    void motorStateProperty();
    void targetProperties();
};

void tst_HingeConstraintMotor::defaults()
{
    HingeConstraint hc;

    QCOMPARE(hc.motorSettings(), nullptr);
    QCOMPARE(hc.motorState(), HingeConstraint::MotorState::Off);
    QCOMPARE(hc.targetAngularVelocity(), 0.0f);
    QCOMPARE(hc.targetAngle(), 0.0f);
    QCOMPARE(hc.limitsMin(), -180.0f);
    QCOMPARE(hc.limitsMax(), 180.0f);
    QCOMPARE(hc.maxFrictionTorque(), 0.0f);
    QCOMPARE(hc.hingeAxis1(), QVector3D(0, 1, 0));
    QCOMPARE(hc.hingeAxis2(), QVector3D(0, 1, 0));
}

void tst_HingeConstraintMotor::motorSettingsProperty()
{
    HingeConstraint hc;
    QSignalSpy spy(&hc, &HingeConstraint::motorSettingsChanged);

    auto *ms = new MotorSettings(&hc);
    ms->setMaxForceLimit(500.0f);
    ms->setMaxTorqueLimit(100.0f);

    hc.setMotorSettings(ms);
    QCOMPARE(hc.motorSettings(), ms);
    QCOMPARE(spy.count(), 1);

    // Setting same pointer — no re-emit
    hc.setMotorSettings(ms);
    QCOMPARE(spy.count(), 1);
}

void tst_HingeConstraintMotor::motorStateProperty()
{
    HingeConstraint hc;
    QSignalSpy spy(&hc, &HingeConstraint::motorStateChanged);

    hc.setMotorState(HingeConstraint::MotorState::Position);
    QCOMPARE(hc.motorState(), HingeConstraint::MotorState::Position);
    QCOMPARE(spy.count(), 1);

    hc.setMotorState(HingeConstraint::MotorState::Velocity);
    QCOMPARE(hc.motorState(), HingeConstraint::MotorState::Velocity);
    QCOMPARE(spy.count(), 2);

    hc.setMotorState(HingeConstraint::MotorState::Off);
    QCOMPARE(hc.motorState(), HingeConstraint::MotorState::Off);
    QCOMPARE(spy.count(), 3);
}

void tst_HingeConstraintMotor::targetProperties()
{
    HingeConstraint hc;
    QSignalSpy angleSpy(&hc, &HingeConstraint::targetAngleChanged);
    QSignalSpy velSpy(&hc, &HingeConstraint::targetAngularVelocityChanged);

    hc.setTargetAngle(45.0f);
    QCOMPARE(hc.targetAngle(), 45.0f);
    QCOMPARE(angleSpy.count(), 1);

    hc.setTargetAngularVelocity(90.0f);
    QCOMPARE(hc.targetAngularVelocity(), 90.0f);
    QCOMPARE(velSpy.count(), 1);

    // No re-emit on same value
    hc.setTargetAngle(45.0f);
    QCOMPARE(angleSpy.count(), 1);
}

QTEST_GUILESS_MAIN(tst_HingeConstraintMotor)
#include "tst_hingeconstraint_motor.moc"
