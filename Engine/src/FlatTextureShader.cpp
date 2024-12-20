#include "FlatTextureShader.h"

#include "FlatTexture.PS.h"
#include "FlatTexture.VS.h"
#include "Mesh.h"

D3D11_INPUT_ELEMENT_DESC ShaderObject_FlatTextureDesc[] =
{
    {
        "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, static_cast<uint32_t>(Axiom::VertexSlot::Position),
        offsetof(Axiom::VertexPos, Position), D3D11_INPUT_PER_VERTEX_DATA, 0
    },
    {
        "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, static_cast<uint32_t>(Axiom::VertexSlot::TexCoord),
        offsetof(Axiom::VertexTexCoord, TexCoord), D3D11_INPUT_PER_VERTEX_DATA, 0
    }
};

Axiom::FlatTextureShader::FlatTextureShader(const Name name)
    : Shader(
        name, sizeof(g_FlatTexture_VS), (void*)g_FlatTexture_VS, sizeof(g_FlatTexture_PS),
        (void*)g_FlatTexture_PS, ShaderObject_FlatTextureDesc, sizeof(ShaderObject_FlatTextureDesc)
    )
{
}
