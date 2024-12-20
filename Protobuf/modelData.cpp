#include "modelData.h"

modelData::modelData()
	: m_meshData{ nullptr }
	, m_numMeshes{ 0 }
	, m_enabled{ true }
{
}

modelData::modelData(meshData* meshes, unsigned int numMeshes)
	: m_meshData{ meshes }
	, m_numMeshes{ numMeshes }
{
}

modelData::modelData(unsigned int numMeshes)
	: m_meshData{ new meshData[numMeshes] }
	, m_numMeshes{ numMeshes }
	, m_enabled{ true }
{
}

modelData::~modelData()
{
	delete[] m_meshData;
}

void modelData::Serialize(modelData_proto& out) const
{
	for (unsigned int i = 0; i < m_numMeshes; ++i)
	{
		meshData_proto* meshData = out.add_meshes();
		m_meshData[i].Serialize(*meshData);
	}
}

void modelData::Deserialize(const modelData_proto& in)
{
	m_numMeshes = in.meshes_size();

	for (unsigned int i = 0; i < m_numMeshes; ++i)
	{
		m_meshData[i].Deserialize(in.meshes(i));
	}
}

void modelData::Print(const char* const pName) const
{
}
