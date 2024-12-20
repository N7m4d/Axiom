#include "CubeMesh.h"

#include "DirectXDeviceMan.h"
#include "MathEngine.h"

Axiom::CubeMesh::CubeMesh()
    : Mesh(0, 0)
{
    const VertexPos vertices[]
    {
        Vec3(-0.25f, 0.25f, -0.25f),
        Vec3(-0.25f, -0.25f, -0.25f),
        Vec3(0.25f, -0.25f, -0.25f),

        // Triangle 1
        Vec3(0.25f, -0.25f, -0.25f),
        Vec3(0.25f, 0.25f, -0.25f),
        Vec3(-0.25f, 0.25f, -0.25f),

        // Triangle 2
        Vec3(0.25f, -0.25f, -0.25f),
        Vec3(0.25f, -0.25f, 0.25f),
        Vec3(0.25f, 0.25f, -0.25f),

        // Triangle 3
        Vec3(0.25f, -0.25f, 0.25f),
        Vec3(0.25f, 0.25f, 0.25f),
        Vec3(0.25f, 0.25f, -0.25f),

        // Triangle 4
        Vec3(0.25f, -0.25f, 0.25f),
        Vec3(-0.25f, -0.25f, 0.25f),
        Vec3(0.25f, 0.25f, 0.25f),

        // Triangle 5
        Vec3(-0.25f, -0.25f, 0.25f),
        Vec3(-0.25f, 0.25f, 0.25f),
        Vec3(0.25f, 0.25f, 0.25f),

        // Triangle 6
        Vec3(-0.25f, -0.25f, 0.25f),
        Vec3(-0.25f, -0.25f, -0.25f),
        Vec3(-0.25f, 0.25f, 0.25f),

        // Triangle 7
        Vec3(-0.25f, -0.25f, -0.25f),
        Vec3(-0.25f, 0.25f, -0.25f),
        Vec3(-0.25f, 0.25f, 0.25f),

        // Triangle 8
        Vec3(-0.25f, -0.25f, 0.25f),
        Vec3(0.25f, -0.25f, 0.25f),
        Vec3(0.25f, -0.25f, -0.25f),

        // Triangle 9
        Vec3(0.25f, -0.25f, -0.25f),
        Vec3(-0.25f, -0.25f, -0.25f),
        Vec3(-0.25f, -0.25f, 0.25f),

        // Triangle 10
        Vec3(-0.25f, 0.25f, -0.25f),
        Vec3(0.25f, 0.25f, -0.25f),
        Vec3(0.25f, 0.25f, 0.25f),

        // Triangle 11
        Vec3(0.25f, 0.25f, 0.25f),
        Vec3(-0.25f, 0.25f, 0.25f),
        Vec3(-0.25f, 0.25f, -0.25f)
    };

    VertexTexCoord textureCoords[]
    {
        // Triangle 0
        Vec2f(0.0f, 0.0f),
        Vec2f(0.0f, 1.0f),
        Vec2f(1.0f, 1.0f),

        // Triangle 1
        Vec2f(1.0f, 1.0f),
        Vec2f(1.0f, 0.0f),
        Vec2f(0.0f, 0.0f),

        // Triangle 2
        Vec2f(0.0f, 1.0f),
        Vec2f(1.0f, 1.0f),
        Vec2f(0.0f, 0.0f),

        // Triangle 3
        Vec2f(1.0f, 1.0f),
        Vec2f(1.0f, 0.0f),
        Vec2f(0.0f, 0.0f),

        // Triangle 4
        Vec2f(1.0f, 1.0f),
        Vec2f(0.0f, 1.0f),
        Vec2f(1.0f, 0.0f),

        // Triangle 5
        Vec2f(0.0f, 1.0f),
        Vec2f(0.0f, 0.0f),
        Vec2f(1.0f, 0.0f),

        // Triangle 6
        Vec2f(0.0f, 0.0f),
        Vec2f(0.0f, 1.0f),
        Vec2f(1.0f, 0.0f),

        // Triangle 7
        Vec2f(0.0f, 1.0f),
        Vec2f(1.0f, 1.0f),
        Vec2f(1.0f, 0.0f),

        // Triangle 8
        Vec2f(0.0f, 0.0f),
        Vec2f(1.0f, 0.0f),
        Vec2f(1.0f, 1.0f),

        // Triangle 9
        Vec2f(1.0f, 1.0f),
        Vec2f(0.0f, 1.0f),
        Vec2f(0.0f, 0.0f),

        // Triangle 10
        Vec2f(0.0f, 1.0f),
        Vec2f(1.0f, 1.0f),
        Vec2f(1.0f, 0.0f),

        // Triangle 11
        Vec2f(1.0f, 0.0f),
        Vec2f(0.0f, 0.0f),
        Vec2f(0.0f, 1.0f)
    };

    const VertexNorm colors[]
    {
        Vec3(1.0f, 0.0f, 0.0f), // Red
        Vec3(0.0f, 1.0f, 0.0f), // Green
        Vec3(0.0f, 0.0f, 1.0f), // Blue

        // Triangle 1
        Vec3(1.0f, 1.0f, 0.0f), // Yellow
        Vec3(0.0f, 1.0f, 1.0f), // Cyan
        Vec3(1.0f, 0.0f, 1.0f), // Magenta

        // Triangle 2
        Vec3(0.5f, 0.5f, 0.5f), // Grey
        Vec3(0.5f, 0.0f, 0.0f), // Dark Red
        Vec3(0.0f, 0.5f, 0.0f), // Dark Green

        // Triangle 3
        Vec3(0.0f, 0.0f, 0.5f), // Dark Blue
        Vec3(0.5f, 0.5f, 0.0f), // Olive
        Vec3(0.0f, 0.5f, 0.5f), // Teal

        // Triangle 4
        Vec3(0.5f, 0.0f, 0.5f), // Purple
        Vec3(0.75f, 0.75f, 0.75f), // Light Grey
        Vec3(0.75f, 0.0f, 0.0f), // Light Red

        // Triangle 5
        Vec3(0.0f, 0.75f, 0.0f), // Light Green
        Vec3(0.0f, 0.0f, 0.75f), // Light Blue
        Vec3(0.75f, 0.75f, 0.0f), // Light Yellow

        // Triangle 6
        Vec3(0.0f, 0.75f, 0.75f), // Light Cyan
        Vec3(0.75f, 0.0f, 0.75f), // Light Magenta
        Vec3(0.25f, 0.25f, 0.25f), // Dark Grey

        // Triangle 7
        Vec3(0.25f, 0.0f, 0.0f), // Very Dark Red
        Vec3(0.0f, 0.25f, 0.0f), // Very Dark Green
        Vec3(0.0f, 0.0f, 0.25f), // Very Dark Blue

        // Triangle 8
        Vec3(0.25f, 0.25f, 0.0f), // Dark Olive
        Vec3(0.0f, 0.25f, 0.25f), // Dark Teal
        Vec3(0.25f, 0.0f, 0.25f), // Dark Purple

        // Triangle 9
        Vec3(0.5f, 0.25f, 0.0f), // Brown
        Vec3(0.0f, 0.5f, 0.25f), // Dark Cyan
        Vec3(0.5f, 0.0f, 0.25f), // Dark Magenta

        // Triangle 10
        Vec3(0.25f, 0.5f, 0.0f), // Dark Olive Green
        Vec3(0.0f, 0.25f, 0.5f), // Dark Sky Blue
        Vec3(0.25f, 0.0f, 0.5f), // Dark Purple

        // Triangle 11
        Vec3(0.5f, 0.25f, 0.5f), // Dark Pink
        Vec3(0.0f, 0.5f, 0.5f), // Dark Turquoise
        Vec3(0.5f, 0.0f, 0.5f) // Dark Violet
    };

    const VertexNorm normals[]
    {
        // Triangle 0
        Vec3(-0.6f, 0.6f, -0.6f),
        Vec3(-0.6f, -0.6f, -0.6f),
        Vec3(0.6f, -0.6f, -0.6f),

        // Triangle 1
        Vec3(0.6f, -0.6f, -0.6f),
        Vec3(0.6f, 0.6f, -0.6f),
        Vec3(-0.6f, 0.6f, -0.6f),

        // Triangle 2
        Vec3(0.6f, -0.6f, -0.6f),
        Vec3(0.6f, -0.6f, 0.6f),
        Vec3(0.6f, 0.6f, -0.6f),

        // Triangle 3
        Vec3(0.6f, -0.6f, 0.6f),
        Vec3(0.6f, 0.6f, 0.6f),
        Vec3(0.6f, 0.6f, -0.6f),

        // Triangle 4
        Vec3(0.6f, -0.6f, 0.6f),
        Vec3(-0.6f, -0.6f, 0.6f),
        Vec3(0.6f, 0.6f, 0.6f),

        // Triangle 5
        Vec3(-0.6f, -0.6f, 0.6f),
        Vec3(-0.6f, 0.6f, 0.6f),
        Vec3(0.6f, 0.6f, 0.6f),

        // Triangle 6
        Vec3(-0.6f, -0.6f, 0.6f),
        Vec3(-0.6f, -0.6f, -0.6f),
        Vec3(-0.6f, 0.6f, 0.6f),

        // Triangle 7
        Vec3(-0.6f, -0.6f, -0.6f),
        Vec3(-0.6f, 0.6f, -0.6f),
        Vec3(-0.6f, 0.6f, 0.6f),

        // Triangle 8
        Vec3(-0.6f, -0.6f, 0.6f),
        Vec3(0.6f, -0.6f, 0.6f),
        Vec3(0.6f, -0.6f, -0.6f),

        // Triangle 9
        Vec3(0.6f, -0.6f, -0.6f),
        Vec3(-0.6f, -0.6f, -0.6f),
        Vec3(-0.6f, -0.6f, 0.6f),

        // Triangle 10
        Vec3(-0.6f, 0.6f, -0.6f),
        Vec3(0.6f, 0.6f, -0.6f),
        Vec3(0.6f, 0.6f, 0.6f),

        // Triangle 11
        Vec3(0.6f, 0.6f, 0.6f),
        Vec3(-0.6f, 0.6f, 0.6f),
        Vec3(-0.6f, 0.6f, -0.6f)
    };

    const uint32_t indices[]
    {
        // Base
        1, 0, 2,
        4, 3, 5,
        7, 6, 8,
        10, 9, 11,
        13, 12, 14,
        16, 15, 17,
        19, 18, 20,
        22, 21, 23,
        25, 24, 26,
        28, 27, 29,
        31, 30, 32,
        34, 33, 35
    };

    mPos.Init(sizeof(vertices), sizeof(VertexPos), vertices);
    mTexture.Init(sizeof(textureCoords), sizeof(VertexTexCoord), textureCoords);
    mColors.Init(sizeof(colors), sizeof(VertexColor), colors);
    mNormals.Init(sizeof(normals), sizeof(VertexNorm), normals);
    mIndexBuffer.Init(sizeof(indices), indices);

    mNumIndices = sizeof(indices) / sizeof(indices[0]);
}

void Axiom::CubeMesh::ActivateMesh()
{
    mPos.SetActive(VertexSlot::Position);
    mTexture.SetActive(VertexSlot::TexCoord);
    mColors.SetActive(VertexSlot::Color);
    mNormals.SetActive(VertexSlot::Norm);
}

void Axiom::CubeMesh::RenderIndexBuffer()
{
    mIndexBuffer.SetActive();

    DirectXDeviceMan::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    DirectXDeviceMan::GetContext()->DrawIndexed(mNumIndices, 0, 0);
}
