#ifndef SOFTBODYSHAREDSETTINGS_P_H
#define SOFTBODYSHAREDSETTINGS_P_H

#include <QtQuick3DJoltPhysics/qtquick3djoltphysicsglobal.h>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlListProperty>
#include <QObject>
#include <QVector3D>

#include <Jolt/Jolt.h>
#include <Jolt/Physics/SoftBody/SoftBodySharedSettings.h>

class Q_QUICK3DJOLTPHYSICS_EXPORT SoftBodyVertex : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QVector3D velocity READ velocity WRITE setVelocity NOTIFY velocityChanged)
    Q_PROPERTY(float inverseMass READ inverseMass WRITE setInverseMass NOTIFY inverseMassChanged)
    QML_NAMED_ELEMENT(SoftBodyVertex)
public:
    explicit SoftBodyVertex(QObject *parent = nullptr);
    ~SoftBodyVertex() override;

    QVector3D position() const;
    void setPosition(const QVector3D &position);

    QVector3D velocity() const;
    void setVelocity(const QVector3D &velocity);

    float inverseMass() const;
    void setInverseMass(float inverseMass);

signals:
    void positionChanged(const QVector3D &position);
    void velocityChanged(const QVector3D &velocity);
    void inverseMassChanged(float inverseMass);

private:
    QVector3D m_position;
    QVector3D m_velocity;
    float m_inverseMass = 1.0f;
};

class Q_QUICK3DJOLTPHYSICS_EXPORT SoftBodyFace : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int vertex1 READ vertex1 WRITE setVertex1 NOTIFY vertex1Changed)
    Q_PROPERTY(int vertex2 READ vertex2 WRITE setVertex2 NOTIFY vertex2Changed)
    Q_PROPERTY(int vertex3 READ vertex3 WRITE setVertex3 NOTIFY vertex3Changed)
    Q_PROPERTY(int materialIndex READ materialIndex WRITE setMaterialIndex NOTIFY materialIndexChanged)
    QML_NAMED_ELEMENT(SoftBodyFace)
public:
    explicit SoftBodyFace(QObject *parent = nullptr);
    ~SoftBodyFace() override;

    int vertex1() const;
    void setVertex1(int vertex1);

    int vertex2() const;
    void setVertex2(int vertex2);

    int vertex3() const;
    void setVertex3(int vertex3);

    int materialIndex() const;
    void setMaterialIndex(int materialIndex);

signals:
    void vertex1Changed(int vertex1);
    void vertex2Changed(int vertex2);
    void vertex3Changed(int vertex3);
    void materialIndexChanged(int materialIndex);

private:
    int m_vertex1 = 0;
    int m_vertex2 = 0;
    int m_vertex3 = 0;
    int m_materialIndex = 0;
};

class Q_QUICK3DJOLTPHYSICS_EXPORT SoftBodySharedSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<SoftBodyVertex> vertices READ vertices CONSTANT)
    Q_PROPERTY(QQmlListProperty<SoftBodyFace> faces READ faces CONSTANT)
    Q_PROPERTY(bool autoCreateConstraints READ autoCreateConstraints WRITE setAutoCreateConstraints NOTIFY autoCreateConstraintsChanged)
    Q_PROPERTY(float edgeCompliance READ edgeCompliance WRITE setEdgeCompliance NOTIFY edgeComplianceChanged)
    Q_PROPERTY(float bendCompliance READ bendCompliance WRITE setBendCompliance NOTIFY bendComplianceChanged)
    QML_NAMED_ELEMENT(SoftBodySharedSettings)
public:
    explicit SoftBodySharedSettings(QObject *parent = nullptr);
    ~SoftBodySharedSettings() override;

    QQmlListProperty<SoftBodyVertex> vertices();
    QQmlListProperty<SoftBodyFace> faces();

    bool autoCreateConstraints() const;
    void setAutoCreateConstraints(bool autoCreate);

    float edgeCompliance() const;
    void setEdgeCompliance(float compliance);

    float bendCompliance() const;
    void setBendCompliance(float compliance);

    Q_INVOKABLE void addVertex(const QVector3D &position, float inverseMass = 1.0f);
    Q_INVOKABLE void addFace(int vertex1, int vertex2, int vertex3, int materialIndex = 0);

    JPH::Ref<JPH::SoftBodySharedSettings> createJoltSettings() const;

signals:
    void autoCreateConstraintsChanged(bool autoCreate);
    void edgeComplianceChanged(float compliance);
    void bendComplianceChanged(float compliance);

private:
    static void appendVertex(QQmlListProperty<SoftBodyVertex> *list, SoftBodyVertex *vertex);
    static qsizetype vertexCount(QQmlListProperty<SoftBodyVertex> *list);
    static SoftBodyVertex *vertexAt(QQmlListProperty<SoftBodyVertex> *list, qsizetype index);
    static void clearVertices(QQmlListProperty<SoftBodyVertex> *list);

    static void appendFace(QQmlListProperty<SoftBodyFace> *list, SoftBodyFace *face);
    static qsizetype faceCount(QQmlListProperty<SoftBodyFace> *list);
    static SoftBodyFace *faceAt(QQmlListProperty<SoftBodyFace> *list, qsizetype index);
    static void clearFaces(QQmlListProperty<SoftBodyFace> *list);

    QList<SoftBodyVertex *> m_vertices;
    QList<SoftBodyFace *> m_faces;
    bool m_autoCreateConstraints = true;
    float m_edgeCompliance = 0.0f;
    float m_bendCompliance = FLT_MAX;
};

#endif // SOFTBODYSHAREDSETTINGS_P_H
