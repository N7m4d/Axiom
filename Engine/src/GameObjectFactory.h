#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include "Mesh.h"

namespace Axiom
{
	class Vec3;
	class Quat;

	class GameObjectFactory
	{
	public:
		//GameObjectFactory();
		void CreateProtoGameObject(const char* const fileName, const Vec3& translation, const Quat& rotation, const float scale, Mesh::Name meshName);
	};
}

#endif