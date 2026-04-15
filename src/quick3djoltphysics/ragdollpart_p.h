#ifndef RAGDOLLPART_P_H
#define RAGDOLLPART_P_H

#include "body_p.h"

#include <QtQuick3DJoltPhysics/qtquick3djoltphysicsglobal.h>
#include <QObject>
#include <QVector3D>
#include <QQuaternion>
#include <QtQml/QQmlEngine>

class AbstractShape;
class AbstractPhysicsConstraint;

class Q_QUICK3DJOLTPHYSICS_EXPORT RagdollPart : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString jointName READ jointName WRITE setJointName NOTIFY jointNameChanged)
    Q_PROPERTY(AbstractShape *shape READ shape WRITE setShape NOTIFY shapeChanged)
    Q_PROPERTY(Body::MotionType motionType READ motionType WRITE setMotionType NOTIFY motionTypeChanged)
    Q_PROPERTY(float mass READ mass WRITE setMass NOTIFY massChanged)
    Q_PROPERTY(int objectLayer READ objectLayer WRITE setObjectLayer NOTIFY objectLayerChanged)
    Q_PROPERTY(AbstractPhysicsConstraint *constraintToParent READ constraintToParent WRITE setConstraintToParent NOTIFY constraintToParentChanged)
    Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QQuaternion rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
    QML_NAMED_ELEMENT(RagdollPart)
public:
    explicit RagdollPart(QObject *parent = nullptr);
    ~RagdollPart() override;

    QString jointName() const;
    void setJointName(const QString &jointName);

    AbstractShape *shape() const;
    void setShape(AbstractShape *shape);

    Body::MotionType motionType() const;
    void setMotionType(Body::MotionType motionType);

    float mass() const;
    void setMass(float mass);

    int objectLayer() const;
    void setObjectLayer(int objectLayer);

    AbstractPhysicsConstraint *constraintToParent() const;
    void setConstraintToParent(AbstractPhysicsConstraint *constraint);

    QVector3D position() const;
    void setPosition(const QVector3D &position);

    QQuaternion rotation() const;
    void setRotation(const QQuaternion &rotation);

signals:
    void jointNameChanged(const QString &jointName);
    void shapeChanged(AbstractShape *shape);
    void motionTypeChanged(Body::MotionType motionType);
    void massChanged(float mass);
    void objectLayerChanged(int objectLayer);
    void constraintToParentChanged(AbstractPhysicsConstraint *constraint);
    void positionChanged(const QVector3D &position);
    void rotationChanged(const QQuaternion &rotation);

private:
    QString m_jointName;
    AbstractShape *m_shape = nullptr;
    Body::MotionType m_motionType = Body::MotionType::Dynamic;
    float m_mass = 1.0f;
    int m_objectLayer = 0;
    AbstractPhysicsConstraint *m_constraintToParent = nullptr;
    QVector3D m_position;
    QQuaternion m_rotation;
};

#endif // RAGDOLLPART_P_H
