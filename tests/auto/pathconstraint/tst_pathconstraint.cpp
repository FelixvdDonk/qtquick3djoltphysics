#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/pathconstraint_p.h>
#include <QtQuick3DJoltPhysics/private/hermitepath_p.h>
#include <QtQuick3DJoltPhysics/private/motorsettings_p.h>

class tst_PathConstraint : public QObject
{
    Q_OBJECT
private slots:
    void defaults();
    void pathProperty();
    void motorProperties();
    void rotationConstraintTypeProperty();
    void fractionProperties();
};

void tst_PathConstraint::defaults()
{
    PathConstraint c;
    QCOMPARE(c.body1(), nullptr);
    QCOMPARE(c.body2(), nullptr);
    QCOMPARE(c.path(), nullptr);
    QCOMPARE(c.pathPosition(), QVector3D());
    QCOMPARE(c.pathRotation(), QQuaternion());
    QCOMPARE(c.pathFraction(), 0.0f);
    QCOMPARE(c.maxFrictionForce(), 0.0f);
    QCOMPARE(c.positionMotorSettings(), nullptr);
    QCOMPARE(c.rotationConstraintType(), PathConstraint::RotationConstraintType::Free);
    QCOMPARE(c.positionMotorState(), PathConstraint::MotorState::Off);
    QCOMPARE(c.targetVelocity(), 0.0f);
    QCOMPARE(c.targetPathFraction(), 0.0f);
}

void tst_PathConstraint::pathProperty()
{
    PathConstraint c;
    QSignalSpy spy(&c, &PathConstraint::pathChanged);

    auto *hermite = new HermitePath(&c);
    c.setPath(hermite);
    QCOMPARE(c.path(), hermite);
    QCOMPARE(spy.count(), 1);

    // Same pointer
    c.setPath(hermite);
    QCOMPARE(spy.count(), 1);
}

void tst_PathConstraint::motorProperties()
{
    PathConstraint c;

    QSignalSpy msSpy(&c, &PathConstraint::positionMotorSettingsChanged);
    QSignalSpy stateSpy(&c, &PathConstraint::positionMotorStateChanged);
    QSignalSpy velSpy(&c, &PathConstraint::targetVelocityChanged);
    QSignalSpy fracSpy(&c, &PathConstraint::targetPathFractionChanged);

    auto *ms = new MotorSettings(&c);
    c.setPositionMotorSettings(ms);
    QCOMPARE(c.positionMotorSettings(), ms);
    QCOMPARE(msSpy.count(), 1);

    c.setPositionMotorState(PathConstraint::MotorState::Velocity);
    QCOMPARE(c.positionMotorState(), PathConstraint::MotorState::Velocity);
    QCOMPARE(stateSpy.count(), 1);

    c.setTargetVelocity(10.0f);
    QCOMPARE(c.targetVelocity(), 10.0f);
    QCOMPARE(velSpy.count(), 1);

    c.setTargetPathFraction(0.5f);
    QCOMPARE(c.targetPathFraction(), 0.5f);
    QCOMPARE(fracSpy.count(), 1);
}

void tst_PathConstraint::rotationConstraintTypeProperty()
{
    PathConstraint c;
    QSignalSpy spy(&c, &PathConstraint::rotationConstraintTypeChanged);

    c.setRotationConstraintType(PathConstraint::RotationConstraintType::ConstrainToPath);
    QCOMPARE(c.rotationConstraintType(), PathConstraint::RotationConstraintType::ConstrainToPath);
    QCOMPARE(spy.count(), 1);

    c.setRotationConstraintType(PathConstraint::RotationConstraintType::FullyConstrained);
    QCOMPARE(c.rotationConstraintType(), PathConstraint::RotationConstraintType::FullyConstrained);
    QCOMPARE(spy.count(), 2);

    // No re-emit
    c.setRotationConstraintType(PathConstraint::RotationConstraintType::FullyConstrained);
    QCOMPARE(spy.count(), 2);
}

void tst_PathConstraint::fractionProperties()
{
    PathConstraint c;
    QSignalSpy pathFracSpy(&c, &PathConstraint::pathFractionChanged);
    QSignalSpy posSpy(&c, &PathConstraint::pathPositionChanged);
    QSignalSpy rotSpy(&c, &PathConstraint::pathRotationChanged);
    QSignalSpy frictionSpy(&c, &PathConstraint::maxFrictionForceChanged);

    c.setPathFraction(0.75f);
    QCOMPARE(c.pathFraction(), 0.75f);
    QCOMPARE(pathFracSpy.count(), 1);

    c.setPathPosition(QVector3D(50, 0, 0));
    QCOMPARE(c.pathPosition(), QVector3D(50, 0, 0));
    QCOMPARE(posSpy.count(), 1);

    QQuaternion rot = QQuaternion::fromEulerAngles(0, 45, 0);
    c.setPathRotation(rot);
    QCOMPARE(c.pathRotation(), rot);
    QCOMPARE(rotSpy.count(), 1);

    c.setMaxFrictionForce(100.0f);
    QCOMPARE(c.maxFrictionForce(), 100.0f);
    QCOMPARE(frictionSpy.count(), 1);
}

QTEST_GUILESS_MAIN(tst_PathConstraint)
#include "tst_pathconstraint.moc"
