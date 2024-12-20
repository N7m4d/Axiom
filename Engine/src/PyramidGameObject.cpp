#include "PyramidGameObject.h"

Axiom::PyramidGameObject::PyramidGameObject(GraphicsObject* graphicsObject)
    : GameObject{graphicsObject}
{
}

Axiom::PyramidGameObject::PyramidGameObject(const Vec3& position, GraphicsObject* graphicsObject)
    : GameObject{graphicsObject}
{
    mTrans->set(position);
}

void Axiom::PyramidGameObject::Update(AnimTime& currTime)
{
    static float angle = 0.0f;
    angle += 0.01f;

    Rot rot(Rot3::XYZ, angle, angle, angle);
    *mWorld = *mScale * rot * *mTrans;
    mGraphicsObject->SetWorld(*mWorld);
}
