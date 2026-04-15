#ifndef PHYSICSSTATE_P_H
#define PHYSICSSTATE_P_H

#include <QtQuick3DJoltPhysics/qtquick3djoltphysicsglobal.h>
#include <QtQml/QQmlEngine>
#include <QObject>

#include <string>

class Q_QUICK3DJOLTPHYSICS_EXPORT PhysicsState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int dataSize READ dataSize CONSTANT)
    QML_NAMED_ELEMENT(PhysicsState)
    QML_UNCREATABLE("PhysicsState is returned by PhysicsSystem.saveState()")
public:
    explicit PhysicsState(QObject *parent = nullptr);
    ~PhysicsState() override;

    int dataSize() const;

private:
    std::string m_data;

    friend class PhysicsSystem;
};

#endif // PHYSICSSTATE_P_H
