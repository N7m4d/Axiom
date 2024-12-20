#include "AnimControllerNodeMan.h"
#include "ManBase.h"
#include "DLinkMan.h"
#include "NullAnimController.h"
#include "RunClip.h"
#include "SideStepLeftClip.h"
#include "HitBackClip.h"
#include "HitLeftClip.h"

Axiom::AnimControllerNodeMan* Axiom::AnimControllerNodeMan::mInstance = nullptr;

Axiom::AnimControllerNodeMan::AnimControllerNodeMan(const int reserveNum, const int reserveGrow)
    : ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
      , mNodeCompare(new AnimControllerNode())
{
    // Preload the reserve
    proFillReservedPool(reserveNum);

    AnimController* controller = new NullAnimController();
    assert(controller);

    assert(mNodeCompare);
    mNodeCompare->Set(AnimController::Name::Null, controller);
}

Axiom::AnimControllerNodeMan::~AnimControllerNodeMan()
{
    delete mNodeCompare;
    mNodeCompare = nullptr;

    Iterator* it = baseGetActiveIterator();

    it->First();

    while (!it->IsDone())
    {
        AnimControllerNode* node = (AnimControllerNode*)it->Curr();
        it->Next();
        delete node;
    }

    it = baseGetReserveIterator();

    it->First();

    while (!it->IsDone())
    {
        AnimControllerNode* node = (AnimControllerNode*)it->Curr();
        it->Next();
        delete node;
    }
}

void Axiom::AnimControllerNodeMan::Create(const int reserveNum, const int reserveGrow)
{
    assert(reserveNum >= 0);
    assert(reserveGrow > 0);

    assert(mInstance == nullptr);

    if (mInstance == nullptr)
    {
        mInstance = new AnimControllerNodeMan(reserveNum, reserveGrow);
    }
}

void Axiom::AnimControllerNodeMan::Destroy()
{
    delete mInstance;
    mInstance = nullptr;
}

Axiom::AnimControllerNode* Axiom::AnimControllerNodeMan::Add(const AnimController::Name name,
                                                             AnimController* controller)
{
    AnimControllerNodeMan* man = GetInstance();

    assert(controller);

    AnimControllerNode* node = (AnimControllerNode*)man->baseAddToFront();
    assert(node != nullptr);

    node->Set(name, controller);

    return node;
}

Axiom::AnimController* Axiom::AnimControllerNodeMan::Find(const AnimController::Name name)
{
    AnimControllerNodeMan* man = GetInstance();
    assert(man != nullptr);

    AnimController* controller = man->mNodeCompare->GetController();
    assert(controller);

    controller->mName = name;

    AnimControllerNode* node = (AnimControllerNode*)man->baseFind(man->mNodeCompare);

    if (node)
    {
        controller = node->GetController();
    }
    else
    {
        controller = nullptr;
    }

    return controller;
}

void Axiom::AnimControllerNodeMan::Play()
{
    AnimController* mainInstance = Find(AnimController::Name::Walk);

    const AnimTime delta = 0.5f * AnimTime(AnimTime::Duration::FILM_24_FRAME);
    mainInstance->SetDeltaTime(delta);
}

void Axiom::AnimControllerNodeMan::Pause()
{
    AnimController* mainInstance = Find(AnimController::Name::Walk);

    const AnimTime delta = 0.0f * AnimTime(AnimTime::Duration::FILM_24_FRAME);
    mainInstance->SetDeltaTime(delta);
}

void Axiom::AnimControllerNodeMan::IncreaseSpeed()
{
    AnimController* mainInstance = Find(AnimController::Name::Walk);

    const AnimTime delta = 0.003f * AnimTime(AnimTime::Duration::FILM_24_FRAME);

    AnimTime currDelta = mainInstance->GetDeltaTime();
    mainInstance->SetDeltaTime(currDelta + delta);
}

void Axiom::AnimControllerNodeMan::DecreaseSpeed()
{
    AnimController* mainInstance = Find(AnimController::Name::Walk);

    const AnimTime delta = 0.003f * AnimTime(AnimTime::Duration::FILM_24_FRAME);

    AnimTime currDelta = mainInstance->GetDeltaTime();
    mainInstance->SetDeltaTime(currDelta - delta);
}

void Axiom::AnimControllerNodeMan::PlayRunAnim()
{
    AnimController* mainInstance = Find(AnimController::Name::Walk);

    delete mainInstance->mAnim->mClip;

    AnimTime delta = mainInstance->mTimerControl->GetDeltaTime();
    delete mainInstance->mTimerControl;

    AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);

    mainInstance->mAnim->mClip = new RunClip(NUM_BONES);
    mainInstance->mTimerControl = new TimerController(delta, minTime, mainInstance->mAnim->mClip->GetTotalTime());
}

void Axiom::AnimControllerNodeMan::PlaySideStepAnim()
{
    AnimController* mainInstance = Find(AnimController::Name::Walk);
    delete mainInstance->mAnim->mClip;

    AnimTime delta = mainInstance->mTimerControl->GetDeltaTime();
    delete mainInstance->mTimerControl;

    AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);

    mainInstance->mAnim->mClip = new SideStepLeftClip(NUM_BONES);
    mainInstance->mTimerControl = new TimerController(delta, minTime, mainInstance->mAnim->mClip->GetTotalTime());
}

void Axiom::AnimControllerNodeMan::PlayHitBackAnim()
{
    AnimController* mainInstance = Find(AnimController::Name::Walk);
    delete mainInstance->mAnim->mClip;

    AnimTime delta = mainInstance->mTimerControl->GetDeltaTime();
    delete mainInstance->mTimerControl;

    AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);

    mainInstance->mAnim->mClip = new HitBackClip(NUM_BONES);
    mainInstance->mTimerControl = new TimerController(delta, minTime, mainInstance->mAnim->mClip->GetTotalTime());
}

void Axiom::AnimControllerNodeMan::PlayHitLeftAnim()
{
    AnimController* mainInstance = Find(AnimController::Name::Walk);
    delete mainInstance->mAnim->mClip;

    AnimTime delta = mainInstance->mTimerControl->GetDeltaTime();
    delete mainInstance->mTimerControl;

    AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);

    mainInstance->mAnim->mClip = new HitLeftClip(NUM_BONES);
    mainInstance->mTimerControl = new TimerController(delta, minTime, mainInstance->mAnim->mClip->GetTotalTime());
}

void Axiom::AnimControllerNodeMan::MoveForward()
{
    AnimController* mainInstance = Find(AnimController::Name::Walk);
    mainInstance->mShouldAnimateReverse = false;
}

void Axiom::AnimControllerNodeMan::MoveBackward()
{
    AnimController* mainInstance = Find(AnimController::Name::Walk);
    mainInstance->mShouldAnimateReverse = true;
}

void Axiom::AnimControllerNodeMan::Update()
{
    AnimControllerNodeMan* man = GetInstance();

    Iterator* it = man->baseGetActiveIterator();
    it->First();

    while (!it->IsDone())
    {
        ((AnimControllerNode*)it->Curr())->GetController()->Update();
        it->Next();
    }
}

void Axiom::AnimControllerNodeMan::Remove(AnimControllerNode* node)
{
    assert(node != nullptr);

    AnimControllerNodeMan* man = GetInstance();
    assert(man != nullptr);

    man->baseRemove(node);
}

void Axiom::AnimControllerNodeMan::Dump()
{
    AnimControllerNodeMan* man = GetInstance();
    assert(man != nullptr);

    man->baseDump();
}

Axiom::AnimControllerNodeMan* Axiom::AnimControllerNodeMan::GetInstance()
{
    // Safety - this forces users to call Create() first before using class
    assert(mInstance != nullptr);
    return mInstance;
}

DLink* Axiom::AnimControllerNodeMan::derivedCreateNode()
{
    DLink* node = new AnimControllerNode();
    assert(node != nullptr);

    return node;
}
