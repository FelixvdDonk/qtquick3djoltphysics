import QtQuick
import QtQuick3D
import QtQuick3D.JoltPhysics

Node {
    id: root

    required property int movingLayer
    property alias targetAngle: hingeConstraint.targetAngle

    Body {
        id: post
        position: Qt.vector3d(0, 0, 0)
        shape: BoxShape { extents: Qt.vector3d(20, 200, 20) }
        objectLayer: root.movingLayer
        motionType: Body.Static
        Model {
            source: "#Cube"
            scale: Qt.vector3d(0.2, 2, 0.2)
            materials: PrincipledMaterial { baseColor: "#555555" }
        }
    }

    Body {
        id: arm
        position: Qt.vector3d(75, 100, 0)
        shape: BoxShape { extents: Qt.vector3d(150, 20, 20) }
        objectLayer: root.movingLayer
        motionType: Body.Dynamic
        Model {
            source: "#Cube"
            scale: Qt.vector3d(1.5, 0.2, 0.2)
            materials: PrincipledMaterial { baseColor: "#e74c3c" }
        }
    }

    HingeConstraint {
        id: hingeConstraint
        body1: post
        body2: arm
        point1: Qt.vector3d(0, 100, 0)
        point2: Qt.vector3d(-75, 0, 0)
        hingeAxis1: Qt.vector3d(0, 0, 1)
        hingeAxis2: Qt.vector3d(0, 0, 1)
        normalAxis1: Qt.vector3d(1, 0, 0)
        normalAxis2: Qt.vector3d(1, 0, 0)
        limitsMin: -90
        limitsMax: 90
        motorSettings: MotorSettings {
            springFrequency: 2.0
            springDamping: 1.0
            maxTorqueLimit: 10000
            minTorqueLimit: -10000
        }
        motorState: HingeConstraint.Position
        targetAngle: 0
    }
}
