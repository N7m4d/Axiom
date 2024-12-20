#ifndef WALK_SKELETON_H
#define WALK_SKELETON_H

#include "GameObjectAnim.h"
#include "Bone.h"

namespace Axiom
{
    class WalkSkeleton
    {
    public:
        struct Data
        {
            int index;
            int parentIndex;
            char name[64];
        };

        WalkSkeleton(Bone* bone, int numBones);

        WalkSkeleton() = delete;
        WalkSkeleton(const WalkSkeleton&) = delete;
        WalkSkeleton& operator =(const WalkSkeleton&) = delete;
        ~WalkSkeleton();

        GameObjectAnim* GetFirstBone();

    private:
        void privSetAnimationHierarchy(Bone* bone);
        GameObjectAnim* privFindBoneByIndex(int index);

        GameObjectAnim* mFirstBone;
        int mNumBones;
    };
}

#endif
