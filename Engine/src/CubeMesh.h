#ifndef CUBE_MESH_H
#define CUBE_MESH_H

#include "IndexBuffer.h"
#include "Mesh.h"
#include "VertexBuffer.h"

namespace Axiom
{
    class IndexBuffer;

    class CubeMesh final : public Mesh
    {
    public:
        CubeMesh();
        CubeMesh(const CubeMesh&) = delete;
        CubeMesh& operator =(CubeMesh&) = delete;
        ~CubeMesh() override = default;

        void ActivateMesh() override;
        void RenderIndexBuffer() override;

        VertexBuffer mPos;
        VertexBuffer mTexture;
        VertexBuffer mColors;
        VertexBuffer mNormals;
        IndexBuffer mIndexBuffer;
    };
}

#endif
