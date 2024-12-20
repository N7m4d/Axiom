#ifndef CUBE_GAME_OBJECT
#define CUBE_GAME_OBJECT

#include "GameObject.h"

namespace Axiom
{
	class CubeGameObject : public GameObject
	{
	public:
		CubeGameObject(GraphicsObject* graphicsObject);
		CubeGameObject(const Vec3& position, GraphicsObject* graphicsObject);
		~CubeGameObject() override = default;

		void Update(AnimTime& currentTime) override;
	};
}

#endif
