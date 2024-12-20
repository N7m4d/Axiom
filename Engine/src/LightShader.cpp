#include "LightShader.h"

#include "LightTexture.PS.h"
#include "LightTexture.VS.h"
#include "Mesh.h"

D3D11_INPUT_ELEMENT_DESC ShaderObject_LightTextureDesc[] =
{
    {
        "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, static_cast<uint32_t>(Axiom::VertexSlot::Position),
        offsetof(Axiom::VertexPos, Position), D3D11_INPUT_PER_VERTEX_DATA, 0
    },
    {
        "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, static_cast<uint32_t>(Axiom::VertexSlot::TexCoord),
        offsetof(Axiom::VertexTexCoord, TexCoord), D3D11_INPUT_PER_VERTEX_DATA, 0
    },
    {
        "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, static_cast<uint32_t>(Axiom::VertexSlot::Norm),
        offsetof(Axiom::VertexNorm, Norm), D3D11_INPUT_PER_VERTEX_DATA, 0
    }
};

Axiom::LightShader::LightShader(Name name)
    : Shader(name, sizeof(g_LightTexture_VS), (void*)g_LightTexture_VS, sizeof(g_LightTexture_PS),
             (void*)g_LightTexture_PS, ShaderObject_LightTextureDesc, sizeof(ShaderObject_LightTextureDesc))
      , mLightColor(sizeof(Vec3))
      , mLightPos(sizeof(Vec3))
{
}

void Axiom::LightShader::ActivateCBV()
{
    Shader::ActivateCBV();

    mLightColor.SetActive(ConstantBufferSlot::LightColor);
    mLightPos.SetActive(ConstantBufferSlot::LightPos);
}

void Axiom::LightShader::TransferLight(const Vec3* lightColor, const Vec3* lightPos) const
{
    mLightColor.Transfer(lightColor);
    mLightPos.Transfer(lightPos);
}
