#ifndef SIMPLE_GAME_OBJECT_RIGID_H
#define SIMPLE_GAME_OBJECT_RIGID_H

#include "GameObject.h"
#include "GraphicsObject.h"
#include "AnimTime.h"

namespace Axiom
{
    class GameObjectRigid : public GameObject
    {
    public:
        GameObjectRigid(GraphicsObject* graphicsObject);

        GameObjectRigid() = delete;
        GameObjectRigid(const GameObjectRigid&) = delete;
        GameObjectRigid& operator=(GameObjectRigid&) = delete;
        virtual ~GameObjectRigid() = default;

        void Update(AnimTime& currTime) override;
    };
}

#endif
