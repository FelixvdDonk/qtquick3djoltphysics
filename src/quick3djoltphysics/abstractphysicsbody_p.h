#ifndef ABSTRACTPHYSICSBODY_P_H
#define ABSTRACTPHYSICSBODY_P_H

#include "abstractshape_p.h"
#include "abstractphysicsnode_p.h"

#include <QtQuick3DJoltPhysics/qtquick3djoltphysicsglobal.h>
#include <QtQuick3D/private/qquick3dnode_p.h>
#include <QtQml/QQmlEngine>

#include <QtQuick3DUtils/private/qssgutils_p.h>

#include <Jolt/Physics/EActivation.h>

class Q_QUICK3DJOLTPHYSICS_EXPORT AbstractPhysicsBody : public AbstractPhysicsNode
{
    Q_OBJECT
    Q_PROPERTY(quint32 bodyID READ bodyID NOTIFY bodyIDChanged)
    Q_PROPERTY(AbstractShape *shape READ shape WRITE setShape NOTIFY shapeChanged)
    Q_PROPERTY(Activation activation READ activation WRITE setActivation NOTIFY activationChanged)
    QML_NAMED_ELEMENT(PhysicsBody)
    QML_UNCREATABLE("abstract interface")
public:
    explicit AbstractPhysicsBody(QQuick3DNode *parent = nullptr);
    ~AbstractPhysicsBody() override;

    enum class Activation {
        Activate,
        DontActivate
    };
    Q_ENUM(Activation)

    quint32 bodyID() const;
    AbstractShape *shape() const;
    void setShape(AbstractShape *shape);
    Activation activation() const;
    void setActivation(Activation activation);

signals:
    void bodyIDChanged(quint32 bodyID);
    void shapeChanged(AbstractShape *shape);
    void activationChanged(Activation activation);

    void bodyContact(AbstractPhysicsBody *body, const QVector3D &baseOffset, const QVector<QVector3D> &contactPoints, const QVector3D &worldSpaceNormal, float penetrationDepth);
    void bodyEntered(AbstractPhysicsBody *body);
    void bodyExited(AbstractPhysicsBody *body);
    void characterContact(AbstractPhysicsBody *body, const QVector3D &contactPosition, const QVector3D &contactNormal);

protected:
    quint32 m_bodyID = 0;
    AbstractShape *m_shape = nullptr;
    Activation m_activation = Activation::Activate;

private:
    QMetaObject::Connection m_shapeSignalConnection;
};

#endif // ABSTRACTPHYSICSBODY_P_H
