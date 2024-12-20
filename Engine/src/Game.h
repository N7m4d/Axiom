#ifndef GAME_H
#define GAME_H

#include "Engine.h"
#include "AnimTimer.h"

namespace Axiom
{
    class Game : public Engine
    {
    public:
        Game(const char* name, int width, int height);

        Game() = delete;
        Game(const Game&) = delete;
        Game& operator =(const Game&) = delete;
        virtual ~Game();

        bool LoadContent() override;
        void UnloadContent() override;
        void Update(float deltaTime) override;
        void Render() override;
        void ClearDepthStencilBuffer() override;

        // Rendering
        float GetAspectRatio() const;
        void SetDefaultTargetMode();

        AnimTimer mIntervalTimer;
        AnimTimer mGlobalTimer;
    };
}

#endif
