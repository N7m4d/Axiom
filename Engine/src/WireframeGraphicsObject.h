#ifndef GRAPHICS_OBJECT_WIREFRAME_H
#define GRAPHICS_OBJECT_WIREFRAME_H

#include "GraphicsObject.h"

namespace Axiom
{
    class WireframeGraphicsObject : public GraphicsObject
    {
    public:
        WireframeGraphicsObject(Mesh* mesh, Shader* shader);

        WireframeGraphicsObject() = delete;
        WireframeGraphicsObject(const WireframeGraphicsObject&) = delete;
        WireframeGraphicsObject& operator =(const WireframeGraphicsObject&) = delete;
        ~WireframeGraphicsObject() override = default;

        void SetState() override;
        void SetDataGPU() override;
        void Draw() override;
        void RestoreState() override;
    };
}

#endif
