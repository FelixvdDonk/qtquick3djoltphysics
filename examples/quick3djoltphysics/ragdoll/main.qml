import QtQuick
import QtQuick.Controls
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick3D.JoltPhysics
import Example

Window {
    width: 900
    height: 700
    visible: true
    title: qsTr("Qt Quick 3D Jolt Physics - Ragdoll")

    readonly property int nonMoving: 0
    readonly property int moving: 1

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

        HumanoidRagdoll {
            id: ragdoll
            movingLayer: moving
        }
    }

    // UI overlay
    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 8

        Label { text: "Ragdoll Demo"; font.bold: true; color: "white" }

        Row {
            spacing: 8
            Button {
                text: "Drop"
                onClicked: ragdoll.ragdollBody.addToPhysicsSystem()
            }
            Button {
                text: "T-Pose"
                onClicked: ragdoll.ragdollBody.driveToPose({})
            }
            Button {
                text: "Remove"
                onClicked: ragdoll.ragdollBody.removeFromPhysicsSystem()
            }
        }

        Label {
            id: jointInfo
            color: "white"
            text: "Joints: " + ragdoll.ragdollBody.getJointCount()
        }
    }
}
