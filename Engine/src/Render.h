#ifndef RENDER_H
#define RENDER_H

namespace Axiom
{
    class Render
    {
    protected:
        Render() = default;
        Render(const Render&) = delete;
        Render& operator =(const Render&) = delete;
        virtual ~Render() = default;

        virtual void SetState() = 0;
        virtual void SetDataGPU() = 0;
        virtual void Draw() = 0;
        virtual void RestoreState() = 0;
    };
}

#endif
