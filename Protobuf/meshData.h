#ifndef MESH_DATA_H
#define MESH_DATA_H

#include "meshData.pb.h"
#include "vboData.h"
#include "textureData.h"
#include "boundingSphereData.h"

class meshData
{
public:
	static const unsigned int FILE_NAME_SIZE = 64;

public:
	enum class RENDER_MODE
	{
		MODE_POINTS = 0,
		MODE_LINE = 1,
		MODE_LINE_LOOP = 2,
		MODE_LINE_STRIP = 3,
		MODE_TRIANGLES = 4,
		MODE_TRIANGLE_STRIP = 5,
		MODE_TRIANGLE_FAN = 6,
		DEFAULT = MODE_TRIANGLES
	};

public:
	meshData();
	meshData(const meshData &) = delete;
	meshData &operator = (const meshData &) = delete;
	~meshData();

	// Serialization 
	void Serialize(meshData_proto &out) const;
	void Deserialize(const meshData_proto &in);

	void Print(const char *const pName) const;

public:
	char               pVersion[protoVersion::VERSION_NUM_BYTES];
	char               pMeshName[FILE_NAME_SIZE];
	RENDER_MODE        mode;
	unsigned int       triCount;
	unsigned int       vertCount;

	vboData            vbo_vert;
	vboData            vbo_norm;
	vboData            vbo_uv;
	vboData            vbo_index;
	vboData            vbo_color;
	textureData		   texture;
	boundingSphereData bounding_sphere;
	float			   rotation[4];
	float		       translation[3];
	float			   scale[3];
	bool			   enabled;
};

#endif

// --- End of File ---
