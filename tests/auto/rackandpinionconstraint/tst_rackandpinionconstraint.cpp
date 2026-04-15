#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/rackandpinionconstraint_p.h>
#include <QtQuick3DJoltPhysics/private/hingeconstraint_p.h>
#include <QtQuick3DJoltPhysics/private/sliderconstraint_p.h>

class tst_RackAndPinionConstraint : public QObject
{
    Q_OBJECT
private slots:
    void defaults();
    void ratioProperty();
    void axisProperties();
    void constraintReferences();
};

void tst_RackAndPinionConstraint::defaults()
{
    RackAndPinionConstraint c;
    QCOMPARE(c.body1(), nullptr);
    QCOMPARE(c.body2(), nullptr);
    QCOMPARE(c.hingeAxis(), QVector3D(1, 0, 0));
    QCOMPARE(c.sliderAxis(), QVector3D(1, 0, 0));
    QCOMPARE(c.ratio(), 1.0f);
    QCOMPARE(c.pinionConstraint(), nullptr);
    QCOMPARE(c.rackConstraint(), nullptr);
}

void tst_RackAndPinionConstraint::ratioProperty()
{
    RackAndPinionConstraint c;
    QSignalSpy spy(&c, &RackAndPinionConstraint::ratioChanged);

    c.setRatio(3.14f);
    QCOMPARE(c.ratio(), 3.14f);
    QCOMPARE(spy.count(), 1);

    c.setRatio(3.14f);
    QCOMPARE(spy.count(), 1);
}

void tst_RackAndPinionConstraint::axisProperties()
{
    RackAndPinionConstraint c;
    QSignalSpy hingeSpy(&c, &RackAndPinionConstraint::hingeAxisChanged);
    QSignalSpy sliderSpy(&c, &RackAndPinionConstraint::sliderAxisChanged);

    c.setHingeAxis(QVector3D(0, 1, 0));
    QCOMPARE(c.hingeAxis(), QVector3D(0, 1, 0));
    QCOMPARE(hingeSpy.count(), 1);

    c.setSliderAxis(QVector3D(0, 0, 1));
    QCOMPARE(c.sliderAxis(), QVector3D(0, 0, 1));
    QCOMPARE(sliderSpy.count(), 1);
}

void tst_RackAndPinionConstraint::constraintReferences()
{
    RackAndPinionConstraint c;
    QSignalSpy pinionSpy(&c, &RackAndPinionConstraint::pinionConstraintChanged);
    QSignalSpy rackSpy(&c, &RackAndPinionConstraint::rackConstraintChanged);

    auto *hinge = new HingeConstraint;
    auto *slider = new SliderConstraint;

    c.setPinionConstraint(hinge);
    QCOMPARE(c.pinionConstraint(), hinge);
    QCOMPARE(pinionSpy.count(), 1);

    c.setRackConstraint(slider);
    QCOMPARE(c.rackConstraint(), slider);
    QCOMPARE(rackSpy.count(), 1);

    // Same pointer
    c.setPinionConstraint(hinge);
    QCOMPARE(pinionSpy.count(), 1);

    delete hinge;
    delete slider;
}

QTEST_GUILESS_MAIN(tst_RackAndPinionConstraint)
#include "tst_rackandpinionconstraint.moc"
