#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/ragdoll_p.h>
#include <QtQuick3DJoltPhysics/private/physicsskeleton_p.h>
#include <QtQuick3DJoltPhysics/private/skeletonjoint_p.h>
#include <QtQuick3DJoltPhysics/private/ragdollpart_p.h>
#include <QtQuick3DJoltPhysics/private/boxshape_p.h>
#include <QtQuick3DJoltPhysics/private/capsuleshape_p.h>
#include <QtQuick3DJoltPhysics/private/fixedconstraint_p.h>

class tst_Ragdoll : public QObject
{
    Q_OBJECT
private slots:
    void defaults();
    void skeletonProperty();
    void partsListProperty();
    void collisionGroupIdProperty();
    void autoDisableProperty();
};

void tst_Ragdoll::defaults()
{
    Ragdoll ragdoll;
    QCOMPARE(ragdoll.skeleton(), nullptr);
    QCOMPARE(ragdoll.collisionGroupId(), 0);
    QCOMPARE(ragdoll.autoDisableParentChildCollisions(), true);

    auto list = ragdoll.parts();
    QCOMPARE(list.count(&list), 0);
}

void tst_Ragdoll::skeletonProperty()
{
    Ragdoll ragdoll;
    QSignalSpy spy(&ragdoll, &Ragdoll::skeletonChanged);

    auto *skel = new PhysicsSkeleton(&ragdoll);
    ragdoll.setSkeleton(skel);
    QCOMPARE(ragdoll.skeleton(), skel);
    QCOMPARE(spy.count(), 1);

    // Same pointer
    ragdoll.setSkeleton(skel);
    QCOMPARE(spy.count(), 1);
}

void tst_Ragdoll::partsListProperty()
{
    Ragdoll ragdoll;
    auto list = ragdoll.parts();

    auto *part1 = new RagdollPart(&ragdoll);
    part1->setJointName(QStringLiteral("torso"));
    auto *shape1 = new BoxShape;
    part1->setShape(shape1);
    part1->setMass(10.0f);
    part1->setObjectLayer(1);

    auto *part2 = new RagdollPart(&ragdoll);
    part2->setJointName(QStringLiteral("head"));
    auto *shape2 = new BoxShape;
    part2->setShape(shape2);

    list.append(&list, part1);
    list.append(&list, part2);

    QCOMPARE(list.count(&list), 2);
    QCOMPARE(list.at(&list, 0)->jointName(), QStringLiteral("torso"));
    QCOMPARE(list.at(&list, 1)->jointName(), QStringLiteral("head"));

    delete shape1;
    delete shape2;
}

void tst_Ragdoll::collisionGroupIdProperty()
{
    Ragdoll ragdoll;
    QSignalSpy spy(&ragdoll, &Ragdoll::collisionGroupIdChanged);

    ragdoll.setCollisionGroupId(5);
    QCOMPARE(ragdoll.collisionGroupId(), 5);
    QCOMPARE(spy.count(), 1);

    ragdoll.setCollisionGroupId(5);
    QCOMPARE(spy.count(), 1);
}

void tst_Ragdoll::autoDisableProperty()
{
    Ragdoll ragdoll;
    QSignalSpy spy(&ragdoll, &Ragdoll::autoDisableParentChildCollisionsChanged);

    ragdoll.setAutoDisableParentChildCollisions(false);
    QCOMPARE(ragdoll.autoDisableParentChildCollisions(), false);
    QCOMPARE(spy.count(), 1);

    ragdoll.setAutoDisableParentChildCollisions(false);
    QCOMPARE(spy.count(), 1);
}

QTEST_GUILESS_MAIN(tst_Ragdoll)
#include "tst_ragdoll.moc"
