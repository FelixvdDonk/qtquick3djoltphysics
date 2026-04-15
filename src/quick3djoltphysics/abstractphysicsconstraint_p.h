#ifndef ABSTRACTCONSTRAINT_P_H
#define ABSTRACTCONSTRAINT_P_H

#include "abstractphysicsnode_p.h"

#include <QtQuick3DJoltPhysics/qtquick3djoltphysicsglobal.h>
#include <QtQuick3D/private/qquick3dnode_p.h>

#include <QtQml/QQmlEngine>
#include <QObject>

#include <Jolt/Jolt.h>
#include <Jolt/Core/Reference.h>

namespace JPH {
class Constraint;
class TwoBodyConstraintSettings;
}

class Q_QUICK3DJOLTPHYSICS_EXPORT AbstractPhysicsConstraint : public AbstractPhysicsNode
{
    Q_OBJECT
    QML_NAMED_ELEMENT(PhysicsConstraint)
    QML_UNCREATABLE("abstract interface")
public:
    explicit AbstractPhysicsConstraint(QQuick3DNode *parent = nullptr);
    ~AbstractPhysicsConstraint() override;

    virtual JPH::Ref<JPH::TwoBodyConstraintSettings> createJoltConstraintSettings() const;

protected:
    void cleanup() override;

    JPH::Constraint *m_constraint = nullptr;

    friend class GearConstraint;
    friend class RackAndPinionConstraint;
};

#endif // ABSTRACTCONSTRAINT_P_H
