#include <QQmlEngine>

#include "../shared/examplelayers.h"
#include "../shared/examplesensorcontactlistener.h"

static inline void registerSharedTypes()
{
    qmlRegisterType<ExampleObjectLayerPairFilter>("Example", 1, 0, "ExampleObjectLayerPairFilter");
    qmlRegisterType<ExampleBroadPhaseLayer>("Example", 1, 0, "ExampleBroadPhaseLayer");
    qmlRegisterType<ExampleObjectVsBroadPhaseLayerFilter>("Example", 1, 0, "ExampleObjectVsBroadPhaseLayerFilter");
    qmlRegisterType<ExampleSensorContactListener>("Example", 1, 0, "ExampleSensorContactListener");
}
