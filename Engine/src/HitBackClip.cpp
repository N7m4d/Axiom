#include "HitBackClip.h"
#include "AnimTime.h"
#include "Bone.h"
#include "Mixer.h"

namespace Axiom
{
	HitBackClip::HitBackClip(int _numBones)
		: mNumBones(_numBones),
		mNumFrames(0),
		mTotalTime(AnimTime::Duration::ZERO),
		mHead(nullptr)
	{
		this->privSetAnimationData();
		this->mTotalTime = this->privFindMaxTime();
		this->mNumFrames = this->privFindNumFrames();
	}

	HitBackClip::~HitBackClip()
	{
		FrameBucket* pTmp = mHead;

		while (pTmp != nullptr)
		{
			FrameBucket* pDeleteMe = pTmp;
			pTmp = pTmp->nextBucket;
			delete pDeleteMe;
		}
	}

	void HitBackClip::AnimateBones(AnimTime tCurr, Bone* pResult)
	{
		// First one 
		FrameBucket* pTmp = this->mHead;

		// Find which key frames
		while (tCurr >= pTmp->KeyTime && pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		// pTmp is the "B" key frame
		// pTmp->prev is the "A" key frame
		FrameBucket* pA = pTmp->prevBucket;
		FrameBucket* pB = pTmp;

		// find the "S" of the time
		float tS = (tCurr - pA->KeyTime) / (pB->KeyTime - pA->KeyTime);

		Mixer::Blend(pResult, pA->poBone, pB->poBone, tS, this->mNumBones);

	}

	void HitBackClip::AnimateBonesReverse(AnimTime tCurr, Bone* pResult)
	{
		// First one 
		FrameBucket* pTmp = this->mHead;

		while (pTmp->nextBucket)
		{
			pTmp = pTmp->nextBucket;
		}

		AnimTime tRev = this->mTotalTime - tCurr;

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

		Mixer::Blend(pResult, pA->poBone, pB->poBone, tS, this->mNumBones);
	}

	int HitBackClip::privFindNumFrames()
	{
		int count = 0;
		FrameBucket* pTmp = this->mHead;

		while (pTmp->nextBucket != nullptr)
		{
			count++;
			pTmp = pTmp->nextBucket;
		}
		return count;
	}

	AnimTime HitBackClip::privFindMaxTime()
	{
		AnimTime tMax;
		FrameBucket* pTmp = this->mHead;

		while (pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		tMax = pTmp->KeyTime;

		return tMax;
	}

	AnimTime& HitBackClip::GetTotalTime()
	{
		return this->mTotalTime;
	}

	void HitBackClip::privSetAnimationData()
	{
		// --------  Frame 0  ----------------------------

		FrameBucket* pTmp = nullptr;
		FrameBucket* pTmpX = nullptr;

		// Keyframe: 0  time: 0.000000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 0 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
		this->mHead = pTmpX;

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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.024873f, 0.000000f, -0.000323f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.031111f, -0.000000f, 0.999516f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.280703f, 0.649004f, 0.649003f, 0.280704f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.534791f, -0.462600f, 0.462601f, 0.534790f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.944067f, -0.000000f, -0.329754f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.280703f, 0.649004f, -0.649003f, 0.280704f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.534791f, -0.462600f, -0.462601f, 0.534790f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.944067f, 0.000000f, -0.329754f, -0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.024873f, 0.000000f, 0.001133f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.044585f, -0.000000f, 0.999006f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.306942f, 0.637014f, 0.637014f, 0.306942f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.538973f, -0.457721f, 0.457721f, 0.538972f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.955443f, -0.000000f, -0.295175f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.306941f, 0.637014f, -0.637014f, 0.306942f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.538973f, -0.457721f, -0.457721f, 0.538972f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.955443f, 0.000000f, -0.295175f, -0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.024780f, 0.000000f, 0.001767f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.042694f, -0.000000f, 0.999088f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.314412f, 0.633360f, 0.633360f, 0.314413f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.539213f, -0.457437f, 0.457438f, 0.539213f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.959533f, -0.000000f, -0.281597f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.314412f, 0.633360f, -0.633360f, 0.314413f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.539214f, -0.457437f, -0.457438f, 0.539213f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.959533f, 0.000000f, -0.281597f, -0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.024499f, 0.000000f, 0.002322f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.036840f, -0.000000f, 0.999321f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.321496f, 0.629794f, 0.629794f, 0.321496f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.535150f, -0.462185f, 0.462185f, 0.535150f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.961819f, -0.000000f, -0.273685f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.321496f, 0.629794f, -0.629794f, 0.321496f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.535150f, -0.462184f, -0.462185f, 0.535150f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.961819f, 0.000000f, -0.273685f, -0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.024043f, 0.000000f, 0.002787f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.027021f, -0.000000f, 0.999635f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.328004f, 0.626429f, 0.626429f, 0.328004f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.526913f, -0.471553f, 0.471554f, 0.526913f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.962512f, -0.000000f, -0.271238f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.329629f, 0.625576f, -0.625575f, 0.329629f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.490108f, 0.509700f, 0.509701f, -0.490107f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.940375f, 0.000000f, -0.340138f, -0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.023447f, 0.000000f, 0.003152f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.013650f, -0.000000f, 0.999907f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.333556f, 0.623491f, 0.623490f, 0.333556f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.515177f, -0.484347f, 0.484348f, 0.515177f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.961887f, -0.000000f, -0.273446f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.304242f, 0.638308f, -0.638307f, 0.304242f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.439474f, 0.553952f, 0.553952f, -0.439474f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.892023f, 0.000000f, -0.451989f, -0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.022771f, 0.000000f, 0.003414f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.002336f, -0.000000f, 0.999997f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.337692f, 0.621260f, 0.621260f, 0.337692f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.501244f, -0.498753f, 0.498753f, 0.501244f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.960310f, -0.000000f, -0.278936f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.233544f, 0.667426f, -0.667426f, 0.233544f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.436671f, 0.556164f, 0.556165f, -0.436670f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.843923f, 0.000000f, -0.536464f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.022095f, 0.000000f, 0.003584f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.019563f, -0.000000f, 0.999809f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.340032f, 0.619983f, 0.619982f, 0.340032f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.486881f, -0.512783f, 0.512784f, 0.486881f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.958220f, -0.000000f, -0.286033f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.139231f, 0.693264f, -0.693263f, 0.139232f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.463375f, 0.534120f, 0.534120f, -0.463374f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.803026f, 0.000000f, -0.595944f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.021499f, 0.000000f, 0.003680f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.036527f, -0.000000f, 0.999333f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.340397f, 0.619783f, 0.619782f, 0.340397f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.473919f, -0.524786f, 0.524786f, 0.473919f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.956070f, -0.000000f, -0.293138f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.089965f, 0.701361f, -0.701360f, 0.089965f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.494700f, 0.505244f, 0.505245f, -0.494700f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.806947f, 0.000000f, -0.590624f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.021043f, 0.000000f, 0.003724f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.051952f, -0.000000f, 0.998650f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.338827f, 0.620642f, 0.620641f, 0.338827f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.463829f, -0.533725f, 0.533726f, 0.463829f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.954247f, -0.000000f, -0.299018f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.083021f, 0.702216f, -0.702216f, 0.083021f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.484312f, 0.515210f, 0.515211f, -0.484312f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.798109f, 0.000000f, -0.602513f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.020762f, 0.000000f, 0.003738f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.064998f, -0.000000f, 0.997885f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.335513f, 0.622440f, 0.622439f, 0.335514f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.457508f, -0.539153f, 0.539154f, 0.457508f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.953030f, -0.000000f, -0.302876f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.075830f, 0.703029f, -0.703029f, 0.075830f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.478023f, 0.521051f, 0.521052f, -0.478022f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.792469f, 0.000000f, -0.609913f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.020669f, 0.000000f, 0.003740f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.075263f, -0.000000f, 0.997164f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.330710f, 0.625005f, 0.625004f, 0.330710f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.455322f, -0.541001f, 0.541001f, 0.455322f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.952587f, -0.000000f, -0.304266f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.069181f, 0.703715f, -0.703714f, 0.069181f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.475902f, 0.522989f, 0.522989f, -0.475901f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.790498f, 0.000000f, -0.612465f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.020760f, 0.000000f, 0.003630f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.084084f, -0.000000f, 0.996459f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.322455f, 0.629304f, 0.629303f, 0.322455f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.456475f, -0.540028f, 0.540029f, 0.456475f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.951922f, -0.000000f, -0.306342f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.060084f, 0.704550f, -0.704549f, 0.060084f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.478848f, 0.520293f, 0.520293f, -0.478847f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.791463f, 0.000000f, -0.611217f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.021037f, 0.000000f, 0.003297f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.091809f, -0.000000f, 0.995777f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.309164f, 0.635939f, 0.635938f, 0.309164f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.460292f, -0.536778f, 0.536779f, 0.460292f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.950015f, -0.000000f, -0.312203f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.045906f, 0.705615f, -0.705615f, 0.045907f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.487955f, 0.511761f, 0.511762f, -0.487955f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.794689f, 0.000000f, -0.607017f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.021489f, 0.000000f, 0.002751f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.096600f, -0.000000f, 0.995323f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.292102f, 0.643954f, 0.643953f, 0.292102f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.467044f, -0.530914f, 0.530914f, 0.467044f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.947103f, -0.000000f, -0.320929f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.028121f, 0.706548f, -0.706547f, 0.028121f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.503048f, -0.496933f, -0.496933f, 0.503048f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.800449f, 0.000000f, -0.599401f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.022093f, 0.000000f, 0.002024f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.098017f, -0.000000f, 0.995185f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.272255f, 0.652593f, 0.652592f, 0.272255f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.476848f, -0.522126f, 0.522127f, 0.476848f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.943658f, -0.000000f, -0.330922f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.007690f, 0.707065f, -0.707065f, 0.007690f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.523350f, -0.475505f, -0.475506f, 0.523349f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.808919f, 0.000000f, -0.587920f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.022799f, 0.000000f, 0.001173f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.095850f, -0.000000f, 0.995396f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.251202f, 0.660983f, 0.660982f, 0.251202f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.489392f, -0.510388f, 0.510388f, 0.489391f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.940324f, -0.000000f, -0.340279f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.014047f, 0.706968f, -0.706967f, -0.014047f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.547332f, -0.447691f, -0.447692f, 0.547332f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.819956f, 0.000000f, -0.572426f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.023542f, 0.000000f, 0.000278f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.089172f, -0.000000f, 0.996016f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.231665f, 0.668081f, 0.668080f, 0.231665f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.503746f, -0.496226f, 0.496227f, 0.503745f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.937716f, -0.000000f, -0.347403f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.034740f, 0.706253f, -0.706253f, -0.034740f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.572791f, -0.414621f, -0.414622f, 0.572790f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.832926f, 0.000000f, -0.553384f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.024248f, 0.000000f, -0.000573f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.078319f, -0.000000f, 0.996928f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.215849f, 0.673357f, 0.673356f, 0.215849f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.518409f, -0.480887f, 0.480887f, 0.518408f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.936157f, -0.000000f, -0.351581f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.052572f, 0.705150f, -0.705149f, -0.052572f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.597187f, -0.378640f, -0.378641f, 0.597186f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.846675f, 0.000000f, -0.532110f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.024851f, 0.000000f, -0.001300f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.064714f, -0.000000f, 0.997904f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.205039f, 0.676727f, 0.676726f, 0.205039f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.531673f, -0.466180f, 0.466180f, 0.531673f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935577f, -0.000000f, -0.353122f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.066306f, 0.703991f, -0.703991f, -0.066306f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.618176f, -0.343306f, -0.343306f, 0.618175f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.859711f, 0.000000f, -0.510781f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.025304f, 0.000000f, -0.001846f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.050571f, -0.000000f, 0.998720f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.199422f, 0.678404f, 0.678403f, 0.199422f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.542060f, -0.454060f, 0.454061f, 0.542060f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935619f, -0.000000f, -0.353011f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.051553f, 0.705225f, -0.705225f, -0.051553f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.617677f, -0.344203f, -0.344203f, 0.617676f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.862415f, 0.000000f, -0.506202f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.025580f, 0.000000f, -0.002179f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.037921f, -0.000000f, 0.999281f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.198627f, 0.678637f, 0.678636f, 0.198627f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.548596f, -0.446141f, 0.446142f, 0.548596f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935862f, -0.000000f, -0.352368f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.009758f, 0.707040f, -0.707039f, 0.009758f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.583096f, -0.399999f, -0.399999f, 0.583096f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.852769f, 0.000000f, -0.522288f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.025672f, 0.000000f, -0.002289f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.027922f, -0.000000f, 0.999610f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.202238f, 0.677570f, 0.677569f, 0.202238f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.550856f, -0.443348f, 0.443348f, 0.550856f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.936003f, -0.000000f, -0.351991f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.086062f, 0.701850f, -0.701850f, 0.086062f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.539211f, -0.457440f, -0.457440f, 0.539211f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.850639f, 0.000000f, -0.525751f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.025561f, 0.000000f, -0.002165f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.018590f, -0.000000f, 0.999827f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.212060f, 0.674560f, 0.674559f, 0.212060f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.548380f, -0.446407f, 0.446407f, 0.548380f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935872f, -0.000000f, -0.352341f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.149080f, 0.691213f, -0.691213f, 0.149080f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.510866f, -0.488893f, -0.488894f, 0.510865f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.861587f, 0.000000f, -0.507611f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.025272f, 0.000000f, -0.001839f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.008976f, -0.000000f, 0.999960f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.227739f, 0.669429f, 0.669429f, 0.227739f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.541805f, -0.454365f, 0.454366f, 0.541804f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935560f, -0.000000f, -0.353167f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.202447f, 0.677507f, -0.677506f, 0.202447f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.505007f, -0.494942f, -0.494943f, 0.505007f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.888839f, 0.000000f, -0.458220f, 0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
		pTmp->poBone[4].T = Vec3(0.024983f, 0.000000f, -0.001513f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.002192f, -0.000000f, 0.999998f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.241392f, 0.664628f, 0.664627f, 0.241392f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.535307f, -0.462002f, 0.462003f, 0.535307f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935385f, -0.000000f, -0.353632f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.237606f, 0.665991f, -0.665990f, 0.237606f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.522041f, -0.476941f, -0.476942f, 0.522041f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.922844f, 0.000000f, -0.385174f, -0.000000f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->mNumBones];
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
