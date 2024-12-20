#ifndef LIGHT_SHADER_H
#define LIGHT_SHADER_H

#include "Shader.h"

namespace Axiom
{
    class LightShader : public Shader
    {
    public:
        LightShader() = delete;
        LightShader(const LightShader&) = delete;
        LightShader& operator =(const LightShader&) = delete;
        ~LightShader() override = default;

        LightShader(Name name);

        void ActivateCBV() override;
        void TransferLight(const Vec3* lightPos, const Vec3* lightColor) const;

        ConstantBuffer mLightColor;
        ConstantBuffer mLightPos;
    };
}

#endif
