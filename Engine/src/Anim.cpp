#include "Anim.h"

Axiom::Anim::Anim()
	: mClip(nullptr)
	, mBone(nullptr)
	, mNumBones(NUM_BONES)
{
	mBone = new Bone[static_cast<unsigned int>(mNumBones)]();
	assert(mBone);
}

Axiom::Anim::~Anim()
{
	delete[] mBone;
	delete mClip;
}

void Axiom::Anim::Animate(const AnimTime curr)
{
	mClip->AnimateBones(curr, mBone);
}

void Axiom::Anim::AnimateReverse(const AnimTime curr)
{
	mClip->AnimateBonesReverse(curr, mBone);
}
