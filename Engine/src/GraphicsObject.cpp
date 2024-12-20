#include "GraphicsObject.h"
#include "MathEngine.h"
#include "Mesh.h"

Axiom::GraphicsObject::GraphicsObject(Mesh* model, Shader* shaderObj)
    : mModel(model)
      , mWorld(new Mat4(Identity))
      , mShaderObj(shaderObj)
{
    assert(model);
    assert(shaderObj);
}

Axiom::GraphicsObject::~GraphicsObject()
{
    delete mWorld;
}

void Axiom::GraphicsObject::Render()
{
    SetState();
    SetDataGPU();
    Draw();
    RestoreState();
}

Axiom::Mesh* Axiom::GraphicsObject::GetModel() const
{
    return mModel;
}

Axiom::Mat4& Axiom::GraphicsObject::GetWorld()
{
    return *mWorld;
}

Axiom::Shader::Name Axiom::GraphicsObject::GetType() const
{
    return mShaderObj->mName;
}

void Axiom::GraphicsObject::SetShader(Shader* shader)
{
    mShaderObj = shader;
}

void Axiom::GraphicsObject::SetWorld(Mat4& world)
{
    *mWorld = world;
}
