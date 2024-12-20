#ifndef CLIP_H
#define CLIP_H

#include "AnimTime.h"
#include "Bone.h"

namespace Axiom
{
    class Clip
    {
    public:
        Clip();
        Clip(const Clip&) = delete;
        Clip& operator =(const Clip&) = delete;
        virtual ~Clip() = default;

        virtual AnimTime& GetTotalTime() = 0;
        virtual void AnimateBones(AnimTime curr, Bone* bone) = 0;
        virtual void AnimateBonesReverse(AnimTime curr, Bone* bone) = 0;
    };
}

#endif
