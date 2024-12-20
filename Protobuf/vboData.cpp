#include "vboData.h"

vboData::~vboData()
{
	delete[] this->poData;
	this->poData = nullptr;
}

vboData::vboData(VBO_TARGET     _targetType,
	VBO_COMPONENT  _componetType,
	VBO_TYPE       _vboType,
	unsigned int  _stride,
	unsigned int   _count,
	unsigned int   _dataSize,
	unsigned char* _poData,
	bool enabled)
{
	this->targetType = _targetType;
	this->componentType = _componetType;
	this->vboType = _vboType;
	this->stride = _stride;
	this->count = _count;
	this->dataSize = _dataSize;
	this->poData = new unsigned char[this->dataSize]();

	assert(this->poData);
	memcpy_s(this->poData, this->dataSize, _poData, _dataSize);

	this->enabled = enabled;
}

vboData::vboData()
{
	targetType = VBO_TARGET::DEFAULT;
	componentType = VBO_COMPONENT::DEFAULT;
	vboType = VBO_TYPE::DEFAULT;
	stride = 0;
	count = 0;
	dataSize = 0;
	poData = nullptr;
	enabled = false;
}

vboData::vboData(const vboData& r)
{
	this->targetType = r.targetType;
	this->componentType = r.componentType;
	this->vboType = r.vboType;
	this->stride = r.stride;
	this->count = r.count;
	this->dataSize = r.dataSize;
	this->poData = new unsigned char[this->dataSize]();

	assert(this->poData);
	memcpy_s(this->poData, this->dataSize, r.poData, r.dataSize);

	this->enabled = r.enabled;
}

vboData& vboData::operator = (const vboData& r)
{
	if (this != &r)
	{
		delete[] this->poData;
		this->poData = nullptr;

		this->targetType = r.targetType;
		this->componentType = r.componentType;
		this->vboType = r.vboType;
		this->stride = r.stride;
		this->count = r.count;
		this->dataSize = r.dataSize;
		this->poData = new unsigned char[this->dataSize]();

		assert(this->poData);
		memcpy_s(this->poData, this->dataSize, r.poData, r.dataSize);

		this->enabled = r.enabled;
	}

	return *this;
}


void vboData::Serialize(vboData_proto& out) const
{
	AZUL_UNUSED_VAR(out);
	out.set_targettype((vboData_proto_VBO_TARGET)this->targetType);
	out.set_componenttype((vboData_proto_VBO_COMPONENT)this->componentType);
	out.set_vbotype((vboData_proto_VBO_TYPE)this->vboType);
	out.set_stride(this->stride);
	out.set_count(this->count);
	out.set_datasize(this->dataSize);
	out.set_enabled(this->enabled);
	// BinaryData 
	// First place "raw" into a string
	//     http://www.cplusplus.com/reference/string/string/string/
	//     from sequence(5): 	string(const char *s, size_t n);
	//     serialize the string
	std::string s((const char*)this->poData, this->dataSize);
	out.set_podata(s);

}

void vboData::Deserialize(const vboData_proto& in)
{
	this->targetType = (VBO_TARGET)in.targettype();
	this->componentType = (VBO_COMPONENT)in.componenttype();
	this->vboType = (VBO_TYPE)in.vbotype();
	this->stride = in.stride();
	this->count = in.count();
	this->dataSize = in.datasize();

	// release memory incase its been allocated
	delete[] this->poData;
	this->poData = nullptr;

	this->poData = new unsigned char[this->dataSize]();
	assert(this->poData);
	memcpy(this->poData, in.podata().data(), this->dataSize);

	this->enabled = in.enabled();
}

void vboData::Print(const char* const pName) const
{
	if (this->enabled)
	{
		Trace::out("%s: \n", pName);
		Trace::out("       dataSize: %d \n", this->dataSize);
		Trace::out("         poBuff: %2x %2x %2x %2x %2x \n",
			this->poData[0],
			this->poData[1],
			this->poData[2],
			this->poData[3],
			this->poData[4]);
		Trace::out("         stride: %d \n", this->stride);
		Trace::out("          count: %d \n", this->count);
		Trace::out("  componentType: %d\n", this->componentType);
		Trace::out("        vboType: %d \n", this->vboType);
		Trace::out("     targetType: %d \n", this->targetType);
	}
}

// --- End of File ---


