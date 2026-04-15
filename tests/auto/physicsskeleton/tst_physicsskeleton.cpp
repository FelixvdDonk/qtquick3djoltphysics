#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/physicsskeleton_p.h>
#include <QtQuick3DJoltPhysics/private/skeletonjoint_p.h>

class tst_PhysicsSkeleton : public QObject
{
    Q_OBJECT
private slots:
    void defaults();
    void jointListProperty();
};

void tst_PhysicsSkeleton::defaults()
{
    PhysicsSkeleton skel;
    auto list = skel.joints();
    QCOMPARE(list.count(&list), 0);
}

void tst_PhysicsSkeleton::jointListProperty()
{
    PhysicsSkeleton skel;
    auto list = skel.joints();

    auto *j1 = new SkeletonJoint(&skel);
    j1->setName(QStringLiteral("root"));

    auto *j2 = new SkeletonJoint(&skel);
    j2->setName(QStringLiteral("spine"));
    j2->setParentName(QStringLiteral("root"));

    list.append(&list, j1);
    list.append(&list, j2);

    QCOMPARE(list.count(&list), 2);
    QCOMPARE(list.at(&list, 0)->name(), QStringLiteral("root"));
    QCOMPARE(list.at(&list, 1)->parentName(), QStringLiteral("root"));
}

QTEST_GUILESS_MAIN(tst_PhysicsSkeleton)
#include "tst_physicsskeleton.moc"
