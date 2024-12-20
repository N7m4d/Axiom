#include "AnimController.h"
#include "StringThis.h"

Axiom::AnimController::AnimController()
	: mAnim(nullptr)
	, mTimerControl(nullptr)
	, mShouldAnimateReverse(false)
{
}

Axiom::AnimController::~AnimController()
{
	delete mAnim;
	delete mTimerControl;

	mAnim = nullptr;
	mTimerControl = nullptr;
}

char* Axiom::AnimController::GetName() const
{
	static char tmp[128];
	strcpy_s(tmp, 128, StringMe(this->mName));
	return tmp;
}

void Axiom::AnimController::SetName(const Name name)
{
	mName = name;
}

void Axiom::AnimController::SetDeltaTime(const AnimTime delta)
{
	mTimerControl->SetDeltaTime(delta);
}

Axiom::AnimTime Axiom::AnimController::GetDeltaTime() const
{
	return mTimerControl->GetDeltaTime();
}

void Axiom::AnimController::Update() const
{
	mTimerControl->Update();
	
	if (!mShouldAnimateReverse)
	{
		mAnim->Animate(mTimerControl->GetCurrTime());
	}
	else
	{
		mAnim->AnimateReverse(mTimerControl->GetCurrTime());
	}
}
