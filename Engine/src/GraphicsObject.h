#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include "MathEngine.h"
#include "Shader.h"
#include "Render.h"

namespace Axiom
{
    class Mesh;

    class GraphicsObject : public Render
    {
    public:
        GraphicsObject(Mesh* model, Shader* shaderObj);

        GraphicsObject() = delete;
        GraphicsObject(const GraphicsObject&) = delete;
        GraphicsObject& operator =(const GraphicsObject&) = delete;
        virtual ~GraphicsObject() override;

        void Render();
        void SetWorld(Mat4& world);

        Mesh* GetModel() const;
        Mat4& GetWorld();

        Shader::Name GetType() const;

        void SetShader(Shader* shader);

    protected:
        Mesh* mModel;
        Mat4* mWorld;
        Shader* mShaderObj;
    };
}

#endif
