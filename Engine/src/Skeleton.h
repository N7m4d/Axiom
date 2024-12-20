

#ifndef SKELETON_H
#define SKELETON_H

#include "GameObjectAnim.h"
#include "Bone.h"

namespace Azul
{
	class Skeleton
	{
	public:
		struct Data
		{
			int  index;
			int  parentIndex;
			char name[64];
		};

	public:
		Skeleton(Bone *pBone, int numBones);

		Skeleton() = delete;
		Skeleton(const Skeleton &) = delete;
		Skeleton &operator = (const Skeleton &) = delete;
		~Skeleton();

		GameObjectAnim *GetFirstBone();

	private:
		void privSetAnimationHierarchy(Bone *pBoneResult);
		GameObjectAnim *privFindBoneByIndex(int index);

	private:
		GameObjectAnim *pFirstBone;
		int             numBones;
	};
}

#endif
