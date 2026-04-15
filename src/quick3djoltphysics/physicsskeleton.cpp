#include "physicsskeleton_p.h"

PhysicsSkeleton::PhysicsSkeleton(QObject *parent) : QObject(parent)
{
}

PhysicsSkeleton::~PhysicsSkeleton() = default;

QQmlListProperty<SkeletonJoint> PhysicsSkeleton::joints()
{
    return QQmlListProperty<SkeletonJoint>(this, nullptr,
                                           &PhysicsSkeleton::appendJoint,
                                           &PhysicsSkeleton::jointCount,
                                           &PhysicsSkeleton::jointAt,
                                           &PhysicsSkeleton::clearJoints);
}

const QList<SkeletonJoint *> &PhysicsSkeleton::jointList() const
{
    return m_joints;
}

JPH::Ref<JPH::Skeleton> PhysicsSkeleton::createJoltSkeleton() const
{
    JPH::Ref<JPH::Skeleton> skeleton = new JPH::Skeleton();

    for (const auto *joint : m_joints) {
        std::string name = joint->name().toStdString();
        std::string parentName = joint->parentName().toStdString();
        skeleton->AddJoint(name, parentName);
    }

    skeleton->CalculateParentJointIndices();
    return skeleton;
}

void PhysicsSkeleton::appendJoint(QQmlListProperty<SkeletonJoint> *list, SkeletonJoint *joint)
{
    auto *self = static_cast<PhysicsSkeleton *>(list->object);
    self->m_joints.append(joint);
    emit self->changed();
}

qsizetype PhysicsSkeleton::jointCount(QQmlListProperty<SkeletonJoint> *list)
{
    auto *self = static_cast<PhysicsSkeleton *>(list->object);
    return self->m_joints.size();
}

SkeletonJoint *PhysicsSkeleton::jointAt(QQmlListProperty<SkeletonJoint> *list, qsizetype index)
{
    auto *self = static_cast<PhysicsSkeleton *>(list->object);
    return self->m_joints.at(index);
}

void PhysicsSkeleton::clearJoints(QQmlListProperty<SkeletonJoint> *list)
{
    auto *self = static_cast<PhysicsSkeleton *>(list->object);
    self->m_joints.clear();
    emit self->changed();
}
