#include "SideStepLeftClip.h"
#include "AnimTime.h"
#include "Bone.h"
#include "Mixer.h"

namespace Axiom
{
    SideStepLeftClip::SideStepLeftClip(int numBones)
        : mNumBones(numBones),
          mNumFrames(0),
          mTotalTime(AnimTime::Duration::ZERO),
          mHead(nullptr)
    {
        privSetAnimationData();
        mTotalTime = privFindMaxTime();
        mNumFrames = privFindNumFrames();
    }

    SideStepLeftClip::~SideStepLeftClip()
    {
        FrameBucket* pTmp = mHead;

        while (pTmp != nullptr)
        {
            FrameBucket* pDeleteMe = pTmp;
            pTmp = pTmp->nextBucket;
            delete pDeleteMe;
        }
    }

    void SideStepLeftClip::AnimateBones(AnimTime curr, Bone* bone)
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

    void SideStepLeftClip::AnimateBonesReverse(AnimTime curr, Bone* bone)
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

    int SideStepLeftClip::privFindNumFrames()
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

    AnimTime SideStepLeftClip::privFindMaxTime()
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

    AnimTime& SideStepLeftClip::GetTotalTime()
    {
        return mTotalTime;
    }

    void SideStepLeftClip::privSetAnimationData()
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
        pTmp->poBone[4].T = Vec3(0.025762f, 0.001041f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.003044f, 0.037526f, 0.999291f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.290807f, 0.648498f, 0.690770f, 0.133112f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.598858f, -0.375991f, 0.375992f, 0.598857f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.957359f, -0.146228f, -0.245308f, 0.043658f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.351696f, -0.624074f, 0.683699f, -0.139275f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.556716f, -0.435967f, -0.435967f, 0.556716f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.947754f, 0.108616f, -0.295965f, -0.048672f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.025448f, 0.000512f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.006511f, 0.032121f, 0.999463f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.290959f, 0.648355f, 0.685019f, 0.160397f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.580374f, -0.403938f, 0.403938f, 0.580374f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.954554f, -0.121046f, -0.269260f, 0.040919f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.357349f, -0.621459f, 0.683428f, -0.137903f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.550737f, -0.443496f, -0.443496f, 0.550737f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.944544f, 0.117710f, -0.301715f, -0.054299f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.025341f, 0.000000f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.010445f, 0.024857f, 0.999636f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.285361f, 0.650265f, 0.680203f, 0.181793f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.567549f, -0.421768f, 0.421768f, 0.567549f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.953107f, -0.094770f, -0.285300f, 0.034784f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.360687f, -0.619753f, 0.682285f, -0.142473f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.541921f, -0.454227f, -0.454228f, 0.541920f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.940785f, 0.122704f, -0.310497f, -0.058816f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.025448f, -0.000560f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.013914f, 0.016525f, 0.999767f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.273925f, 0.654244f, 0.676136f, 0.199425f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.560788f, -0.430717f, 0.430717f, 0.560788f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.953152f, -0.066619f, -0.293952f, 0.025602f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.362721f, -0.618586f, 0.680238f, -0.151862f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.530955f, -0.466997f, -0.466998f, 0.530955f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.936672f, 0.124434f, -0.321397f, -0.062171f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.025762f, -0.001097f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.016191f, 0.008019f, 0.999837f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.257749f, 0.659775f, 0.673108f, 0.212576f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.560894f, -0.430579f, 0.430579f, 0.560893f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.954734f, -0.038499f, -0.294580f, 0.014960f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.361508f, -0.618876f, 0.677436f, -0.165486f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.520195f, -0.478954f, -0.478955f, 0.520195f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.933246f, 0.121538f, -0.332182f, -0.062736f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.026241f, -0.001578f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.016961f, -0.000000f, 0.999856f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.238300f, 0.666170f, 0.671135f, 0.221377f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.567130f, -0.422331f, 0.422332f, 0.567129f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.957582f, -0.011620f, -0.287891f, 0.004529f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.354621f, -0.621737f, 0.674576f, -0.180649f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.513750f, -0.485861f, -0.485862f, 0.513749f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.931932f, 0.114061f, -0.339077f, -0.059323f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.026785f, -0.001981f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.016191f, -0.008255f, 0.999835f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.218880f, 0.672212f, 0.669938f, 0.226726f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.576588f, -0.409324f, 0.409324f, 0.576588f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.960797f, 0.013317f, -0.276896f, -0.004403f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.340436f, -0.627775f, 0.672178f, -0.195392f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.514491f, -0.485076f, -0.485077f, 0.514491f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.933531f, 0.103045f, -0.339410f, -0.051991f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.027264f, -0.002291f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.013916f, -0.016871f, 0.999761f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.202445f, 0.676990f, 0.668855f, 0.230938f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.585816f, -0.396004f, 0.396004f, 0.585816f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.963358f, 0.036014f, -0.265541f, -0.011502f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.320526f, -0.636001f, 0.670165f, -0.208913f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.521747f, -0.477263f, -0.477264f, 0.521746f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.937519f, 0.089789f, -0.333472f, -0.042330f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.027579f, -0.002492f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.010448f, -0.025197f, 0.999628f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.190423f, 0.680117f, 0.667272f, 0.236492f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.592324f, -0.386202f, 0.386203f, 0.592324f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.964590f, 0.056394f, -0.257076f, -0.017257f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.297545f, -0.644941f, 0.667592f, -0.223247f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.531547f, -0.466324f, -0.466324f, 0.531546f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.942421f, 0.073500f, -0.324720f, -0.031568f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.027685f, -0.002563f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.006514f, -0.032376f, 0.999454f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.182751f, 0.681822f, 0.664733f, 0.244642f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.595048f, -0.381992f, 0.381992f, 0.595048f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.964290f, 0.074472f, -0.253193f, -0.022168f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.272871f, -0.653749f, 0.663590f, -0.240421f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.540644f, -0.455746f, -0.455747f, 0.540643f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.947015f, 0.052588f, -0.316219f, -0.020060f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.027568f, -0.002500f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.003046f, -0.037672f, 0.999286f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.178498f, 0.682516f, 0.660940f, 0.255868f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.593618f, -0.384210f, 0.384210f, 0.593618f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.962443f, 0.090457f, -0.254562f, -0.026803f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.247078f, 0.662016f, -0.658238f, 0.259634f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.548323f, -0.446478f, -0.446478f, 0.548322f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.950754f, 0.027240f, -0.308640f, -0.008182f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.027222f, -0.002313f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.000769f, -0.040762f, 0.999169f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.176618f, 0.682265f, 0.655899f, 0.270403f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.587848f, -0.392983f, 0.392983f, 0.587847f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.959040f, 0.104647f, -0.261266f, -0.032114f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.220450f, 0.669487f, -0.651832f, 0.279828f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.554479f, -0.438809f, -0.438809f, 0.554479f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.953269f, -0.001812f, -0.302092f, 0.003958f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.026696f, -0.002007f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000000f, -0.000000f, -0.041730f, 0.999129f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.175823f, 0.681428f, 0.649853f, 0.287111f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.578662f, -0.406386f, 0.406387f, 0.578662f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.954435f, 0.117160f, -0.271770f, -0.038329f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.192374f, 0.676249f, -0.645009f, 0.299403f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.560355f, -0.431280f, -0.431281f, 0.560354f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.954702f, -0.033637f, -0.295202f, 0.016350f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.026098f, -0.001595f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.000919f, -0.040810f, 0.999167f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.174158f, 0.680658f, 0.643598f, 0.303569f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.568406f, -0.420612f, 0.420613f, 0.568406f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.949483f, 0.127959f, -0.282980f, -0.045071f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.161775f, 0.682592f, -0.638953f, 0.315651f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.568283f, -0.420779f, -0.420779f, 0.568282f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.955688f, -0.066836f, -0.285283f, 0.028392f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.025571f, -0.001101f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.003639f, -0.037840f, 0.999277f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.169216f, 0.680791f, 0.638241f, 0.317076f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.560317f, -0.431330f, 0.431330f, 0.560316f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.945391f, 0.136886f, -0.291283f, -0.051493f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.128576f, 0.688589f, -0.635001f, 0.325710f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.579924f, -0.404585f, -0.404585f, 0.579923f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.956827f, -0.099727f, -0.270236f, 0.038846f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.025225f, -0.000556f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.007783f, -0.032687f, 0.999435f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.197216f, 0.674136f, 0.640065f, 0.311390f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.542023f, -0.454105f, 0.454105f, 0.542023f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.942725f, 0.107885f, -0.312496f, -0.044459f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.141983f, 0.686138f, -0.634793f, 0.325718f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.568401f, -0.420619f, -0.420620f, 0.568400f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.953382f, -0.094614f, -0.283802f, 0.039581f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.025108f, 0.000000f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.012483f, -0.025608f, 0.999594f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.223275f, 0.667256f, 0.642942f, 0.302561f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.525788f, -0.472808f, 0.472808f, 0.525787f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.940044f, 0.076861f, -0.330520f, -0.034141f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.152916f, 0.684527f, -0.636990f, 0.319818f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.561465f, -0.429834f, -0.429834f, 0.561465f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.951499f, -0.089329f, -0.291842f, 0.038707f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.025198f, 0.000537f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.016626f, -0.017286f, 0.999712f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.247748f, 0.660124f, 0.646440f, 0.291500f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.512164f, -0.487533f, 0.487533f, 0.512164f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.937304f, 0.044944f, -0.344961f, -0.021039f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.162511f, 0.683363f, -0.641037f, 0.309315f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.558760f, -0.433344f, -0.433345f, 0.558760f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.951107f, -0.083350f, -0.295182f, 0.036261f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.025465f, 0.001039f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.019345f, -0.008538f, 0.999776f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.270454f, 0.652932f, 0.650441f, 0.278319f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.502423f, -0.497566f, 0.497566f, 0.502422f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.934854f, 0.013060f, -0.354742f, -0.005945f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.171232f, 0.682368f, -0.646309f, 0.295531f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.559944f, -0.431813f, -0.431814f, 0.559944f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.952098f, -0.076431f, -0.294303f, 0.032456f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.025885f, 0.001489f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.020264f, 0.000000f, 0.999795f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.289757f, 0.646470f, 0.655063f, 0.262698f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.498726f, -0.501271f, 0.501271f, 0.498726f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.933485f, -0.017611f, -0.358054f, 0.009637f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.179250f, 0.681401f, -0.652390f, 0.279192f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.564719f, -0.425550f, -0.425550f, 0.564718f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.954368f, -0.068240f, -0.289423f, 0.027536f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.026397f, 0.001870f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.019561f, 0.008302f, 0.999774f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.303584f, 0.641766f, 0.660215f, 0.245131f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.502251f, -0.497739f, 0.497739f, 0.502251f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.933794f, -0.045842f, -0.354071f, 0.023670f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.187371f, 0.680171f, -0.658814f, 0.261198f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.571722f, -0.416093f, -0.416094f, 0.571722f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.957416f, -0.058626f, -0.281839f, 0.022001f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.026909f, 0.002173f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.017462f, 0.016430f, 0.999713f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.311126f, 0.639345f, 0.665537f, 0.226934f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.512250f, -0.487443f, 0.487443f, 0.512249f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.935807f, -0.070688f, -0.343624f, 0.034512f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.196958f, 0.678216f, -0.664962f, 0.243014f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.578891f, -0.406060f, -0.406061f, 0.578891f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.960485f, -0.047552f, -0.273752f, 0.016362f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.027329f, 0.002390f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.014158f, 0.023999f, 0.999612f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.313380f, 0.638919f, 0.670635f, 0.209343f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.526509f, -0.472005f, 0.472005f, 0.526509f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.939037f, -0.091730f, -0.328731f, 0.041611f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(0.209126f, 0.675155f, -0.670220f, 0.226357f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.584358f, -0.398152f, -0.398153f, 0.584358f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.962889f, -0.035001f, -0.267397f, 0.010894f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.027596f, 0.002520f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.010133f, 0.030547f, 0.999482f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.312881f, 0.639511f, 0.675542f, 0.191763f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.542774f, -0.453207f, 0.453208f, 0.542773f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.942753f, -0.110460f, -0.311289f, 0.045987f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.224292f, -0.670829f, 0.674284f, -0.212184f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.587003f, -0.394244f, -0.394244f, 0.587002f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.964200f, -0.020938f, -0.264288f, 0.005543f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.027685f, 0.002563f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.006107f, 0.035674f, 0.999345f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.311415f, 0.640404f, 0.680297f, 0.173491f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.559368f, -0.432559f, 0.432560f, 0.559367f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.946351f, -0.127953f, -0.292720f, 0.048601f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.242064f, -0.665323f, 0.677182f, -0.200439f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.586573f, -0.394882f, -0.394883f, 0.586573f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.964274f, -0.005303f, -0.264855f, 0.000000f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.027579f, 0.002489f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.002802f, 0.039186f, 0.999228f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.309081f, 0.641531f, 0.684423f, 0.156435f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.574323f, -0.412496f, 0.412496f, 0.574323f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.949468f, -0.142540f, -0.275203f, 0.049554f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.262480f, -0.658549f, 0.679127f, -0.190274f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.582925f, -0.400248f, -0.400249f, 0.582924f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.962969f, 0.012584f, -0.269241f, -0.006395f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.027264f, 0.002279f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.000703f, 0.041137f, 0.999153f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.306241f, 0.642746f, 0.687435f, 0.143272f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.585621f, -0.396292f, 0.396293f, 0.585621f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.951842f, -0.152399f, -0.261419f, 0.049315f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.285570f, -0.650370f, 0.680315f, -0.180665f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.576101f, -0.410009f, -0.410010f, 0.576101f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.960145f, 0.033234f, -0.277147f, -0.014395f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.026785f, 0.001953f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000000f, -0.000000f, 0.041731f, 0.999129f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.302692f, 0.644142f, 0.689275f, 0.135493f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.592786f, -0.385494f, 0.385494f, 0.592785f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.953650f, -0.156445f, -0.252479f, 0.048278f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.310090f, -0.641110f, 0.681090f, -0.170111f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.567460f, -0.421887f, -0.421888f, 0.567460f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.956076f, 0.056451f, -0.286594f, -0.024430f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.026241f, 0.001532f, -0.000000f);
        pTmp->poBone[4].Q = Quat(0.000000f, -0.000769f, 0.040729f, 0.999170f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.297700f, 0.646004f, 0.690245f, 0.132719f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.596731f, -0.379358f, 0.379358f, 0.596730f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.955366f, -0.154236f, -0.247653f, 0.046431f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.333346f, -0.631792f, 0.682018f, -0.156752f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.559841f, -0.431947f, -0.431948f, 0.559840f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.951570f, 0.081844f, -0.294110f, -0.036275f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

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
        pTmp->poBone[4].T = Vec3(0.025762f, 0.001041f, -0.000000f);
        pTmp->poBone[4].Q = Quat(-0.000000f, -0.003046f, 0.037549f, 0.999290f);
        pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 5 
        pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
        pTmp->poBone[5].Q = Quat(-0.290782f, 0.648507f, 0.690771f, 0.133120f);
        pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 6 
        pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[6].Q = Quat(-0.598866f, -0.375978f, 0.375978f, 0.598866f);
        pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 7 
        pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
        pTmp->poBone[7].Q = Quat(0.957362f, -0.146227f, -0.245297f, 0.043653f);
        pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

        // Bone: 8 
        pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
        pTmp->poBone[8].Q = Quat(-0.351717f, -0.624065f, 0.683699f, -0.139264f);
        pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 9 
        pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
        pTmp->poBone[9].Q = Quat(0.556708f, -0.435977f, -0.435978f, 0.556708f);
        pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 10 
        pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
        pTmp->poBone[10].Q = Quat(0.947751f, 0.108616f, -0.295974f, -0.048678f);
        pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

        // Bone: 11 
        pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
        pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
        pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);
    }
}
