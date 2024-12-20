#ifndef LIGHT_TEXTURE_GRAPHICS_OBJECT_H
#define LIGHT_TEXTURE_GRAPHICS_OBJECT_H

#include "GraphicsObject.h"
#include "Texture.h"

namespace Axiom
{
    class LightTextureGraphicsObject : public GraphicsObject
    {
    public:
        LightTextureGraphicsObject(Mesh* mesh, Shader* shader, Texture* texture,
                                   const Vec3& lightColor, const Vec3& lightPos);

        LightTextureGraphicsObject() = delete;
        LightTextureGraphicsObject(const LightTextureGraphicsObject&) = delete;
        LightTextureGraphicsObject& operator =(const LightTextureGraphicsObject&) = delete;
        ~LightTextureGraphicsObject() override;

        void SetState() override;
        void SetDataGPU() override;
        void Draw() override;
        void RestoreState() override;

        Texture* mTexture;
        Vec3* mLightColor;
        Vec3* mLightPos;
    };
}

#endif
