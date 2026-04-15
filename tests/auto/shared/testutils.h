#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <QtQuick3DJoltPhysics/physicslayers.h>

// Minimal object layer pair filter for tests
class TestObjectLayerPairFilter : public AbstractObjectLayerPairFilter
{
    Q_OBJECT
public:
    TestObjectLayerPairFilter(QObject *parent = nullptr) : AbstractObjectLayerPairFilter(parent) {}
    bool shouldCollide(quint16 /*obj1*/, quint16 /*obj2*/) const override { return true; }
};

// Minimal broad phase layer for tests
class TestBroadPhaseLayer : public AbstractBroadPhaseLayer
{
    Q_OBJECT
public:
    TestBroadPhaseLayer(QObject *parent = nullptr) : AbstractBroadPhaseLayer(parent)
    {
        m_objectToBroadPhase[0] = 0;
        m_objectToBroadPhase[1] = 1;
    }
    unsigned int getNumBroadPhaseLayers() const override { return 2; }
    quint8 getBroadPhaseLayer(quint16 layer) const override
    {
        if (layer < 2) return m_objectToBroadPhase[layer];
        return 0;
    }
private:
    quint8 m_objectToBroadPhase[2];
};

// Minimal object vs broad phase layer filter for tests
class TestObjectVsBroadPhaseLayerFilter : public AbstractObjectVsBroadPhaseLayerFilter
{
    Q_OBJECT
public:
    TestObjectVsBroadPhaseLayerFilter(QObject *parent = nullptr) : AbstractObjectVsBroadPhaseLayerFilter(parent) {}
    bool shouldCollide(quint16 /*layer1*/, quint8 /*layer2*/) const override { return true; }
};

#endif // TESTUTILS_H
