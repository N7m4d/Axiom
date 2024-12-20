#include "GameObjectAnim.h"
#include "GraphicsObject.h"

namespace Axiom
{
	GameObjectAnim::GameObjectAnim(GraphicsObject *graphicsObject)
		: GameObject(graphicsObject),
		mIndex(-1)
	{
	}

	void GameObjectAnim::Update(AnimTime& currentTime)
	{
	}
}
