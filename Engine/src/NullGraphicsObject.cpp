#include "NullGraphicsObject.h"

Axiom::NullGraphicsObject::NullGraphicsObject(Mesh* mesh, Shader* shader)
    : GraphicsObject(mesh, shader)
{
}

void Axiom::NullGraphicsObject::SetState()
{
}

void Axiom::NullGraphicsObject::SetDataGPU()
{
}

void Axiom::NullGraphicsObject::Draw()
{
}

void Axiom::NullGraphicsObject::RestoreState()
{
}
