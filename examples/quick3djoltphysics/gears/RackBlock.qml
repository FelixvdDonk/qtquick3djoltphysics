import QtQuick
import QtQuick3D
import QtQuick3D.JoltPhysics

Node {
    id: root
    required property int movingLayer
    property alias block: blockBody

    property vector3d blockPosition: Qt.vector3d(0, 0, 0)

    Body {
        id: blockBody
        position: root.blockPosition
        shape: BoxShape { extents: Qt.vector3d(60, 20, 20) }
        objectLayer: root.movingLayer
        motionType: Body.Dynamic
        Model {
            source: "#Cube"
            scale: Qt.vector3d(0.6, 0.2, 0.2)
            materials: PrincipledMaterial { baseColor: "#2ecc71" }
        }
    }
}
