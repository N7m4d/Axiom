#ifndef SIDE_STEP_LEFT_CLIP_H
#define SIDE_STEP_LEFT_CLIP_H

#include "AnimTime.h"
#include "Bone.h"
#include "Clip.h"

namespace Axiom
{
    class SideStepLeftClip : public Clip
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

        SideStepLeftClip(int numFrames);

        SideStepLeftClip() = delete;
        SideStepLeftClip(const SideStepLeftClip&) = delete;
        SideStepLeftClip& operator =(const SideStepLeftClip&) = delete;
        ~SideStepLeftClip();

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
