#ifndef SHADER_OBJECT_NODE_MAN_H
#define SHADER_OBJECT_NODE_MAN_H 

#include "ManBase.h"
#include "ShaderObjectNode.h"
#include "Shader.h"

namespace Axiom
{
    class ShaderObjectNodeMan : public ManBase
    {
    public:
        static void Create(int reserveNum = 0, int reserveGrow = 1);
        static void Destroy();

        static ShaderObjectNode* Add(Shader* pShaderObject);
        static Shader* Find(Shader::Name name);

        static void Remove(ShaderObjectNode* node);
        static void Dump();

        static ShaderObjectNode* GetNext();

    private:
        static ShaderObjectNodeMan* GetInstance();

        ~ShaderObjectNodeMan() override;
        ShaderObjectNodeMan(int reserveNum, int reserveGrow);

    protected:
        DLink* derivedCreateNode() override;

    private:
        ShaderObjectNode* mNodeCompare;
        DLink* mCurrent;
        static ShaderObjectNodeMan* mInstance;
    };
}

#endif
