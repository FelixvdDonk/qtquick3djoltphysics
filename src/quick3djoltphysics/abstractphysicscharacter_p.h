#ifndef ABSTRACTPHYSICSCHARACTER_P_H
#define ABSTRACTPHYSICSCHARACTER_P_H

#include "abstractphysicsbody_p.h"

#include <QtQuick3DJoltPhysics/qtquick3djoltphysicsglobal.h>
#include <QtQml/QQmlEngine>

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Character/CharacterBase.h>

class AbstractShape;

class Q_QUICK3DJOLTPHYSICS_EXPORT AbstractPhysicsCharacter : public AbstractPhysicsBody
{
    Q_OBJECT
    Q_PROPERTY(QVector4D supportingVolume READ supportingVolume WRITE setSupportingVolume NOTIFY supportingVolumeChanged)
    Q_PROPERTY(float maxSlopeAngle READ maxSlopeAngle WRITE setMaxSlopeAngle NOTIFY maxSlopeAngleChanged)
    QML_NAMED_ELEMENT(PhysicsCharacter)
    QML_UNCREATABLE("abstract interface")
public:
    explicit AbstractPhysicsCharacter(QQuick3DNode *parent = nullptr);
    ~AbstractPhysicsCharacter() override;

    enum class GroundState {
        OnGround,
        OnSteepGround,
        NotSupported,
        InAir
    };
    Q_ENUM(GroundState)

    QVector4D supportingVolume() const;
    void setSupportingVolume(const QVector4D &supportingVolume);
    float maxSlopeAngle() const;
    void setMaxSlopeAngle(float maxSlopeAngle);

    Q_INVOKABLE bool isSlopeTooSteep(const QVector3D &normal) const;
    Q_INVOKABLE bool isSupported() const;

    Q_INVOKABLE GroundState getGroundState() const;
    Q_INVOKABLE QVector3D getGroundPosition() const;
    Q_INVOKABLE QVector3D getGroundNormal() const;
    Q_INVOKABLE QVector3D getGroundVelocity() const;

    Q_INVOKABLE AbstractPhysicsBody *getGroundBody() const;

signals:
    void supportingVolumeChanged(const QVector4D &supportingVolume);
    void maxSlopeAngleChanged(float maxSlopeAngle);

private slots:
    void handleUpChanged();

protected:
    virtual JPH::CharacterBase *character() const = 0;

private:
    QVector4D m_supportingVolume;
    float m_maxSlopeAngle = 50.0f;
};

#endif // ABSTRACTPHYSICSCHARACTER_P_H
