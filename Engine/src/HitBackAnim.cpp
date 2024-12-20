#include "HitBackAnim.h"
#include "MathEngine.h"
#include "MathApp.h"
#include "HitBackClip.h"
#include "GameObjectAnimSkin.h"

namespace Axiom
{
    HitBackAnim::HitBackAnim()
        : mSkeleton(new HitBackSkeleton(mBone, mNumBones))
    {
        assert(mSkeleton);

        mClip = new HitBackClip(mNumBones);
        assert(mClip);
    }

    HitBackAnim::~HitBackAnim()
    {
        delete mSkeleton;
    }

    AnimTime HitBackAnim::FindMaxTime()
    {
        assert(mClip);
        return mClip->GetTotalTime();
    }

    void HitBackAnim::PoseSkeleton(GameObjectAnimSkeleton* node)
    {
        assert(node);

        GameObjectAnimSkeleton* childNode = (GameObjectAnimSkeleton*)node->GetChild();
        GameObjectAnimSkeleton* parentNode = node;

        if (parentNode != nullptr && childNode != nullptr)
        {
            Vec3 start(0.0f, 0.0f, 0.0f);

            Vec3 ptA(Vec4(start, 1) * *parentNode->GetWorld());
            Vec3 ptB(Vec4(start, 1) * *childNode->GetWorld());

            Vec3 dir = ptB - ptA;

            float mag = dir.len();

            Scale scale(1, 1, mag);
            Quat quat(Orient::LocalToWorld, dir.getNorm(), Vec3(0.0f, 1.0f, 0.0f));
            Trans trans(ptA);
            Mat4 boneOrient = scale * quat * trans;
            parentNode->SetBoneOrientation(boneOrient);
        }

        if (parentNode != nullptr && childNode == nullptr)
        {
            GameObjectAnimSkin* grandParentNode = (GameObjectAnimSkin*)parentNode->GetParent();
            assert(grandParentNode);

            Vec3 grandParentWorld(Vec4(0, 0, 0, 1) * *grandParentNode->GetWorld());
            Vec3 parentWorld(Vec4(0, 0, 0, 1) * *parentNode->GetWorld());
            Vec3 dir = parentWorld - grandParentWorld;
            float mag = dir.len();

            Vec3 pTmp3(Vec4(0, 0, 0, 1) * *parentNode->GetWorld());
            Vec3 pTmp4(Vec4(1, 0, 0, 1) * *parentNode->GetWorld());
            dir = pTmp4 - pTmp3;

            Scale scale(1.0f, 1.0f, mag);
            Rot rot(Orient::LocalToWorld, dir.getNorm(), Vec3(0.0f, 1.0f, 0.0f));
            Trans trans(parentWorld);

            Mat4 mTmp = scale * rot * trans;
            parentNode->SetBoneOrientation(mTmp);
        }
    }
}
