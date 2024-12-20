#ifndef ANIM_CONTROLLER_NODE_MAN_H
#define ANIM_CONTROLLER_NODE_MAN_H

#include "ManBase.h"
#include "AnimControllerNode.h"

namespace Axiom
{
    class AnimControllerNodeMan : public ManBase
    {
    public:
        static void Create(int reserveNum = 0, int reserveGrow = 1);
        static void Destroy();

        static AnimControllerNode* Add(AnimController::Name name, AnimController* controller);
        static AnimController* Find(AnimController::Name name);

        static void Play();
        static void Pause();
        static void IncreaseSpeed();
        static void DecreaseSpeed();
        static void PlayRunAnim();
        static void PlaySideStepAnim();
        static void PlayHitBackAnim();
        static void PlayHitLeftAnim();
        static void MoveForward();
        static void MoveBackward();
        static void Update();

        static void Remove(AnimControllerNode* node);
        static void Dump();

    private:
        static AnimControllerNodeMan* GetInstance();

        ~AnimControllerNodeMan();
        AnimControllerNodeMan(int reserveNum, int reserveGrow);

    protected:
        DLink* derivedCreateNode() override;

    private:
        AnimControllerNode* mNodeCompare;
        static AnimControllerNodeMan* mInstance;
    };
}

#endif
