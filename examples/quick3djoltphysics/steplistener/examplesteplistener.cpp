#include "examplesteplistener.h"

#include <QtMath>

ExampleStepListener::ExampleStepListener(QObject *parent)
    : AbstractPhysicsStepListener(parent)
{
}

void ExampleStepListener::onStep(float deltaTime, PhysicsSystem *)
{
    m_time += deltaTime;
    m_stepCount++;

    // Sinusoidal force: amplitude 500000, period ~2s
    m_currentForce = 500000.0f * qSin(m_time * 3.14159f);

    // Note: signals cannot be emitted on the physics thread.
    // We store the values and let QML poll them via Timer.
}
