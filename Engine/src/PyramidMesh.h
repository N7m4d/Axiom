#ifndef PYRAMID_MESH_H
#define PYRAMID_MESH_H

#include "Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Axiom
{
	class PyramidMesh final : public Mesh
	{
	public:
		PyramidMesh();
		PyramidMesh(const PyramidMesh&) = delete;
		PyramidMesh& operator = (PyramidMesh&) = delete;
		~PyramidMesh() override = default;

		void ActivateMesh() override;
		void RenderIndexBuffer() override;

		VertexBuffer mPos;
		VertexBuffer mTexture;
		VertexBuffer mColors;
		VertexBuffer mNorm;
		IndexBuffer mIndexBuffer;
	};
}

#endif
