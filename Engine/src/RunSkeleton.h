#ifndef RUN_SKELETON_H
#define RUN_SKELETON_H

#include "GameObjectAnim.h"
#include "Bone.h"

namespace Axiom
{
    class RunSkeleton
    {
    public:
        struct Data
        {
            int index;
            int parentIndex;
            char name[64];
        };

        RunSkeleton(Bone* bone, int numBones);

        RunSkeleton() = delete;
        RunSkeleton(const RunSkeleton&) = delete;
        RunSkeleton& operator =(const RunSkeleton&) = delete;
        ~RunSkeleton();

        GameObjectAnim* GetFirstBone();

    private:
        void privSetAnimationHierarchy(Bone* pBoneResult);
        GameObjectAnim* privFindBoneByIndex(int index);

        GameObjectAnim* mFirstBone;
        int mNumBones;
    };
}

#endif
