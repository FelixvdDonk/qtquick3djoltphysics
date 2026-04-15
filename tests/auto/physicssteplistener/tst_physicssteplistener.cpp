#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/abstractphysicssteplistener_p.h>
#include <QtQuick3DJoltPhysics/private/physicssystem_p.h>

class TestStepListener : public AbstractPhysicsStepListener
{
    Q_OBJECT
public:
    TestStepListener(QObject *parent = nullptr) : AbstractPhysicsStepListener(parent) {}

    int stepCount = 0;
    float lastDeltaTime = 0.0f;

    void onStep(float deltaTime, PhysicsSystem *) override
    {
        ++stepCount;
        lastDeltaTime = deltaTime;
    }
};

class tst_PhysicsStepListener : public QObject
{
    Q_OBJECT
private slots:
    void listenerCreation();
    void stepListenersListProperty();
};

void tst_PhysicsStepListener::listenerCreation()
{
    TestStepListener listener;
    QCOMPARE(listener.stepCount, 0);
    QCOMPARE(listener.lastDeltaTime, 0.0f);
}

void tst_PhysicsStepListener::stepListenersListProperty()
{
    PhysicsSystem sys;

    auto list = sys.stepListeners();
    QCOMPARE(list.count(&list), 0);

    auto *l1 = new TestStepListener(&sys);
    auto *l2 = new TestStepListener(&sys);

    list.append(&list, l1);
    list.append(&list, l2);
    QCOMPARE(list.count(&list), 2);
    QCOMPARE(list.at(&list, 0), l1);
    QCOMPARE(list.at(&list, 1), l2);
}

QTEST_GUILESS_MAIN(tst_PhysicsStepListener)
#include "tst_physicssteplistener.moc"
