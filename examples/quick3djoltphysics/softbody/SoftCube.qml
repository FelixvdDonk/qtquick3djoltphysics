import QtQuick
import QtQuick3D
import QtQuick3D.JoltPhysics

Node {
    id: root
    required property int movingLayer
    property alias softBody: softBodyItem

    property vector3d cubePosition: Qt.vector3d(0, 200, 0)
    property real cubeSize: 50
    property real initialPressure: 1.0
    property int initialNumIterations: 5

    SoftBodySharedSettings {
        id: cubeSettings
        autoCreateConstraints: true
        edgeCompliance: 0.0
        bendCompliance: 0.001
    }

    SoftBody {
        id: softBodyItem
        sharedSettings: cubeSettings
        objectLayer: root.movingLayer
        numIterations: root.initialNumIterations
        pressure: root.initialPressure
        linearDamping: 0.1
        position: root.cubePosition
    }

    Component.onCompleted: {
        // 8 cube vertices (unit cube corners)
        cubeSettings.addVertex(Qt.vector3d(-1, -1, -1), 1.0)
        cubeSettings.addVertex(Qt.vector3d( 1, -1, -1), 1.0)
        cubeSettings.addVertex(Qt.vector3d( 1,  1, -1), 1.0)
        cubeSettings.addVertex(Qt.vector3d(-1,  1, -1), 1.0)
        cubeSettings.addVertex(Qt.vector3d(-1, -1,  1), 1.0)
        cubeSettings.addVertex(Qt.vector3d( 1, -1,  1), 1.0)
        cubeSettings.addVertex(Qt.vector3d( 1,  1,  1), 1.0)
        cubeSettings.addVertex(Qt.vector3d(-1,  1,  1), 1.0)

        // 12 triangles (2 per face, CCW winding)
        cubeSettings.addFace(4, 5, 6)  // front
        cubeSettings.addFace(4, 6, 7)
        cubeSettings.addFace(1, 0, 3)  // back
        cubeSettings.addFace(1, 3, 2)
        cubeSettings.addFace(3, 7, 6)  // top
        cubeSettings.addFace(3, 6, 2)
        cubeSettings.addFace(0, 1, 5)  // bottom
        cubeSettings.addFace(0, 5, 4)
        cubeSettings.addFace(1, 2, 6)  // right
        cubeSettings.addFace(1, 6, 5)
        cubeSettings.addFace(0, 4, 7)  // left
        cubeSettings.addFace(0, 7, 3)
    }
}
