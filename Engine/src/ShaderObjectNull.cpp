#include "ShaderObjectNull.h"
#include "Mesh.h"
#include "ShaderMappings.h"

#include "Null.PS.h"
#include "Null.VS.h"

D3D11_INPUT_ELEMENT_DESC ShaderObject_NullDesc[] =
{
    {
        "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, static_cast<uint32_t>(Axiom::VertexSlot::Position),
        offsetof(Axiom::VertexPos, Position), D3D11_INPUT_PER_VERTEX_DATA, 0
    },
    {
        "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, static_cast<uint32_t>(Axiom::VertexSlot::Color),
        offsetof(Axiom::VertexColor, Color), D3D11_INPUT_PER_VERTEX_DATA, 0
    }
};

Axiom::ShaderObjectNull::ShaderObjectNull(const Name name)
    : Shader(name, sizeof(g_Null_VS), (void*)g_Null_VS, sizeof(g_Null_PS),
             (void*)g_Null_PS, ShaderObject_NullDesc, sizeof(ShaderObject_NullDesc))
{
}

void Axiom::ShaderObjectNull::ActivateShader()
{
    mVertexShader.SetActive();
    mPixelShader.SetActive();
}
