#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/skeletonjoint_p.h>

class tst_SkeletonJoint : public QObject
{
    Q_OBJECT
private slots:
    void defaults();
    void setGetProperties();
    void signalEmission_data();
    void signalEmission();
};

void tst_SkeletonJoint::defaults()
{
    SkeletonJoint joint;
    QVERIFY(joint.name().isEmpty());
    QVERIFY(joint.parentName().isEmpty());
}

void tst_SkeletonJoint::setGetProperties()
{
    SkeletonJoint joint;

    joint.setName(QStringLiteral("spine"));
    QCOMPARE(joint.name(), QStringLiteral("spine"));

    joint.setParentName(QStringLiteral("pelvis"));
    QCOMPARE(joint.parentName(), QStringLiteral("pelvis"));
}

void tst_SkeletonJoint::signalEmission_data()
{
    QTest::addColumn<QString>("property");
    QTest::addColumn<QString>("value");

    QTest::newRow("name") << "name" << "hip";
    QTest::newRow("parentName") << "parentName" << "root";
}

void tst_SkeletonJoint::signalEmission()
{
    QFETCH(QString, property);
    QFETCH(QString, value);

    SkeletonJoint joint;
    QSignalSpy changedSpy(&joint, &SkeletonJoint::changed);

    if (property == "name") {
        QSignalSpy spy(&joint, &SkeletonJoint::nameChanged);
        joint.setName(value);
        QCOMPARE(spy.count(), 1);
        // Set same value — should not re-emit
        joint.setName(value);
        QCOMPARE(spy.count(), 1);
    } else {
        QSignalSpy spy(&joint, &SkeletonJoint::parentNameChanged);
        joint.setParentName(value);
        QCOMPARE(spy.count(), 1);
        joint.setParentName(value);
        QCOMPARE(spy.count(), 1);
    }
    QVERIFY(changedSpy.count() >= 1);
}

QTEST_GUILESS_MAIN(tst_SkeletonJoint)
#include "tst_skeletonjoint.moc"
