#ifndef SHADER_CBV_BUFFER_H
#define SHADER_CBV_BUFFER_H

#include <d3d11.h>
#include "ShaderMappings.h"

namespace Axiom
{
	class ShaderCBVBuffer
	{
	public:
		ShaderCBVBuffer() = delete;
		ShaderCBVBuffer(const ShaderCBVBuffer &r) = delete;
		ShaderCBVBuffer &operator=(const ShaderCBVBuffer &) = delete;
		virtual ~ShaderCBVBuffer();

		ShaderCBVBuffer(size_t structSize);

		void Transfer(const void *buffer) const;
		void SetActive(ConstantBufferSlot slot);

	private:
		void privCreate(size_t structSize);
	
	public:
		size_t mStructSize;
		ID3D11Buffer *mShaderCBVBuffer;
		bool mCreate;
	};
}

#endif
