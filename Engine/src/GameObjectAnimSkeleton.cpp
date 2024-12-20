#include "GameObjectAnimSkeleton.h"

#include "MathEngine.h"
#include "GameObject.h"
#include "GraphicsObject.h"
#include "SideStepLeftAnim.h"

namespace Axiom
{
    GameObjectAnimSkeleton::GameObjectAnimSkeleton(GraphicsObject* graphicsObject, Bone* bone)
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

    GameObjectAnimSkeleton::~GameObjectAnimSkeleton()
    {
        delete mTrans;
        delete mScale;
        delete mQuat;
        delete mLocal;
        delete mBoneOrientation;
    }

    void GameObjectAnimSkeleton::PrivUpdate(AnimTime& currTime)
    {
        AZUL_UNUSED_VAR(currTime);

        Trans trans;
        Scale scale;
        Quat quat;

        GameObjectAnimSkeleton* parentObject = (GameObjectAnimSkeleton*)GetParent();
        Mat4 matParent(Identity);

        if (parentObject)
        {
            matParent = *parentObject->mWorld;

            // REMEMBER this is for Animation and hierarchy, 
            //          you need to handle models differently
            // Get the result bone array, from there make the matrix
            trans.set(this->mBoneResult[mIndex].T);
            scale.set(this->mBoneResult[mIndex].S);
            quat = this->mBoneResult[mIndex].Q;
        }
        else
        {
            trans.set(0, 0, 0);
            scale.set(1, 1, 1);
            quat.set(Identity);
        }

        *mLocal = scale * quat * trans;
        *mWorld = *mLocal * matParent;
    }

    void GameObjectAnimSkeleton::Update(AnimTime& currentTime)
    {
        // Goal: update the world matrix
        PrivUpdate(currentTime);

        // This updates the orientation
        SideStepLeftAnim::PoseSkeleton(this);

        // push to graphics object
        Mat4 tmp = *mBoneOrientation;

        // push to graphics object
        mGraphicsObject->SetWorld(tmp);
    }

    void GameObjectAnimSkeleton::SetQuat(const float qx, const float qy, const float qz, const float qw) const
    {
        mQuat->set(qx, qy, qz, qw);
    }

    void GameObjectAnimSkeleton::SetScale(const float sx, const float sy, const float sz) const
    {
        mScale->set(sx, sy, sz);
    }

    void GameObjectAnimSkeleton::SetTrans(const float x, const float y, const float z)
    {
        mTrans->set(x, y, z);
    }

    void GameObjectAnimSkeleton::SetIndex(const int i)
    {
        mIndex = i;
    }

    void GameObjectAnimSkeleton::SetScale(Vec3& r)
    {
        *mScale = r;
    }

    void GameObjectAnimSkeleton::SetQuat(Quat& r)
    {
        *mQuat = r;
    }

    void GameObjectAnimSkeleton::SetTrans(Vec3& r)
    {
        *mTrans = r;
    }

    void GameObjectAnimSkeleton::SetBoneOrientation(const Mat4& tmp)
    {
        *mBoneOrientation = tmp;
    }

    Mat4 GameObjectAnimSkeleton::GetBoneOrientation(void) const
    {
        return Mat4(*mBoneOrientation);
    }
}
