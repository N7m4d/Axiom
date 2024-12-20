#ifndef MODEL_DATA_H
#define MODEL_DATA_H

#include "modelData.pb.h"
#include "meshData.h"

class modelData
{
public:
	modelData();
	modelData(meshData* meshes, unsigned int numMeshes);
	modelData(unsigned int numMeshes);
	modelData(const modelData &) = delete;
	modelData &operator = (const modelData &) = delete;
	~modelData();

	// Serialization 
	void Serialize(modelData_proto &out) const;
	void Deserialize(const modelData_proto &in);

	void Print(const char *const pName) const;

public:
	meshData* m_meshData;
	unsigned int m_numMeshes;
	bool m_enabled;
};

#endif

// --- End of File ---
