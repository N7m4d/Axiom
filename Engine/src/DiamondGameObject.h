#ifndef DIAMOND_GAME_OBJECT
#define DIAMOND_GAME_OBJECT

#include "GameObject.h"

namespace Axiom
{
    class DiamondGameObject : public GameObject
    {
    public:
        DiamondGameObject(GraphicsObject* graphicsObject);
        DiamondGameObject(const Vec3& position, GraphicsObject* graphicsObject);
        ~DiamondGameObject() override = default;

        void Update(AnimTime& currentTime) override;
    };
}

#endif
