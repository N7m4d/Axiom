#ifndef SIDE_STEPLEFT_SKELETON_H
#define SIDE_STEPLEFT_SKELETON_H

#include "GameObjectAnim.h"
#include "Bone.h"

namespace Axiom
{
    class SideStepLeftSkeleton
    {
    public:
        struct Data
        {
            int index;
            int parentIndex;
            char name[64];
        };

    public:
        SideStepLeftSkeleton(Bone* bone, int numBones);

        SideStepLeftSkeleton() = delete;
        SideStepLeftSkeleton(const SideStepLeftSkeleton&) = delete;
        SideStepLeftSkeleton& operator =(const SideStepLeftSkeleton&) = delete;
        ~SideStepLeftSkeleton();

        GameObjectAnim* GetFirstBone();

    private:
        void privSetAnimationHierarchy(Bone* bone);
        GameObjectAnim* privFindBoneByIndex(int index);

    private:
        GameObjectAnim* mFirstBone;
        int mNumBones;
    };
}

#endif
