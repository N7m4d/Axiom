#ifndef FLAT_TEXTURE_GRAPHICS_OBJECT_H
#define FLAT_TEXTURE_GRAPHICS_OBJECT_H

#include "GraphicsObject.h"
#include "Texture.h"

namespace Axiom
{
    class FlatTextureGraphicsObject : public GraphicsObject
    {
    public:
        FlatTextureGraphicsObject(Mesh* mesh, Shader* shader, Texture* texture);

        FlatTextureGraphicsObject() = delete;
        FlatTextureGraphicsObject(const FlatTextureGraphicsObject&) = delete;
        FlatTextureGraphicsObject& operator =(const FlatTextureGraphicsObject&) = delete;
        ~FlatTextureGraphicsObject() override;

        void SetState() override;
        void SetDataGPU() override;
        void Draw() override;
        void RestoreState() override;

        Texture* mTexture;
    };
}

#endif
