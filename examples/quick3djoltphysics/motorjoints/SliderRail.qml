import QtQuick
import QtQuick3D
import QtQuick3D.JoltPhysics

Node {
    id: root

    required property int movingLayer
    property alias targetPosition: sliderConstraint.targetPosition

    Body {
        id: rail
        position: Qt.vector3d(0, 0, 0)
        shape: BoxShape { extents: Qt.vector3d(400, 10, 20) }
        objectLayer: root.movingLayer
        motionType: Body.Static
        Model {
            source: "#Cube"
            scale: Qt.vector3d(4, 0.1, 0.2)
            materials: PrincipledMaterial { baseColor: "#888888" }
        }
    }

    Body {
        id: block
        position: Qt.vector3d(0, 15, 0)
        shape: BoxShape { extents: Qt.vector3d(40, 30, 30) }
        objectLayer: root.movingLayer
        motionType: Body.Dynamic
        Model {
            source: "#Cube"
            scale: Qt.vector3d(0.4, 0.3, 0.3)
            materials: PrincipledMaterial { baseColor: "#3498db" }
        }
    }

    SliderConstraint {
        id: sliderConstraint
        body1: rail
        body2: block
        point1: Qt.vector3d(0, 15, 0)
        point2: Qt.vector3d(0, 0, 0)
        sliderAxis1: Qt.vector3d(1, 0, 0)
        sliderAxis2: Qt.vector3d(1, 0, 0)
        normalAxis1: Qt.vector3d(0, 1, 0)
        normalAxis2: Qt.vector3d(0, 1, 0)
        limitsMin: -180
        limitsMax: 180
        motorSettings: MotorSettings {
            springFrequency: 2.0
            springDamping: 1.0
            maxForceLimit: 50000
            minForceLimit: -50000
        }
        motorState: SliderConstraint.Position
        targetPosition: 0
    }
}
