#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/hermitepath_p.h>

class tst_HermitePathIntegration : public QObject
{
    Q_OBJECT
private slots:
    void pointListManagement();
    void isLoopingProperty();
};

void tst_HermitePathIntegration::pointListManagement()
{
    HermitePath path;
    auto list = path.points();

    auto *p1 = new HermitePathPoint(&path);
    p1->setPosition(QVector3D(0, 0, 0));
    p1->setTangent(QVector3D(100, 0, 0));
    p1->setNormal(QVector3D(0, 1, 0));
    list.append(&list, p1);

    auto *p2 = new HermitePathPoint(&path);
    p2->setPosition(QVector3D(200, 0, 0));
    p2->setTangent(QVector3D(100, 0, 0));
    p2->setNormal(QVector3D(0, 1, 0));
    list.append(&list, p2);

    QCOMPARE(list.count(&list), 2);
    QCOMPARE(list.at(&list, 0)->position(), QVector3D(0, 0, 0));
    QCOMPARE(list.at(&list, 1)->position(), QVector3D(200, 0, 0));
}

void tst_HermitePathIntegration::isLoopingProperty()
{
    HermitePath path;
    QSignalSpy spy(&path, &HermitePath::isLoopingChanged);

    QCOMPARE(path.isLooping(), false);

    path.setIsLooping(true);
    QCOMPARE(path.isLooping(), true);
    QCOMPARE(spy.count(), 1);

    path.setIsLooping(true);
    QCOMPARE(spy.count(), 1);
}

QTEST_GUILESS_MAIN(tst_HermitePathIntegration)
#include "tst_hermitepath_integration.moc"
