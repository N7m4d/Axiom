#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "MathEngine.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "AnimTime.h"

namespace Axiom
{
    class Texture;
    
    class GameObject : public PCSNode
    {
    public:
        GameObject() = delete;
        GameObject(const GameObject&) = delete;
        GameObject& operator =(const GameObject&) = delete;
        virtual ~GameObject();

        GameObject(GraphicsObject* graphicsObject);

        virtual void Update(AnimTime& currTime) = 0;
        void Draw() const;

        Mat4* GetWorld() const;
        void SetWorld(const Mat4* world) const;
        void SetPos(const Vec3& v) const;
        void SetScale(float scale) const;
        void SetRot(const Quat& q);

        void SwapTexture(Texture* texture) const;
        void SwapShader(Shader* shader);

        GraphicsObject* GetGraphicsObject();
        void DrawEnable();
        void DrawDisable();

    protected:
        Scale* mScale;
        Quat* mRot;
        Trans* mTrans;
        Mat4* mWorld;
        GraphicsObject* mGraphicsObject;
        bool mDrawEnable;
    };
}

#endif
