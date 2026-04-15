#ifndef EXAMPLESOFTBODYCONTACTLISTENER_H
#define EXAMPLESOFTBODYCONTACTLISTENER_H

#include <abstractsoftbodycontactlistener.h>
#include <QObject>
#include <QtQml/QQmlEngine>

class ExampleSoftBodyContactListener : public AbstractSoftBodyContactListener
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ExampleSoftBodyContactListener)
    Q_PROPERTY(int contactCount READ contactCount NOTIFY contactCountChanged)
    Q_PROPERTY(int lastVerticesInContact READ lastVerticesInContact NOTIFY lastVerticesInContactChanged)

public:
    explicit ExampleSoftBodyContactListener(QObject *parent = nullptr);

    int contactCount() const { return m_contactCount; }
    int lastVerticesInContact() const { return m_lastVerticesInContact; }

    ValidateResult softBodyContactValidate(quint32 softBodyID, quint32 otherBodyID) override;
    void softBodyContactAdded(quint32 softBodyID, int numVerticesInContact) override;

signals:
    void contactCountChanged();
    void lastVerticesInContactChanged();

private:
    int m_contactCount = 0;
    int m_lastVerticesInContact = 0;
};

#endif // EXAMPLESOFTBODYCONTACTLISTENER_H
