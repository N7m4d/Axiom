#include "GameObjectAnimSkin.h"

#include "MathEngine.h"
#include "GraphicsObject.h"
#include "WalkAnim.h"

namespace Axiom
{
    GameObjectAnimSkin::GameObjectAnimSkin(GraphicsObject* graphicsObject, Bone* bone)
        : GameObjectAnim(graphicsObject)
          , mScale(new Vec3(1.0f, 1.0f, 1.0f))
          , mQuat(new Quat(0.0f, 0.0f, 0.0f, 1.0f))
          , mTrans(new Vec3(0.0f, 0.0f, 0.0f))
          , mLocal(new Mat4(Identity))
          , mBoneResult(bone)
          , mBoneOrientation(new Mat4(Identity))
    {
        assert(graphicsObject);
        assert(bone);
        assert(mBoneOrientation);
        assert(mTrans);
        assert(mScale);
        assert(mQuat);
        assert(mLocal);
    }

    GameObjectAnimSkin::~GameObjectAnimSkin()
    {
        delete mTrans;
        delete mScale;
        delete mQuat;
        delete mLocal;
        delete mBoneOrientation;
    }

    void GameObjectAnimSkin::PrivUpdate(AnimTime& currentTime)
    {
        AZUL_UNUSED_VAR(currentTime);

        Trans trans;
        Scale scale;
        Quat quat;

        GameObjectAnimSkin* pParentObject = (GameObjectAnimSkin*)this->GetParent();
        Mat4 matParent(Identity);

        if (pParentObject)
        {
            matParent = *pParentObject->mWorld;

            trans.set(mBoneResult[mIndex].T);
            scale.set(mBoneResult[mIndex].S);
            quat = mBoneResult[mIndex].Q;
        }
        else
        {
            trans.set(0, 0, 0);
            scale.set(1, 1, 1);
            quat.set(Identity);
        }

        // world matrix
        *mLocal = scale * quat * trans;
        *mWorld = *mLocal * matParent;
    }

    void GameObjectAnimSkin::Update(AnimTime& currentTime)
    {
        PrivUpdate(currentTime);
        mGraphicsObject->SetWorld(*mWorld);
    }

    void GameObjectAnimSkin::SetQuat(const float qx, const float qy, const float qz, const float qw) const
    {
        mQuat->set(qx, qy, qz, qw);
    }

    void GameObjectAnimSkin::SetScale(const float sx, const float sy, const float sz) const
    {
        mScale->set(sx, sy, sz);
    }

    void GameObjectAnimSkin::SetTrans(const float x, const float y, const float z) const
    {
        mTrans->set(x, y, z);
    }

    void GameObjectAnimSkin::SetIndex(const int i)
    {
        mIndex = i;
    }

    void GameObjectAnimSkin::SetScale(Vec3& r)
    {
        *mScale = r;
    }

    void GameObjectAnimSkin::SetQuat(Quat& r)
    {
        *mQuat = r;
    }

    void GameObjectAnimSkin::SetTrans(Vec3& r)
    {
        *mTrans = r;
    }

    void GameObjectAnimSkin::SetBoneOrientation(const Mat4& tmp)
    {
        *mBoneOrientation = tmp;
    }

    Mat4 GameObjectAnimSkin::GetBoneOrientation(void) const
    {
        return Mat4(*mBoneOrientation);
    }
}
