#include "physicsstate_p.h"

PhysicsState::PhysicsState(QObject *parent)
    : QObject(parent)
{
}

PhysicsState::~PhysicsState() = default;

int PhysicsState::dataSize() const
{
    return static_cast<int>(m_data.size());
}
