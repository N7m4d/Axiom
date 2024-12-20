#ifndef NULL_MESH_H
#define NULL_MESH_H

#include "Mesh.h"

namespace Axiom
{
    class NullMesh : public Mesh
    {
    public:
        NullMesh();
        NullMesh(const NullMesh&) = delete;
        NullMesh& operator=(const NullMesh& other) = delete;
        ~NullMesh() override = default;

        void ActivateMesh() override;
        void RenderIndexBuffer() override;
    };
}

#endif
