import QtQuick
import QtQuick.Controls
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick3D.JoltPhysics
import Example

Window {
    width: 900
    height: 600
    visible: true
    title: qsTr("Qt Quick 3D Jolt Physics - Gears & Rack-and-Pinion")

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
            position: Qt.vector3d(0, 100, 600)
            eulerRotation: Qt.vector3d(-5, 0, 0)
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

        // ---- Gear train ----

        // Left post (static mount for gear 1)
        Body {
            id: gearPost1
            position: Qt.vector3d(-100, 150, 0)
            shape: BoxShape { extents: Qt.vector3d(10, 10, 10) }
            objectLayer: nonMoving
            motionType: Body.Static
        }

        // Gear disc 1 (large, driven)
        GearDisc {
            id: gear1
            discPosition: Qt.vector3d(-100, 150, 0)
            discRadius: 60
            discThickness: 15
            discColor: "#e74c3c"
            movingLayer: moving
        }

        // Left hinge
        HingeConstraint {
            id: hinge1
            body1: gearPost1
            body2: gear1.disc
            point1: Qt.vector3d(0, 0, 0)
            point2: Qt.vector3d(0, 0, 0)
            hingeAxis1: Qt.vector3d(0, 0, 1)
            hingeAxis2: Qt.vector3d(0, 0, 1)
            normalAxis1: Qt.vector3d(1, 0, 0)
            normalAxis2: Qt.vector3d(1, 0, 0)
            motorState: HingeConstraint.Velocity
            targetAngularVelocity: velocitySlider.value
            motorSettings: MotorSettings {
                springFrequency: 2.0
                springDamping: 1.0
                maxTorqueLimit: 50000
                minTorqueLimit: -50000
            }
        }

        // Right post (static mount for gear 2)
        Body {
            id: gearPost2
            position: Qt.vector3d(100, 150, 0)
            shape: BoxShape { extents: Qt.vector3d(10, 10, 10) }
            objectLayer: nonMoving
            motionType: Body.Static
        }

        // Gear disc 2 (small, driven by gear constraint)
        GearDisc {
            id: gear2
            discPosition: Qt.vector3d(100, 150, 0)
            discRadius: 30
            discThickness: 15
            discColor: "#3498db"
            movingLayer: moving
        }

        // Right hinge
        HingeConstraint {
            id: hinge2
            body1: gearPost2
            body2: gear2.disc
            point1: Qt.vector3d(0, 0, 0)
            point2: Qt.vector3d(0, 0, 0)
            hingeAxis1: Qt.vector3d(0, 0, 1)
            hingeAxis2: Qt.vector3d(0, 0, 1)
            normalAxis1: Qt.vector3d(1, 0, 0)
            normalAxis2: Qt.vector3d(1, 0, 0)
        }

        // Gear constraint: 2:1 ratio
        GearConstraint {
            body1: gear1.disc
            body2: gear2.disc
            hingeAxis1: Qt.vector3d(0, 0, 1)
            hingeAxis2: Qt.vector3d(0, 0, 1)
            ratio: gearRatioSlider.value
            gear1Constraint: hinge1
            gear2Constraint: hinge2
        }

        // ---- Rack and Pinion ----

        // Pinion post
        Body {
            id: pinionPost
            position: Qt.vector3d(-100, -20, 0)
            shape: BoxShape { extents: Qt.vector3d(10, 10, 10) }
            objectLayer: nonMoving
            motionType: Body.Static
        }

        // Pinion disc
        GearDisc {
            id: pinion
            discPosition: Qt.vector3d(-100, -20, 0)
            discRadius: 30
            discThickness: 15
            discColor: "#f39c12"
            movingLayer: moving
        }

        HingeConstraint {
            id: pinionHinge
            body1: pinionPost
            body2: pinion.disc
            point1: Qt.vector3d(0, 0, 0)
            point2: Qt.vector3d(0, 0, 0)
            hingeAxis1: Qt.vector3d(0, 0, 1)
            hingeAxis2: Qt.vector3d(0, 0, 1)
            normalAxis1: Qt.vector3d(1, 0, 0)
            normalAxis2: Qt.vector3d(1, 0, 0)
            motorState: HingeConstraint.Velocity
            targetAngularVelocity: velocitySlider.value
            motorSettings: MotorSettings {
                springFrequency: 2.0
                springDamping: 1.0
                maxTorqueLimit: 50000
                minTorqueLimit: -50000
            }
        }

        // Rack (slider body)
        RackBlock {
            id: rack
            blockPosition: Qt.vector3d(0, -60, 0)
            movingLayer: moving
        }

        // Rack slider rail
        Body {
            id: rackRail
            position: Qt.vector3d(0, -60, 0)
            shape: BoxShape { extents: Qt.vector3d(10, 10, 10) }
            objectLayer: nonMoving
            motionType: Body.Static
        }

        SliderConstraint {
            id: rackSlider
            body1: rackRail
            body2: rack.block
            point1: Qt.vector3d(0, 0, 0)
            point2: Qt.vector3d(0, 0, 0)
            sliderAxis1: Qt.vector3d(1, 0, 0)
            sliderAxis2: Qt.vector3d(1, 0, 0)
            normalAxis1: Qt.vector3d(0, 1, 0)
            normalAxis2: Qt.vector3d(0, 1, 0)
            limitsMin: -200
            limitsMax: 200
        }

        RackAndPinionConstraint {
            body1: pinion.disc
            body2: rack.block
            hingeAxis: Qt.vector3d(0, 0, 1)
            sliderAxis: Qt.vector3d(1, 0, 0)
            ratio: 10
            pinionConstraint: pinionHinge
            rackConstraint: rackSlider
        }
    }

    // UI overlay
    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 6

        Label { text: "Gears & Rack-and-Pinion"; font.bold: true; color: "white" }

        Row {
            spacing: 8
            Label { text: "Motor Velocity:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider { id: velocitySlider; from: -360; to: 360; value: 90; width: 200 }
            Label { text: velocitySlider.value.toFixed(0) + "°/s"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
        }

        Row {
            spacing: 8
            Label { text: "Gear Ratio:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider { id: gearRatioSlider; from: 0.5; to: 4.0; value: 2.0; width: 200 }
            Label { text: gearRatioSlider.value.toFixed(1); color: "white"; anchors.verticalCenter: parent.verticalCenter }
        }
    }
}
