#ifndef TEXTURE_NODE_MAN_H
#define TEXTURE_NODE_MAN_H

#include "ManBase.h"
#include "TextureNode.h"

namespace Axiom
{
    class TextureNodeMan : public ManBase
    {
    public:
        static void Create(int reserveNum = 0, int reserveGrow = 1);
        static void Destroy();

        static TextureNode* Add(Texture::Name name, Texture* texture);
        static Texture* Find(Texture::Name name);

        static TextureNode* GetNext();

        static void Remove(TextureNode* node);
        static void Dump();
    
    private:
        static TextureNodeMan* GetInstance();

        ~TextureNodeMan() override;
        TextureNodeMan(int reserveNum, int reserveGrow);
    
    protected:
        DLink* derivedCreateNode() override;
    
    private:
        TextureNode* mNodeCompare;
        DLink* mCurrent;
        static TextureNodeMan* mInstance;
    };
}

#endif
