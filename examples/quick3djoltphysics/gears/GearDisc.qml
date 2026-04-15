import QtQuick
import QtQuick3D
import QtQuick3D.JoltPhysics

Node {
    id: root
    required property int movingLayer
    property alias disc: discBody

    property vector3d discPosition: Qt.vector3d(0, 0, 0)
    property real discRadius: 50
    property real discThickness: 15
    property color discColor: "#e74c3c"

    Body {
        id: discBody
        position: root.discPosition
        shape: CapsuleShape {
            diameter: root.discRadius * 2
            height: root.discThickness
        }
        objectLayer: root.movingLayer
        motionType: Body.Dynamic
        Model {
            source: "#Cylinder"
            scale: Qt.vector3d(root.discRadius / 50, root.discThickness / 100, root.discRadius / 50)
            materials: PrincipledMaterial { baseColor: root.discColor }
        }
    }
}
