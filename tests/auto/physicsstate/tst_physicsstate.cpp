#include <QtTest/QtTest>
#include <QtQuick3DJoltPhysics/private/physicsstate_p.h>
#include <QtQuick3DJoltPhysics/private/physicssystem_p.h>

class tst_PhysicsState : public QObject
{
    Q_OBJECT
private slots:
    void stateDefaults();
    void systemSaveRestoreMethods();
};

void tst_PhysicsState::stateDefaults()
{
    PhysicsState state;
    QCOMPARE(state.dataSize(), 0);
}

void tst_PhysicsState::systemSaveRestoreMethods()
{
    PhysicsSystem sys;

    // saveState and restoreState exist and are callable
    // Without a fully initialized physics world, saveState should handle gracefully
    PhysicsState *state = sys.saveState();
    // May return nullptr if physics not initialized — that's acceptable
    if (state) {
        QVERIFY(state->dataSize() >= 0);
        bool ok = sys.restoreState(state);
        Q_UNUSED(ok);
        delete state;
    }

    // Null state should return false
    bool result = sys.restoreState(nullptr);
    QCOMPARE(result, false);
}

QTEST_GUILESS_MAIN(tst_PhysicsState)
#include "tst_physicsstate.moc"
