#include "LightTextureGraphicsObject.h"

#include "CameraNodeMan.h"
#include "LightShader.h"
#include "Mesh.h"

Axiom::LightTextureGraphicsObject::LightTextureGraphicsObject(Mesh* mesh, Shader* shader, Texture* texture,
                                                              const Vec3& lightColor,
                                                              const Vec3& lightPos)
    : GraphicsObject(mesh, shader)
      , mTexture(texture)
      , mLightColor(new Vec3(lightColor))
      , mLightPos(new Vec3(lightPos))
{
}

Axiom::LightTextureGraphicsObject::~LightTextureGraphicsObject()
{
    delete mLightColor;
    delete mLightPos;
}

void Axiom::LightTextureGraphicsObject::SetState()
{
    mTexture->ActivateTexture();
}

void Axiom::LightTextureGraphicsObject::SetDataGPU()
{
    mShaderObj->ActivateShader();
    mShaderObj->ActivateCBV();

    mShaderObj->TransferWorldViewProj(CameraNodeMan::GetActive(), mWorld);
    ((LightShader*)mShaderObj)->TransferLight(mLightColor, mLightPos);

    mModel->ActivateMesh();
}

void Axiom::LightTextureGraphicsObject::Draw()
{
    mModel->RenderIndexBuffer();
}

void Axiom::LightTextureGraphicsObject::RestoreState()
{
    // TODO
}
