#include "DiamondMesh.h"

#include "DirectXDeviceMan.h"

Axiom::DiamondMesh::DiamondMesh()
    : Mesh(0, 0)
{
    const VertexPos vertices[]{
        {Vec3(0.0f, 1.0f, 0.0f)}, // Top
        {Vec3(-1.0f, 0.0f, -1.0f)}, // Left front
        {Vec3(1.0f, 0.0f, -1.0f)}, // Right front
        {Vec3(1.0f, 0.0f, 1.0f)}, // Right back
        {Vec3(-1.0f, 0.0f, 1.0f)}, // Left back
        {Vec3(0.0f, -1.0f, 0.0f)}, // Bottom
    };

    constexpr uint32_t indices[]{
        0, 1, 2, // Top front
        0, 2, 3, // Top right
        0, 3, 4, // Top back
        0, 4, 1, // Top left
        5, 2, 1, // Bottom front
        5, 3, 2, // Bottom right
        5, 4, 3, // Bottom back
        5, 1, 4 // Bottom left
    };

    const VertexTexCoord textureCoords[]
    {
        {Vec2f(0.5f, 1.0f)}, // Top
        {Vec2f(0.0f, 0.0f)}, // Left front
        {Vec2f(1.0f, 0.0f)}, // Right front
        {Vec2f(1.0f, 1.0f)}, // Right back
        {Vec2f(0.0f, 1.0f)}, // Left back
        {Vec2f(0.5f, 0.0f)}, // Bottom
    };

    const VertexNorm normals[]
    {
        {Vec3(0.0f, 1.0f, 0.0f)}, // Top
        {Vec3(-1.0f, 0.0f, -1.0f)}, // Left front
        {Vec3(1.0f, 0.0f, -1.0f)}, // Right front
        {Vec3(1.0f, 0.0f, 1.0f)}, // Right back
        {Vec3(-1.0f, 0.0f, 1.0f)}, // Left back
        {Vec3(0.0f, -1.0f, 0.0f)}, // Bottom
    };

    const VertexColor colors[]
    {
        {Vec3(1.0f, 0.0f, 0.0f)}, // Top
        {Vec3(0.0f, 1.0f, 0.0f)}, // Right
        {Vec3(0.0f, 0.0f, 1.0f)}, // Front
        {Vec3(1.0f, 1.0f, 0.0f)}, // Left
        {Vec3(1.0f, 0.0f, 1.0f)}, // Back
        {Vec3(0.0f, 1.0f, 1.0f)}, // Bottom
    };

    mPos.Init(sizeof(vertices), sizeof(VertexPos), vertices);
    mTextureCoords.Init(sizeof(textureCoords), sizeof(VertexTexCoord), textureCoords);
    mNorm.Init(sizeof(normals), sizeof(VertexNorm), normals);
    mColors.Init(sizeof(colors), sizeof(VertexColor), colors);
    mIndexBuffer.Init(sizeof(indices), indices);

    mNumIndices = 24;
}

void Axiom::DiamondMesh::ActivateMesh()
{
    mPos.SetActive(VertexSlot::Position);
    mTextureCoords.SetActive(VertexSlot::TexCoord);
    mNorm.SetActive(VertexSlot::Norm);
    mColors.SetActive(VertexSlot::Color);
}

void Axiom::DiamondMesh::RenderIndexBuffer()
{
    mIndexBuffer.SetActive();

    DirectXDeviceMan::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    DirectXDeviceMan::GetContext()->DrawIndexed(mNumIndices, 0, 0);
}
