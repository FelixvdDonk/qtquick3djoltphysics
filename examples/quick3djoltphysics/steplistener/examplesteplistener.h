#ifndef EXAMPLESTEPLISTENER_H
#define EXAMPLESTEPLISTENER_H

#include <abstractphysicssteplistener_p.h>
#include <QObject>
#include <QtQml/QQmlEngine>

class ExampleStepListener : public AbstractPhysicsStepListener
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ExampleStepListener)
    Q_PROPERTY(int stepCount READ stepCount NOTIFY stepCountChanged)
    Q_PROPERTY(float currentForce READ currentForce NOTIFY currentForceChanged)

public:
    explicit ExampleStepListener(QObject *parent = nullptr);

    int stepCount() const { return m_stepCount; }
    float currentForce() const { return m_currentForce; }

    void onStep(float deltaTime, PhysicsSystem *system) override;

signals:
    void stepCountChanged();
    void currentForceChanged();

private:
    int m_stepCount = 0;
    float m_currentForce = 0.0f;
    float m_time = 0.0f;
};

#endif // EXAMPLESTEPLISTENER_H
