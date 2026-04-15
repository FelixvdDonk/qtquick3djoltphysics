#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/physicssystem_p.h>

class tst_PhysicsSystemTimeStepping : public QObject
{
    Q_OBJECT
private slots:
    void defaultTimeSteppingProperties();
    void timeScaleProperty();
    void fixedTimestepProperty();
    void maxSubStepsProperty();
};

void tst_PhysicsSystemTimeStepping::defaultTimeSteppingProperties()
{
    PhysicsSystem sys;
    // Check that new time stepping properties have sane defaults
    QCOMPARE(sys.timeScale(), 1.0f);
    QCOMPARE(sys.fixedTimestep(), 0.0f);
    QCOMPARE(sys.maxSubSteps(), 8);
}

void tst_PhysicsSystemTimeStepping::timeScaleProperty()
{
    PhysicsSystem sys;
    QSignalSpy spy(&sys, &PhysicsSystem::timeScaleChanged);

    sys.setTimeScale(2.0f);
    QCOMPARE(sys.timeScale(), 2.0f);
    QCOMPARE(spy.count(), 1);

    sys.setTimeScale(0.5f);
    QCOMPARE(sys.timeScale(), 0.5f);
    QCOMPARE(spy.count(), 2);

    // Same value — no re-emit
    sys.setTimeScale(0.5f);
    QCOMPARE(spy.count(), 2);
}

void tst_PhysicsSystemTimeStepping::fixedTimestepProperty()
{
    PhysicsSystem sys;
    QSignalSpy spy(&sys, &PhysicsSystem::fixedTimestepChanged);

    sys.setFixedTimestep(0.001f);
    QCOMPARE(sys.fixedTimestep(), 0.001f);
    QCOMPARE(spy.count(), 1);

    sys.setFixedTimestep(0.033f);
    QCOMPARE(sys.fixedTimestep(), 0.033f);
    QCOMPARE(spy.count(), 2);
}

void tst_PhysicsSystemTimeStepping::maxSubStepsProperty()
{
    PhysicsSystem sys;
    QSignalSpy spy(&sys, &PhysicsSystem::maxSubStepsChanged);

    sys.setMaxSubSteps(10);
    QCOMPARE(sys.maxSubSteps(), 10);
    QCOMPARE(spy.count(), 1);

    sys.setMaxSubSteps(1);
    QCOMPARE(sys.maxSubSteps(), 1);
    QCOMPARE(spy.count(), 2);
}

QTEST_GUILESS_MAIN(tst_PhysicsSystemTimeStepping)
#include "tst_physicssystem_timestepping.moc"
