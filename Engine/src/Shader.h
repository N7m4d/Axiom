#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

#include "MathEngine.h"
#include "Camera.h"
#include "ConstantBuffer.h"
#include "InputLayout.h"
#include "PixelShader.h"
#include "VertexShader.h"

namespace Axiom
{
	class Shader
	{
	public:
		enum class Name
		{
			NullShader,
			ColorByVertex,
			FlatTexture,
			Light,
			ConstColor,
			Uninitialized,
			LightTexture
		};

		Shader() = delete;
		Shader(const Shader&) = delete;
		Shader& operator = (const Shader&) = delete;
		virtual ~Shader() = default;

		Shader(Name name, size_t vsSize, const void* vsBytecode, size_t psSize, const void* psBytecode, 
		D3D11_INPUT_ELEMENT_DESC* inputElemsDesc, size_t inputElemsDescSize);

		virtual void ActivateShader();
		virtual void ActivateCBV();
		virtual void TransferWorldViewProj(Camera* camera, Mat4* worldMatrix);

		static const char* GetLatestPixelShaderProfile();
		static const char* GetLatestVertexShaderProfile();

		char* GetName() const;
		void SetName(Name name);

		Name GetType() const;

		Name mName;

		ConstantBuffer mProjection;
		ConstantBuffer mWorld;
		ConstantBuffer mView;

		VertexShader mVertexShader;
		PixelShader mPixelShader;

		InputLayout mInputLayout;
	};
}

#endif
