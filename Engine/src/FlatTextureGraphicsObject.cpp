#include "FlatTextureGraphicsObject.h"

#include "CameraNodeMan.h"
#include "Mesh.h"

Axiom::FlatTextureGraphicsObject::FlatTextureGraphicsObject(Mesh* mesh, Shader* shader, Texture* texture)
    : GraphicsObject(mesh, shader)
      , mTexture(texture)
{
}

Axiom::FlatTextureGraphicsObject::~FlatTextureGraphicsObject()
{
}

void Axiom::FlatTextureGraphicsObject::SetState()
{
    mTexture->ActivateTexture();
}

void Axiom::FlatTextureGraphicsObject::SetDataGPU()
{
    mShaderObj->ActivateShader();
    mShaderObj->ActivateCBV();
    mShaderObj->TransferWorldViewProj(CameraNodeMan::GetActive(), mWorld);
    mModel->ActivateMesh();
}

void Axiom::FlatTextureGraphicsObject::Draw()
{
    mModel->RenderIndexBuffer();
}

void Axiom::FlatTextureGraphicsObject::RestoreState()
{
    // TODO
}
