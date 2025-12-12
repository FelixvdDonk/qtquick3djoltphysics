#ifndef CHARACTER_P_H
#define CHARACTER_P_H

#include "abstractphysicscharacter_p.h"

#include <QtQuick3DJoltPhysics/qtquick3djoltphysicsglobal.h>
#include <QtQml/QQmlEngine>

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>
#include <Jolt/Physics/Character/Character.h>

class Q_QUICK3DJOLTPHYSICS_EXPORT Character : public AbstractPhysicsCharacter
{
    Q_OBJECT
    Q_PROPERTY(int layer READ layer WRITE setLayer NOTIFY layerChanged)
    Q_PROPERTY(float mass READ mass WRITE setMass NOTIFY massChanged)
    Q_PROPERTY(float friction READ friction WRITE setFriction NOTIFY frictionChanged)
    Q_PROPERTY(float gravityFactor READ gravityFactor WRITE setGravityFactor NOTIFY gravityFactorChanged)
    QML_NAMED_ELEMENT(Character)
public:
    explicit Character(QQuick3DNode *parent = nullptr);
    ~Character() override;

    int layer() const;
    void setLayer(int layer);
    float mass() const;
    void setMass(float mass);
    float friction() const;
    void setFriction(float friction);
    float gravityFactor() const;
    void setGravityFactor(float gravityFactor);

    Q_INVOKABLE QVector3D getLinearVelocity() const;
    Q_INVOKABLE void setLinearVelocity(const QVector3D &linearVelocity);

    Q_INVOKABLE void postSimulation(float maxSeparationDistance);
    Q_INVOKABLE bool setShape(float maxPenetrationDepth);

signals:
    void layerChanged(int layer);
    void massChanged(float mass);
    void frictionChanged(float friction);
    void gravityFactorChanged(float gravityFactor);

protected:
    JPH::CharacterBase *character() const override;
    void updateJoltObject() override;
    void cleanup() override;
    void sync() override;

private:
    JPH::Character *m_character = nullptr;
    JPH::CharacterSettings m_characterSettings;
};

#endif // CHARACTER_P_H
