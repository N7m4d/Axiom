#ifndef RUN_CLIP_H
#define RUN_CLIP_H

#include "AnimTime.h"
#include "Bone.h"
#include "Clip.h"

namespace Axiom
{
	class RunClip : public Clip
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
			AnimTime      KeyTime;
			Bone* poBone;
			char          pad[4];
		};

		RunClip(int _numFrames);

		RunClip() = delete;
		RunClip(const RunClip&) = delete;
		RunClip& operator = (const RunClip&) = delete;
		virtual ~RunClip();

		AnimTime& GetTotalTime() override;
		void AnimateBones(AnimTime tCurr, Bone* pResult) override;
		void AnimateBonesReverse(AnimTime tCurr, Bone* pResult) override;

	private:
		void privSetAnimationData();
		AnimTime privFindMaxTime();
		int  privFindNumFrames();

		int          numBones;
		int          numFrames;
		AnimTime     TotalTime;
		FrameBucket* poHead;
	};
}

#endif
