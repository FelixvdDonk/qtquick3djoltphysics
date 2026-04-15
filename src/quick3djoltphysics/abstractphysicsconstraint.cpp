#include "abstractphysicsconstraint_p.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Constraints/TwoBodyConstraint.h>

AbstractPhysicsConstraint::AbstractPhysicsConstraint(QQuick3DNode *parent) : AbstractPhysicsNode(parent)
{
}

AbstractPhysicsConstraint::~AbstractPhysicsConstraint()
{
    cleanup();
}

JPH::Ref<JPH::TwoBodyConstraintSettings> AbstractPhysicsConstraint::createJoltConstraintSettings() const
{
    return nullptr;
}

void AbstractPhysicsConstraint::cleanup()
{
    if (m_constraint)
        m_jolt->RemoveConstraint(m_constraint);

    m_constraint = nullptr;
}
