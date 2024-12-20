#include "HitLeftClip.h"
#include "AnimTime.h"
#include "Bone.h"
#include "Mixer.h"

namespace Axiom
{
	HitLeftClip::HitLeftClip(int numBones)
		: mNumBones(numBones),
		mNumFrames(0),
		mTotalTime(AnimTime::Duration::ZERO),
		mHead(nullptr)
	{
		privSetAnimationData();
		mTotalTime = privFindMaxTime();
		mNumFrames = privFindNumFrames();
	}

	HitLeftClip::~HitLeftClip()
	{
		FrameBucket* pTmp = mHead;

		while (pTmp != nullptr)
		{
			FrameBucket* pDeleteMe = pTmp;
			pTmp = pTmp->nextBucket;
			delete pDeleteMe;
		}
	}

	void HitLeftClip::AnimateBones(AnimTime curr, Bone* bone)
	{
		// First one 
		FrameBucket* pTmp = mHead;

		// Find which key frames
		while (curr >= pTmp->KeyTime && pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		// pTmp is the "B" key frame
		// pTmp->prev is the "A" key frame
		FrameBucket* pA = pTmp->prevBucket;
		FrameBucket* pB = pTmp;

		// find the "S" of the time
		float tS = (curr - pA->KeyTime) / (pB->KeyTime - pA->KeyTime);

		Mixer::Blend(bone, pA->poBone, pB->poBone, tS, mNumBones);

	}

	void HitLeftClip::AnimateBonesReverse(AnimTime curr, Bone* bone)
	{
		// First one 
		FrameBucket* pTmp = mHead;

		while (pTmp->nextBucket)
		{
			pTmp = pTmp->nextBucket;
		}

		AnimTime tRev = mTotalTime - curr;

		// Find which key frames
		while (tRev <= pTmp->KeyTime && pTmp->prevBucket != nullptr)
		{
			pTmp = pTmp->prevBucket;
		}

		// pTmp is the "A" key frame (reverse direction)
		// pTmp->next is the "B" key frame
		FrameBucket* pA = pTmp;
		FrameBucket* pB = pTmp->nextBucket;

		// Calculate the interpolation factor for reverse
		float tS = (tRev - pA->KeyTime) / (pB->KeyTime - pA->KeyTime);

		Mixer::Blend(bone, pA->poBone, pB->poBone, tS, mNumBones);
	}

	int HitLeftClip::privFindNumFrames()
	{
		int count = 0;
		FrameBucket* pTmp = mHead;

		while (pTmp->nextBucket != nullptr)
		{
			count++;
			pTmp = pTmp->nextBucket;
		}
		return count;
	}

	AnimTime HitLeftClip::privFindMaxTime()
	{
		AnimTime tMax;
		FrameBucket* pTmp = mHead;

		while (pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		tMax = pTmp->KeyTime;

		return tMax;
	}

	AnimTime& HitLeftClip::GetTotalTime()
	{
		return mTotalTime;
	}

	void HitLeftClip::privSetAnimationData()
	{
		// --------  Frame 0  ----------------------------

		FrameBucket* pTmp = nullptr;
		FrameBucket* pTmpX = nullptr;

		// Keyframe: 0  time: 0.000000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 0 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		//pTmp->nextBucket = pTmpX;
		mHead = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024873f, 0.000000f, -0.001388f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.000000f, -0.000000f, 1.000000f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.246312f, 0.662820f, 0.662819f, 0.246312f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.532849f, -0.464835f, 0.464836f, 0.532849f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935355f, -0.000000f, -0.353710f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.246312f, 0.662820f, -0.662820f, 0.246313f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.532849f, -0.464835f, -0.464836f, 0.532848f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.935355f, 0.000000f, -0.353710f, -0.000000f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 1  time: 0.041667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 1 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024450f, 0.000680f, -0.000694f);
		pTmp->poBone[4].Q = Quat(-0.000000f, 0.006561f, 0.041202f, 0.999129f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.237759f, 0.664491f, 0.653948f, 0.272534f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.540700f, -0.455679f, 0.455680f, 0.540699f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.943427f, -0.015299f, -0.331208f, 0.003403f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.294974f, -0.644631f, 0.655674f, -0.259871f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.507624f, -0.492258f, -0.492258f, 0.507624f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.930987f, -0.015137f, -0.364725f, 0.003256f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 2  time: 0.083333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 2 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023792f, 0.001678f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000000f, 0.000000f, 0.082339f, 0.996604f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.228716f, 0.666456f, 0.648782f, 0.287414f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.544389f, -0.451265f, 0.451265f, 0.544389f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.948979f, -0.038338f, -0.312872f, 0.008925f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.331380f, -0.629103f, 0.648108f, -0.272715f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.478444f, 0.520665f, 0.520665f, -0.478443f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.925587f, -0.038379f, -0.376463f, 0.009579f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 3  time: 0.125000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 3 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023388f, 0.002194f, -0.000008f);
		pTmp->poBone[4].Q = Quat(0.000110f, -0.002739f, 0.081835f, 0.996642f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.241452f, 0.662637f, 0.649869f, 0.283344f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.535808f, -0.461422f, 0.461422f, 0.535807f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.945435f, -0.049196f, -0.321776f, 0.013921f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.325097f, -0.630992f, 0.643991f, -0.285372f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.470274f, 0.528056f, 0.528056f, -0.470273f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.922003f, -0.050071f, -0.383572f, 0.016617f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 4  time: 0.166667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 4 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.022987f, 0.002645f, -0.000034f);
		pTmp->poBone[4].Q = Quat(0.000440f, -0.010915f, 0.080105f, 0.996727f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.250605f, 0.660062f, 0.652380f, 0.275528f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.526829f, -0.471648f, 0.471648f, 0.526828f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.941575f, -0.058802f, -0.331079f, 0.019103f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.314507f, -0.634841f, 0.641683f, -0.293778f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.462704f, 0.534701f, 0.534702f, -0.462703f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.918341f, -0.060424f, -0.390433f, 0.023691f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 5  time: 0.208333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 5 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.022607f, 0.003015f, -0.000083f);
		pTmp->poBone[4].Q = Quat(0.000959f, -0.023790f, 0.076877f, 0.996756f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.256304f, 0.658680f, 0.656172f, 0.264360f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.517634f, -0.481721f, 0.481721f, 0.517634f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.937474f, -0.066655f, -0.340743f, 0.024378f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.300014f, -0.640448f, 0.641151f, -0.297897f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.456127f, 0.540322f, 0.540323f, -0.456126f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.914781f, -0.068856f, -0.396864f, 0.030546f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 6  time: 0.250000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 6 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.022274f, 0.003291f, -0.000157f);
		pTmp->poBone[4].Q = Quat(0.001592f, -0.039469f, 0.071995f, 0.996623f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.259282f, 0.658163f, 0.660795f, 0.250889f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.508593f, -0.491257f, 0.491257f, 0.508593f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.933262f, -0.072390f, -0.350588f, 0.029496f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.282775f, 0.647196f, -0.641985f, 0.298381f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.451029f, 0.544585f, 0.544586f, -0.451028f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.911577f, -0.074947f, -0.402566f, 0.036763f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 7  time: 0.291667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 7 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.022010f, 0.003474f, -0.000257f);
		pTmp->poBone[4].Q = Quat(0.002223f, -0.055136f, 0.065532f, 0.996324f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.260876f, 0.657959f, 0.665577f, 0.236730f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.500198f, -0.499802f, 0.499802f, 0.500198f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.929113f, -0.075971f, -0.360296f, 0.034117f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.264604f, 0.654175f, -0.643466f, 0.296633f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.447838f, 0.547212f, 0.547213f, -0.447837f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.908980f, -0.078655f, -0.407202f, 0.041886f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 8  time: 0.333333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 8 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.021828f, 0.003577f, -0.000376f);
		pTmp->poBone[4].Q = Quat(0.002741f, -0.067985f, 0.057798f, 0.996007f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.262633f, 0.657500f, 0.669873f, 0.223581f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.492892f, -0.507008f, 0.507008f, 0.492892f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.925192f, -0.077740f, -0.369507f, 0.037958f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.247415f, 0.660527f, -0.644840f, 0.294399f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.446744f, 0.548106f, 0.548106f, -0.446743f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.907149f, -0.080363f, -0.410537f, 0.045631f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 9  time: 0.375000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 9 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.021726f, 0.003624f, -0.000509f);
		pTmp->poBone[4].Q = Quat(0.003071f, -0.076148f, 0.049215f, 0.995876f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.265788f, 0.656383f, 0.673268f, 0.212670f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.486920f, -0.512746f, 0.512747f, 0.486920f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.921615f, -0.078248f, -0.377929f, 0.040911f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.232590f, 0.665729f, -0.645582f, 0.293142f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.447652f, 0.547364f, 0.547364f, -0.447652f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.906103f, -0.080672f, -0.412514f, 0.047986f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 10  time: 0.416667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 10 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.021695f, 0.003635f, -0.000650f);
		pTmp->poBone[4].Q = Quat(0.003182f, -0.078900f, 0.040165f, 0.996068f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.271036f, 0.654412f, 0.675594f, 0.204588f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.482312f, -0.517083f, 0.517084f, 0.482312f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.918438f, -0.078029f, -0.385398f, 0.043026f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.220767f, 0.669608f, -0.645452f, 0.293732f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.450289f, 0.545197f, 0.545197f, -0.450289f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.905763f, -0.080157f, -0.413225f, 0.049136f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 11  time: 0.458333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 11 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.021833f, 0.003469f, -0.000825f);
		pTmp->poBone[4].Q = Quat(0.003132f, -0.077993f, 0.029783f, 0.996504f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.274031f, 0.653248f, 0.677177f, 0.199009f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.480353f, -0.518904f, 0.518904f, 0.480352f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.916208f, -0.073939f, -0.391561f, 0.042141f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.211394f, 0.672703f, -0.646496f, 0.291250f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.456594f, 0.539928f, 0.539929f, -0.456593f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.906917f, -0.075538f, -0.411850f, 0.046631f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 12  time: 0.500000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 12 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.022245f, 0.002971f, -0.001061f);
		pTmp->poBone[4].Q = Quat(0.002978f, -0.075062f, 0.017256f, 0.997025f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.270191f, 0.654652f, 0.678356f, 0.195601f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.482715f, -0.516707f, 0.516707f, 0.482715f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.915583f, -0.062715f, -0.395573f, 0.036013f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.203672f, 0.675552f, -0.650644f, 0.280731f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.468896f, 0.529280f, 0.529280f, -0.468895f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.910494f, -0.063553f, -0.406812f, 0.038299f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 13  time: 0.541667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 13 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.022893f, 0.002189f, -0.001341f);
		pTmp->poBone[4].Q = Quat(0.002723f, -0.070005f, 0.003374f, 0.997537f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.260399f, 0.658244f, 0.679152f, 0.194063f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.489685f, -0.510107f, 0.510107f, 0.489684f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.916640f, -0.045634f, -0.396267f, 0.025699f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.196933f, 0.678195f, -0.657089f, 0.263634f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.486929f, 0.512738f, 0.512738f, -0.486929f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.916305f, -0.045763f, -0.397006f, 0.026035f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 14  time: 0.583333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 14 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023683f, 0.001235f, -0.001637f);
		pTmp->poBone[4].Q = Quat(0.002390f, -0.063006f, -0.010520f, 0.997955f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.247056f, 0.663000f, 0.679621f, 0.193674f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.500608f, -0.499391f, 0.499392f, 0.500608f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.919155f, -0.025486f, -0.392835f, 0.013642f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.190398f, 0.680632f, -0.664398f, 0.243031f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.508996f, -0.490839f, -0.490839f, 0.508996f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.923627f, -0.025190f, -0.382244f, 0.012957f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 15  time: 0.625000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 15 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024473f, 0.000281f, -0.001908f);
		pTmp->poBone[4].Q = Quat(0.002020f, -0.054588f, -0.022800f, 0.998247f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.233713f, 0.667574f, 0.679792f, 0.193924f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.513376f, -0.486257f, 0.486257f, 0.513375f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.922476f, -0.005976f, -0.385999f, 0.002742f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.184095f, 0.682715f, -0.671003f, 0.223081f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.531653f, -0.466202f, -0.466203f, 0.531653f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.931195f, -0.005588f, -0.364473f, 0.002067f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 16  time: 0.666667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 16 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025122f, -0.000501f, -0.002119f);
		pTmp->poBone[4].Q = Quat(0.001661f, -0.045493f, -0.032102f, 0.998447f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.223818f, 0.670848f, 0.679589f, 0.195007f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.524989f, -0.473695f, 0.473695f, 0.524988f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.925683f, 0.009607f, -0.378145f, -0.005063f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.179282f, 0.684130f, -0.675752f, 0.207805f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.550768f, -0.443457f, -0.443458f, 0.550768f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.937580f, 0.009879f, -0.347592f, -0.005139f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 17  time: 0.708333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 17 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025534f, -0.000999f, -0.002247f);
		pTmp->poBone[4].Q = Quat(0.001349f, -0.036431f, -0.037706f, 0.998624f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.219612f, 0.672222f, 0.678856f, 0.197589f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.532865f, -0.464817f, 0.464817f, 0.532865f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.927955f, 0.019356f, -0.372074f, -0.009298f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.177760f, 0.684536f, -0.678089f, 0.200017f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.563169f, -0.427598f, -0.427599f, 0.563169f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.941707f, 0.019473f, -0.335755f, -0.008765f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 18  time: 0.750000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 18 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025672f, -0.001165f, -0.002289f);
		pTmp->poBone[4].Q = Quat(0.001104f, -0.027901f, -0.039522f, 0.998828f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.221933f, 0.671508f, 0.677464f, 0.202149f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.535642f, -0.461614f, 0.461614f, 0.535642f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.928823f, 0.022692f, -0.369683f, -0.010339f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.180741f, 0.683703f, -0.677862f, 0.200962f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.567424f, -0.421936f, -0.421936f, 0.567424f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.943088f, 0.022729f, -0.331629f, -0.009575f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 19  time: 0.791667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 19 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025635f, -0.001112f, -0.002248f);
		pTmp->poBone[4].Q = Quat(0.000887f, -0.020118f, -0.037727f, 0.999085f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.227521f, 0.669714f, 0.675408f, 0.208666f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.535537f, -0.461736f, 0.461736f, 0.535537f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.929203f, 0.021830f, -0.368801f, -0.009529f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.188084f, 0.681626f, -0.676033f, 0.207341f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.565893f, -0.423987f, -0.423988f, 0.565893f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.942672f, 0.021843f, -0.332888f, -0.008842f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 20  time: 0.833333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 20 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025528f, -0.000956f, -0.002128f);
		pTmp->poBone[4].Q = Quat(0.000659f, -0.013319f, -0.032420f, 0.999385f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.232921f, 0.667906f, 0.672782f, 0.216826f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.535082f, -0.462263f, 0.462264f, 0.535081f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.930115f, 0.018952f, -0.366693f, -0.007928f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.199131f, 0.678379f, -0.673569f, 0.215530f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.561180f, -0.430206f, -0.430206f, 0.561180f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.941515f, 0.018943f, -0.336355f, -0.007426f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 21  time: 0.875000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 21 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025365f, -0.000718f, -0.001943f);
		pTmp->poBone[4].Q = Quat(0.000438f, -0.007849f, -0.024337f, 0.999673f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.237767f, 0.666191f, 0.669824f, 0.225815f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.534411f, -0.463038f, 0.463039f, 0.534411f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.931443f, 0.014399f, -0.363556f, -0.005779f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.212590f, 0.674222f, -0.670620f, 0.224720f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.554008f, -0.439403f, -0.439404f, 0.554008f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.939842f, 0.014383f, -0.341261f, -0.005497f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 22  time: 0.916667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 22 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025180f, -0.000447f, -0.001734f);
		pTmp->poBone[4].Q = Quat(0.000248f, -0.003928f, -0.015170f, 0.999877f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.241667f, 0.664722f, 0.666963f, 0.234311f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.533736f, -0.463816f, 0.463817f, 0.533736f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.932925f, 0.009085f, -0.359939f, -0.003512f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.226121f, 0.669817f, -0.667585f, 0.233549f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.545953f, -0.449372f, -0.449373f, 0.545952f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.938058f, 0.009074f, -0.346342f, -0.003403f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 23  time: 0.958333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 23 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025016f, -0.000209f, -0.001550f);
		pTmp->poBone[4].Q = Quat(0.000107f, -0.001512f, -0.007091f, 0.999974f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.244370f, 0.663641f, 0.664678f, 0.240970f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.533228f, -0.464401f, 0.464402f, 0.533227f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.934222f, 0.004290f, -0.356662f, -0.001610f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.237164f, 0.666053f, -0.665017f, 0.240581f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.538937f, -0.457762f, -0.457763f, 0.538937f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.936581f, 0.004287f, -0.350422f, -0.001587f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 24  time: 1.000000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 24 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024909f, -0.000053f, -0.001429f);
		pTmp->poBone[4].Q = Quat(0.000025f, -0.000323f, -0.001791f, 0.999998f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.245863f, 0.663015f, 0.663274f, 0.245011f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.532939f, -0.464732f, 0.464733f, 0.532938f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935070f, 0.001090f, -0.354462f, -0.000402f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.244053f, 0.663628f, -0.663367f, 0.244907f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.534380f, -0.463074f, -0.463075f, 0.534380f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.935658f, 0.001091f, -0.352905f, -0.000400f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 25  time: 1.041667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 25 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024873f, 0.000000f, -0.001388f);
		pTmp->poBone[4].Q = Quat(0.000008f, 0.000000f, -0.000000f, 1.000000f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.246312f, 0.662821f, 0.662820f, 0.246312f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.532849f, -0.464835f, 0.464836f, 0.532849f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935355f, -0.000003f, -0.353711f, -0.000007f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.246312f, 0.662820f, -0.662820f, 0.246313f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.532849f, -0.464835f, -0.464836f, 0.532848f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.935355f, -0.000003f, -0.353710f, -0.000008f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 26  time: 1.083333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 26 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024873f, 0.000000f, -0.001388f);
		pTmp->poBone[4].Q = Quat(0.000001f, 0.000000f, -0.000000f, 1.000000f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.246312f, 0.662820f, 0.662820f, 0.246312f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.532849f, -0.464835f, 0.464836f, 0.532849f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935355f, -0.000000f, -0.353711f, -0.000001f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.246312f, 0.662820f, -0.662820f, 0.246313f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.532849f, -0.464835f, -0.464836f, 0.532848f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.935355f, -0.000000f, -0.353710f, -0.000001f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 27  time: 1.125000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 27 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)mNumBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024873f, 0.000000f, -0.001388f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.000000f, -0.000000f, 1.000000f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.246312f, 0.662820f, 0.662819f, 0.246312f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.532849f, -0.464835f, 0.464836f, 0.532849f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935355f, -0.000000f, -0.353710f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.246312f, 0.662820f, -0.662820f, 0.246313f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.532849f, -0.464835f, -0.464836f, 0.532848f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.935355f, 0.000000f, -0.353710f, -0.000000f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);
	}
}
