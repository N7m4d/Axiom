#ifndef HIT_LEFT_CLIP_H
#define HIT_LEFT_CLIP_H

#include "AnimTime.h"
#include "Bone.h"
#include "Clip.h"

namespace Axiom
{
    class HitLeftClip : public Clip
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

        HitLeftClip(int numFrames);

        HitLeftClip() = delete;
        HitLeftClip(const HitLeftClip&) = delete;
        HitLeftClip& operator =(const HitLeftClip&) = delete;
        ~HitLeftClip();

        AnimTime& GetTotalTime() override;
        void AnimateBones(AnimTime curr, Bone* bone) override;
        void AnimateBonesReverse(AnimTime curr, Bone* bone) override;

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
