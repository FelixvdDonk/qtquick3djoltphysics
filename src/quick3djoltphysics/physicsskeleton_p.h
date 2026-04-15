#ifndef PHYSICSSKELETON_P_H
#define PHYSICSSKELETON_P_H

#include "skeletonjoint_p.h"

#include <QtQuick3DJoltPhysics/qtquick3djoltphysicsglobal.h>
#include <QObject>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlListProperty>

#include <Jolt/Jolt.h>
#include <Jolt/Core/Reference.h>
#include <Jolt/Skeleton/Skeleton.h>

class Q_QUICK3DJOLTPHYSICS_EXPORT PhysicsSkeleton : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<SkeletonJoint> joints READ joints CONSTANT)
    Q_CLASSINFO("DefaultProperty", "joints")
    QML_NAMED_ELEMENT(PhysicsSkeleton)
public:
    explicit PhysicsSkeleton(QObject *parent = nullptr);
    ~PhysicsSkeleton() override;

    QQmlListProperty<SkeletonJoint> joints();

    const QList<SkeletonJoint *> &jointList() const;

    JPH::Ref<JPH::Skeleton> createJoltSkeleton() const;

signals:
    void changed();

private:
    static void appendJoint(QQmlListProperty<SkeletonJoint> *list, SkeletonJoint *joint);
    static qsizetype jointCount(QQmlListProperty<SkeletonJoint> *list);
    static SkeletonJoint *jointAt(QQmlListProperty<SkeletonJoint> *list, qsizetype index);
    static void clearJoints(QQmlListProperty<SkeletonJoint> *list);

    QList<SkeletonJoint *> m_joints;
};

#endif // PHYSICSSKELETON_P_H
