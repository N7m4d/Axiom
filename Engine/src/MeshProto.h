#ifndef MESH_PROTO_H
#define MESH_PROTO_H

#include "Mesh.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "meshData.h"

namespace Axiom
{
    class MeshProto : public Mesh
    {
    public:
        MeshProto(const meshData& mesh);

        MeshProto() = delete;
        MeshProto(const MeshProto&) = delete;
        MeshProto& operator =(MeshProto& mesh) = delete;
        virtual ~MeshProto();

        void ActivateMesh() override;
        void RenderIndexBuffer() override;

    private:
        VertexBuffer mPos;
        VertexBuffer mTex;
        VertexBuffer mNorm;
        IndexBuffer mIndexBuffer;
    };
}

#endif
