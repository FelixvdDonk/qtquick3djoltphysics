#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/sixdofconstraint_p.h>
#include <QtQuick3DJoltPhysics/private/motorsettings_p.h>

class tst_SixDOFConstraint : public QObject
{
    Q_OBJECT
private slots:
    void defaults();
    void axisProperties();
    void swingTypeProperty();
    void targetProperties();
    void motorSettingsListProperty();
    void axisConfigInvocables();
};

void tst_SixDOFConstraint::defaults()
{
    SixDOFConstraint c;
    QCOMPARE(c.position1(), QVector3D());
    QCOMPARE(c.position2(), QVector3D());
    QCOMPARE(c.axisX1(), QVector3D(1, 0, 0));
    QCOMPARE(c.axisY1(), QVector3D(0, 1, 0));
    QCOMPARE(c.axisX2(), QVector3D(1, 0, 0));
    QCOMPARE(c.axisY2(), QVector3D(0, 1, 0));
    QCOMPARE(c.swingType(), SixDOFConstraint::SwingType::Cone);
    QCOMPARE(c.targetPositionCS(), QVector3D());
    QCOMPARE(c.targetOrientationCS(), QQuaternion());
    QCOMPARE(c.targetVelocityCS(), QVector3D());
    QCOMPARE(c.targetAngularVelocityCS(), QVector3D());
}

void tst_SixDOFConstraint::axisProperties()
{
    SixDOFConstraint c;
    QSignalSpy x1Spy(&c, &SixDOFConstraint::axisX1Changed);
    QSignalSpy y1Spy(&c, &SixDOFConstraint::axisY1Changed);

    c.setAxisX1(QVector3D(0, 0, 1));
    QCOMPARE(c.axisX1(), QVector3D(0, 0, 1));
    QCOMPARE(x1Spy.count(), 1);

    c.setAxisY1(QVector3D(1, 0, 0));
    QCOMPARE(c.axisY1(), QVector3D(1, 0, 0));
    QCOMPARE(y1Spy.count(), 1);
}

void tst_SixDOFConstraint::swingTypeProperty()
{
    SixDOFConstraint c;
    QSignalSpy spy(&c, &SixDOFConstraint::swingTypeChanged);

    c.setSwingType(SixDOFConstraint::SwingType::Pyramid);
    QCOMPARE(c.swingType(), SixDOFConstraint::SwingType::Pyramid);
    QCOMPARE(spy.count(), 1);
}

void tst_SixDOFConstraint::targetProperties()
{
    SixDOFConstraint c;
    QSignalSpy posSpy(&c, &SixDOFConstraint::targetPositionCSChanged);
    QSignalSpy oriSpy(&c, &SixDOFConstraint::targetOrientationCSChanged);
    QSignalSpy velSpy(&c, &SixDOFConstraint::targetVelocityCSChanged);
    QSignalSpy angVelSpy(&c, &SixDOFConstraint::targetAngularVelocityCSChanged);

    c.setTargetPositionCS(QVector3D(10, 20, 30));
    QCOMPARE(c.targetPositionCS(), QVector3D(10, 20, 30));
    QCOMPARE(posSpy.count(), 1);

    QQuaternion ori = QQuaternion::fromEulerAngles(45, 0, 0);
    c.setTargetOrientationCS(ori);
    QCOMPARE(c.targetOrientationCS(), ori);
    QCOMPARE(oriSpy.count(), 1);

    c.setTargetVelocityCS(QVector3D(1, 2, 3));
    QCOMPARE(c.targetVelocityCS(), QVector3D(1, 2, 3));
    QCOMPARE(velSpy.count(), 1);

    c.setTargetAngularVelocityCS(QVector3D(5, 10, 15));
    QCOMPARE(c.targetAngularVelocityCS(), QVector3D(5, 10, 15));
    QCOMPARE(angVelSpy.count(), 1);
}

void tst_SixDOFConstraint::motorSettingsListProperty()
{
    SixDOFConstraint c;
    auto list = c.motorSettings();

    // Start empty
    QCOMPARE(list.count(&list), 0);

    // Add 6 motor settings, one per axis
    for (int i = 0; i < 6; ++i) {
        auto *ms = new MotorSettings(&c);
        ms->setMaxForceLimit(100.0f * (i + 1));
        list.append(&list, ms);
    }
    QCOMPARE(list.count(&list), 6);

    auto *ms0 = list.at(&list, 0);
    QVERIFY(ms0 != nullptr);
    QCOMPARE(ms0->maxForceLimit(), 100.0f);
}

void tst_SixDOFConstraint::axisConfigInvocables()
{
    SixDOFConstraint c;

    // These configure deferred axis state — no crash, values stored internally
    c.setAxisFree(SixDOFConstraint::Axis::TranslationX);
    c.setAxisFixed(SixDOFConstraint::Axis::TranslationY);
    c.setAxisLimits(SixDOFConstraint::Axis::TranslationZ, -50.0f, 50.0f);
    c.setAxisFree(SixDOFConstraint::Axis::RotationX);
    c.setAxisFixed(SixDOFConstraint::Axis::RotationY);
    c.setAxisLimits(SixDOFConstraint::Axis::RotationZ, -45.0f, 45.0f);
    c.setMaxFriction(SixDOFConstraint::Axis::TranslationX, 10.0f);
    c.setMotorState(SixDOFConstraint::Axis::RotationX, SixDOFConstraint::MotorState::Velocity);

    // Convenience
    c.setTranslationLimits(QVector3D(-100, -100, -100), QVector3D(100, 100, 100));
    c.setRotationLimits(QVector3D(-90, -90, -90), QVector3D(90, 90, 90));

    // All of the above should not crash — configuration is applied in updateJoltObject
}

QTEST_GUILESS_MAIN(tst_SixDOFConstraint)
#include "tst_sixdofconstraint.moc"
