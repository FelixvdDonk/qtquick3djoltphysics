import QtQuick
import QtQuick3D
import QtQuick3D.JoltPhysics

Body {
    scale: Qt.vector3d(100, 100, 100)
    property color color: "red"
    PrincipledMaterial {
        id: _material
        baseColor: color
        metalness: 1.0
        roughness: 0.5
    }

    motionType: Body.Dynamic
    objectLayer: moving
    motionQuality: Body.LinearCast

    Model {
        source: "meshes/ring.mesh"
        materials: [_material]
    }

    shape: StaticCompoundShape {
        shapes: [
            ConvexHullShape {
                source: "meshes/segmentedRing_001.mesh"
            },
            ConvexHullShape {
                source: "meshes/segmentedRing_002.mesh"
            },
            ConvexHullShape {
                source: "meshes/segmentedRing_003.mesh"
            },
            ConvexHullShape {
                source: "meshes/segmentedRing_004.mesh"
            },
            ConvexHullShape {
                source: "meshes/segmentedRing_005.mesh"
            },
            ConvexHullShape {
                source: "meshes/segmentedRing_006.mesh"
            },
            ConvexHullShape {
                source: "meshes/segmentedRing_007.mesh"
            },
            ConvexHullShape {
                source: "meshes/segmentedRing_008.mesh"
            },
            ConvexHullShape {
                source: "meshes/segmentedRing_009.mesh"
            },
            ConvexHullShape {
                source: "meshes/segmentedRing_010.mesh"
            },
            ConvexHullShape {
                source: "meshes/segmentedRing_011.mesh"
            },
            ConvexHullShape {
                source: "meshes/segmentedRing_012.mesh"
            }
        ]
    }
}
