#ifndef SPHERE_GAME_OBJECT
#define SPHERE_GAME_OBJECT

#include "GameObject.h"

namespace Axiom
{
    class SphereGameObject : public GameObject
    {
    public:
        SphereGameObject(GraphicsObject* graphicsObject);
        SphereGameObject(const Vec3& position, GraphicsObject* graphicsObject);
        ~SphereGameObject() override = default;

        void Update(AnimTime& currTime) override;
    };
}

#endif
