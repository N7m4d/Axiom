#ifndef HIT_LEFT_SKELETON_H
#define HIT_LEFT_SKELETON_H

#include "GameObjectAnim.h"
#include "Bone.h"

namespace Axiom
{
    class HitLeftSkeleton
    {
    public:
        struct Data
        {
            int index;
            int parentIndex;
            char name[64];
        };

        HitLeftSkeleton(Bone* bone, int numBones);

        HitLeftSkeleton() = delete;
        HitLeftSkeleton(const HitLeftSkeleton&) = delete;
        HitLeftSkeleton& operator =(const HitLeftSkeleton&) = delete;
        ~HitLeftSkeleton();

        GameObjectAnim* GetFirstBone();

    private:
        void privSetAnimationHierarchy(Bone* pBoneResult);
        GameObjectAnim* privFindBoneByIndex(int index);

        GameObjectAnim* mFirstBone;
        int mNumBones;
    };
}

#endif
