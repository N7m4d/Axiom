#ifndef STRING_THIS_H
#define STRING_THIS_H

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "AnimController.h"

#define StringMe(x)  ((char *)StringThis(x)) 

namespace Axiom
{
	class StringThis
	{
	public:
		static const unsigned int BUFFER_SIZE = 64;

		StringThis(Mesh::Name);
		StringThis(Shader::Name);
		StringThis(Camera::Name);
		StringThis(Texture::Name);
		StringThis(AnimController::Name);

		operator char *();
		
		char mBuffer[BUFFER_SIZE];
	};
}

#endif
