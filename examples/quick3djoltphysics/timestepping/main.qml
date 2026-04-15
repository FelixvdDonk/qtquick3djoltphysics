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
    title: qsTr("Qt Quick 3D Jolt Physics - Time Stepping")

    readonly property int nonMoving: 0
    readonly property int moving: 1

    PhysicsSystem {
        id: physicsSystem
        scene: viewport.scene
        running: runningCheck.checked
        gravity: Qt.vector3d(0, -981, 0)
        timeScale: timeScaleSlider.value
        fixedTimestep: fixedTimestepSlider.value / 1000.0
        maxSubSteps: maxSubStepsSlider.value
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
            position: Qt.vector3d(0, 300, 600)
            eulerRotation: Qt.vector3d(-20, 0, 0)
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

        // Row of falling spheres
        Repeater3D {
            model: 5
            Body {
                id: ball
                position: Qt.vector3d(-200 + index * 100, 400, 0)
                shape: SphereShape { diameter: 40 }
                objectLayer: moving
                motionType: Body.Dynamic
                Model {
                    source: "#Sphere"
                    scale: Qt.vector3d(0.4, 0.4, 0.4)
                    materials: PrincipledMaterial {
                        baseColor: ["#e74c3c", "#3498db", "#2ecc71", "#f39c12", "#9b59b6"][index]
                    }
                }
            }
        }
    }

    // UI overlay
    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 6

        Label { text: "Decoupled Time Stepping"; font.bold: true; color: "white" }

        Row {
            spacing: 8
            Label { text: "Time Scale:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider { id: timeScaleSlider; from: 0.1; to: 5.0; value: 1.0; width: 200 }
            Label { text: timeScaleSlider.value.toFixed(2) + "x"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
        }

        Row {
            spacing: 8
            Label { text: "Fixed Timestep:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider { id: fixedTimestepSlider; from: 1; to: 33; value: 16; stepSize: 1; width: 200 }
            Label { text: fixedTimestepSlider.value.toFixed(0) + " ms"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
        }

        Row {
            spacing: 8
            Label { text: "Max Sub-Steps:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider { id: maxSubStepsSlider; from: 1; to: 10; value: 4; stepSize: 1; width: 200 }
            Label { text: maxSubStepsSlider.value.toFixed(0); color: "white"; anchors.verticalCenter: parent.verticalCenter }
        }

        Row {
            spacing: 8
            CheckBox { id: runningCheck; text: "Running"; checked: true }
            Button {
                text: "Step Once"
                enabled: !runningCheck.checked
                onClicked: physicsSystem.stepPhysics(0.016)
            }
        }
    }
}
