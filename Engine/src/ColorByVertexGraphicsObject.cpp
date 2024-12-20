#include "Mesh.h"
#include "ColorByVertexGraphicsObject.h"
#include "CameraNodeMan.h"

// ---------------------------------------------
//  Transfer data to the constant buffer
//    CPU ---> GPU
//    World, View, Projection Matrix
// ---------------------------------------------
Axiom::ColorByVertexGraphicsObject::ColorByVertexGraphicsObject(Mesh* mesh, Shader* shader)
	: GraphicsObject(mesh, shader)
{
}

void Axiom::ColorByVertexGraphicsObject::SetState()
{
	// Future - settings to directX
	// say make it wireframe or change culling mode
}

void Axiom::ColorByVertexGraphicsObject::SetDataGPU()
{
	mShaderObj->ActivateShader();
	mShaderObj->ActivateCBV();
	mShaderObj->TransferWorldViewProj(CameraNodeMan::GetActive(), mWorld);
	mModel->ActivateMesh();
}

void Axiom::ColorByVertexGraphicsObject::Draw()
{
	mModel->RenderIndexBuffer();
}

void Axiom::ColorByVertexGraphicsObject::RestoreState()
{
	// Future - Undo settings to directX
}
