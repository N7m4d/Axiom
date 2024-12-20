#include "SphereGameObject.h"

Axiom::SphereGameObject::SphereGameObject(GraphicsObject* graphicsObject)
	: GameObject(graphicsObject)
{
}

Axiom::SphereGameObject::SphereGameObject(const Vec3& position, GraphicsObject* graphicsObject)
	: GameObject(graphicsObject)
{
	mTrans->set(position);
}

void Axiom::SphereGameObject::Update(AnimTime& currTime)
{
	static float angle = 0.0f;
	angle += 0.01f;

	Rot rot(Rot1::Y, angle);
	*mWorld = *mScale * rot * *mTrans;
	mGraphicsObject->SetWorld(*mWorld);
}
