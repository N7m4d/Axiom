#ifndef PYRAMID_GAME_OBJECT
#define PYRAMID_GAME_OBJECT

#include "GameObject.h"

namespace Axiom
{
    class PyramidGameObject : public GameObject
    {
    public:
        PyramidGameObject(GraphicsObject* graphicsObject);
        PyramidGameObject(const Vec3& position, GraphicsObject* graphicsObject);
        ~PyramidGameObject() override = default;

        void Update(AnimTime& currTime) override;
    };
}

#endif
