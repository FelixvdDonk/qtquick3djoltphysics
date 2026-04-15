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
    title: qsTr("Qt Quick 3D Jolt Physics - Cone Constraint")

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
            position: Qt.vector3d(0, 250, 500)
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

        // Static anchor
        Body {
            id: anchor
            position: Qt.vector3d(0, 300, 0)
            shape: SphereShape { diameter: 20 }
            objectLayer: nonMoving
            motionType: Body.Static
            Model {
                source: "#Sphere"
                scale: Qt.vector3d(0.2, 0.2, 0.2)
                materials: PrincipledMaterial { baseColor: "#555555" }
            }
        }

        // Pendulum bob
        Body {
            id: bob
            position: Qt.vector3d(80, 150, 0)
            shape: SphereShape { diameter: 40 }
            objectLayer: moving
            motionType: Body.Dynamic
            Model {
                source: "#Sphere"
                scale: Qt.vector3d(0.4, 0.4, 0.4)
                materials: PrincipledMaterial { baseColor: "#3498db" }
            }
        }

        ConeConstraint {
            id: coneConstraint
            body1: anchor
            body2: bob
            point1: Qt.vector3d(0, 0, 0)
            point2: Qt.vector3d(0, 0, 0)
            twistAxis1: Qt.vector3d(0, -1, 0)
            twistAxis2: Qt.vector3d(0, -1, 0)
            halfConeAngle: coneSlider.value
        }
    }

    // UI overlay
    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 6

        Label { text: "Cone Constraint"; font.bold: true; color: "white" }

        Row {
            spacing: 8
            Label { text: "Half Cone Angle:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider { id: coneSlider; from: 5; to: 85; value: 45; width: 200 }
            Label { text: coneSlider.value.toFixed(0) + "°"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
        }
    }
}
