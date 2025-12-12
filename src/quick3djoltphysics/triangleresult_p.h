#ifndef TRIANGLERESULT_P_H
#define TRIANGLERESULT_P_H

#include <QtQuick3DJoltPhysics/qtquick3djoltphysicsglobal.h>
#include <QtCore/QObject>
#include <QtGui/QVector3D>
#include <QtQml/QQmlEngine>

#include "body_p.h"

class PhysicsMaterial;

class Q_QUICK3DJOLTPHYSICS_EXPORT TriangleResult
{
    Q_GADGET
    Q_PROPERTY(QVector3D vertex0 READ vertex0 CONSTANT)
    Q_PROPERTY(QVector3D vertex1 READ vertex1 CONSTANT)
    Q_PROPERTY(QVector3D vertex2 READ vertex2 CONSTANT)
    Q_PROPERTY(Body *body READ body CONSTANT)
public:
    TriangleResult();
    TriangleResult(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2, Body *body);

    QVector3D vertex0() const;
    QVector3D vertex1() const;
    QVector3D vertex2() const;
    Body *body() const;

private:
    QVector3D m_vertex0;
    QVector3D m_vertex1;
    QVector3D m_vertex2;
    Body *m_body = nullptr;
};

#endif // TRIANGLERESULT_P_H

