#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/ragdollpart_p.h>
#include <QtQuick3DJoltPhysics/private/boxshape_p.h>
#include <QtQuick3DJoltPhysics/private/hingeconstraint_p.h>

class tst_RagdollPart : public QObject
{
    Q_OBJECT
private slots:
    void defaults();
    void setGetProperties();
    void signalsEmitted();
};

void tst_RagdollPart::defaults()
{
    RagdollPart part;
    QVERIFY(part.jointName().isEmpty());
    QVERIFY(part.shape() == nullptr);
    QCOMPARE(part.motionType(), Body::MotionType::Dynamic);
    QCOMPARE(part.mass(), 1.0f);
    QCOMPARE(part.objectLayer(), 0);
    QVERIFY(part.constraintToParent() == nullptr);
    QCOMPARE(part.position(), QVector3D());
    QCOMPARE(part.rotation(), QQuaternion());
}

void tst_RagdollPart::setGetProperties()
{
    RagdollPart part;

    part.setJointName(QStringLiteral("torso"));
    QCOMPARE(part.jointName(), QStringLiteral("torso"));

    auto *box = new BoxShape;
    part.setShape(box);
    QCOMPARE(part.shape(), box);

    part.setMotionType(Body::MotionType::Kinematic);
    QCOMPARE(part.motionType(), Body::MotionType::Kinematic);

    part.setMass(5.0f);
    QCOMPARE(part.mass(), 5.0f);

    part.setObjectLayer(2);
    QCOMPARE(part.objectLayer(), 2);

    auto *hinge = new HingeConstraint;
    part.setConstraintToParent(hinge);
    QCOMPARE(part.constraintToParent(), hinge);

    QVector3D pos(10, 20, 30);
    part.setPosition(pos);
    QCOMPARE(part.position(), pos);

    QQuaternion rot = QQuaternion::fromEulerAngles(45, 0, 0);
    part.setRotation(rot);
    QCOMPARE(part.rotation(), rot);

    delete hinge;
    delete box;
}

void tst_RagdollPart::signalsEmitted()
{
    RagdollPart part;

    QSignalSpy jointNameSpy(&part, &RagdollPart::jointNameChanged);
    QSignalSpy massSpy(&part, &RagdollPart::massChanged);
    QSignalSpy layerSpy(&part, &RagdollPart::objectLayerChanged);
    QSignalSpy posSpy(&part, &RagdollPart::positionChanged);
    QSignalSpy rotSpy(&part, &RagdollPart::rotationChanged);

    part.setJointName(QStringLiteral("head"));
    part.setMass(2.0f);
    part.setObjectLayer(1);
    part.setPosition(QVector3D(1, 2, 3));
    part.setRotation(QQuaternion::fromEulerAngles(0, 90, 0));

    QCOMPARE(jointNameSpy.count(), 1);
    QCOMPARE(massSpy.count(), 1);
    QCOMPARE(layerSpy.count(), 1);
    QCOMPARE(posSpy.count(), 1);
    QCOMPARE(rotSpy.count(), 1);

    // Setting same value — no re-emit
    part.setMass(2.0f);
    QCOMPARE(massSpy.count(), 1);
}

QTEST_GUILESS_MAIN(tst_RagdollPart)
#include "tst_ragdollpart.moc"
