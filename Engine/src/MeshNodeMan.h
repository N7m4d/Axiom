#ifndef MESH_NODE_MAN_H
#define MESH_NODE_MAN_H

#include "ManBase.h"
#include "MeshNode.h"

namespace Axiom
{
    class MeshNodeMan : public ManBase
    {
    public:
        static void Create(int reserveNum = 0, int reserveGrow = 1);
        static void Destroy();

        static MeshNode* Add(Mesh::Name name, Mesh* mesh);
        static Mesh* Find(Mesh::Name name);

        static void Remove(MeshNode* node);
        static void Dump();

    private:
        static MeshNodeMan* GetInstance();

        ~MeshNodeMan();
        MeshNodeMan(int reserveNum, int reserveGrow);

    protected:
        DLink* derivedCreateNode() override;

    private:
        MeshNode* mNodeCompare;
        static MeshNodeMan* mInstance;
    };
}

#endif
