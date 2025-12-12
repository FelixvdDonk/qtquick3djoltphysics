#include "triangleresult_p.h"

TriangleResult::TriangleResult() = default;

TriangleResult::TriangleResult(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2, Body *body)
    : m_vertex0(v0)
    , m_vertex1(v1)
    , m_vertex2(v2)
    , m_body(body)
{
}

QVector3D TriangleResult::vertex0() const
{
    return m_vertex0;
}

QVector3D TriangleResult::vertex1() const
{
    return m_vertex1;
}

QVector3D TriangleResult::vertex2() const
{
    return m_vertex2;
}

Body *TriangleResult::body() const
{
    return m_body;
}
