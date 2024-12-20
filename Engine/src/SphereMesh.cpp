#include "SphereMesh.h"
#include "DirectXDeviceMan.h"

Axiom::SphereMesh::SphereMesh()
	: Mesh(0, 0)
{
	constexpr unsigned int numRings = 18;
	constexpr unsigned int numSegments = 36;

	VertexPos vertices[(numRings + 1) * (numSegments + 1)];
	uint32_t indices[numRings * numSegments * 6];
	VertexColor colors[(numRings + 1) * (numSegments + 1)];
	Vec2f texCoords[(numRings + 1) * (numSegments + 1)];
	Vec3 normals[(numRings + 1) * (numSegments + 1)];

	unsigned int vIndex = 0, iIndex = 0, cIndex = 0, tIndex = 0, nIndex = 0;

	for (unsigned int y = 0; y <= numRings; ++y) {
		for (unsigned int x = 0; x <= numSegments; ++x) {
			const float xSegment = static_cast<float>(x) / static_cast<float>(numSegments);
			const float ySegment = static_cast<float>(y) / static_cast<float>(numRings);
			const float xPos = Trig::cos(xSegment * 2.0f * MATH_PI) * Trig::sin(ySegment * MATH_PI);
			const float yPos = Trig::cos(ySegment * MATH_PI);
			const float zPos = Trig::sin(xSegment * 2.0f * MATH_PI) * Trig::sin(ySegment * MATH_PI);

			Vec3 vec(xPos, yPos, zPos);
			vertices[vIndex++] = { vec };
			normals[nIndex++] = vec; // The normal is the same as the position vector for a sphere centered at the origin

			const float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            const float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            const float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

			vec.set(r, g, b);
			colors[cIndex++] = { vec };

			texCoords[tIndex++] = { xSegment, ySegment };

			if (x != numSegments && y != numRings) {
				const unsigned int current = y * (numSegments + 1) + x;
				indices[iIndex++] = current;
				indices[iIndex++] = current + numSegments + 1;
				indices[iIndex++] = current + numSegments + 2;
				indices[iIndex++] = current;
				indices[iIndex++] = current + numSegments + 2;
				indices[iIndex++] = current + 1;
			}
		}
	}

	mPos.Init(sizeof(VertexPos) * vIndex, sizeof(VertexPos), vertices);
	mColor.Init(sizeof(VertexColor) * cIndex, sizeof(VertexColor), colors);
	mTexCoords.Init(sizeof(VertexTexCoord) * tIndex, sizeof(VertexTexCoord), texCoords);
	mNormals.Init(sizeof(Vec3) * nIndex, sizeof(Vec3), normals);
	mIndexBuffer.Init(sizeof(uint32_t) * iIndex, indices);

	mNumIndices = iIndex;
}

void Axiom::SphereMesh::ActivateMesh()
{
	mPos.SetActive(VertexSlot::Position);
	mColor.SetActive(VertexSlot::Color);
	mTexCoords.SetActive(VertexSlot::TexCoord);
	mNormals.SetActive(VertexSlot::Norm);
}

void Axiom::SphereMesh::RenderIndexBuffer()
{
	mIndexBuffer.SetActive();

	DirectXDeviceMan::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DirectXDeviceMan::GetContext()->DrawIndexed(mNumIndices, 0, 0);
}
