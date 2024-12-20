#ifndef COLOR_BY_VERTEX_GRAPHICS_OBJECT_H
#define COLOR_BY_VERTEX_GRAPHICS_OBJECT_H

#include "GraphicsObject.h"

namespace Axiom
{
    class ColorByVertexGraphicsObject : public GraphicsObject
    {
    public:
        ColorByVertexGraphicsObject(Mesh* mesh, Shader* shader);

        ColorByVertexGraphicsObject() = delete;
        ColorByVertexGraphicsObject(const ColorByVertexGraphicsObject&) = delete;
        ColorByVertexGraphicsObject& operator =(const ColorByVertexGraphicsObject&) = delete;
        ~ColorByVertexGraphicsObject() override = default;

        void SetState() override;
        void SetDataGPU() override;
        void Draw() override;
        void RestoreState() override;
    };
}

#endif
