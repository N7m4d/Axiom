#ifndef NULL_GRAPHICS_OBJECT_H
#define NULL_GRAPHICS_OBJECT_H

#include "GraphicsObject.h"

namespace Axiom
{
    class NullGraphicsObject : public GraphicsObject
    {
    public:
        NullGraphicsObject(Mesh* mesh, Shader* shader);

        NullGraphicsObject() = delete;
        NullGraphicsObject(const NullGraphicsObject&) = delete;
        NullGraphicsObject& operator =(const NullGraphicsObject&) = delete;
        ~NullGraphicsObject() override = default;

        void SetState() override;
        void SetDataGPU() override;
        void Draw() override;
        void RestoreState() override;
    };
}

#endif
