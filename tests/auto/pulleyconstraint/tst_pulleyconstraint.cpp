#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/pulleyconstraint_p.h>

class tst_PulleyConstraint : public QObject
{
    Q_OBJECT
private slots:
    void defaults();
    void pointProperties();
    void ratioProperty();
    void lengthProperties();
};

void tst_PulleyConstraint::defaults()
{
    PulleyConstraint c;
    QCOMPARE(c.body1(), nullptr);
    QCOMPARE(c.body2(), nullptr);
    QCOMPARE(c.bodyPoint1(), QVector3D());
    QCOMPARE(c.fixedPoint1(), QVector3D());
    QCOMPARE(c.bodyPoint2(), QVector3D());
    QCOMPARE(c.fixedPoint2(), QVector3D());
    QCOMPARE(c.ratio(), 1.0f);
    QCOMPARE(c.minLength(), 0.0f);
    QCOMPARE(c.maxLength(), -1.0f);
}

void tst_PulleyConstraint::pointProperties()
{
    PulleyConstraint c;
    QSignalSpy bp1Spy(&c, &PulleyConstraint::bodyPoint1Changed);
    QSignalSpy fp1Spy(&c, &PulleyConstraint::fixedPoint1Changed);
    QSignalSpy bp2Spy(&c, &PulleyConstraint::bodyPoint2Changed);
    QSignalSpy fp2Spy(&c, &PulleyConstraint::fixedPoint2Changed);

    c.setBodyPoint1(QVector3D(0, 10, 0));
    QCOMPARE(c.bodyPoint1(), QVector3D(0, 10, 0));
    QCOMPARE(bp1Spy.count(), 1);

    c.setFixedPoint1(QVector3D(0, 200, 0));
    QCOMPARE(c.fixedPoint1(), QVector3D(0, 200, 0));
    QCOMPARE(fp1Spy.count(), 1);

    c.setBodyPoint2(QVector3D(100, 10, 0));
    QCOMPARE(c.bodyPoint2(), QVector3D(100, 10, 0));
    QCOMPARE(bp2Spy.count(), 1);

    c.setFixedPoint2(QVector3D(100, 200, 0));
    QCOMPARE(c.fixedPoint2(), QVector3D(100, 200, 0));
    QCOMPARE(fp2Spy.count(), 1);
}

void tst_PulleyConstraint::ratioProperty()
{
    PulleyConstraint c;
    QSignalSpy spy(&c, &PulleyConstraint::ratioChanged);

    c.setRatio(2.0f);
    QCOMPARE(c.ratio(), 2.0f);
    QCOMPARE(spy.count(), 1);

    c.setRatio(2.0f);
    QCOMPARE(spy.count(), 1);
}

void tst_PulleyConstraint::lengthProperties()
{
    PulleyConstraint c;
    QSignalSpy minSpy(&c, &PulleyConstraint::minLengthChanged);
    QSignalSpy maxSpy(&c, &PulleyConstraint::maxLengthChanged);

    c.setMinLength(50.0f);
    QCOMPARE(c.minLength(), 50.0f);
    QCOMPARE(minSpy.count(), 1);

    c.setMaxLength(500.0f);
    QCOMPARE(c.maxLength(), 500.0f);
    QCOMPARE(maxSpy.count(), 1);

    // No re-emit
    c.setMinLength(50.0f);
    QCOMPARE(minSpy.count(), 1);
}

QTEST_GUILESS_MAIN(tst_PulleyConstraint)
#include "tst_pulleyconstraint.moc"
