#ifndef GAME_OBJECT_ANIM_SKIN_H
#define GAME_OBJECT_ANIM_SKIN_H

#include "GameObjectAnim.h"
#include "MathEngine.h"
#include "GraphicsObject.h"
#include "AnimTime.h"
#include "Bone.h"

namespace Axiom
{
    class GameObjectAnimSkin : public GameObjectAnim
    {
    public:
        GameObjectAnimSkin(GraphicsObject* graphicsObject, Bone* pBoneResult);

        GameObjectAnimSkin() = delete;
        GameObjectAnimSkin(const GameObjectAnimSkin&) = delete;
        GameObjectAnimSkin& operator=(GameObjectAnimSkin&) = delete;
        virtual ~GameObjectAnimSkin();

        void Update(AnimTime& currTime) override;

        void SetScale(float sx, float sy, float sz) const;
        void SetQuat(float qx, float qy, float qz, float qw) const;
        void SetTrans(float x, float y, float z) const;

        void SetScale(Vec3& r);
        void SetQuat(Quat& r);
        void SetTrans(Vec3& r);

        void SetIndex(int i) override;

        Mat4 GetBoneOrientation() const;
        void SetBoneOrientation(const Mat4&);

    private:
        void PrivUpdate(AnimTime& currTime);

    public:
        Vec3* mScale;
        Quat* mQuat;
        Vec3* mTrans;
        Mat4* mLocal;
        Bone* mBoneResult;
        Mat4* mBoneOrientation;
    };
}

#endif
