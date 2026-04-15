#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/softbodysharedsettings_p.h>

class tst_SoftBodySharedSettings : public QObject
{
    Q_OBJECT
private slots:
    void vertexDefaults();
    void vertexSetGet();
    void faceDefaults();
    void faceSetGet();
    void settingsDefaults();
    void settingsProperties();
    void addVertexInvocable();
    void addFaceInvocable();
};

void tst_SoftBodySharedSettings::vertexDefaults()
{
    SoftBodyVertex v;
    QCOMPARE(v.position(), QVector3D());
    QCOMPARE(v.velocity(), QVector3D());
    QCOMPARE(v.inverseMass(), 1.0f);
}

void tst_SoftBodySharedSettings::vertexSetGet()
{
    SoftBodyVertex v;
    QSignalSpy posSpy(&v, &SoftBodyVertex::positionChanged);
    QSignalSpy velSpy(&v, &SoftBodyVertex::velocityChanged);
    QSignalSpy massSpy(&v, &SoftBodyVertex::inverseMassChanged);

    v.setPosition(QVector3D(1, 2, 3));
    QCOMPARE(v.position(), QVector3D(1, 2, 3));
    QCOMPARE(posSpy.count(), 1);

    v.setVelocity(QVector3D(0, -1, 0));
    QCOMPARE(v.velocity(), QVector3D(0, -1, 0));
    QCOMPARE(velSpy.count(), 1);

    v.setInverseMass(0.5f);
    QCOMPARE(v.inverseMass(), 0.5f);
    QCOMPARE(massSpy.count(), 1);

    // No re-emit on same value
    v.setInverseMass(0.5f);
    QCOMPARE(massSpy.count(), 1);
}

void tst_SoftBodySharedSettings::faceDefaults()
{
    SoftBodyFace f;
    QCOMPARE(f.vertex1(), 0);
    QCOMPARE(f.vertex2(), 0);
    QCOMPARE(f.vertex3(), 0);
    QCOMPARE(f.materialIndex(), 0);
}

void tst_SoftBodySharedSettings::faceSetGet()
{
    SoftBodyFace f;
    QSignalSpy v1Spy(&f, &SoftBodyFace::vertex1Changed);
    QSignalSpy v2Spy(&f, &SoftBodyFace::vertex2Changed);
    QSignalSpy v3Spy(&f, &SoftBodyFace::vertex3Changed);
    QSignalSpy matSpy(&f, &SoftBodyFace::materialIndexChanged);

    f.setVertex1(1);
    f.setVertex2(2);
    f.setVertex3(3);
    f.setMaterialIndex(1);

    QCOMPARE(f.vertex1(), 1);
    QCOMPARE(f.vertex2(), 2);
    QCOMPARE(f.vertex3(), 3);
    QCOMPARE(f.materialIndex(), 1);

    QCOMPARE(v1Spy.count(), 1);
    QCOMPARE(v2Spy.count(), 1);
    QCOMPARE(v3Spy.count(), 1);
    QCOMPARE(matSpy.count(), 1);
}

void tst_SoftBodySharedSettings::settingsDefaults()
{
    SoftBodySharedSettings s;
    QCOMPARE(s.autoCreateConstraints(), true);
    QCOMPARE(s.edgeCompliance(), 0.0f);
    QCOMPARE(s.bendCompliance(), FLT_MAX);
}

void tst_SoftBodySharedSettings::settingsProperties()
{
    SoftBodySharedSettings s;
    QSignalSpy autoSpy(&s, &SoftBodySharedSettings::autoCreateConstraintsChanged);
    QSignalSpy edgeSpy(&s, &SoftBodySharedSettings::edgeComplianceChanged);
    QSignalSpy bendSpy(&s, &SoftBodySharedSettings::bendComplianceChanged);

    s.setAutoCreateConstraints(false);
    QCOMPARE(s.autoCreateConstraints(), false);
    QCOMPARE(autoSpy.count(), 1);

    s.setEdgeCompliance(0.1f);
    QCOMPARE(s.edgeCompliance(), 0.1f);
    QCOMPARE(edgeSpy.count(), 1);

    s.setBendCompliance(0.2f);
    QCOMPARE(s.bendCompliance(), 0.2f);
    QCOMPARE(bendSpy.count(), 1);
}

void tst_SoftBodySharedSettings::addVertexInvocable()
{
    SoftBodySharedSettings s;

    s.addVertex(QVector3D(0, 0, 0), 1.0f);
    s.addVertex(QVector3D(100, 0, 0), 1.0f);
    s.addVertex(QVector3D(0, 100, 0), 1.0f);

    // Verify list property reflects added vertices
    auto list = s.vertices();
    QCOMPARE(list.count(&list), 3);

    auto *v0 = list.at(&list, 0);
    QVERIFY(v0 != nullptr);
    QCOMPARE(v0->position(), QVector3D(0, 0, 0));

    auto *v1 = list.at(&list, 1);
    QCOMPARE(v1->position(), QVector3D(100, 0, 0));
}

void tst_SoftBodySharedSettings::addFaceInvocable()
{
    SoftBodySharedSettings s;

    s.addVertex(QVector3D(0, 0, 0));
    s.addVertex(QVector3D(100, 0, 0));
    s.addVertex(QVector3D(0, 100, 0));

    s.addFace(0, 1, 2);

    auto list = s.faces();
    QCOMPARE(list.count(&list), 1);

    auto *f = list.at(&list, 0);
    QCOMPARE(f->vertex1(), 0);
    QCOMPARE(f->vertex2(), 1);
    QCOMPARE(f->vertex3(), 2);
}

QTEST_GUILESS_MAIN(tst_SoftBodySharedSettings)
#include "tst_softbodysharedsettings.moc"
