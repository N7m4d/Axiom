#ifndef SPHERE_MESH_H
#define SPHERE_MESH_H

#include "Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Axiom
{
    class SphereMesh final : public Mesh
    {
    public:
        SphereMesh();
        SphereMesh(const SphereMesh&) = delete;
        SphereMesh& operator =(SphereMesh&) = delete;
        ~SphereMesh() override = default;

        void ActivateMesh() override;
        void RenderIndexBuffer() override;

        VertexBuffer mPos;
        VertexBuffer mColor;
        VertexBuffer mTexCoords;
        VertexBuffer mNormals;
        IndexBuffer mIndexBuffer;
    };
}

#endif
