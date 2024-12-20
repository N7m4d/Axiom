#include "CubeGameObject.h"

Axiom::CubeGameObject::CubeGameObject(GraphicsObject* graphicsObject)
    : GameObject(graphicsObject)
{
}

Axiom::CubeGameObject::CubeGameObject(const Vec3& position, GraphicsObject* graphicsObject)
    : GameObject(graphicsObject)
{
    mTrans->set(position);
}

void Axiom::CubeGameObject::Update(AnimTime& currentTime)
{
    static float angle = 0.0f;
    angle += 0.01f;

    const Rot rot(Rot1::Y, angle);

    *mWorld = *mScale * rot * *mTrans;
    mGraphicsObject->SetWorld(*mWorld);
}
