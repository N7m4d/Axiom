#ifndef CONST_COLOR_GRAPHICS_OBJECT_H
#define CONST_COLOR_GRAPHICS_OBJECT_H

#include "GraphicsObject.h"

namespace Axiom
{
    class ConstColorGraphicsObject : public GraphicsObject
    {
    public:
        ConstColorGraphicsObject(Mesh* mesh, Shader* shader, const Vec3& lightColor);

        ConstColorGraphicsObject() = delete;
        ConstColorGraphicsObject(const ConstColorGraphicsObject&) = delete;
        ConstColorGraphicsObject& operator =(const ConstColorGraphicsObject&) = delete;
        ~ConstColorGraphicsObject() override;

        void SetState() override;
        void SetDataGPU() override;
        void Draw() override;
        void RestoreState() override;

        Vec3* mLightColor;
    };
}

#endif
