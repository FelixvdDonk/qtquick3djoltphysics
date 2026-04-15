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
    title: qsTr("Qt Quick 3D Jolt Physics - Pulley Constraint")

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

        // Ceiling bar
        Body {
            id: ceiling
            position: Qt.vector3d(0, 400, 0)
            shape: BoxShape { extents: Qt.vector3d(300, 10, 20) }
            objectLayer: nonMoving
            motionType: Body.Static
            Model {
                source: "#Cube"
                scale: Qt.vector3d(3, 0.1, 0.2)
                materials: PrincipledMaterial { baseColor: "#7f8c8d" }
            }
        }

        // Weight 1 (heavy)
        Body {
            id: weight1
            position: Qt.vector3d(-100, 250, 0)
            shape: BoxShape { extents: Qt.vector3d(50, 50, 50) }
            objectLayer: moving
            motionType: Body.Dynamic
            overrideMassProperties: Body.CalculateInertia
            mass: 20
            Model {
                source: "#Cube"
                scale: Qt.vector3d(0.5, 0.5, 0.5)
                materials: PrincipledMaterial { baseColor: "#e74c3c" }
            }
        }

        // Weight 2 (light)
        Body {
            id: weight2
            position: Qt.vector3d(100, 250, 0)
            shape: BoxShape { extents: Qt.vector3d(30, 30, 30) }
            objectLayer: moving
            motionType: Body.Dynamic
            Model {
                source: "#Cube"
                scale: Qt.vector3d(0.3, 0.3, 0.3)
                materials: PrincipledMaterial { baseColor: "#3498db" }
            }
        }

        PulleyConstraint {
            id: pulley
            body1: weight1
            body2: weight2
            bodyPoint1: Qt.vector3d(0, 25, 0)
            fixedPoint1: Qt.vector3d(-100, 400, 0)
            bodyPoint2: Qt.vector3d(0, 15, 0)
            fixedPoint2: Qt.vector3d(100, 400, 0)
            ratio: ratioSlider.value
            minLength: minLenSlider.value
            maxLength: maxLenSlider.value
        }
    }

    // UI overlay
    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 6

        Label { text: "Pulley Constraint"; font.bold: true; color: "white" }

        Row {
            spacing: 8
            Label { text: "Ratio:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider { id: ratioSlider; from: 0.5; to: 3.0; value: 1.0; width: 200 }
            Label { text: ratioSlider.value.toFixed(1); color: "white"; anchors.verticalCenter: parent.verticalCenter }
        }

        Row {
            spacing: 8
            Label { text: "Min Length:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider { id: minLenSlider; from: 0; to: 200; value: 0; width: 200 }
            Label { text: minLenSlider.value.toFixed(0) + " cm"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
        }

        Row {
            spacing: 8
            Label { text: "Max Length:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider { id: maxLenSlider; from: 100; to: 600; value: 400; width: 200 }
            Label { text: maxLenSlider.value.toFixed(0) + " cm"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
        }
    }
}
