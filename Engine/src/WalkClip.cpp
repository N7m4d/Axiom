#include "WalkClip.h"
#include "AnimTime.h"
#include "Bone.h"
#include "Mixer.h"

namespace Axiom
{
    WalkClip::WalkClip(int numBones)
        : mNumBones(numBones),
          mNumFrames(0),
          mTotalTime(AnimTime::Duration::ZERO),
          mHead(nullptr)
    {
        privSetAnimationData();
        mTotalTime = privFindMaxTime();
        mNumFrames = privFindNumFrames();
    }

    WalkClip::~WalkClip()
    {
        FrameBucket* pTmp = mHead;

        while (pTmp != nullptr)
        {
            FrameBucket* pDeleteMe = pTmp;
            pTmp = pTmp->nextBucket;
            delete pDeleteMe;
            pDeleteMe = nullptr;
        }

        mHead = nullptr;
    }

    void WalkClip::AnimateBones(AnimTime curr, Bone* bone)
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

    int WalkClip::privFindNumFrames()
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

    AnimTime WalkClip::privFindMaxTime()
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

    AnimTime& WalkClip::GetTotalTime()
    {
        return mTotalTime;
    }

    void WalkClip::privSetAnimationData()
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
        pTmp->poBone[4].T = Vec3(0.026428f, 0.001437f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000500f, -0.020833f, 0.007737f, 0.999753f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.273342f, 0.650441f, 0.641298f, 0.301576f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.480434f, -0.518829f, 0.518829f, 0.480434f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.926996f, 0.010783f, -0.374829f, -0.008046f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.142469f, 0.693114f, -0.668960f, 0.227570f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.571355f, -0.416597f, -0.416598f, 0.571355f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.939128f, -0.065612f, -0.336303f, 0.025158f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.026878f, 0.001573f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000500f, -0.015882f, 0.011317f, 0.999810f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.248711f, 0.660774f, 0.651723f, 0.277088f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.492427f, -0.507460f, 0.507460f, 0.492427f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.919628f, 0.007867f, -0.392664f, -0.006086f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.157052f, 0.689055f, -0.665764f, 0.239365f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.581072f, -0.402934f, -0.402935f, 0.581071f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.951171f, -0.067765f, -0.300205f, 0.023637f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.027222f, 0.001670f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000499f, -0.009405f, 0.014569f, 0.999849f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.219280f, 0.671673f, 0.662507f, 0.248707f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.508527f, -0.491325f, 0.491326f, 0.508526f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.912469f, 0.005930f, -0.409080f, -0.004349f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.172767f, 0.684337f, -0.662070f, 0.251989f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.589800f, -0.390046f, -0.390046f, 0.589800f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.961425f, -0.069354f, -0.265285f, 0.021808f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.027433f, 0.001728f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000497f, -0.002066f, 0.017413f, 0.999846f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.186397f, 0.682144f, 0.672744f, 0.217604f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.528093f, -0.470231f, 0.470232f, 0.528093f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.906576f, 0.004900f, -0.422005f, -0.002822f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.189777f, 0.678816f, -0.657657f, 0.265858f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.596910f, -0.379076f, -0.379077f, 0.596909f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.969887f, -0.070408f, -0.232303f, 0.019922f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.027504f, 0.001748f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000495f, 0.005272f, 0.019790f, 0.999790f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.150795f, 0.691574f, 0.681919f, 0.184316f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.550164f, -0.444207f, 0.444207f, 0.550164f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.902516f, 0.004665f, -0.430629f, -0.001479f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.207858f, 0.672464f, -0.652450f, 0.280884f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.602208f, -0.370601f, -0.370602f, 0.602208f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.976750f, -0.070934f, -0.201488f, 0.018145f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.027417f, 0.001726f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000491f, 0.011749f, 0.021659f, 0.999696f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.113161f, 0.699465f, 0.689648f, 0.149429f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.573042f, -0.414273f, 0.414274f, 0.573042f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.900070f, 0.005147f, -0.435715f, -0.000345f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.226970f, 0.665203f, -0.646327f, 0.297071f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.605371f, -0.365412f, -0.365413f, 0.605370f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.982189f, -0.070909f, -0.173207f, 0.016630f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.027156f, 0.001662f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000486f, 0.016699f, 0.022997f, 0.999596f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.074389f, 0.705436f, 0.695611f, 0.113806f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.594617f, -0.382663f, 0.382663f, 0.594617f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.898272f, 0.006319f, -0.439393f, 0.000531f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.247223f, 0.656894f, -0.639114f, 0.314492f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.606099f, -0.364203f, -0.364203f, 0.606099f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.986410f, -0.070289f, -0.147697f, 0.015472f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.026738f, 0.001554f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000480f, 0.019743f, 0.023797f, 0.999522f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.035425f, 0.709271f, 0.699671f, 0.078363f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.613264f, -0.352004f, 0.352005f, 0.613264f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.895964f, 0.008159f, -0.444051f, 0.001071f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.268153f, 0.647592f, -0.630968f, 0.332563f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.604882f, -0.366221f, -0.366222f, 0.604881f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.989761f, -0.068983f, -0.124093f, 0.014656f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.026205f, 0.001404f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000472f, 0.020754f, 0.024061f, 0.999495f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(0.002603f, 0.711036f, 0.701761f, 0.044183f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.627851f, -0.325274f, 0.325274f, 0.627851f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.891876f, 0.010697f, -0.452152f, 0.001286f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.288816f, 0.637658f, -0.622406f, 0.350126f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.602842f, -0.369570f, -0.369571f, 0.602841f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.992561f, -0.066852f, -0.100782f, 0.014040f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.025631f, 0.001213f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000460f, 0.019504f, 0.023768f, 0.999527f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(0.038679f, 0.711091f, 0.701930f, 0.012171f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.637796f, -0.305313f, 0.305314f, 0.637796f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.884793f, 0.013967f, -0.465774f, 0.001253f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.307599f, 0.628259f, -0.614188f, 0.365304f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.601669f, -0.371476f, -0.371477f, 0.601668f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.994988f, -0.063914f, -0.075778f, 0.013073f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.025098f, 0.000986f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000444f, 0.015755f, 0.022881f, 0.999614f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(0.008006f, 0.712285f, 0.700156f, 0.048655f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.612932f, -0.352582f, 0.352583f, 0.612932f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.873157f, 0.018841f, -0.487073f, -0.001489f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.316669f, 0.624309f, -0.609920f, 0.371424f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.580290f, -0.404060f, -0.404060f, 0.580289f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.991437f, -0.060584f, -0.114703f, 0.015010f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.024680f, 0.000728f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000418f, 0.009732f, 0.021398f, 0.999724f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.016885f, 0.712305f, 0.697119f, 0.079754f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.591023f, -0.388190f, 0.388191f, 0.591023f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.866422f, 0.024358f, -0.498694f, -0.004885f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.324051f, 0.621116f, -0.606707f, 0.375649f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.558394f, -0.433816f, -0.433817f, 0.558393f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.986751f, -0.056417f, -0.151207f, 0.016617f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.024419f, 0.000447f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000355f, 0.002069f, 0.019329f, 0.999811f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.037331f, 0.711548f, 0.693499f, 0.106607f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.573264f, -0.413967f, 0.413968f, 0.573263f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.864757f, 0.030316f, -0.501195f, -0.008890f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.329252f, 0.619012f, -0.604930f, 0.377461f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.536924f, -0.460123f, -0.460123f, 0.536923f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.981152f, -0.051441f, -0.185416f, 0.017754f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.024332f, 0.000151f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000281f, -0.006200f, 0.016707f, 0.999841f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.054648f, 0.710167f, 0.689732f, 0.130181f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.560306f, -0.431344f, 0.431344f, 0.560305f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.867909f, 0.036419f, -0.495207f, -0.013330f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.332036f, 0.618233f, -0.604710f, 0.376650f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.516745f, -0.482675f, -0.482675f, 0.516744f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.974759f, -0.045821f, -0.217748f, 0.018197f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.024403f, -0.000151f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000203f, -0.013863f, 0.013581f, 0.999812f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.070259f, 0.708319f, 0.685897f, 0.151307f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.552078f, -0.441825f, 0.441826f, 0.552078f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.875028f, 0.042433f, -0.481886f, -0.017656f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.332281f, 0.618857f, -0.606078f, 0.373196f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(-0.498627f, 0.501369f, 0.501370f, -0.498627f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.967584f, -0.039758f, -0.248757f, 0.017878f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.024614f, -0.000447f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000127f, -0.019885f, 0.010029f, 0.999752f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.085088f, 0.705989f, 0.682119f, 0.170453f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.548460f, -0.446309f, 0.446310f, 0.548459f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.885259f, 0.048120f, -0.462104f, -0.021448f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.329397f, 0.621178f, -0.609281f, 0.366621f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(-0.483850f, 0.515645f, 0.515645f, -0.483849f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.959699f, -0.033480f, -0.278525f, 0.016779f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.024958f, -0.000728f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000058f, -0.023634f, 0.006154f, 0.999702f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.099498f, 0.703230f, 0.678514f, 0.187580f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.549407f, -0.445143f, 0.445143f, 0.549406f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.897839f, 0.053287f, -0.436415f, -0.024264f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.322454f, 0.625596f, -0.614657f, 0.356160f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(-0.474019f, 0.524696f, 0.524696f, -0.474019f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.951332f, -0.027243f, -0.306594f, 0.014980f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.025408f, -0.000986f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.024883f, 0.002074f, 0.999688f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.113640f, 0.700198f, 0.675095f, 0.202621f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.554394f, -0.438916f, 0.438917f, 0.554394f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.911767f, 0.057834f, -0.405799f, -0.025744f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.310883f, 0.632168f, -0.622143f, 0.341545f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(-0.470141f, 0.528174f, 0.528174f, -0.470141f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.942819f, -0.021356f, -0.332378f, 0.012707f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.025918f, -0.001213f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000057f, -0.023872f, -0.002074f, 0.999713f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.127511f, 0.696929f, 0.671922f, 0.215756f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.562362f, -0.428660f, 0.428660f, 0.562361f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.925947f, 0.061685f, -0.371677f, -0.025963f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.294626f, 0.640563f, -0.631274f, 0.323060f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(-0.472319f, 0.526227f, 0.526228f, -0.472318f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.934539f, -0.016118f, -0.355346f, 0.010279f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.026428f, -0.001404f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000120f, -0.020829f, -0.006154f, 0.999764f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.141437f, 0.693348f, 0.668891f, 0.227704f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.571884f, -0.415871f, 0.415871f, 0.571884f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.939377f, 0.064817f, -0.335760f, -0.025199f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.274283f, 0.650094f, -0.641253f, 0.301565f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(-0.479835f, 0.519382f, 0.519383f, -0.479835f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.926825f, -0.011770f, -0.375226f, 0.007977f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.026878f, -0.001554f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000189f, -0.015880f, -0.010030f, 0.999824f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.156065f, 0.689287f, 0.665692f, 0.239543f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.581520f, -0.402286f, 0.402287f, 0.581520f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.951353f, 0.067269f, -0.299730f, -0.023760f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.251491f, 0.659718f, -0.651004f, 0.278780f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(-0.491527f, 0.508331f, 0.508332f, -0.491527f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.920266f, -0.008445f, -0.391156f, 0.005974f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.027222f, -0.001662f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000259f, -0.009404f, -0.013582f, 0.999864f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.171902f, 0.684548f, 0.662007f, 0.252171f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.590159f, -0.389503f, 0.389504f, 0.590159f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.961549f, 0.069082f, -0.264894f, -0.021963f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.227762f, 0.668701f, -0.659814f, 0.256141f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.505745f, -0.494188f, -0.494188f, 0.505745f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.915030f, -0.006172f, -0.403316f, 0.004348f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.027433f, -0.001726f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000327f, -0.002066f, -0.016707f, 0.999858f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.189091f, 0.678990f, 0.657611f, 0.266014f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.597174f, -0.378659f, 0.378660f, 0.597174f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.969963f, 0.070281f, -0.232010f, -0.020068f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.203366f, 0.676942f, -0.667652f, 0.233737f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.521135f, -0.477932f, -0.477932f, 0.521134f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.910683f, -0.004911f, -0.413065f, 0.003082f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.027504f, -0.001748f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000388f, 0.005272f, -0.019329f, 0.999799f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.207390f, 0.672588f, 0.652426f, 0.280991f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.602382f, -0.370319f, 0.370320f, 0.602381f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.976793f, 0.070872f, -0.201296f, -0.018253f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.177994f, 0.684522f, -0.674691f, 0.211042f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.536922f, -0.460125f, -0.460125f, 0.536921f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.906845f, -0.004587f, -0.421434f, 0.002110f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.027433f, -0.001728f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000445f, 0.011748f, -0.021398f, 0.999702f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.226342f, 0.665415f, 0.646472f, 0.296761f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.605849f, -0.364619f, 0.364620f, 0.605849f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.982293f, 0.070882f, -0.172623f, -0.016628f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.151053f, 0.691525f, -0.681124f, 0.187206f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.552709f, -0.441036f, -0.441036f, 0.552709f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.903195f, -0.005069f, -0.429199f, 0.001355f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.027222f, -0.001670f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000472f, 0.016699f, -0.022881f, 0.999599f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.245641f, 0.657533f, 0.639774f, 0.313050f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.607636f, -0.361633f, 0.361634f, 0.607636f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.986691f, 0.070311f, -0.145821f, -0.015288f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.121894f, 0.697923f, -0.687019f, 0.161403f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.568206f, -0.420882f, -0.420883f, 0.568205f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.899371f, -0.006268f, -0.437141f, 0.000751f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.026878f, -0.001573f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000471f, 0.019743f, -0.023768f, 0.999522f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.264971f, 0.648994f, 0.632498f, 0.329458f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.608038f, -0.360957f, 0.360958f, 0.608038f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.990221f, 0.069072f, -0.120364f, -0.014284f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.089679f, 0.703541f, -0.692362f, 0.132747f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.583457f, -0.399472f, -0.399473f, 0.583456f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.895123f, -0.008119f, -0.445746f, 0.000349f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

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
        pTmp->poBone[4].T = Vec3(0.026428f, -0.001437f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000467f, 0.020754f, -0.024061f, 0.999495f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.283769f, 0.640053f, 0.624981f, 0.345263f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.607754f, -0.361434f, 0.361434f, 0.607754f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.993101f, 0.067074f, -0.095232f, -0.013508f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.053302f, 0.708164f, -0.696895f, 0.099999f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.598964f, -0.375822f, -0.375823f, 0.598963f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.890456f, -0.010573f, -0.454947f, 0.000050f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 11 
        pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
        pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
        pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Keyframe: 28  time: 1.166667 seconds

        pTmpX = new FrameBucket();
        pTmpX->prevBucket = pTmp;
        pTmpX->nextBucket = nullptr;
        pTmpX->KeyTime = 28 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
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
        pTmp->poBone[4].T = Vec3(0.025918f, -0.001264f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000458f, 0.019743f, -0.023797f, 0.999522f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.301135f, 0.631494f, 0.617595f, 0.359317f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.607884f, -0.361216f, 0.361216f, 0.607884f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.995453f, 0.064386f, -0.069072f, -0.012490f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.011102f, 0.711132f, -0.700272f, 0.061532f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.615511f, -0.348060f, -0.348061f, 0.615511f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.885597f, -0.013539f, -0.464258f, -0.000041f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 11 
        pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
        pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
        pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Keyframe: 29  time: 1.208333 seconds

        pTmpX = new FrameBucket();
        pTmpX->prevBucket = pTmp;
        pTmpX->nextBucket = nullptr;
        pTmpX->KeyTime = 29 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
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
        pTmp->poBone[4].T = Vec3(0.025408f, -0.001058f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000442f, 0.016699f, -0.022997f, 0.999596f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.315822f, 0.624065f, 0.611350f, 0.370204f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.609744f, -0.358067f, 0.358068f, 0.609744f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.997263f, 0.060875f, -0.040447f, -0.011197f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.038623f, 0.711525f, -0.701429f, 0.015452f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.633004f, -0.315129f, -0.315130f, 0.633003f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.879920f, -0.016969f, -0.474820f, -0.000164f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 11 
        pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
        pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
        pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Keyframe: 30  time: 1.250000 seconds

        pTmpX = new FrameBucket();
        pTmpX->prevBucket = pTmp;
        pTmpX->nextBucket = nullptr;
        pTmpX->KeyTime = 30 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
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
        pTmp->poBone[4].T = Vec3(0.024958f, -0.000822f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000418f, 0.011748f, -0.021658f, 0.999696f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.323346f, 0.620904f, 0.607842f, 0.374771f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.588243f, -0.392390f, 0.392390f, 0.588243f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.994832f, 0.057129f, -0.082888f, -0.013207f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.010273f, 0.712678f, -0.699672f, 0.049439f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.609650f, -0.358228f, -0.358229f, 0.609649f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.870023f, -0.022054f, -0.492509f, 0.002900f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 11 
        pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
        pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
        pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Keyframe: 31  time: 1.291667 seconds

        pTmpX = new FrameBucket();
        pTmpX->prevBucket = pTmp;
        pTmpX->nextBucket = nullptr;
        pTmpX->KeyTime = 31 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
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
        pTmp->poBone[4].T = Vec3(0.024614f, -0.000562f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000385f, 0.005272f, -0.019789f, 0.999790f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.329223f, 0.618520f, 0.605339f, 0.377637f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.565991f, -0.423856f, 0.423856f, 0.565991f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.990819f, 0.052733f, -0.123599f, -0.014850f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.013425f, 0.712754f, -0.696818f, 0.079038f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.589173f, -0.390993f, -0.390993f, 0.589172f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.864715f, -0.027624f, -0.501460f, 0.006530f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 11 
        pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
        pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
        pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Keyframe: 32  time: 1.333333 seconds

        pTmpX = new FrameBucket();
        pTmpX->prevBucket = pTmp;
        pTmpX->nextBucket = nullptr;
        pTmpX->KeyTime = 32 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
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
        pTmp->poBone[4].T = Vec3(0.024403f, -0.000285f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000323f, -0.002067f, -0.017413f, 0.999846f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.333280f, 0.617035f, 0.603998f, 0.378653f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.543638f, -0.452170f, 0.452171f, 0.543638f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.985377f, 0.047746f, -0.162775f, -0.016046f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.033764f, 0.712044f, -0.693369f, 0.105319f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.572382f, -0.415186f, -0.415187f, 0.572381f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.863928f, -0.033488f, -0.502388f, 0.010621f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 11 
        pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
        pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
        pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Keyframe: 33  time: 1.375000 seconds

        pTmpX = new FrameBucket();
        pTmpX->prevBucket = pTmp;
        pTmpX->nextBucket = nullptr;
        pTmpX->KeyTime = 33 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
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
        pTmp->poBone[4].T = Vec3(0.024332f, 0.000000f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000254f, -0.009404f, -0.014568f, 0.999850f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.335359f, 0.616596f, 0.603902f, 0.377686f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.522016f, -0.476969f, 0.476970f, 0.522015f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.978640f, 0.042307f, -0.200493f, -0.016634f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.051849f, 0.710613f, -0.689692f, 0.129097f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.559737f, -0.432081f, -0.432082f, 0.559737f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.867350f, -0.039380f, -0.495911f, 0.015036f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 11 
        pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
        pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
        pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Keyframe: 34  time: 1.416667 seconds

        pTmpX = new FrameBucket();
        pTmpX->prevBucket = pTmp;
        pTmpX->nextBucket = nullptr;
        pTmpX->KeyTime = 34 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
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
        pTmp->poBone[4].T = Vec3(0.024403f, 0.000285f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000184f, -0.015881f, -0.011316f, 0.999810f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.335035f, 0.617471f, 0.605281f, 0.374320f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.502364f, -0.497624f, 0.497625f, 0.502364f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.970790f, 0.036575f, -0.236552f, -0.016508f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.068620f, 0.708621f, -0.685870f, 0.150765f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.551482f, -0.442569f, -0.442570f, 0.551482f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.874467f, -0.045089f, -0.482603f, 0.019227f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 11 
        pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
        pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
        pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Keyframe: 35  time: 1.458333 seconds

        pTmpX = new FrameBucket();
        pTmpX->prevBucket = pTmp;
        pTmpX->nextBucket = nullptr;
        pTmpX->KeyTime = 35 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
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
        pTmp->poBone[4].T = Vec3(0.024614f, 0.000562f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000116f, -0.020830f, -0.007736f, 0.999753f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.331470f, 0.620114f, 0.608568f, 0.367739f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.486415f, -0.513226f, 0.513226f, 0.486414f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.962135f, 0.030724f, -0.270387f, -0.015622f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.084540f, 0.706109f, -0.682085f, 0.170361f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.547848f, -0.447060f, -0.447061f, 0.547847f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.884722f, -0.050396f, -0.462827f, 0.022783f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 11 
        pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
        pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
        pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Keyframe: 36  time: 1.500000 seconds

        pTmpX = new FrameBucket();
        pTmpX->prevBucket = pTmp;
        pTmpX->nextBucket = nullptr;
        pTmpX->KeyTime = 36 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
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
        pTmp->poBone[4].T = Vec3(0.024958f, 0.000822f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000054f, -0.023874f, -0.003927f, 0.999707f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.323806f, 0.624881f, 0.614068f, 0.357204f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.475791f, -0.523090f, 0.523091f, 0.475790f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.953085f, 0.024978f, -0.301342f, -0.014058f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.099762f, 0.703188f, -0.678484f, 0.187705f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.548791f, -0.445901f, -0.445902f, 0.548791f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.897346f, -0.055141f, -0.437138f, 0.025313f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 11 
        pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
        pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
        pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Keyframe: 37  time: 1.541667 seconds

        pTmpX = new FrameBucket();
        pTmpX->prevBucket = pTmp;
        pTmpX->nextBucket = nullptr;
        pTmpX->KeyTime = 37 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
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
        pTmp->poBone[4].T = Vec3(0.025408f, 0.001058f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.024885f, -0.000000f, 0.999690f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.311538f, 0.631790f, 0.621697f, 0.342460f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.471420f, -0.527032f, 0.527032f, 0.471420f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.944075f, 0.019603f, -0.328929f, -0.012030f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.114334f, 0.700057f, -0.675104f, 0.202691f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.553789f, -0.439679f, -0.439679f, 0.553789f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.911336f, -0.059260f, -0.406512f, 0.026513f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 11 
        pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
        pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
        pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Keyframe: 38  time: 1.583333 seconds

        pTmpX = new FrameBucket();
        pTmpX->prevBucket = pTmp;
        pTmpX->nextBucket = nullptr;
        pTmpX->KeyTime = 38 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
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
        pTmp->poBone[4].T = Vec3(0.025918f, 0.001264f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000054f, -0.023873f, 0.003927f, 0.999707f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.294653f, 0.640481f, 0.630971f, 0.323789f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.473259f, -0.525382f, 0.525382f, 0.473259f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.935406f, 0.014862f, -0.353126f, -0.009829f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.128386f, 0.696741f, -0.671979f, 0.215671f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.561788f, -0.429412f, -0.429413f, 0.561787f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.925587f, -0.062709f, -0.372363f, 0.026487f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 11 
        pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
        pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
        pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Keyframe: 39  time: 1.625000 seconds

        pTmpX = new FrameBucket();
        pTmpX->prevBucket = pTmp;
        pTmpX->nextBucket = nullptr;
        pTmpX->KeyTime = 39 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
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
        pTmp->poBone[4].T = Vec3(0.026428f, 0.001437f, 0.000000f);
        pTmp->poBone[4].Q = Quat(0.000116f, -0.020830f, 0.007736f, 0.999753f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.273412f, 0.650407f, 0.641251f, 0.301684f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.480448f, -0.518816f, 0.518817f, 0.480447f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[7].Q = Quat(0.927060f, 0.010960f, -0.374673f, -0.007709f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.142395f, 0.693133f, -0.668972f, 0.227524f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
        pTmp->poBone[9].Q = Quat(0.571363f, -0.416587f, -0.416588f, 0.571362f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[10].Q = Quat(0.939094f, -0.065492f, -0.336395f, 0.025523f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 11 
        pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
        pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
        pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);
    }
}
