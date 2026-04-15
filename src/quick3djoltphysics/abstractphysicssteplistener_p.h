#ifndef ABSTRACTPHYSICSSTEPLISTENER_P_H
#define ABSTRACTPHYSICSSTEPLISTENER_P_H

#include <QtQuick3DJoltPhysics/qtquick3djoltphysicsglobal.h>
#include <QtQml/QQmlEngine>
#include <QObject>

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsStepListener.h>

class PhysicsSystem;

class Q_QUICK3DJOLTPHYSICS_EXPORT AbstractPhysicsStepListener : public QObject, public JPH::PhysicsStepListener
{
    Q_OBJECT
    QML_NAMED_ELEMENT(PhysicsStepListener)
    QML_UNCREATABLE("Use a C++ subclass of AbstractPhysicsStepListener")
public:
    explicit AbstractPhysicsStepListener(QObject *parent = nullptr);
    ~AbstractPhysicsStepListener() override;

    // Override in C++ subclass for hot-loop control logic.
    // Called ON the physics thread with body/constraint mutexes held.
    // Do NOT emit Qt signals or interact with QML here.
    virtual void onStep(float deltaTime, PhysicsSystem *system) = 0;

protected:
    // JPH::PhysicsStepListener implementation — dispatches to onStep()
    void OnStep(const JPH::PhysicsStepListenerContext &inContext) override;

private:
    friend class PhysicsSystem;
    PhysicsSystem *m_physicsSystem = nullptr;
};

#endif // ABSTRACTPHYSICSSTEPLISTENER_P_H
