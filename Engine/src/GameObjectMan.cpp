#include "NullMesh.h"
#include "NullGraphicsObject.h"
#include "ShaderObjectNull.h"
#include "GameObject.h"
#include "GameObjectMan.h"
#include "PCSTreeForwardIterator.h"
#include "ShaderObjectNodeMan.h"
#include "TextureNodeMan.h"
#include "MeshNodeMan.h"
#include "GameObjectRigid.h"

namespace Axiom
{
    NullMesh* pModel = nullptr;
    Shader* pShader = nullptr;

    void GameObjectMan::Add(GameObject* obj, GameObject* parent)
    {
        assert(obj);
        assert(parent);

        GameObjectMan* man = GetInstance();
        man->mRoot->Insert(obj, parent);
    }

    void GameObjectMan::Destroy()
    {
        GameObjectMan* man = GetInstance();
        assert(man);

        PCSTree* tree = man->mRoot;

        PCSTreeForwardIterator it(tree->GetRoot());
        it.First();

        while (!it.IsDone())
        {
            PCSNode* tmp = it.Current();
            it.Next();
            delete tmp;
        }
    }

    void GameObjectMan::SwapTextures()
    {
        GameObjectMan* man = GetInstance();
        assert(man);

        PCSNode* root = man->mRoot->GetRoot();
        assert(root);

        TextureNode* textureNode = TextureNodeMan::GetNext();

        PCSTreeForwardIterator it(root);
        for (it.First(); !it.IsDone(); it.Next())
        {
            GameObject* gameObj = (GameObject*)it.Current();
            gameObj->SwapTexture(textureNode->GetTexture());
        }
    }

    void GameObjectMan::SwapShaders()
    {
        GameObjectMan* man = GetInstance();
        assert(man);

        PCSNode* root = man->mRoot->GetRoot();
        assert(root);

        ShaderObjectNode* shaderNode = ShaderObjectNodeMan::GetNext();

        PCSTreeForwardIterator it(root);
        for (it.First(); !it.IsDone(); it.Next())
        {
            GameObject* pGameObj = (GameObject*)it.Current();
            pGameObj->SwapShader(shaderNode->GetShaderObject());
        }
    }

    void GameObjectMan::Update(AnimTime currTime)
    {
        GameObjectMan* man = GetInstance();
        assert(man);

        PCSNode* root = man->mRoot->GetRoot();
        assert(root);

        PCSTreeForwardIterator it(root);

        for (it.First(); !it.IsDone(); it.Next())
        {
            GameObject* gameObj = (GameObject*)it.Current();
            gameObj->Update(currTime);
        }
    }

    void GameObjectMan::Draw()
    {
        GameObjectMan* man = GetInstance();
        assert(man);

        PCSNode* root = man->mRoot->GetRoot();
        assert(root);

        PCSTreeForwardIterator it(root);

        for (it.First(); !it.IsDone(); it.Next())
        {
            GameObject* gameObj = (GameObject*)it.Current();
            gameObj->Draw();
        }
    }

    void GameObjectMan::Create()
    {
        GameObjectMan* man = GetInstance();
        AZUL_UNUSED_VAR(man);
        assert(man);
    }

    GameObjectMan::GameObjectMan()
    {
        NullMesh* mesh = new NullMesh();
        assert(mesh);

        MeshNodeMan::Add(Mesh::Name::NULL_MESH, mesh);

        Shader* shader = new ShaderObjectNull(Shader::Name::NullShader);
        assert(shader);
        ShaderObjectNodeMan::Add(shader);

        NullGraphicsObject* graphicsObject = new NullGraphicsObject(mesh, shader);
        GameObjectRigid* root = new GameObjectRigid(graphicsObject);
        root->SetName("GameObject_Root");

        mRoot = new PCSTree();
        assert(mRoot);

        mRoot->Insert(root, mRoot->GetRoot());
    }

    GameObjectMan::~GameObjectMan()
    {
        delete pModel;
        delete pShader;

        delete mRoot;
    }

    GameObjectMan* GameObjectMan::GetInstance()
    {
        static GameObjectMan man;
        return &man;
    }

    GameObject* GameObjectMan::GetRoot()
    {
        GameObjectMan* man = GetInstance();
        assert(man);

        GameObject* gameObj = (GameObject*)man->mRoot->GetRoot();
        assert(gameObj);

        return gameObj;
    }

    PCSTree* GameObjectMan::GetPCSTree()
    {
        GameObjectMan* man = GetInstance();
        assert(man);

        return man->mRoot;
    }
}
