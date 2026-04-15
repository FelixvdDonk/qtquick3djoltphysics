#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/coneconstraint_p.h>

class tst_ConeConstraint : public QObject
{
    Q_OBJECT
private slots:
    void defaults();
    void properties();
};

void tst_ConeConstraint::defaults()
{
    ConeConstraint c;
    QCOMPARE(c.point1(), QVector3D());
    QCOMPARE(c.point2(), QVector3D());
    QCOMPARE(c.body1(), nullptr);
    QCOMPARE(c.body2(), nullptr);
    QCOMPARE(c.twistAxis1(), QVector3D(1, 0, 0));
    QCOMPARE(c.twistAxis2(), QVector3D(1, 0, 0));
    QCOMPARE(c.halfConeAngle(), 0.0f);
}

void tst_ConeConstraint::properties()
{
    ConeConstraint c;

    QSignalSpy pt1Spy(&c, &ConeConstraint::point1Changed);
    QSignalSpy pt2Spy(&c, &ConeConstraint::point2Changed);
    QSignalSpy ax1Spy(&c, &ConeConstraint::twistAxis1Changed);
    QSignalSpy ax2Spy(&c, &ConeConstraint::twistAxis2Changed);
    QSignalSpy angleSpy(&c, &ConeConstraint::halfConeAngleChanged);

    c.setPoint1(QVector3D(10, 0, 0));
    QCOMPARE(c.point1(), QVector3D(10, 0, 0));
    QCOMPARE(pt1Spy.count(), 1);

    c.setPoint2(QVector3D(20, 0, 0));
    QCOMPARE(c.point2(), QVector3D(20, 0, 0));
    QCOMPARE(pt2Spy.count(), 1);

    c.setTwistAxis1(QVector3D(0, 1, 0));
    QCOMPARE(c.twistAxis1(), QVector3D(0, 1, 0));
    QCOMPARE(ax1Spy.count(), 1);

    c.setTwistAxis2(QVector3D(0, 1, 0));
    QCOMPARE(c.twistAxis2(), QVector3D(0, 1, 0));
    QCOMPARE(ax2Spy.count(), 1);

    // halfConeAngle in degrees
    c.setHalfConeAngle(45.0f);
    QCOMPARE(c.halfConeAngle(), 45.0f);
    QCOMPARE(angleSpy.count(), 1);

    // No re-emit
    c.setHalfConeAngle(45.0f);
    QCOMPARE(angleSpy.count(), 1);
}

QTEST_GUILESS_MAIN(tst_ConeConstraint)
#include "tst_coneconstraint.moc"
