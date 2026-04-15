#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/motorsettings_p.h>

class tst_MotorSettings : public QObject
{
    Q_OBJECT
private slots:
    void defaults();
    void setGetProperties();
    void signalsEmitted();
    void changedSignalCoalescing();
};

void tst_MotorSettings::defaults()
{
    MotorSettings ms;
    QCOMPARE(ms.springMode(), MotorSettings::SpringMode::FrequencyAndDamping);
    QCOMPARE(ms.springFrequency(), 2.0f);
    QCOMPARE(ms.springStiffness(), 0.0f);
    QCOMPARE(ms.springDamping(), 1.0f);
    QCOMPARE(ms.minForceLimit(), -FLT_MAX);
    QCOMPARE(ms.maxForceLimit(), FLT_MAX);
    QCOMPARE(ms.minTorqueLimit(), -FLT_MAX);
    QCOMPARE(ms.maxTorqueLimit(), FLT_MAX);
}

void tst_MotorSettings::setGetProperties()
{
    MotorSettings ms;

    ms.setSpringMode(MotorSettings::SpringMode::StiffnessAndDamping);
    QCOMPARE(ms.springMode(), MotorSettings::SpringMode::StiffnessAndDamping);

    ms.setSpringFrequency(10.0f);
    QCOMPARE(ms.springFrequency(), 10.0f);

    ms.setSpringStiffness(5.0f);
    QCOMPARE(ms.springStiffness(), 5.0f);

    ms.setSpringDamping(0.5f);
    QCOMPARE(ms.springDamping(), 0.5f);

    ms.setMinForceLimit(-100.0f);
    QCOMPARE(ms.minForceLimit(), -100.0f);

    ms.setMaxForceLimit(200.0f);
    QCOMPARE(ms.maxForceLimit(), 200.0f);

    ms.setMinTorqueLimit(-50.0f);
    QCOMPARE(ms.minTorqueLimit(), -50.0f);

    ms.setMaxTorqueLimit(75.0f);
    QCOMPARE(ms.maxTorqueLimit(), 75.0f);
}

void tst_MotorSettings::signalsEmitted()
{
    MotorSettings ms;

    QSignalSpy freqSpy(&ms, &MotorSettings::springFrequencyChanged);
    QSignalSpy dampSpy(&ms, &MotorSettings::springDampingChanged);
    QSignalSpy modeSpy(&ms, &MotorSettings::springModeChanged);
    QSignalSpy stiffSpy(&ms, &MotorSettings::springStiffnessChanged);
    QSignalSpy minFSpy(&ms, &MotorSettings::minForceLimitChanged);
    QSignalSpy maxFSpy(&ms, &MotorSettings::maxForceLimitChanged);
    QSignalSpy minTSpy(&ms, &MotorSettings::minTorqueLimitChanged);
    QSignalSpy maxTSpy(&ms, &MotorSettings::maxTorqueLimitChanged);

    ms.setSpringFrequency(20.0f);
    ms.setSpringDamping(3.0f);
    ms.setSpringMode(MotorSettings::SpringMode::StiffnessAndDamping);
    ms.setSpringStiffness(10.0f);
    ms.setMinForceLimit(-1.0f);
    ms.setMaxForceLimit(1.0f);
    ms.setMinTorqueLimit(-2.0f);
    ms.setMaxTorqueLimit(2.0f);

    QCOMPARE(freqSpy.count(), 1);
    QCOMPARE(dampSpy.count(), 1);
    QCOMPARE(modeSpy.count(), 1);
    QCOMPARE(stiffSpy.count(), 1);
    QCOMPARE(minFSpy.count(), 1);
    QCOMPARE(maxFSpy.count(), 1);
    QCOMPARE(minTSpy.count(), 1);
    QCOMPARE(maxTSpy.count(), 1);

    // Setting same value should NOT re-emit
    ms.setSpringFrequency(20.0f);
    QCOMPARE(freqSpy.count(), 1);
}

void tst_MotorSettings::changedSignalCoalescing()
{
    MotorSettings ms;
    QSignalSpy changedSpy(&ms, &MotorSettings::changed);

    // Multiple property changes should each emit changed()
    ms.setSpringFrequency(10.0f);
    ms.setSpringDamping(2.0f);
    ms.setMaxForceLimit(100.0f);

    QVERIFY(changedSpy.count() >= 1);
}

QTEST_GUILESS_MAIN(tst_MotorSettings)
#include "tst_motorsettings.moc"
