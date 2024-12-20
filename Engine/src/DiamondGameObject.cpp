#include "DiamondGameObject.h"

Axiom::DiamondGameObject::DiamondGameObject(GraphicsObject* graphicsObject)
    : GameObject(graphicsObject)
{
}

Axiom::DiamondGameObject::DiamondGameObject(const Vec3& position, GraphicsObject* graphicsObject)
    : GameObject(graphicsObject)
{
    mTrans->set(position);
}

void Axiom::DiamondGameObject::Update(AnimTime& currentTime)
{
    static float angle = 0.0f;
    angle += 0.01f;

    const Rot rot(Rot3::YZX, angle, 2 * angle, 3 * angle);

    *mWorld = *mScale * rot * *mTrans;
    mGraphicsObject->SetWorld(*mWorld);
}
