#include "softbodysharedsettings_p.h"
#include "physicsutils_p.h"

// --- SoftBodyVertex ---

SoftBodyVertex::SoftBodyVertex(QObject *parent)
    : QObject(parent)
{
}

SoftBodyVertex::~SoftBodyVertex() = default;

QVector3D SoftBodyVertex::position() const
{
    return m_position;
}

void SoftBodyVertex::setPosition(const QVector3D &position)
{
    if (m_position == position)
        return;
    m_position = position;
    emit positionChanged(m_position);
}

QVector3D SoftBodyVertex::velocity() const
{
    return m_velocity;
}

void SoftBodyVertex::setVelocity(const QVector3D &velocity)
{
    if (m_velocity == velocity)
        return;
    m_velocity = velocity;
    emit velocityChanged(m_velocity);
}

float SoftBodyVertex::inverseMass() const
{
    return m_inverseMass;
}

void SoftBodyVertex::setInverseMass(float inverseMass)
{
    if (qFuzzyCompare(m_inverseMass, inverseMass))
        return;
    m_inverseMass = inverseMass;
    emit inverseMassChanged(m_inverseMass);
}

// --- SoftBodyFace ---

SoftBodyFace::SoftBodyFace(QObject *parent)
    : QObject(parent)
{
}

SoftBodyFace::~SoftBodyFace() = default;

int SoftBodyFace::vertex1() const { return m_vertex1; }
void SoftBodyFace::setVertex1(int vertex1)
{
    if (m_vertex1 == vertex1) return;
    m_vertex1 = vertex1;
    emit vertex1Changed(m_vertex1);
}

int SoftBodyFace::vertex2() const { return m_vertex2; }
void SoftBodyFace::setVertex2(int vertex2)
{
    if (m_vertex2 == vertex2) return;
    m_vertex2 = vertex2;
    emit vertex2Changed(m_vertex2);
}

int SoftBodyFace::vertex3() const { return m_vertex3; }
void SoftBodyFace::setVertex3(int vertex3)
{
    if (m_vertex3 == vertex3) return;
    m_vertex3 = vertex3;
    emit vertex3Changed(m_vertex3);
}

int SoftBodyFace::materialIndex() const { return m_materialIndex; }
void SoftBodyFace::setMaterialIndex(int materialIndex)
{
    if (m_materialIndex == materialIndex) return;
    m_materialIndex = materialIndex;
    emit materialIndexChanged(m_materialIndex);
}

// --- SoftBodySharedSettings ---

SoftBodySharedSettings::SoftBodySharedSettings(QObject *parent)
    : QObject(parent)
{
}

SoftBodySharedSettings::~SoftBodySharedSettings() = default;

QQmlListProperty<SoftBodyVertex> SoftBodySharedSettings::vertices()
{
    return QQmlListProperty<SoftBodyVertex>(this, nullptr,
                                            &SoftBodySharedSettings::appendVertex,
                                            &SoftBodySharedSettings::vertexCount,
                                            &SoftBodySharedSettings::vertexAt,
                                            &SoftBodySharedSettings::clearVertices);
}

QQmlListProperty<SoftBodyFace> SoftBodySharedSettings::faces()
{
    return QQmlListProperty<SoftBodyFace>(this, nullptr,
                                          &SoftBodySharedSettings::appendFace,
                                          &SoftBodySharedSettings::faceCount,
                                          &SoftBodySharedSettings::faceAt,
                                          &SoftBodySharedSettings::clearFaces);
}

bool SoftBodySharedSettings::autoCreateConstraints() const
{
    return m_autoCreateConstraints;
}

void SoftBodySharedSettings::setAutoCreateConstraints(bool autoCreate)
{
    if (m_autoCreateConstraints == autoCreate)
        return;
    m_autoCreateConstraints = autoCreate;
    emit autoCreateConstraintsChanged(m_autoCreateConstraints);
}

float SoftBodySharedSettings::edgeCompliance() const
{
    return m_edgeCompliance;
}

void SoftBodySharedSettings::setEdgeCompliance(float compliance)
{
    if (qFuzzyCompare(m_edgeCompliance, compliance))
        return;
    m_edgeCompliance = compliance;
    emit edgeComplianceChanged(m_edgeCompliance);
}

float SoftBodySharedSettings::bendCompliance() const
{
    return m_bendCompliance;
}

void SoftBodySharedSettings::setBendCompliance(float compliance)
{
    if (qFuzzyCompare(m_bendCompliance, compliance))
        return;
    m_bendCompliance = compliance;
    emit bendComplianceChanged(m_bendCompliance);
}

void SoftBodySharedSettings::addVertex(const QVector3D &position, float inverseMass)
{
    auto *v = new SoftBodyVertex(this);
    v->setPosition(position);
    v->setInverseMass(inverseMass);
    m_vertices.append(v);
}

void SoftBodySharedSettings::addFace(int vertex1, int vertex2, int vertex3, int materialIndex)
{
    auto *f = new SoftBodyFace(this);
    f->setVertex1(vertex1);
    f->setVertex2(vertex2);
    f->setVertex3(vertex3);
    f->setMaterialIndex(materialIndex);
    m_faces.append(f);
}

JPH::Ref<JPH::SoftBodySharedSettings> SoftBodySharedSettings::createJoltSettings() const
{
    auto settings = new JPH::SoftBodySharedSettings;

    // Convert vertices (cm -> m for positions, cm/s -> m/s for velocity)
    settings->mVertices.reserve(m_vertices.size());
    for (const SoftBodyVertex *v : m_vertices) {
        JPH::SoftBodySharedSettings::Vertex joltVertex;
        joltVertex.mPosition = JPH::Float3(v->position().x() / 100.0f,
                                            v->position().y() / 100.0f,
                                            v->position().z() / 100.0f);
        joltVertex.mVelocity = JPH::Float3(v->velocity().x() / 100.0f,
                                            v->velocity().y() / 100.0f,
                                            v->velocity().z() / 100.0f);
        joltVertex.mInvMass = v->inverseMass();
        settings->mVertices.push_back(joltVertex);
    }

    // Convert faces
    for (const SoftBodyFace *f : m_faces) {
        settings->AddFace(JPH::SoftBodySharedSettings::Face(
            static_cast<uint32_t>(f->vertex1()),
            static_cast<uint32_t>(f->vertex2()),
            static_cast<uint32_t>(f->vertex3()),
            static_cast<uint32_t>(f->materialIndex())));
    }

    // Auto-create constraints from faces
    if (m_autoCreateConstraints && !m_faces.isEmpty()) {
        JPH::SoftBodySharedSettings::VertexAttributes va(m_edgeCompliance, m_edgeCompliance, m_bendCompliance);
        settings->CreateConstraints(&va, 1);
    }

    settings->Optimize();

    return settings;
}

// --- List property helpers ---

void SoftBodySharedSettings::appendVertex(QQmlListProperty<SoftBodyVertex> *list, SoftBodyVertex *vertex)
{
    auto *self = static_cast<SoftBodySharedSettings *>(list->object);
    self->m_vertices.append(vertex);
}

qsizetype SoftBodySharedSettings::vertexCount(QQmlListProperty<SoftBodyVertex> *list)
{
    auto *self = static_cast<SoftBodySharedSettings *>(list->object);
    return self->m_vertices.size();
}

SoftBodyVertex *SoftBodySharedSettings::vertexAt(QQmlListProperty<SoftBodyVertex> *list, qsizetype index)
{
    auto *self = static_cast<SoftBodySharedSettings *>(list->object);
    return self->m_vertices.at(index);
}

void SoftBodySharedSettings::clearVertices(QQmlListProperty<SoftBodyVertex> *list)
{
    auto *self = static_cast<SoftBodySharedSettings *>(list->object);
    self->m_vertices.clear();
}

void SoftBodySharedSettings::appendFace(QQmlListProperty<SoftBodyFace> *list, SoftBodyFace *face)
{
    auto *self = static_cast<SoftBodySharedSettings *>(list->object);
    self->m_faces.append(face);
}

qsizetype SoftBodySharedSettings::faceCount(QQmlListProperty<SoftBodyFace> *list)
{
    auto *self = static_cast<SoftBodySharedSettings *>(list->object);
    return self->m_faces.size();
}

SoftBodyFace *SoftBodySharedSettings::faceAt(QQmlListProperty<SoftBodyFace> *list, qsizetype index)
{
    auto *self = static_cast<SoftBodySharedSettings *>(list->object);
    return self->m_faces.at(index);
}

void SoftBodySharedSettings::clearFaces(QQmlListProperty<SoftBodyFace> *list)
{
    auto *self = static_cast<SoftBodySharedSettings *>(list->object);
    self->m_faces.clear();
}
