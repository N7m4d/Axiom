#ifndef MESH_NODE_H
#define MESH_NODE_H

#include "DLink.h"
#include "Mesh.h"

namespace Axiom
{
    class MeshNode : public DLink
    {
    public:
        MeshNode();
        MeshNode(const Mesh&) = delete;
        MeshNode& operator =(const Mesh&) = delete;
        virtual ~MeshNode();

        void Set(Mesh::Name name, Mesh* mesh);
        Mesh* GetMesh() const;

        char* GetName() override;
        void Wash() override;
        bool Compare(DLink* targetNode) override;
        void Dump() override;

    private:
        void InternalClear();

        Mesh* mMesh;
    };
}

#endif
