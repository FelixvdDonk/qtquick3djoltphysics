#include "skeletonjoint_p.h"

SkeletonJoint::SkeletonJoint(QObject *parent) : QObject(parent)
{
}

SkeletonJoint::~SkeletonJoint() = default;

QString SkeletonJoint::name() const
{
    return m_name;
}

void SkeletonJoint::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
    emit changed();
}

QString SkeletonJoint::parentName() const
{
    return m_parentName;
}

void SkeletonJoint::setParentName(const QString &parentName)
{
    if (m_parentName == parentName)
        return;

    m_parentName = parentName;
    emit parentNameChanged(m_parentName);
    emit changed();
}
