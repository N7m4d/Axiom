#ifndef GAME_OBJECT_MAN_H
#define GAME_OBJECT_MAN_H

#include "GameObject.h"
#include "PCSTree.h"
#include "AnimTime.h"

namespace Axiom
{
    class GameObjectMan
    {
    public:
        static void Add(GameObject* obj, GameObject* parent);
        static void Draw();
        static void Update(AnimTime currTime);

        static void Create();
        static void Destroy();

        static void SwapTextures();
        static void SwapShaders();

        static GameObject* GetRoot();
        static PCSTree* GetPCSTree();

        GameObjectMan(const GameObjectMan&) = delete;
        GameObjectMan& operator =(const GameObjectMan&) = delete;

        ~GameObjectMan();

    private:
        GameObjectMan();

        static GameObjectMan* GetInstance();
        PCSTree* mRoot;
    };
}

#endif
