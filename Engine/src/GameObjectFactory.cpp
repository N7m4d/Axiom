#include "GameObjectFactory.h"
#include "File.h"
#include "meshData.pb.h"
#include "meshData.h"
#include "MeshProto.h"
#include "SphereMesh.h"
#include "TextureProto.h"
#include "MeshNodeMan.h"
#include "Shader.h"
#include "FlatTextureGraphicsObject.h"
#include "TextureNodeMan.h"

void Axiom::GameObjectFactory::CreateProtoGameObject(const char* const fileName, const Vec3& translation, const Quat& rotation, const float scale, Mesh::Name meshName)
{
	assert(fileName);

	File::Handle fh;
	File::Error  ferror;

	ferror = File::Open(fh, fileName, File::Mode::READ);
	assert(ferror == File::Error::SUCCESS);

	// Get the size
	ferror = File::Seek(fh, File::Position::END, 0);
	assert(ferror == File::Error::SUCCESS);

	DWORD length;
	ferror = File::Tell(fh, length);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Position::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	char* poBuff = new char[length];
	assert(poBuff);

	ferror = File::Read(fh, poBuff, length);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);

	std::string strIn(poBuff, length);

	meshData_proto meshProtoBuf;
	meshProtoBuf.ParseFromArray(poBuff, length);

	meshData rawMesh;
	rawMesh.Deserialize(meshProtoBuf);

	MeshProto* mesh = new MeshProto(rawMesh);
	MeshNodeMan::Add(meshName, mesh);

	TextureProto* texture = new TextureProto(rawMesh.texture, Texture::Name::ChickenBot);
	TextureNodeMan::Add(Texture::Name::ChickenBot, texture);

	delete[] poBuff;
}
