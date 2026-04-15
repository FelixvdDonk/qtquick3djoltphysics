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
    title: qsTr("Qt Quick 3D Jolt Physics - Motor Joints")

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
            position: Qt.vector3d(0, 200, 600)
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

        // Motorized hinge arm
        MotorArm {
            id: motorArm
            position: Qt.vector3d(-150, 0, 0)
            movingLayer: moving
            targetAngle: hingeSlider.value
        }

        // Motorized slider rail
        SliderRail {
            id: sliderRail
            position: Qt.vector3d(0, -30, 0)
            movingLayer: moving
            targetPosition: positionSlider.value
        }
    }

    // UI overlay
    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 8

        Label {
            text: "Hinge Motor"
            font.bold: true
            color: "white"
        }

        Row {
            spacing: 8
            Label { text: "Target Angle:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider {
                id: hingeSlider
                from: -90
                to: 90
                value: 0
                width: 200
            }
            Label {
                text: hingeSlider.value.toFixed(1) + "°"
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Item { width: 1; height: 10 }

        Label {
            text: "Slider Motor"
            font.bold: true
            color: "white"
        }

        Row {
            spacing: 8
            Label { text: "Target Position:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider {
                id: positionSlider
                from: -150
                to: 150
                value: 0
                width: 200
            }
            Label {
                text: positionSlider.value.toFixed(1) + " cm"
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
