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
    title: qsTr("Qt Quick 3D Jolt Physics - Soft Body")

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
            position: Qt.vector3d(0, 150, 400)
            eulerRotation: Qt.vector3d(-10, 0, 0)
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

        SoftCube {
            id: softCube
            cubePosition: Qt.vector3d(0, 200, 0)
            cubeSize: 50
            movingLayer: moving
            initialPressure: pressureSlider.value
            initialNumIterations: iterSlider.value
        }
    }

    // UI overlay
    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 6

        Label { text: "Soft Body"; font.bold: true; color: "white" }

        Row {
            spacing: 8
            Label { text: "Pressure:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider {
                id: pressureSlider; from: 0; to: 5.0; value: 1.0; width: 200
                onValueChanged: if (softCube.softBody) softCube.softBody.setPressureRuntime(value)
            }
            Label { text: pressureSlider.value.toFixed(2); color: "white"; anchors.verticalCenter: parent.verticalCenter }
        }

        Row {
            spacing: 8
            Label { text: "Iterations:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider {
                id: iterSlider; from: 1; to: 20; value: 5; stepSize: 1; width: 200
                onValueChanged: if (softCube.softBody) softCube.softBody.setNumIterationsRuntime(value)
            }
            Label { text: iterSlider.value.toFixed(0); color: "white"; anchors.verticalCenter: parent.verticalCenter }
        }

        Label {
            id: readback
            color: "white"
            Timer {
                interval: 100; running: true; repeat: true
                onTriggered: {
                    if (softCube.softBody) {
                        readback.text = "Vertices: " + softCube.softBody.getNumVertices()
                            + "  Volume: " + softCube.softBody.getVolume().toFixed(1)
                    }
                }
            }
        }
    }
}
