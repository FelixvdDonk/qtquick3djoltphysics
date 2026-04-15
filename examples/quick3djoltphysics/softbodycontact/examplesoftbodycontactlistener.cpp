#include "examplesoftbodycontactlistener.h"

ExampleSoftBodyContactListener::ExampleSoftBodyContactListener(QObject *parent)
    : AbstractSoftBodyContactListener(parent)
{
}

AbstractSoftBodyContactListener::ValidateResult
ExampleSoftBodyContactListener::softBodyContactValidate(quint32, quint32)
{
    return ValidateResult::AcceptContact;
}

void ExampleSoftBodyContactListener::softBodyContactAdded(quint32, int numVerticesInContact)
{
    m_contactCount++;
    m_lastVerticesInContact = numVerticesInContact;
    // Note: called on physics thread. Values polled from QML via Timer.
}
