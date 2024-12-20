#include "meshData.h"

meshData::~meshData()
{

}

meshData::meshData()
	:pVersion{0},
	pMeshName{0},
	mode{meshData::RENDER_MODE::DEFAULT},
	triCount{0},
	vertCount{0},
	vbo_vert(),
	vbo_norm(),
	vbo_uv(),
	vbo_index(),
	rotation{0.0f},
	translation{0.0f},
	scale{1.0f}
{
	strcpy_s(this->pVersion, protoVersion::VERSION_NUM_BYTES, protoVersion::VERSION_STRING);
	assert(strlen(this->pVersion) < protoVersion::VERSION_NUM_BYTES);
}

void meshData::Serialize(meshData_proto &out) const
{
	AZUL_UNUSED_VAR(out);

	std::string sVersion((const char*)pVersion, protoVersion::VERSION_NUM_BYTES);
	out.set_pversion(sVersion);

	std::string sName((const char *)pMeshName, FILE_NAME_SIZE);
	out.set_pmeshname(sName);
	out.set_mode((meshData_proto_RENDER_MODE)mode);
	out.set_tricount(triCount);
	out.set_vertcount(vertCount);

	vboData_proto *pVBO_proto;

	pVBO_proto = new vboData_proto();
	vbo_vert.Serialize(*pVBO_proto);
	out.set_allocated_vbo_vert(pVBO_proto);

	pVBO_proto = new vboData_proto();
	vbo_norm.Serialize(*pVBO_proto);
	out.set_allocated_vbo_norm(pVBO_proto);

	pVBO_proto = new vboData_proto();
	vbo_uv.Serialize(*pVBO_proto);
	out.set_allocated_vbo_uv(pVBO_proto);

	pVBO_proto = new vboData_proto();
	vbo_index.Serialize(*pVBO_proto);
	out.set_allocated_vbo_index(pVBO_proto);

	pVBO_proto = new vboData_proto();
	vbo_color.Serialize(*pVBO_proto);
	out.set_allocated_vbo_color(pVBO_proto);

	textureData_proto* tex_proto = new textureData_proto();
	texture.Serialize(*tex_proto);
	out.set_allocated_texture(tex_proto);

	boundingSphereData_proto* boundingSphere_proto = new boundingSphereData_proto(); 
	bounding_sphere.Serialize(*boundingSphere_proto);
	out.set_allocated_bounding_sphere(boundingSphere_proto);

	out.add_rotation(rotation[0]);
	out.add_rotation(rotation[1]);
	out.add_rotation(rotation[2]);
	out.add_rotation(rotation[3]);

	out.add_translation(translation[0]);
	out.add_translation(translation[1]);
	out.add_translation(translation[2]);

	out.add_scale(scale[0]);
	out.add_scale(scale[1]);
	out.add_scale(scale[2]);

	out.set_enabled(enabled);
}

void meshData::Deserialize(const meshData_proto &in)
{
	memcpy_s(pVersion, protoVersion::VERSION_NUM_BYTES, in.pversion().data(), protoVersion::VERSION_NUM_BYTES);
	assert(strcmp(pVersion, protoVersion::VERSION_STRING) == 0);

	memcpy_s(pMeshName, FILE_NAME_SIZE, in.pmeshname().data(), FILE_NAME_SIZE);
	mode = (RENDER_MODE)in.mode();
	triCount = in.tricount();
	vertCount = in.vertcount();
	vbo_vert.Deserialize(in.vbo_vert());
	vbo_norm.Deserialize(in.vbo_norm());
	vbo_uv.Deserialize(in.vbo_uv());
	vbo_index.Deserialize(in.vbo_index());

	vbo_color.Deserialize(in.vbo_color());
	texture.Deserialize(in.texture());
	bounding_sphere.Deserialize(in.bounding_sphere());

	rotation[0] = in.rotation(0);
	rotation[1] = in.rotation(1);
	rotation[2] = in.rotation(2);
	rotation[3] = in.rotation(3);

	translation[0] = in.translation(0);
	translation[1] = in.translation(1);
	translation[2] = in.translation(2);

	scale[0] = in.scale(0);
	scale[1] = in.scale(1);
	scale[2] = in.scale(2);

	enabled = in.enabled();
}

void meshData::Print(const char *const pName) const
{
	Trace::out("%s: \n", pName);
	Trace::out("\n");

	Trace::out("version: %s \n", this->pVersion);

	this->vbo_vert.Print("vbo_vert");
	this->vbo_norm.Print("vbo_norm");
	this->vbo_uv.Print("vbo_uv");
	this->vbo_index.Print("vbo_index");
	this->vbo_color.Print("vbo_color");
	this->bounding_sphere.Print("bounding_sphere");
}

// --- End of File ---


