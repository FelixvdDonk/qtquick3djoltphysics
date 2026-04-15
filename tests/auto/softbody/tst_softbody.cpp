#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/softbody_p.h>
#include <QtQuick3DJoltPhysics/private/softbodysharedsettings_p.h>

class tst_SoftBody : public QObject
{
    Q_OBJECT
private slots:
    void defaults();
    void sharedSettingsProperty();
    void objectLayerProperty();
    void numIterationsProperty();
    void dampingAndVelocityProperties();
    void materialProperties();
    void pressureAndGravityProperties();
    void allowSleepingProperty();
};

void tst_SoftBody::defaults()
{
    SoftBody sb;
    QCOMPARE(sb.sharedSettings(), nullptr);
    QCOMPARE(sb.objectLayer(), 0u);
    QCOMPARE(sb.numIterations(), 5);
    QCOMPARE(sb.linearDamping(), 0.1f);
    QCOMPARE(sb.maxLinearVelocity(), 50000.0f);
    QCOMPARE(sb.restitution(), 0.0f);
    QCOMPARE(sb.friction(), 0.2f);
    QCOMPARE(sb.pressure(), 0.0f);
    QCOMPARE(sb.gravityFactor(), 1.0f);
    QCOMPARE(sb.allowSleeping(), true);
}

void tst_SoftBody::sharedSettingsProperty()
{
    SoftBody sb;
    QSignalSpy spy(&sb, &SoftBody::sharedSettingsChanged);

    auto *settings = new SoftBodySharedSettings(&sb);
    sb.setSharedSettings(settings);
    QCOMPARE(sb.sharedSettings(), settings);
    QCOMPARE(spy.count(), 1);

    sb.setSharedSettings(settings);
    QCOMPARE(spy.count(), 1);
}

void tst_SoftBody::objectLayerProperty()
{
    SoftBody sb;
    QSignalSpy spy(&sb, &SoftBody::objectLayerChanged);

    sb.setObjectLayer(3);
    QCOMPARE(sb.objectLayer(), 3u);
    QCOMPARE(spy.count(), 1);

    sb.setObjectLayer(3);
    QCOMPARE(spy.count(), 1);
}

void tst_SoftBody::numIterationsProperty()
{
    SoftBody sb;
    QSignalSpy spy(&sb, &SoftBody::numIterationsChanged);

    sb.setNumIterations(10);
    QCOMPARE(sb.numIterations(), 10);
    QCOMPARE(spy.count(), 1);
}

void tst_SoftBody::dampingAndVelocityProperties()
{
    SoftBody sb;
    QSignalSpy dampSpy(&sb, &SoftBody::linearDampingChanged);
    QSignalSpy velSpy(&sb, &SoftBody::maxLinearVelocityChanged);

    sb.setLinearDamping(0.5f);
    QCOMPARE(sb.linearDamping(), 0.5f);
    QCOMPARE(dampSpy.count(), 1);

    sb.setMaxLinearVelocity(100000.0f);
    QCOMPARE(sb.maxLinearVelocity(), 100000.0f);
    QCOMPARE(velSpy.count(), 1);
}

void tst_SoftBody::materialProperties()
{
    SoftBody sb;
    QSignalSpy restSpy(&sb, &SoftBody::restitutionChanged);
    QSignalSpy fricSpy(&sb, &SoftBody::frictionChanged);

    sb.setRestitution(0.5f);
    QCOMPARE(sb.restitution(), 0.5f);
    QCOMPARE(restSpy.count(), 1);

    sb.setFriction(0.8f);
    QCOMPARE(sb.friction(), 0.8f);
    QCOMPARE(fricSpy.count(), 1);
}

void tst_SoftBody::pressureAndGravityProperties()
{
    SoftBody sb;
    QSignalSpy presSpy(&sb, &SoftBody::pressureChanged);
    QSignalSpy gravSpy(&sb, &SoftBody::gravityFactorChanged);

    sb.setPressure(1.0f);
    QCOMPARE(sb.pressure(), 1.0f);
    QCOMPARE(presSpy.count(), 1);

    sb.setGravityFactor(0.5f);
    QCOMPARE(sb.gravityFactor(), 0.5f);
    QCOMPARE(gravSpy.count(), 1);
}

void tst_SoftBody::allowSleepingProperty()
{
    SoftBody sb;
    QSignalSpy spy(&sb, &SoftBody::allowSleepingChanged);

    sb.setAllowSleeping(false);
    QCOMPARE(sb.allowSleeping(), false);
    QCOMPARE(spy.count(), 1);

    sb.setAllowSleeping(false);
    QCOMPARE(spy.count(), 1);
}

QTEST_GUILESS_MAIN(tst_SoftBody)
#include "tst_softbody.moc"
