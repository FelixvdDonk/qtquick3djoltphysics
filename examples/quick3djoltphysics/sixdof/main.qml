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
    title: qsTr("Qt Quick 3D Jolt Physics - Six DOF Constraint")

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
            position: Qt.vector3d(0, 200, 500)
            eulerRotation: Qt.vector3d(-15, 0, 0)
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

        // Static frame
        Body {
            id: frame
            position: Qt.vector3d(0, 200, 0)
            shape: BoxShape { extents: Qt.vector3d(30, 30, 30) }
            objectLayer: nonMoving
            motionType: Body.Static
            Model {
                source: "#Cube"
                scale: Qt.vector3d(0.3, 0.3, 0.3)
                materials: PrincipledMaterial { baseColor: "#555555" }
            }
        }

        // Dynamic payload
        Body {
            id: payload
            position: Qt.vector3d(0, 130, 0)
            shape: BoxShape { extents: Qt.vector3d(40, 40, 40) }
            objectLayer: moving
            motionType: Body.Dynamic
            Model {
                source: "#Cube"
                scale: Qt.vector3d(0.4, 0.4, 0.4)
                materials: PrincipledMaterial { baseColor: "#e74c3c" }
            }
        }

        SixDOFConstraint {
            id: sixDof
            body1: frame
            body2: payload
            position1: Qt.vector3d(0, 0, 0)
            position2: Qt.vector3d(0, 70, 0)
            axisX1: Qt.vector3d(1, 0, 0)
            axisY1: Qt.vector3d(0, 1, 0)
            axisX2: Qt.vector3d(1, 0, 0)
            axisY2: Qt.vector3d(0, 1, 0)
        }
    }

    // UI overlay
    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 4

        Label { text: "Six DOF Constraint"; font.bold: true; color: "white" }

        Repeater {
            model: [
                { label: "Trans X", axis: SixDOFConstraint.TranslationX },
                { label: "Trans Y", axis: SixDOFConstraint.TranslationY },
                { label: "Trans Z", axis: SixDOFConstraint.TranslationZ },
                { label: "Rot X",   axis: SixDOFConstraint.RotationX },
                { label: "Rot Y",   axis: SixDOFConstraint.RotationY },
                { label: "Rot Z",   axis: SixDOFConstraint.RotationZ }
            ]

            delegate: Row {
                spacing: 6
                Label {
                    text: modelData.label + ":"
                    color: "white"
                    width: 60
                    anchors.verticalCenter: parent.verticalCenter
                }
                Button {
                    text: "Free"
                    width: 60
                    onClicked: sixDof.setAxisFree(modelData.axis)
                }
                Button {
                    text: "Limited"
                    width: 70
                    onClicked: {
                        if (modelData.axis <= SixDOFConstraint.TranslationZ)
                            sixDof.setAxisLimits(modelData.axis, -50, 50)
                        else
                            sixDof.setAxisLimits(modelData.axis, -45, 45)
                    }
                }
                Button {
                    text: "Locked"
                    width: 65
                    onClicked: sixDof.setAxisFixed(modelData.axis)
                }
            }
        }
    }
}
