#ifndef GAME_OBJECT_ANIM_H
#define GAME_OBJECT_ANIM_H

#include "GameObject.h"
#include "GraphicsObject.h"
#include "AnimTime.h"

namespace Axiom
{
    class GameObjectAnim : public GameObject
    {
    public:
        GameObjectAnim(GraphicsObject* graphicsObject);

        GameObjectAnim() = delete;
        GameObjectAnim(const GameObjectAnim&) = delete;
        GameObjectAnim& operator=(GameObjectAnim&) = delete;
        virtual ~GameObjectAnim() = default;

        virtual void Update(AnimTime& currTime);
        virtual void SetIndex(int i) = 0;

        int mIndex;
    };
}

#endif
