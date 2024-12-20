#ifndef HIT_BACK_CLIP_H
#define HIT_BACK_CLIP_H

#include "AnimTime.h"
#include "Bone.h"
#include "Clip.h"

namespace Axiom
{
    class HitBackClip : public Clip
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

        HitBackClip(int _numFrames);

        HitBackClip() = delete;
        HitBackClip(const HitBackClip&) = delete;
        HitBackClip& operator =(const HitBackClip&) = delete;
        virtual ~HitBackClip();

        AnimTime& GetTotalTime() override;
        void AnimateBones(AnimTime tCurr, Bone* pResult) override;
        void AnimateBonesReverse(AnimTime tCurr, Bone* pResult) override;

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
