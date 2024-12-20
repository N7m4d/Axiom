#ifndef BOUNDING_SPHERE_DATA_H
#define BOUNDING_SPHERE_DATA_H

#include "boundingSphereData.pb.h"

class boundingSphereData
{
public:
	boundingSphereData() = default;
	//boundingSphereData(float* cntr, const float rad);

	void Serialize(boundingSphereData_proto& out) const;
	void Deserialize(const boundingSphereData_proto& in);
	
	void Print(const char *const pName) const;

	float mCntr[3];
	float mRad;
};

#endif
