#ifndef DIAMOND_MESH_H
#define DIAMOND_MESH_H

#include "Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Axiom
{
    class DiamondMesh final : public Mesh
    {
    public:
        DiamondMesh();
        DiamondMesh(const DiamondMesh&) = delete;
        DiamondMesh& operator =(DiamondMesh&) = delete;
        ~DiamondMesh() override = default;

        void ActivateMesh() override;
        void RenderIndexBuffer() override;

        VertexBuffer mPos;
        VertexBuffer mTextureCoords;
        VertexBuffer mNorm;
        VertexBuffer mColors;
        IndexBuffer mIndexBuffer;
    };
}

#endif
