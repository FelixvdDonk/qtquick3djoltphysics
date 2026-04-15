#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/hermitepath_p.h>

class tst_HermitePath : public QObject
{
    Q_OBJECT
private slots:
    void pointDefaults();
    void pointSetGet();
    void pathDefaults();
    void pathIsLooping();
    void pointListProperty();
};

void tst_HermitePath::pointDefaults()
{
    HermitePathPoint p;
    QCOMPARE(p.position(), QVector3D());
    QCOMPARE(p.tangent(), QVector3D());
    QCOMPARE(p.normal(), QVector3D(0, 1, 0));
}

void tst_HermitePath::pointSetGet()
{
    HermitePathPoint p;

    QSignalSpy posSpy(&p, &HermitePathPoint::positionChanged);
    QSignalSpy tanSpy(&p, &HermitePathPoint::tangentChanged);
    QSignalSpy normSpy(&p, &HermitePathPoint::normalChanged);

    p.setPosition(QVector3D(100, 0, 0));
    QCOMPARE(p.position(), QVector3D(100, 0, 0));
    QCOMPARE(posSpy.count(), 1);

    p.setTangent(QVector3D(1, 0, 0));
    QCOMPARE(p.tangent(), QVector3D(1, 0, 0));
    QCOMPARE(tanSpy.count(), 1);

    p.setNormal(QVector3D(0, 0, 1));
    QCOMPARE(p.normal(), QVector3D(0, 0, 1));
    QCOMPARE(normSpy.count(), 1);

    // No re-emit
    p.setPosition(QVector3D(100, 0, 0));
    QCOMPARE(posSpy.count(), 1);
}

void tst_HermitePath::pathDefaults()
{
    HermitePath path;
    QCOMPARE(path.isLooping(), false);
}

void tst_HermitePath::pathIsLooping()
{
    HermitePath path;
    QSignalSpy spy(&path, &PathConstraintPathBase::isLoopingChanged);

    path.setIsLooping(true);
    QCOMPARE(path.isLooping(), true);
    QCOMPARE(spy.count(), 1);

    path.setIsLooping(true);
    QCOMPARE(spy.count(), 1);
}

void tst_HermitePath::pointListProperty()
{
    HermitePath path;
    auto list = path.points();

    QCOMPARE(list.count(&list), 0);

    auto *p1 = new HermitePathPoint(&path);
    p1->setPosition(QVector3D(0, 0, 0));
    p1->setTangent(QVector3D(100, 0, 0));

    auto *p2 = new HermitePathPoint(&path);
    p2->setPosition(QVector3D(100, 0, 0));
    p2->setTangent(QVector3D(100, 0, 0));

    list.append(&list, p1);
    list.append(&list, p2);
    QCOMPARE(list.count(&list), 2);
    QCOMPARE(list.at(&list, 0), p1);
    QCOMPARE(list.at(&list, 1), p2);
}

QTEST_GUILESS_MAIN(tst_HermitePath)
#include "tst_hermitepath.moc"
