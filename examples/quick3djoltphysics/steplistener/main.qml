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
    title: qsTr("Qt Quick 3D Jolt Physics - Step Listener")

    readonly property int nonMoving: 0
    readonly property int moving: 1

    ExampleStepListener {
        id: stepListener
    }

    PhysicsSystem {
        id: physicsSystem
        scene: viewport.scene
        running: true
        gravity: Qt.vector3d(0, -981, 0)
        objectLayerPairFilter: ExampleObjectLayerPairFilter {}
        broadPhaseLayer: ExampleBroadPhaseLayer {}
        objectVsBroadPhaseLayerFilter: ExampleObjectVsBroadPhaseLayerFilter {}
        stepListeners: [stepListener]
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
            position: Qt.vector3d(0, 200, 400)
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

        // Oscillating body - the step listener applies sinusoidal vertical force
        Body {
            id: oscillator
            position: Qt.vector3d(0, 100, 0)
            shape: SphereShape { diameter: 40 }
            objectLayer: moving
            motionType: Body.Dynamic
            gravityFactor: 0
            Model {
                source: "#Sphere"
                scale: Qt.vector3d(0.4, 0.4, 0.4)
                materials: PrincipledMaterial { baseColor: "#e74c3c" }
            }
        }
    }

    // Apply force from step listener data each frame
    Timer {
        interval: 16; running: true; repeat: true
        onTriggered: {
            oscillator.addForce(Qt.vector3d(0, stepListener.currentForce, 0))
        }
    }

    // UI overlay
    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 6

        Label { text: "Physics Step Listener"; font.bold: true; color: "white" }

        Label {
            color: "white"
            text: "Step count: " + stepListener.stepCount
        }

        Label {
            color: "white"
            text: "Current force: " + stepListener.currentForce.toFixed(0) + " N"
        }
    }
}
