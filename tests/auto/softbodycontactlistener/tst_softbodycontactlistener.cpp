#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/abstractsoftbodycontactlistener.h>
#include <QtQuick3DJoltPhysics/private/physicssystem_p.h>

class TestSoftBodyContactListener : public AbstractSoftBodyContactListener
{
    Q_OBJECT
public:
    TestSoftBodyContactListener(QObject *parent = nullptr)
        : AbstractSoftBodyContactListener(parent) {}

    int validateCount = 0;
    int addedCount = 0;
    quint32 lastSoftBodyID = 0;
    quint32 lastOtherBodyID = 0;

    ValidateResult softBodyContactValidate(quint32 softBodyID, quint32 otherBodyID) override
    {
        ++validateCount;
        lastSoftBodyID = softBodyID;
        lastOtherBodyID = otherBodyID;
        return ValidateResult::AcceptContact;
    }

    void softBodyContactAdded(quint32 softBodyID, int numVerticesInContact) override
    {
        ++addedCount;
        lastSoftBodyID = softBodyID;
        Q_UNUSED(numVerticesInContact);
    }
};

class tst_SoftBodyContactListener : public QObject
{
    Q_OBJECT
private slots:
    void subclassCreation();
    void systemProperty();
    void validateResultEnum();
};

void tst_SoftBodyContactListener::subclassCreation()
{
    TestSoftBodyContactListener listener;
    QCOMPARE(listener.validateCount, 0);
    QCOMPARE(listener.addedCount, 0);

    // Test that the virtual interface works
    auto result = listener.softBodyContactValidate(1, 2);
    QCOMPARE(result, AbstractSoftBodyContactListener::ValidateResult::AcceptContact);
    QCOMPARE(listener.validateCount, 1);
    QCOMPARE(listener.lastSoftBodyID, 1u);
    QCOMPARE(listener.lastOtherBodyID, 2u);

    listener.softBodyContactAdded(3, 5);
    QCOMPARE(listener.addedCount, 1);
    QCOMPARE(listener.lastSoftBodyID, 3u);
}

void tst_SoftBodyContactListener::systemProperty()
{
    PhysicsSystem sys;
    QSignalSpy spy(&sys, &PhysicsSystem::softBodyContactListenerChanged);

    auto *listener = new TestSoftBodyContactListener(&sys);
    sys.setSoftBodyContactListener(listener);
    QCOMPARE(sys.softBodyContactListener(), listener);
    QCOMPARE(spy.count(), 1);

    // Same pointer
    sys.setSoftBodyContactListener(listener);
    QCOMPARE(spy.count(), 1);
}

void tst_SoftBodyContactListener::validateResultEnum()
{
    // Ensure enum values match Jolt semantics
    QCOMPARE(static_cast<int>(AbstractSoftBodyContactListener::ValidateResult::AcceptContact), 0);
    QCOMPARE(static_cast<int>(AbstractSoftBodyContactListener::ValidateResult::RejectContact), 1);
}

QTEST_GUILESS_MAIN(tst_SoftBodyContactListener)
#include "tst_softbodycontactlistener.moc"
