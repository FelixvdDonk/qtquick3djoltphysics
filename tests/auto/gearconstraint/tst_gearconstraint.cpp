#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/gearconstraint_p.h>
#include <QtQuick3DJoltPhysics/private/hingeconstraint_p.h>

class tst_GearConstraint : public QObject
{
    Q_OBJECT
private slots:
    void defaults();
    void ratioProperty();
    void constraintReferences();
    void axisProperties();
};

void tst_GearConstraint::defaults()
{
    GearConstraint gc;
    QCOMPARE(gc.body1(), nullptr);
    QCOMPARE(gc.body2(), nullptr);
    QCOMPARE(gc.hingeAxis1(), QVector3D(1, 0, 0));
    QCOMPARE(gc.hingeAxis2(), QVector3D(1, 0, 0));
    QCOMPARE(gc.ratio(), 1.0f);
    QCOMPARE(gc.gear1Constraint(), nullptr);
    QCOMPARE(gc.gear2Constraint(), nullptr);
}

void tst_GearConstraint::ratioProperty()
{
    GearConstraint gc;
    QSignalSpy spy(&gc, &GearConstraint::ratioChanged);

    gc.setRatio(2.0f);
    QCOMPARE(gc.ratio(), 2.0f);
    QCOMPARE(spy.count(), 1);

    gc.setRatio(0.5f);
    QCOMPARE(gc.ratio(), 0.5f);
    QCOMPARE(spy.count(), 2);

    // No re-emit
    gc.setRatio(0.5f);
    QCOMPARE(spy.count(), 2);
}

void tst_GearConstraint::constraintReferences()
{
    GearConstraint gc;
    QSignalSpy g1Spy(&gc, &GearConstraint::gear1ConstraintChanged);
    QSignalSpy g2Spy(&gc, &GearConstraint::gear2ConstraintChanged);

    auto *hinge1 = new HingeConstraint;
    auto *hinge2 = new HingeConstraint;

    gc.setGear1Constraint(hinge1);
    QCOMPARE(gc.gear1Constraint(), hinge1);
    QCOMPARE(g1Spy.count(), 1);

    gc.setGear2Constraint(hinge2);
    QCOMPARE(gc.gear2Constraint(), hinge2);
    QCOMPARE(g2Spy.count(), 1);

    // Same pointer
    gc.setGear1Constraint(hinge1);
    QCOMPARE(g1Spy.count(), 1);

    delete hinge1;
    delete hinge2;
}

void tst_GearConstraint::axisProperties()
{
    GearConstraint gc;
    QSignalSpy ax1Spy(&gc, &GearConstraint::hingeAxis1Changed);
    QSignalSpy ax2Spy(&gc, &GearConstraint::hingeAxis2Changed);

    gc.setHingeAxis1(QVector3D(0, 1, 0));
    QCOMPARE(gc.hingeAxis1(), QVector3D(0, 1, 0));
    QCOMPARE(ax1Spy.count(), 1);

    gc.setHingeAxis2(QVector3D(0, 0, 1));
    QCOMPARE(gc.hingeAxis2(), QVector3D(0, 0, 1));
    QCOMPARE(ax2Spy.count(), 1);
}

QTEST_GUILESS_MAIN(tst_GearConstraint)
#include "tst_gearconstraint.moc"
