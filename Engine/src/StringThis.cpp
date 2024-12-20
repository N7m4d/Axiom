#include "StringThis.h"
#include "Texture.h"

Axiom::StringThis::StringThis(Mesh::Name name)
{
	switch(name)
	{
	case Mesh::Name::Cube:
		strcpy_s(mBuffer, BUFFER_SIZE, STRING_ME(Mesh::Cube));
		break;

	case Mesh::Name::NotInitialized:
		strcpy_s(mBuffer, BUFFER_SIZE, STRING_ME(Mesh::NotInitialized));
		break;

	case Mesh::Name::NullMesh:
		strcpy_s(mBuffer, BUFFER_SIZE, STRING_ME(Mesh::NullMesh));
		break;

	default:
		assert(false);
	}
}

Axiom::StringThis::StringThis(Shader::Name name)
{
	switch(name)
	{
	case Shader::Name::NullShader:
		strcpy_s(mBuffer, BUFFER_SIZE, STRING_ME(Shader::NullShader));
		break;

	case Shader::Name::ColorByVertex:
		strcpy_s(mBuffer, BUFFER_SIZE, STRING_ME(Shader::ColorByVertex));
		break;

	case Shader::Name::Uninitialized:
		strcpy_s(mBuffer, BUFFER_SIZE, STRING_ME(Shader::Uninitialized));
		break;

	default:
		assert(false);
	}
}

Axiom::StringThis::StringThis(Camera::Name name)
{
	switch(name)
	{
	case Camera::Name::NullCamera:
		strcpy_s(mBuffer, BUFFER_SIZE, STRING_ME(Camera::NullCamera));
		break;

	case Camera::Name::FrontCamera:
		strcpy_s(mBuffer, BUFFER_SIZE, STRING_ME(Camera::DefaultCamera));
		break;

	case Camera::Name::Uninitialized:
		strcpy_s(mBuffer, BUFFER_SIZE, STRING_ME(Camera::Uninitialized));
		break;

	default:
		assert(false);
	}
}

Axiom::StringThis::StringThis(Texture::Name status)
{
	switch(status)
	{
	case Texture::Name::Duckweed:
		strcpy_s(mBuffer, BUFFER_SIZE, STRING_ME(Camera::NullCamera));
		break;

	/*case Texture::Name::DefaultCamera:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Camera::DefaultCamera));
		break;

	case Texture::Name::Uninitialized:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Camera::Uninitialized));
		break;*/

	default:
		assert(false);
	}
}

Axiom::StringThis::StringThis(AnimController::Name)
{

}

Axiom::StringThis::operator char *()
{
	return mBuffer;
}
