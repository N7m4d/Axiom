#include "PyramidMesh.h"

#include "DirectXDeviceMan.h"

Axiom::PyramidMesh::PyramidMesh()
    : Mesh(0, 0)
{
    const VertexPos vertices[]
    {
        {Vec3(-1.0f, -1.0f, -1.0f)}, // 0
        {Vec3(1.0f, -1.0f, -1.0f)}, // 1
        {Vec3(1.0f, -1.0f, 1.0f)}, // 2
        {Vec3(-1.0f, -1.0f, 1.0f)}, // 3
        {Vec3(0.0f, 1.0f, 0.0f)} // 4
    };

    const VertexTexCoord textureCoords[]
    {
        {Vec2f(0.0f, 0.0f)},
        {Vec2f(1.0f, 0.0f)},
        {Vec2f(1.0f, 1.0f)},
        {Vec2f(0.0f, 1.0f)},
        {Vec2f(0.5f, 0.5f)}
    };

    const VertexColor colors[]
    {
        {Vec3(1.0f, 0.0f, 0.0f)},
        {Vec3(0.0f, 1.0f, 0.0f)},
        {Vec3(0.0f, 0.0f, 1.0f)},
        {Vec3(1.0f, 1.0f, 0.0f)},
        {Vec3(0.0f, 1.0f, 1.0f)}
    };

    const VertexNorm normals[]
    {
        {Vec3(0.0f, 0.0f, 1.0f)},
        {Vec3(-0.4f, -0.4f, -0.8f)},
        {Vec3(0.4f, -0.4f, -0.8f)},
        {Vec3(0.4f, 0.4f, -0.8f)},
        {Vec3(-0.4f, 0.4f, -0.8f)}
    };

    constexpr uint32_t indices[]
    {
        // Base
        0, 1, 2,
        2, 3, 0,

        // Sides
        0, 4, 1,
        1, 4, 2,
        2, 4, 3,
        3, 4, 0
    };

    mPos.Init(sizeof(vertices), sizeof(VertexPos), vertices);
    mTexture.Init(sizeof(textureCoords), sizeof(VertexTexCoord), textureCoords);
    mColors.Init(sizeof(colors), sizeof(VertexColor), colors);
    mNorm.Init(sizeof(normals), sizeof(VertexNorm), normals);
    mIndexBuffer.Init(sizeof(indices), indices);

    mNumIndices = 18;
}

void Axiom::PyramidMesh::ActivateMesh()
{
    mPos.SetActive(VertexSlot::Position);
    mTexture.SetActive(VertexSlot::TexCoord);
    mColors.SetActive(VertexSlot::Color);
    mNorm.SetActive(VertexSlot::Norm);
}

void Axiom::PyramidMesh::RenderIndexBuffer()
{
    mIndexBuffer.SetActive();

    DirectXDeviceMan::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    DirectXDeviceMan::GetContext()->DrawIndexed(mNumIndices, 0, 0);
}
