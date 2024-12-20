#ifndef SHADER_OBJECT_NODE_H
#define SHADER_OBJECT_NODE_H

#include "DLink.h"
#include "Shader.h"

namespace Axiom
{
    class ShaderObjectNode : public DLink
    {
    public:
        ShaderObjectNode();
        ShaderObjectNode(const Shader&) = delete;
        ShaderObjectNode& operator =(const Shader&) = delete;
        virtual ~ShaderObjectNode();

        void Set(Shader* shader);
        Shader* GetShaderObject() const;

        char* GetName() override;
        void Wash() override;
        bool Compare(DLink* targetNode) override;
        void Dump() override;

    private:
        void privClear();

        Shader* mShaderObject;
    };
}

#endif
