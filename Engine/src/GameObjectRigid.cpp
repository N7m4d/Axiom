#include "GameObjectRigid.h"
#include "GraphicsObject.h"

namespace Axiom
{
    GameObjectRigid::GameObjectRigid(GraphicsObject* graphicsObject)
        : GameObject(graphicsObject)
    {
    }

    void GameObjectRigid::Update(AnimTime& currTime)
    {
    }
}
