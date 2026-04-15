import QtQuick
import QtQuick.Controls
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick3D.JoltPhysics
import Example

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Qt Quick 3D Jolt Physics - Save & Restore State")

    readonly property int nonMoving: 0
    readonly property int moving: 1
    property var savedState: null

    PhysicsSystem {
        id: physicsSystem
        scene: viewport.scene
        running: true
        gravity: Qt.vector3d(0, -981, 0)
        objectLayerPairFilter: ExampleObjectLayerPairFilter {}
        broadPhaseLayer: ExampleBroadPhaseLayer {}
        objectVsBroadPhaseLayerFilter: ExampleObjectVsBroadPhaseLayerFilter {}
    }

    View3D {
        id: viewport
        anchors.fill: parent

        environment: SceneEnvironment {
            clearColor: "#d6dbdf"
            backgroundMode: SceneEnvironment.Color
        }

        PerspectiveCamera {
            id: camera
            position: Qt.vector3d(0, 200, 500)
            eulerRotation: Qt.vector3d(-15, 0, 0)
            clipFar: 5000
            clipNear: 1
        }

        DirectionalLight {
            eulerRotation.x: -45
            eulerRotation.y: -45
            castsShadow: true
            brightness: 1
            shadowFactor: 50
        }

        // Floor
        Body {
            position: Qt.vector3d(0, -50, 0)
            eulerRotation: Qt.vector3d(-90, 0, 0)
            shape: PlaneShape { extent: 2000 }
            objectLayer: nonMoving
            motionType: Body.Static
            Model {
                source: "#Rectangle"
                scale: Qt.vector3d(20, 20, 1)
                materials: DefaultMaterial { diffuseColor: "#27ae60" }
                castsShadows: false
                receivesShadows: true
            }
        }

        // Stack of boxes
        Repeater3D {
            model: 5
            Body {
                position: Qt.vector3d(0, 25 + index * 55, 0)
                shape: BoxShape { extents: Qt.vector3d(50, 50, 50) }
                objectLayer: moving
                motionType: Body.Dynamic
                Model {
                    source: "#Cube"
                    scale: Qt.vector3d(0.5, 0.5, 0.5)
                    materials: PrincipledMaterial {
                        baseColor: ["#e74c3c", "#3498db", "#2ecc71", "#f39c12", "#9b59b6"][index]
                    }
                }
            }
        }

        // Projectile sphere
        Body {
            id: ball
            position: Qt.vector3d(-300, 80, 0)
            shape: SphereShape { diameter: 30 }
            objectLayer: moving
            motionType: Body.Dynamic
            Model {
                source: "#Sphere"
                scale: Qt.vector3d(0.3, 0.3, 0.3)
                materials: PrincipledMaterial { baseColor: "#e67e22" }
            }
        }
    }

    // UI overlay
    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 8

        Label { text: "State Save & Restore"; font.bold: true; color: "white" }

        Row {
            spacing: 8
            Button {
                text: "Save State"
                onClicked: {
                    savedState = physicsSystem.saveState()
                    stateInfo.text = "Saved: " + savedState.dataSize + " bytes"
                }
            }
            Button {
                text: "Restore State"
                enabled: savedState !== null
                onClicked: {
                    var ok = physicsSystem.restoreState(savedState)
                    stateInfo.text = "Restored: " + (ok ? "OK" : "FAILED")
                }
            }
        }

        Button {
            text: "Launch Ball"
            onClicked: {
                ball.position = Qt.vector3d(-300, 80, 0)
                ball.setLinearVelocity(Qt.vector3d(800, 200, 0))
            }
        }

        Label {
            id: stateInfo
            color: "white"
            text: "No state saved"
        }
    }
}
