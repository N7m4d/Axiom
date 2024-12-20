#ifndef WALK_CLIP_H
#define WALK_CLIP_H

#include "AnimTime.h"
#include "Bone.h"
#include "Clip.h"

namespace Axiom
{
    class WalkClip : public Clip
    {
    public:
        struct FrameBucket
        {
            ~FrameBucket()
            {
                delete[] poBone;
            }

            FrameBucket* nextBucket;
            FrameBucket* prevBucket;
            AnimTime KeyTime;
            Bone* poBone;
            char pad[4];
        };

        WalkClip(int _numFrames);

        WalkClip() = delete;
        WalkClip(const WalkClip&) = delete;
        WalkClip& operator =(const WalkClip&) = delete;
        ~WalkClip();

        AnimTime& GetTotalTime() override;
        void AnimateBones(AnimTime curr, Bone* bone) override;

    private:
        void privSetAnimationData();
        AnimTime privFindMaxTime();
        int privFindNumFrames();

        int mNumBones;
        int mNumFrames;
        AnimTime mTotalTime;
        FrameBucket* mHead;
    };
}

#endif
