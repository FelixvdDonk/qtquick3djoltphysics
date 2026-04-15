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
    title: qsTr("Qt Quick 3D Jolt Physics - Swing Twist Constraint")

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
            position: Qt.vector3d(0, 150, 500)
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

        // Static anchor post
        Body {
            id: post
            position: Qt.vector3d(0, 200, 0)
            shape: BoxShape { extents: Qt.vector3d(20, 20, 20) }
            objectLayer: nonMoving
            motionType: Body.Static
            Model {
                source: "#Cube"
                scale: Qt.vector3d(0.2, 0.2, 0.2)
                materials: PrincipledMaterial { baseColor: "#555555" }
            }
        }

        // Dynamic arm attached via swing-twist
        Body {
            id: arm
            position: Qt.vector3d(0, 100, 0)
            shape: CapsuleShape { diameter: 20; height: 150 }
            objectLayer: moving
            motionType: Body.Dynamic
            Model {
                source: "#Cylinder"
                scale: Qt.vector3d(0.2, 1.5, 0.2)
                materials: PrincipledMaterial { baseColor: "#e74c3c" }
            }
        }

        SwingTwistConstraint {
            id: stConstraint
            body1: post
            body2: arm
            position1: Qt.vector3d(0, 0, 0)
            position2: Qt.vector3d(0, 75, 0)
            twistAxis1: Qt.vector3d(0, -1, 0)
            twistAxis2: Qt.vector3d(0, -1, 0)
            planeAxis1: Qt.vector3d(1, 0, 0)
            planeAxis2: Qt.vector3d(1, 0, 0)
            normalHalfConeAngle: normalSlider.value
            planeHalfConeAngle: planeSlider.value
            twistMinAngle: -twistSlider.value
            twistMaxAngle: twistSlider.value
            swingMotorSettings: MotorSettings {
                springFrequency: 2.0
                springDamping: 1.0
                maxTorqueLimit: 10000
                minTorqueLimit: -10000
            }
            twistMotorSettings: MotorSettings {
                springFrequency: 2.0
                springDamping: 1.0
                maxTorqueLimit: 10000
                minTorqueLimit: -10000
            }
            swingMotorState: swingMotorCheck.checked ? SwingTwistConstraint.Position : SwingTwistConstraint.Off
            twistMotorState: twistMotorCheck.checked ? SwingTwistConstraint.Velocity : SwingTwistConstraint.Off
            targetAngularVelocityCS: Qt.vector3d(0, twistVelSlider.value, 0)
        }
    }

    // UI overlay
    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 6

        Label { text: "Swing-Twist Constraint"; font.bold: true; color: "white" }

        Row {
            spacing: 8
            Label { text: "Normal Half Cone:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider { id: normalSlider; from: 5; to: 85; value: 45; width: 150 }
            Label { text: normalSlider.value.toFixed(0) + "°"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
        }

        Row {
            spacing: 8
            Label { text: "Plane Half Cone:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider { id: planeSlider; from: 5; to: 85; value: 45; width: 150 }
            Label { text: planeSlider.value.toFixed(0) + "°"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
        }

        Row {
            spacing: 8
            Label { text: "Twist Range:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider { id: twistSlider; from: 0; to: 180; value: 60; width: 150 }
            Label { text: "±" + twistSlider.value.toFixed(0) + "°"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
        }

        Row {
            spacing: 8
            CheckBox { id: swingMotorCheck; text: "Swing Motor"; checked: false }
            CheckBox { id: twistMotorCheck; text: "Twist Motor"; checked: false }
        }

        Row {
            spacing: 8
            visible: twistMotorCheck.checked
            Label { text: "Twist Velocity:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider { id: twistVelSlider; from: -360; to: 360; value: 90; width: 150 }
            Label { text: twistVelSlider.value.toFixed(0) + "°/s"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
        }
    }
}
