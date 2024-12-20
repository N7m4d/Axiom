#include "GameObjectBasic.h"

#include "MathEngine.h"
#include "GraphicsObject.h"

namespace Axiom
{
    GameObjectBasic::GameObjectBasic(GraphicsObject* pGraphicsObject)
        : GameObjectRigid(pGraphicsObject)
          , mScale(new Vec3(1.0f, 1.0f, 1.0f))
          , mQuat(new Quat(0.0f, 0.0f, 0.0f, 1.0f))
          , mTrans(new Vec3(0.0f, 0.0f, 0.0f))
          , mDeltaX(0.0f)
          , mDeltaY(0.0f)
          , mDeltaZ(0.0f)
          , mCurRotX(0.0f)
          , mCurRotY(0.0f)
          , mCurRotZ(0.0f)
    {
        assert(pGraphicsObject);
    }

    GameObjectBasic::~GameObjectBasic()
    {
        delete mTrans;
        delete mScale;
        delete mQuat;
    }

    void GameObjectBasic::PrivUpdate(AnimTime& currTime)
    {
        AZUL_UNUSED_VAR(currTime);

        Trans trans(*mTrans);
        Scale scale(*mScale);
        Quat quat(*mQuat);

        mCurRotX += mDeltaX;
        mCurRotY += mDeltaY;
        mCurRotZ += mDeltaZ;

        Rot Rx(Rot1::X, mCurRotX);
        Rot Ry(Rot1::Y, mCurRotY);
        Rot Rz(Rot1::Z, mCurRotZ);

        *mWorld = scale * quat * Rx * Ry * Rz * trans;
    }

    void GameObjectBasic::Update(AnimTime& currTime)
    {
        PrivUpdate(currTime);
        mGraphicsObject->SetWorld(*mWorld);
    }

    void GameObjectBasic::SetQuat(const float qx, const float qy, const float qz, const float qw) const
    {
        mQuat->set(qx, qy, qz, qw);
    }

    void GameObjectBasic::SetScale(const float sx, const float sy, const float sz) const
    {
        mScale->set(sx, sy, sz);
    }

    void GameObjectBasic::SetTrans(const float x, const float y, const float z) const
    {
        mTrans->set(x, y, z);
    }

    void GameObjectBasic::SetScale(Vec3& r)
    {
        *mScale = r;
    }

    void GameObjectBasic::SetQuat(Quat& r)
    {
        *mQuat = r;
    }

    void GameObjectBasic::SetTrans(Vec3& r)
    {
        *mTrans = r;
    }
}
