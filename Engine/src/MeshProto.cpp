#include "MeshProto.h"
#include "DirectXDeviceMan.h"
#include "ShaderMappings.h"

using namespace Axiom;

MeshProto::MeshProto(const meshData& meshProtoData)
    : Mesh(0, 0)
{
    mNumVertices = static_cast<int>(meshProtoData.vbo_vert.count);
    mNumIndices = static_cast<int>(meshProtoData.triCount) * 3;

    assert(mNumVertices > 0);
    assert(mNumVertices > 0);

    if (meshProtoData.vbo_vert.enabled)
    {
        assert(meshProtoData.vbo_vert.poData);
        assert(meshProtoData.vbo_vert.dataSize > 0);
        assert(meshProtoData.vbo_vert.vboType == vboData::VBO_TYPE::VEC3);
        assert(meshProtoData.vbo_vert.componentType == vboData::VBO_COMPONENT::FLOAT);

        mPos.Init(meshProtoData.vbo_vert.dataSize, meshProtoData.vbo_vert.stride, meshProtoData.vbo_vert.poData);
    }

    if (meshProtoData.vbo_uv.enabled)
    {
        assert(meshProtoData.vbo_uv.poData);
        assert(meshProtoData.vbo_uv.dataSize > 0);
        assert(meshProtoData.vbo_uv.vboType == vboData::VBO_TYPE::VEC2);
        assert(meshProtoData.vbo_uv.componentType == vboData::VBO_COMPONENT::FLOAT);

        mTex.Init(meshProtoData.vbo_uv.dataSize, meshProtoData.vbo_uv.stride, meshProtoData.vbo_uv.poData);
    }

    if (meshProtoData.vbo_norm.enabled)
    {
        assert(meshProtoData.vbo_norm.poData);
        assert(meshProtoData.vbo_norm.dataSize > 0);
        assert(meshProtoData.vbo_norm.vboType == vboData::VBO_TYPE::VEC3);
        assert(meshProtoData.vbo_norm.componentType == vboData::VBO_COMPONENT::FLOAT);

        mNorm.Init(meshProtoData.vbo_norm.dataSize, meshProtoData.vbo_norm.stride, meshProtoData.vbo_norm.poData);
    }

    if (meshProtoData.vbo_index.enabled)
    {
        assert(meshProtoData.vbo_index.vboType == vboData::VBO_TYPE::SCALAR);
        assert(meshProtoData.vbo_index.componentType != vboData::VBO_COMPONENT::DOUBLE
            && meshProtoData.vbo_index.componentType != vboData::VBO_COMPONENT::FLOAT);

        assert(meshProtoData.vbo_index.dataSize > 0);
        assert(meshProtoData.vbo_index.poData);

        mIndexBuffer.Init(meshProtoData.vbo_index.dataSize, meshProtoData.vbo_index.poData);
    }
}

void MeshProto::ActivateMesh()
{
    mPos.SetActive(VertexSlot::Position);
    mTex.SetActive(VertexSlot::TexCoord);
    mNorm.SetActive(VertexSlot::Norm);
}

void MeshProto::RenderIndexBuffer()
{
    mIndexBuffer.SetActive();
    DirectXDeviceMan::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    DirectXDeviceMan::GetContext()->DrawIndexed(mNumIndices, 0, 0);
}

MeshProto::~MeshProto()
{
}
