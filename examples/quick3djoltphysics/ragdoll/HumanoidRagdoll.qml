import QtQuick
import QtQuick3D
import QtQuick3D.JoltPhysics

Node {
    id: root
    required property int movingLayer
    property alias ragdollBody: ragdoll

    PhysicsSkeleton {
        id: skeleton
        SkeletonJoint { name: "pelvis" }
        SkeletonJoint { name: "spine"; parentName: "pelvis" }
        SkeletonJoint { name: "head"; parentName: "spine" }
        SkeletonJoint { name: "upperArmL"; parentName: "spine" }
        SkeletonJoint { name: "lowerArmL"; parentName: "upperArmL" }
        SkeletonJoint { name: "upperArmR"; parentName: "spine" }
        SkeletonJoint { name: "lowerArmR"; parentName: "upperArmR" }
        SkeletonJoint { name: "upperLegL"; parentName: "pelvis" }
        SkeletonJoint { name: "lowerLegL"; parentName: "upperLegL" }
        SkeletonJoint { name: "upperLegR"; parentName: "pelvis" }
        SkeletonJoint { name: "lowerLegR"; parentName: "upperLegR" }
    }

    Ragdoll {
        id: ragdoll
        skeleton: skeleton

        // Pelvis (root) - no constraint to parent
        RagdollPart {
            jointName: "pelvis"
            shape: BoxShape { extents: Qt.vector3d(30, 15, 20) }
            motionType: Body.Dynamic
            objectLayer: root.movingLayer
            mass: 10
            position: Qt.vector3d(0, 300, 0)
        }

        // Spine
        RagdollPart {
            jointName: "spine"
            shape: BoxShape { extents: Qt.vector3d(28, 30, 18) }
            motionType: Body.Dynamic
            objectLayer: root.movingLayer
            mass: 8
            position: Qt.vector3d(0, 335, 0)
            constraintToParent: SwingTwistConstraint {
                twistAxis1: Qt.vector3d(0, 1, 0)
                twistAxis2: Qt.vector3d(0, 1, 0)
                planeAxis1: Qt.vector3d(1, 0, 0)
                planeAxis2: Qt.vector3d(1, 0, 0)
                normalHalfConeAngle: 20
                planeHalfConeAngle: 20
                twistMinAngle: -10
                twistMaxAngle: 10
            }
        }

        // Head
        RagdollPart {
            jointName: "head"
            shape: SphereShape { diameter: 22 }
            motionType: Body.Dynamic
            objectLayer: root.movingLayer
            mass: 4
            position: Qt.vector3d(0, 365, 0)
            constraintToParent: SwingTwistConstraint {
                twistAxis1: Qt.vector3d(0, 1, 0)
                twistAxis2: Qt.vector3d(0, 1, 0)
                planeAxis1: Qt.vector3d(1, 0, 0)
                planeAxis2: Qt.vector3d(1, 0, 0)
                normalHalfConeAngle: 30
                planeHalfConeAngle: 30
                twistMinAngle: -30
                twistMaxAngle: 30
            }
        }

        // Upper arm left
        RagdollPart {
            jointName: "upperArmL"
            shape: CapsuleShape { diameter: 8; height: 30 }
            motionType: Body.Dynamic
            objectLayer: root.movingLayer
            mass: 3
            position: Qt.vector3d(-30, 340, 0)
            constraintToParent: SwingTwistConstraint {
                twistAxis1: Qt.vector3d(-1, 0, 0)
                twistAxis2: Qt.vector3d(-1, 0, 0)
                planeAxis1: Qt.vector3d(0, -1, 0)
                planeAxis2: Qt.vector3d(0, -1, 0)
                normalHalfConeAngle: 60
                planeHalfConeAngle: 60
                twistMinAngle: -45
                twistMaxAngle: 45
            }
        }

        // Lower arm left
        RagdollPart {
            jointName: "lowerArmL"
            shape: CapsuleShape { diameter: 7; height: 28 }
            motionType: Body.Dynamic
            objectLayer: root.movingLayer
            mass: 2
            position: Qt.vector3d(-62, 340, 0)
            constraintToParent: HingeConstraint {
                hingeAxis1: Qt.vector3d(0, 0, 1)
                hingeAxis2: Qt.vector3d(0, 0, 1)
                normalAxis1: Qt.vector3d(1, 0, 0)
                normalAxis2: Qt.vector3d(1, 0, 0)
                limitsMin: 0
                limitsMax: 140
            }
        }

        // Upper arm right
        RagdollPart {
            jointName: "upperArmR"
            shape: CapsuleShape { diameter: 8; height: 30 }
            motionType: Body.Dynamic
            objectLayer: root.movingLayer
            mass: 3
            position: Qt.vector3d(30, 340, 0)
            constraintToParent: SwingTwistConstraint {
                twistAxis1: Qt.vector3d(1, 0, 0)
                twistAxis2: Qt.vector3d(1, 0, 0)
                planeAxis1: Qt.vector3d(0, -1, 0)
                planeAxis2: Qt.vector3d(0, -1, 0)
                normalHalfConeAngle: 60
                planeHalfConeAngle: 60
                twistMinAngle: -45
                twistMaxAngle: 45
            }
        }

        // Lower arm right
        RagdollPart {
            jointName: "lowerArmR"
            shape: CapsuleShape { diameter: 7; height: 28 }
            motionType: Body.Dynamic
            objectLayer: root.movingLayer
            mass: 2
            position: Qt.vector3d(62, 340, 0)
            constraintToParent: HingeConstraint {
                hingeAxis1: Qt.vector3d(0, 0, 1)
                hingeAxis2: Qt.vector3d(0, 0, 1)
                normalAxis1: Qt.vector3d(1, 0, 0)
                normalAxis2: Qt.vector3d(1, 0, 0)
                limitsMin: -140
                limitsMax: 0
            }
        }

        // Upper leg left
        RagdollPart {
            jointName: "upperLegL"
            shape: CapsuleShape { diameter: 10; height: 40 }
            motionType: Body.Dynamic
            objectLayer: root.movingLayer
            mass: 5
            position: Qt.vector3d(-12, 260, 0)
            constraintToParent: SwingTwistConstraint {
                twistAxis1: Qt.vector3d(0, -1, 0)
                twistAxis2: Qt.vector3d(0, -1, 0)
                planeAxis1: Qt.vector3d(1, 0, 0)
                planeAxis2: Qt.vector3d(1, 0, 0)
                normalHalfConeAngle: 45
                planeHalfConeAngle: 30
                twistMinAngle: -20
                twistMaxAngle: 20
            }
        }

        // Lower leg left
        RagdollPart {
            jointName: "lowerLegL"
            shape: CapsuleShape { diameter: 9; height: 40 }
            motionType: Body.Dynamic
            objectLayer: root.movingLayer
            mass: 4
            position: Qt.vector3d(-12, 210, 0)
            constraintToParent: HingeConstraint {
                hingeAxis1: Qt.vector3d(0, 0, 1)
                hingeAxis2: Qt.vector3d(0, 0, 1)
                normalAxis1: Qt.vector3d(0, 1, 0)
                normalAxis2: Qt.vector3d(0, 1, 0)
                limitsMin: -140
                limitsMax: 0
            }
        }

        // Upper leg right
        RagdollPart {
            jointName: "upperLegR"
            shape: CapsuleShape { diameter: 10; height: 40 }
            motionType: Body.Dynamic
            objectLayer: root.movingLayer
            mass: 5
            position: Qt.vector3d(12, 260, 0)
            constraintToParent: SwingTwistConstraint {
                twistAxis1: Qt.vector3d(0, -1, 0)
                twistAxis2: Qt.vector3d(0, -1, 0)
                planeAxis1: Qt.vector3d(1, 0, 0)
                planeAxis2: Qt.vector3d(1, 0, 0)
                normalHalfConeAngle: 45
                planeHalfConeAngle: 30
                twistMinAngle: -20
                twistMaxAngle: 20
            }
        }

        // Lower leg right
        RagdollPart {
            jointName: "lowerLegR"
            shape: CapsuleShape { diameter: 9; height: 40 }
            motionType: Body.Dynamic
            objectLayer: root.movingLayer
            mass: 4
            position: Qt.vector3d(12, 210, 0)
            constraintToParent: HingeConstraint {
                hingeAxis1: Qt.vector3d(0, 0, 1)
                hingeAxis2: Qt.vector3d(0, 0, 1)
                normalAxis1: Qt.vector3d(0, 1, 0)
                normalAxis2: Qt.vector3d(0, 1, 0)
                limitsMin: -140
                limitsMax: 0
            }
        }
    }
}
