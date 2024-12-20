#include "RunClip.h"
#include "AnimTime.h"
#include "Bone.h"
#include "Mixer.h"

namespace Axiom
{
	RunClip::RunClip(int _numBones)
		: numBones(_numBones),
		numFrames(0),
		TotalTime(AnimTime::Duration::ZERO),
		poHead(nullptr)
	{
		this->privSetAnimationData();
		this->TotalTime = this->privFindMaxTime();
		this->numFrames = this->privFindNumFrames();
	}

	RunClip::~RunClip()
	{
		FrameBucket* pTmp = poHead;

		while (pTmp != nullptr)
		{
			FrameBucket* pDeleteMe = pTmp;
			pTmp = pTmp->nextBucket;
			delete pDeleteMe;
		}
	}

	void RunClip::AnimateBones(AnimTime tCurr, Bone* pResult)
	{
		// First one 
		FrameBucket* pTmp = this->poHead;

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

		Mixer::Blend(pResult, pA->poBone, pB->poBone, tS, this->numBones);
	}

	void RunClip::AnimateBonesReverse(AnimTime tCurr, Bone* pResult)
	{
		// First one 
		FrameBucket* pTmp = this->poHead;

		while (pTmp->nextBucket)
		{
			pTmp = pTmp->nextBucket;
		}

		AnimTime tRev = this->TotalTime - tCurr;

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

		Mixer::Blend(pResult, pA->poBone, pB->poBone, tS, this->numBones);
	}

	int RunClip::privFindNumFrames()
	{
		int count = 0;
		FrameBucket* pTmp = this->poHead;

		while (pTmp->nextBucket != nullptr)
		{
			count++;
			pTmp = pTmp->nextBucket;
		}
		return count;
	}

	AnimTime RunClip::privFindMaxTime()
	{
		AnimTime tMax;
		FrameBucket* pTmp = this->poHead;

		while (pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		tMax = pTmp->KeyTime;

		return tMax;
	}

	AnimTime& RunClip::GetTotalTime()
	{
		return this->TotalTime;
	}

	void RunClip::privSetAnimationData()
	{
		// --------  Frame 0  ----------------------------

		FrameBucket* pTmp = nullptr;
		FrameBucket* pTmpX = nullptr;

		// Keyframe: 0  time: 0.000000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 0 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		//pTmp->nextBucket = pTmpX;
		this->poHead = pTmpX;

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
		pTmp->poBone[4].T = Vec3(0.029046f, 0.000595f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.013580f, 0.016625f, 0.999770f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(0.064687f, 0.714037f, 0.696910f, 0.016826f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.614958f, -0.349037f, 0.349037f, 0.614958f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.858792f, 0.041700f, -0.510526f, -0.010000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.289341f, 0.634752f, -0.620608f, 0.358075f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.636551f, -0.307901f, -0.307902f, 0.636550f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.997063f, -0.064530f, 0.039341f, 0.012385f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.029278f, 0.000000f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000000f, -0.004239f, 0.013590f, 0.999899f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(0.071097f, 0.712060f, 0.698260f, 0.018682f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.655043f, -0.266307f, 0.266307f, 0.655042f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.912355f, 0.050050f, -0.406216f, -0.009562f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.322482f, 0.619251f, -0.605391f, 0.382145f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.609518f, -0.358452f, -0.358452f, 0.609518f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.998394f, -0.054851f, -0.005081f, 0.013241f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.028823f, -0.000687f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000003f, 0.003998f, 0.009633f, 0.999946f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(0.007374f, 0.713090f, 0.694619f, 0.094620f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.645959f, -0.287641f, 0.287641f, 0.645958f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.933659f, 0.062262f, -0.352442f, -0.013761f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.359474f, 0.599715f, -0.585854f, 0.409752f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.553955f, -0.439471f, -0.439471f, 0.553954f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.994042f, -0.043581f, -0.098740f, 0.015198f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.027542f, -0.001341f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000012f, 0.009405f, 0.005010f, 0.999943f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.075003f, 0.705698f, 0.678006f, 0.191502f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.610632f, -0.356551f, 0.356552f, 0.610631f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.937199f, 0.076533f, -0.339569f, -0.022198f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.386524f, 0.584164f, -0.570514f, 0.428795f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.475809f, 0.523073f, 0.523074f, -0.475809f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.973654f, -0.032284f, -0.225133f, 0.016452f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.025896f, -0.001876f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000028f, 0.011232f, -0.000000f, 0.999937f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.150338f, 0.688559f, 0.650997f, 0.281935f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.567252f, -0.422168f, 0.422168f, 0.567251f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.938701f, 0.090894f, -0.330871f, -0.033204f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.391189f, 0.583319f, -0.569798f, 0.426661f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.398316f, 0.584247f, 0.584247f, -0.398316f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.933164f, -0.022189f, -0.358447f, 0.015117f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.024614f, -0.002240f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000052f, 0.007652f, -0.005533f, 0.999955f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.210475f, 0.665541f, 0.624120f, 0.351040f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.543793f, -0.451983f, 0.451983f, 0.543793f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.952414f, 0.100768f, -0.284621f, -0.041765f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.366897f, 0.600940f, -0.588143f, 0.397926f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.348862f, 0.615058f, 0.615058f, -0.348861f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.881744f, -0.013885f, -0.471372f, 0.011952f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.024159f, -0.002377f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000197f, -0.002436f, -0.011232f, 0.999934f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.250448f, 0.646723f, 0.607617f, 0.387074f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.551074f, -0.443078f, 0.443078f, 0.551073f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.973107f, 0.103494f, -0.201607f, -0.041314f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.304640f, 0.636548f, -0.622721f, 0.337963f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.337490f, 0.621370f, 0.621370f, -0.337489f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.825828f, -0.010427f, -0.563740f, 0.009897f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.024475f, -0.002305f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000384f, -0.015389f, -0.016066f, 0.999752f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.267589f, 0.638620f, 0.607018f, 0.389986f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.585908f, -0.395869f, 0.395869f, 0.585907f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.990215f, 0.099691f, -0.092053f, -0.032578f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.207744f, 0.676963f, -0.660480f, 0.249659f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.364214f, 0.606093f, 0.606093f, -0.364213f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.774464f, -0.012423f, -0.632422f, 0.009732f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.025396f, -0.002092f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000530f, -0.025475f, -0.019064f, 0.999494f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.256258f, 0.644416f, 0.623592f, 0.360823f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.641701f, -0.297019f, 0.297019f, 0.641700f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.994580f, 0.091792f, 0.045122f, -0.018656f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.107080f, 0.703133f, -0.684881f, 0.158356f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.424052f, 0.565844f, 0.565845f, -0.424051f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.756151f, -0.017072f, -0.654103f, 0.009645f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.026719f, -0.001741f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000529f, -0.029054f, -0.020001f, 0.999378f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.236419f, 0.653785f, 0.640217f, 0.326793f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.670798f, -0.223673f, 0.223673f, 0.670798f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.989536f, 0.083128f, 0.117448f, -0.010663f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.024724f, 0.713651f, -0.694879f, 0.085053f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.498206f, 0.501788f, 0.501788f, -0.498205f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.776075f, -0.023361f, -0.630137f, 0.009412f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.028042f, -0.001263f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000518f, -0.026567f, -0.019267f, 0.999461f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.255984f, 0.647882f, 0.633611f, 0.336540f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.656303f, -0.263187f, 0.263187f, 0.656302f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.993998f, 0.075462f, 0.078319f, -0.011823f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.033420f, 0.715274f, -0.697085f, 0.036585f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.565043f, -0.425120f, -0.425120f, 0.565042f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.815762f, -0.031033f, -0.577475f, 0.009610f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.028962f, -0.000673f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000493f, -0.019326f, -0.016966f, 0.999669f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.286692f, 0.635817f, 0.621093f, 0.357476f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.635033f, -0.311020f, 0.311021f, 0.635032f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.997013f, 0.066200f, 0.037673f, -0.012818f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.067189f, 0.713894f, -0.696898f, 0.013204f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.613249f, -0.352031f, -0.352032f, 0.613248f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.857049f, -0.040303f, -0.513551f, 0.010370f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.029278f, 0.000000f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000384f, -0.008912f, -0.013224f, 0.999873f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.321820f, 0.619530f, 0.605276f, 0.382434f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.606762f, -0.363097f, 0.363098f, 0.606762f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.998357f, 0.055045f, -0.008311f, -0.013579f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.074264f, 0.712839f, -0.697184f, 0.016752f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.642484f, -0.295322f, -0.295323f, 0.642483f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.893687f, -0.051011f, -0.445628f, 0.011728f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.028823f, 0.000718f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000251f, 0.001501f, -0.008646f, 0.999961f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.359917f, 0.599308f, 0.585061f, 0.411087f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.549811f, -0.444643f, 0.444644f, 0.549811f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.993515f, 0.043109f, -0.104066f, -0.015506f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.044636f, 0.714035f, -0.696270f, 0.058054f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.644942f, -0.289914f, -0.289915f, 0.644941f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.913431f, -0.063406f, -0.401746f, 0.014976f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.027542f, 0.001386f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000118f, 0.008744f, -0.004044f, 0.999954f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.386674f, 0.584074f, 0.570204f, 0.429195f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.471740f, -0.526746f, 0.526746f, 0.471740f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.972170f, 0.031467f, -0.231575f, -0.016403f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.020007f, 0.713239f, -0.687252f, 0.136289f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.617903f, -0.343797f, -0.343798f, 0.617902f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.916016f, -0.077228f, -0.393035f, 0.021764f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.025896f, 0.001918f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000000f, 0.011232f, 0.000000f, 0.999937f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.390855f, 0.583794f, 0.570676f, 0.425142f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.396063f, -0.585777f, 0.585777f, 0.396062f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.931210f, 0.021429f, -0.363559f, -0.014649f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.095889f, 0.703003f, -0.666745f, 0.228131f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.573392f, -0.413790f, -0.413791f, 0.573391f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.915140f, -0.091205f, -0.391302f, 0.032909f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.024614f, 0.002259f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000128f, 0.007652f, 0.004407f, 0.999961f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.368076f, 0.600436f, 0.588414f, 0.397197f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.348400f, -0.615319f, 0.615319f, 0.348399f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.881566f, 0.013687f, -0.471719f, -0.011660f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.162047f, 0.684330f, -0.641669f, 0.306095f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.537867f, -0.459020f, -0.459020f, 0.537866f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.924908f, -0.101523f, -0.363747f, 0.043885f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.024159f, 0.002377f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000288f, -0.002436f, 0.009901f, 0.999948f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.312444f, 0.632618f, 0.619347f, 0.344358f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.336995f, -0.621638f, 0.621638f, 0.336995f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.831697f, 0.010586f, -0.555037f, -0.010137f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.211811f, 0.665110f, -0.622652f, 0.353651f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.532418f, -0.465329f, -0.465330f, 0.532417f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.948500f, -0.104644f, -0.295388f, 0.046306f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.024391f, 0.002316f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000442f, -0.015390f, 0.015218f, 0.999766f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.228328f, 0.669670f, 0.653365f, 0.269300f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.357414f, -0.610127f, 0.610127f, 0.357413f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.786357f, 0.012196f, -0.617566f, -0.010310f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.243815f, 0.651402f, -0.614463f, 0.372377f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.554195f, -0.439168f, -0.439168f, 0.554194f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.973904f, -0.101785f, -0.198840f, 0.040160f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.025078f, 0.002145f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000547f, -0.025475f, 0.018816f, 0.999498f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.139272f, 0.696431f, 0.677950f, 0.189659f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.403353f, -0.580781f, 0.580781f, 0.403353f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.762551f, 0.016096f, -0.646643f, -0.010475f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.255935f, 0.646259f, -0.617799f, 0.367656f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.596591f, -0.379578f, -0.379578f, 0.596590f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.991632f, -0.095469f, -0.081964f, 0.028874f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.026125f, 0.001880f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000545f, -0.029054f, 0.020001f, 0.999378f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.062194f, 0.710158f, 0.690926f, 0.120118f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.464498f, -0.533143f, 0.533144f, 0.464497f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.767507f, 0.021176f, -0.640610f, -0.010176f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.240632f, 0.652469f, -0.635242f, 0.335927f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.654887f, -0.266689f, -0.266690f, 0.654887f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.994122f, -0.086472f, 0.063429f, 0.014844f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.027312f, 0.001530f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000525f, -0.027227f, 0.019695f, 0.999435f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.002304f, 0.714893f, 0.695983f, 0.067315f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.526465f, -0.472054f, 0.472054f, 0.526464f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.793176f, 0.026956f, -0.608314f, -0.009908f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.221153f, 0.660236f, -0.649814f, 0.304830f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.682594f, -0.184571f, -0.184571f, 0.682593f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.986402f, -0.078243f, 0.144356f, 0.007104f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.028359f, 0.001102f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000477f, -0.021822f, 0.018637f, 0.999588f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(0.040022f, 0.715169f, 0.697026f, 0.032948f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.577871f, -0.407511f, 0.407512f, 0.577870f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.826411f, 0.033688f, -0.561971f, -0.009912f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.252512f, 0.649768f, -0.637068f, 0.328913f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.662572f, -0.246979f, -0.246980f, 0.662571f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.993343f, -0.072042f, 0.089347f, 0.009893f);
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
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
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
		pTmp->poBone[4].T = Vec3(0.029046f, 0.000595f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000358f, -0.013585f, 0.016631f, 0.999769f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(0.064943f, 0.714049f, 0.696873f, 0.016843f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.615034f, -0.348903f, 0.348903f, 0.615034f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.858806f, 0.041697f, -0.510496f, -0.010359f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.289180f, 0.634787f, -0.620598f, 0.358161f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.636622f, -0.307754f, -0.307754f, 0.636622f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.997048f, -0.064700f, 0.039540f, 0.012063f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

	}
}
