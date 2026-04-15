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
    title: qsTr("Qt Quick 3D Jolt Physics - Path Constraint")

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

        // Visualize path control points
        Repeater3D {
            model: [
                Qt.vector3d(-200, 100, 0),
                Qt.vector3d(-100, 200, 150),
                Qt.vector3d(100, 200, 150),
                Qt.vector3d(200, 100, 0),
                Qt.vector3d(100, 200, -150),
                Qt.vector3d(-100, 200, -150)
            ]
            Model {
                source: "#Sphere"
                position: modelData
                scale: Qt.vector3d(0.08, 0.08, 0.08)
                materials: PrincipledMaterial { baseColor: "#95a5a6" }
            }
        }

        // Static world anchor for path
        Body {
            id: worldAnchor
            position: Qt.vector3d(0, 0, 0)
            shape: BoxShape { extents: Qt.vector3d(10, 10, 10) }
            objectLayer: nonMoving
            motionType: Body.Static
        }

        // Body following the path
        Body {
            id: follower
            position: Qt.vector3d(-200, 100, 0)
            shape: SphereShape { diameter: 30 }
            objectLayer: moving
            motionType: Body.Dynamic
            Model {
                source: "#Sphere"
                scale: Qt.vector3d(0.3, 0.3, 0.3)
                materials: PrincipledMaterial { baseColor: "#e74c3c" }
            }
        }

        HermitePath {
            id: ovalPath
            isLooping: loopCheck.checked

            HermitePathPoint {
                position: Qt.vector3d(-200, 100, 0)
                tangent: Qt.vector3d(0, 150, 200)
                normal: Qt.vector3d(0, 1, 0)
            }
            HermitePathPoint {
                position: Qt.vector3d(-100, 200, 150)
                tangent: Qt.vector3d(200, 0, 100)
                normal: Qt.vector3d(0, 1, 0)
            }
            HermitePathPoint {
                position: Qt.vector3d(100, 200, 150)
                tangent: Qt.vector3d(200, 0, -100)
                normal: Qt.vector3d(0, 1, 0)
            }
            HermitePathPoint {
                position: Qt.vector3d(200, 100, 0)
                tangent: Qt.vector3d(0, -150, -200)
                normal: Qt.vector3d(0, 1, 0)
            }
            HermitePathPoint {
                position: Qt.vector3d(100, 200, -150)
                tangent: Qt.vector3d(-200, 0, -100)
                normal: Qt.vector3d(0, 1, 0)
            }
            HermitePathPoint {
                position: Qt.vector3d(-100, 200, -150)
                tangent: Qt.vector3d(-200, 0, 100)
                normal: Qt.vector3d(0, 1, 0)
            }
        }

        PathConstraint {
            id: pathConstraint
            body1: worldAnchor
            body2: follower
            path: ovalPath
            pathPosition: Qt.vector3d(0, 0, 0)
            pathRotation: Qt.quaternion(1, 0, 0, 0)
            pathFraction: 0
            positionMotorState: PathConstraint.Velocity
            targetVelocity: velSlider.value
            positionMotorSettings: MotorSettings {
                springFrequency: 2.0
                springDamping: 1.0
                maxForceLimit: 100000
                minForceLimit: -100000
            }
            rotationConstraintType: PathConstraint.ConstrainToPath
        }
    }

    // UI overlay
    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 6

        Label { text: "Path Constraint"; font.bold: true; color: "white" }

        Row {
            spacing: 8
            Label { text: "Motor Velocity:"; color: "white"; anchors.verticalCenter: parent.verticalCenter }
            Slider { id: velSlider; from: -5; to: 5; value: 1.0; width: 200 }
            Label { text: velSlider.value.toFixed(2); color: "white"; anchors.verticalCenter: parent.verticalCenter }
        }

        CheckBox { id: loopCheck; text: "Looping"; checked: true }
    }
}
