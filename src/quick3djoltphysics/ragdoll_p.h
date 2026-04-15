#ifndef RAGDOLL_P_H
#define RAGDOLL_P_H

#include "abstractphysicsnode_p.h"
#include "physicsskeleton_p.h"
#include "ragdollpart_p.h"

#include <QtQuick3DJoltPhysics/qtquick3djoltphysicsglobal.h>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlListProperty>
#include <QHash>
#include <QVector3D>
#include <QQuaternion>
#include <QVariantMap>

#include <Jolt/Jolt.h>
#include <Jolt/Core/Reference.h>
#include <Jolt/Physics/Ragdoll/Ragdoll.h>

class Q_QUICK3DJOLTPHYSICS_EXPORT Ragdoll : public AbstractPhysicsNode
{
    Q_OBJECT
    Q_PROPERTY(PhysicsSkeleton *skeleton READ skeleton WRITE setSkeleton NOTIFY skeletonChanged)
    Q_PROPERTY(QQmlListProperty<RagdollPart> parts READ parts CONSTANT)
    Q_PROPERTY(int collisionGroupId READ collisionGroupId WRITE setCollisionGroupId NOTIFY collisionGroupIdChanged)
    Q_PROPERTY(bool autoDisableParentChildCollisions READ autoDisableParentChildCollisions WRITE setAutoDisableParentChildCollisions NOTIFY autoDisableParentChildCollisionsChanged)
    QML_NAMED_ELEMENT(Ragdoll)
public:
    explicit Ragdoll(QQuick3DNode *parent = nullptr);
    ~Ragdoll() override;

    PhysicsSkeleton *skeleton() const;
    void setSkeleton(PhysicsSkeleton *skeleton);

    QQmlListProperty<RagdollPart> parts();

    int collisionGroupId() const;
    void setCollisionGroupId(int collisionGroupId);

    bool autoDisableParentChildCollisions() const;
    void setAutoDisableParentChildCollisions(bool autoDisable);

    Q_INVOKABLE void addToPhysicsSystem();
    Q_INVOKABLE void removeFromPhysicsSystem();
    Q_INVOKABLE void activate();

    Q_INVOKABLE void driveToPose(const QVariantMap &jointOrientations);
    Q_INVOKABLE void driveJointToAngle(const QString &jointName, float angleDegrees);

    Q_INVOKABLE QVector3D getJointPosition(const QString &jointName) const;
    Q_INVOKABLE QQuaternion getJointRotation(const QString &jointName) const;
    Q_INVOKABLE int getJointCount() const;

signals:
    void skeletonChanged(PhysicsSkeleton *skeleton);
    void collisionGroupIdChanged(int collisionGroupId);
    void autoDisableParentChildCollisionsChanged(bool autoDisable);

protected:
    void updateJoltObject() override;
    void cleanup() override;

private:
    static void appendPart(QQmlListProperty<RagdollPart> *list, RagdollPart *part);
    static qsizetype partCount(QQmlListProperty<RagdollPart> *list);
    static RagdollPart *partAt(QQmlListProperty<RagdollPart> *list, qsizetype index);
    static void clearParts(QQmlListProperty<RagdollPart> *list);

    int jointIndexForName(const QString &name) const;

    PhysicsSkeleton *m_skeleton = nullptr;
    QList<RagdollPart *> m_parts;
    int m_collisionGroupId = 0;
    bool m_autoDisableParentChildCollisions = true;

    JPH::Ref<JPH::RagdollSettings> m_ragdollSettings;
    JPH::Ragdoll *m_ragdoll = nullptr;
    QHash<QString, int> m_nameToIndex;
};

#endif // RAGDOLL_P_H
