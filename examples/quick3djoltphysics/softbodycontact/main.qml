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
    title: qsTr("Qt Quick 3D Jolt Physics - Soft Body Contact Listener")

    readonly property int nonMoving: 0
    readonly property int moving: 1

    ExampleSoftBodyContactListener {
        id: contactListener
    }

    PhysicsSystem {
        id: physicsSystem
        scene: viewport.scene
        running: true
        gravity: Qt.vector3d(0, -981, 0)
        objectLayerPairFilter: ExampleObjectLayerPairFilter {}
        broadPhaseLayer: ExampleBroadPhaseLayer {}
        objectVsBroadPhaseLayerFilter: ExampleObjectVsBroadPhaseLayerFilter {}
        softBodyContactListener: contactListener
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
            position: Qt.vector3d(0, 150, 400)
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

        // Floor - changes color on contact
        Body {
            id: floor
            position: Qt.vector3d(0, -50, 0)
            eulerRotation: Qt.vector3d(-90, 0, 0)
            shape: PlaneShape { extent: 2000 }
            objectLayer: nonMoving
            motionType: Body.Static
            Model {
                source: "#Rectangle"
                scale: Qt.vector3d(20, 20, 1)
                materials: DefaultMaterial {
                    diffuseColor: contactListener.contactCount > 0 ? "#e74c3c" : "#27ae60"
                }
                castsShadows: false
                receivesShadows: true
            }
        }

        // Soft cube falling onto the floor
        SoftBodySharedSettings {
            id: cubeSettings
            autoCreateConstraints: true
            edgeCompliance: 0.0
            bendCompliance: 0.001
        }

        SoftBody {
            id: softCube
            sharedSettings: cubeSettings
            objectLayer: moving
            numIterations: 5
            pressure: 1.0
            linearDamping: 0.1
            position: Qt.vector3d(0, 200, 0)
        }
    }

    Component.onCompleted: {
        cubeSettings.addVertex(Qt.vector3d(-1, -1, -1), 1.0)
        cubeSettings.addVertex(Qt.vector3d( 1, -1, -1), 1.0)
        cubeSettings.addVertex(Qt.vector3d( 1,  1, -1), 1.0)
        cubeSettings.addVertex(Qt.vector3d(-1,  1, -1), 1.0)
        cubeSettings.addVertex(Qt.vector3d(-1, -1,  1), 1.0)
        cubeSettings.addVertex(Qt.vector3d( 1, -1,  1), 1.0)
        cubeSettings.addVertex(Qt.vector3d( 1,  1,  1), 1.0)
        cubeSettings.addVertex(Qt.vector3d(-1,  1,  1), 1.0)

        cubeSettings.addFace(4, 5, 6)
        cubeSettings.addFace(4, 6, 7)
        cubeSettings.addFace(1, 0, 3)
        cubeSettings.addFace(1, 3, 2)
        cubeSettings.addFace(3, 7, 6)
        cubeSettings.addFace(3, 6, 2)
        cubeSettings.addFace(0, 1, 5)
        cubeSettings.addFace(0, 5, 4)
        cubeSettings.addFace(1, 2, 6)
        cubeSettings.addFace(1, 6, 5)
        cubeSettings.addFace(0, 4, 7)
        cubeSettings.addFace(0, 7, 3)
    }

    // UI overlay
    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 6

        Label { text: "Soft Body Contact Listener"; font.bold: true; color: "white" }

        Label {
            color: "white"
            text: "Contact count: " + contactListener.contactCount
        }

        Label {
            color: "white"
            text: "Last vertices in contact: " + contactListener.lastVerticesInContact
        }

        Label {
            color: "white"
            text: contactListener.contactCount > 0
                  ? "Floor changed to RED on contact!"
                  : "Waiting for soft body to hit floor..."
        }
    }
}
