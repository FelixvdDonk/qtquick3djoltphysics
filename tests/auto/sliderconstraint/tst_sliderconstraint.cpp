#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/sliderconstraint_p.h>
#include <QtQuick3DJoltPhysics/private/motorsettings_p.h>

class tst_SliderConstraint : public QObject
{
    Q_OBJECT
private slots:
    void defaults();
    void axisProperties();
    void limitsProperties();
    void motorProperties();
    void targetProperties();
};

void tst_SliderConstraint::defaults()
{
    SliderConstraint sc;
    QCOMPARE(sc.point1(), QVector3D());
    QCOMPARE(sc.point2(), QVector3D());
    QCOMPARE(sc.sliderAxis1(), QVector3D(1, 0, 0));
    QCOMPARE(sc.sliderAxis2(), QVector3D(1, 0, 0));
    QCOMPARE(sc.normalAxis1(), QVector3D(0, 1, 0));
    QCOMPARE(sc.normalAxis2(), QVector3D(0, 1, 0));
    QCOMPARE(sc.limitsMin(), -FLT_MAX);
    QCOMPARE(sc.limitsMax(), FLT_MAX);
    QCOMPARE(sc.maxFrictionForce(), 0.0f);
    QCOMPARE(sc.motorSettings(), nullptr);
    QCOMPARE(sc.motorState(), SliderConstraint::MotorState::Off);
    QCOMPARE(sc.targetVelocity(), 0.0f);
    QCOMPARE(sc.targetPosition(), 0.0f);
}

void tst_SliderConstraint::axisProperties()
{
    SliderConstraint sc;
    QSignalSpy ax1Spy(&sc, &SliderConstraint::sliderAxis1Changed);
    QSignalSpy ax2Spy(&sc, &SliderConstraint::sliderAxis2Changed);

    sc.setSliderAxis1(QVector3D(0, 1, 0));
    QCOMPARE(sc.sliderAxis1(), QVector3D(0, 1, 0));
    QCOMPARE(ax1Spy.count(), 1);

    sc.setSliderAxis2(QVector3D(0, 0, 1));
    QCOMPARE(sc.sliderAxis2(), QVector3D(0, 0, 1));
    QCOMPARE(ax2Spy.count(), 1);
}

void tst_SliderConstraint::limitsProperties()
{
    SliderConstraint sc;
    QSignalSpy minSpy(&sc, &SliderConstraint::limitsMinChanged);
    QSignalSpy maxSpy(&sc, &SliderConstraint::limitsMaxChanged);

    // Limits are in cm
    sc.setLimitsMin(-100.0f);
    QCOMPARE(sc.limitsMin(), -100.0f);
    QCOMPARE(minSpy.count(), 1);

    sc.setLimitsMax(200.0f);
    QCOMPARE(sc.limitsMax(), 200.0f);
    QCOMPARE(maxSpy.count(), 1);
}

void tst_SliderConstraint::motorProperties()
{
    SliderConstraint sc;
    QSignalSpy msSpy(&sc, &SliderConstraint::motorSettingsChanged);
    QSignalSpy stateSpy(&sc, &SliderConstraint::motorStateChanged);

    auto *ms = new MotorSettings(&sc);
    ms->setMaxForceLimit(1000.0f);

    sc.setMotorSettings(ms);
    QCOMPARE(sc.motorSettings(), ms);
    QCOMPARE(msSpy.count(), 1);

    sc.setMotorState(SliderConstraint::MotorState::Position);
    QCOMPARE(sc.motorState(), SliderConstraint::MotorState::Position);
    QCOMPARE(stateSpy.count(), 1);

    sc.setMotorState(SliderConstraint::MotorState::Velocity);
    QCOMPARE(sc.motorState(), SliderConstraint::MotorState::Velocity);
    QCOMPARE(stateSpy.count(), 2);
}

void tst_SliderConstraint::targetProperties()
{
    SliderConstraint sc;
    QSignalSpy velSpy(&sc, &SliderConstraint::targetVelocityChanged);
    QSignalSpy posSpy(&sc, &SliderConstraint::targetPositionChanged);

    sc.setTargetVelocity(50.0f);
    QCOMPARE(sc.targetVelocity(), 50.0f);
    QCOMPARE(velSpy.count(), 1);

    sc.setTargetPosition(100.0f);
    QCOMPARE(sc.targetPosition(), 100.0f);
    QCOMPARE(posSpy.count(), 1);

    // No re-emit
    sc.setTargetPosition(100.0f);
    QCOMPARE(posSpy.count(), 1);
}

QTEST_GUILESS_MAIN(tst_SliderConstraint)
#include "tst_sliderconstraint.moc"
