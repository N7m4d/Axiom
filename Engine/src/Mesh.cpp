#include "Mesh.h"
#include "StringThis.h"
#include "DirectXDeviceMan.h"

Axiom::Mesh::Mesh(const unsigned int numVertices, const unsigned int numIndices)
    : mName(Name::NotInitialized)
      , mNumVertices(numVertices)
      , mNumIndices(numIndices)
{
}

void Axiom::Mesh::Wash()
{
}

bool Axiom::Mesh::Compare(DLink* target)
{
    assert(target != nullptr);

    Mesh* mesh = (Mesh*)target;

    if (mName == mesh->mName)
    {
        return true;
    }

    return false;
}

void Axiom::Mesh::SetName(Name name)
{
    mName = name;
}

char* Axiom::Mesh::GetName() const
{
    static char tmp[128];
    strcpy_s(tmp, 128, StringMe(mName));
    return tmp;
}
