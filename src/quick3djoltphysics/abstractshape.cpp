#include "abstractshape_p.h"
#include "physicsutils_p.h"

#include <QtQuick3D>

#include <Jolt/Physics/Collision/Shape/ConvexShape.h>
#include <Jolt/Physics/Collision/Shape/DecoratedShape.h>

AbstractShape::AbstractShape(QQuick3DNode *parent) : QQuick3DNode(parent)
{
    connect(this, &QQuick3DNode::sceneScaleChanged, this, [this] { handleShapeChange(); });
}

AbstractShape::~AbstractShape() = default;

float AbstractShape::density() const
{
    return m_density;
}

void AbstractShape::setDensity(float density)
{
    if (qFuzzyCompare(m_density, density))
        return;

    m_density = density;
    updateJoltShapeDensity();

    emit densityChanged(m_density);
}

JPH::Ref<JPH::Shape> AbstractShape::getJoltShape()
{
    if (m_joltShape == nullptr)
        updateJoltShape();

    return m_joltShape;
}

void AbstractShape::updateJoltShape()
{
    m_joltShape = nullptr;
    
    createJoltShape();

    updateJoltShapeDensity();
}

void AbstractShape::handleShapeChange()
{
    updateJoltShape();
    emit changed();
}

static JPH::ConvexShape *getInnerConvexShape(JPH::Shape *shape)
{
    if (!shape)
        return nullptr;

    while (shape->GetType() == JPH::EShapeType::Decorated) {
        auto *decorated = static_cast<JPH::DecoratedShape *>(shape);
        shape = const_cast<JPH::Shape *>(decorated->GetInnerShape());
    }

    if (shape->GetType() == JPH::EShapeType::Convex)
        return static_cast<JPH::ConvexShape *>(shape);

    return nullptr;
}

void AbstractShape::updateJoltShapeDensity()
{
    if (!m_joltShape)
        return;

    auto *convexShape = getInnerConvexShape(m_joltShape.GetPtr());
    if (convexShape)
        convexShape->SetDensity(m_density);
    else if (m_joltShape)
        qWarning() << "AbstractShape::updateJoltShapeDensity: Cannot set density on non-convex shape";
}
