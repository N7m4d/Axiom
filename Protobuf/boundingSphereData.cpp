#include "boundingSphereData.h"

//boundingSphereData::boundingSphereData(float* cntr, const float rad)
//	: mCntr{ cntr }
//	, mRad{ rad }
//{
//}

void boundingSphereData::Serialize(boundingSphereData_proto& out) const
{
	/*const float x = mCntr.x();
	const float y = mCntr.y();
	const float z = mCntr.z();*/

	out.add_cntr(mCntr[0]);
	out.add_cntr(mCntr[1]);
	out.add_cntr(mCntr[2]);
	out.set_rad(mRad);
}

void boundingSphereData::Deserialize(const boundingSphereData_proto& in)
{
	for (int i = 0; i < in.cntr().size(); ++i)
	{
		mCntr[i] = in.cntr(i);
	}

	mRad = in.rad();
}

void boundingSphereData::Print(const char* const pName) const
{
	Trace::out("%s: \n", pName);
	Trace::out("      cntr: x -> %.6f, y -> %.6f, z -> %.6f \n", mCntr[0], mCntr[1], mCntr[2]);
	Trace::out("      rad: %.6f", mRad);
}
