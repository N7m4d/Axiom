#ifndef HIT_BACK_SKELETON_H
#define HIT_BACK_SKELETON_H

#include "GameObjectAnim.h"
#include "Bone.h"

namespace Axiom
{
	class HitBackSkeleton
	{
	public:
		struct Data
		{
			int  index;
			int  parentIndex;
			char name[64];
		};

		HitBackSkeleton(Bone* pBone, int numBones);

		HitBackSkeleton() = delete;
		HitBackSkeleton(const HitBackSkeleton&) = delete;
		HitBackSkeleton& operator = (const HitBackSkeleton&) = delete;
		~HitBackSkeleton();

		GameObjectAnim* GetFirstBone();

	private:
		void privSetAnimationHierarchy(Bone* pBoneResult);
		GameObjectAnim* privFindBoneByIndex(int index);

		GameObjectAnim* pFirstBone;
		int             numBones;
	};
}

#endif
