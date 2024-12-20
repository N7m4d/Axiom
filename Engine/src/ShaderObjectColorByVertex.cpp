#include "ShaderObjectColorByVertex.h"
#include "Mesh.h"
#include "ShaderMappings.h"

#include "ColorByVertex.PS.h"
#include "ColorByVertex.VS.h"

D3D11_INPUT_ELEMENT_DESC ShaderObject_ColorByVertexDesc[] =
{
    {
        "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, (uint32_t)Axiom::VertexSlot::Position,
        offsetof(Axiom::VertexPos, Position), D3D11_INPUT_PER_VERTEX_DATA, 0
    },
    {
        "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, (uint32_t)Axiom::VertexSlot::Color,
        offsetof(Axiom::VertexColor, Color), D3D11_INPUT_PER_VERTEX_DATA, 0
    }
};

Axiom::ShaderObjectColorByVertex::ShaderObjectColorByVertex(Name name)
    : Shader(
        name, sizeof(g_ColorByVertex_VS), (void*)g_ColorByVertex_VS, sizeof(g_ColorByVertex_PS),
        (void*)g_ColorByVertex_PS, ShaderObject_ColorByVertexDesc, sizeof(ShaderObject_ColorByVertexDesc)
    )
{
}
