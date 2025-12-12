import QtQuick
import QtQuick3D
import QtQuick3D.JoltPhysics

Body {
    property real len: 170
    property real w: 17
    PrincipledMaterial {
        id: material3
        baseColor: "red"
        metalness: 1.0
        roughness: 0.5
    }

    motionType: Body.Dynamic
    objectLayer: moving
    motionQuality: Body.LinearCast

    Node {
        opacity: 1
        Model {
            materials: material3
            source: "#Cylinder"
            scale: Qt.vector3d(w / 100, len / 100, w / 100)
            eulerRotation.z: 90
            y: -len / 2
        }
        Model {
            materials: material3
            source: "#Cylinder"
            scale: Qt.vector3d(w / 100, len / 100, w / 100)
            eulerRotation.z: 90
            y: len / 2
        }
        Model {
            materials: material3
            source: "#Cylinder"
            scale: Qt.vector3d(w / 100, len / 100, w / 100)
            x: len / 2
        }
        Model {
            materials: material3
            source: "#Cylinder"
            scale: Qt.vector3d(w / 100, len / 100, w / 100)
            x: -len / 2
        }
        Model {
            materials: material3
            source: "#Sphere"
            scale: Qt.vector3d(w / 100, w / 100, w / 100)
            x: -len / 2
            y: -len / 2
        }
        Model {
            materials: material3
            source: "#Sphere"
            scale: Qt.vector3d(w / 100, w / 100, w / 100)
            x: -len / 2
            y: len / 2
        }
        Model {
            materials: material3
            source: "#Sphere"
            scale: Qt.vector3d(w / 100, w / 100, w / 100)
            x: len / 2
            y: -len / 2
        }
        Model {
            materials: material3
            source: "#Sphere"
            scale: Qt.vector3d(w / 100, w / 100, w / 100)
            x: len / 2
            y: len / 2
        }
    }
    shape: StaticCompoundShape {
        shapes: [
            CapsuleShape {
                y: -len / 2
                eulerRotation.z: -90
                height: len
                diameter: w
            },
            CapsuleShape {
                y: len / 2
                eulerRotation.z: -90
                height: len
                diameter: w
            },
            CapsuleShape {
                x: -len / 2
                height: len
                diameter: w
            },
            CapsuleShape {
                x: len / 2
                height: len
                diameter: w
            }
        ]
    }
}
//! [capsulelink]
