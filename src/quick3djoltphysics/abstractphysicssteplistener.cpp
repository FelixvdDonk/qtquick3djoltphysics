#include "abstractphysicssteplistener_p.h"

AbstractPhysicsStepListener::AbstractPhysicsStepListener(QObject *parent) : QObject(parent)
{
}

AbstractPhysicsStepListener::~AbstractPhysicsStepListener() = default;

void AbstractPhysicsStepListener::OnStep(const JPH::PhysicsStepListenerContext &inContext)
{
    onStep(inContext.mDeltaTime, m_physicsSystem);
}
