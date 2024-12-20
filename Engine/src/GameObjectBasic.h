#ifndef GAME_OBJECT_BASIC_H
#define GAME_OBJECT_BASIC_H

#include "GameObjectRigid.h"
#include "MathEngine.h"
#include "GraphicsObject.h"
#include "AnimTime.h"

namespace Axiom
{
    class GameObjectBasic : public GameObjectRigid
    {
    public:
        GameObjectBasic(GraphicsObject* graphicsObject);

        GameObjectBasic() = delete;
        GameObjectBasic(const GameObjectBasic&) = delete;
        GameObjectBasic& operator=(GameObjectBasic&) = delete;
        virtual ~GameObjectBasic();

        void Update(AnimTime& currTime) override;

        void SetScale(float sx, float sy, float sz) const;
        void SetQuat(float qx, float qy, float qz, float qw) const;
        void SetTrans(float x, float y, float z) const;

        void SetScale(Vec3& r);
        void SetQuat(Quat& r);
        void SetTrans(Vec3& r);

    private:
        void PrivUpdate(AnimTime& currTime);

    public:
        Vec3* mScale;
        Quat* mQuat;
        Vec3* mTrans;

        float mDeltaX;
        float mDeltaY;
        float mDeltaZ;

        float mCurRotX;
        float mCurRotY;
        float mCurRotZ;
    };
}

#endif
