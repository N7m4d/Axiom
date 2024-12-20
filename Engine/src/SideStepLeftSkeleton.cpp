#include "LightTextureGraphicsObject.h"
#include "FlatTextureGraphicsObject.h"
#include "GameObjectBasic.h"
#include "GameObjectMan.h"
#include "ShaderObjectNodeMan.h"
#include "NullGraphicsObject.h"
#include "SideStepLeftSkeleton.h"
#include "MeshNodeMan.h"
#include "GameObjectAnimSkeleton.h"
#include "GameObjectAnimSkin.h"
#include "TextureNodeMan.h"
#include "PCSTreeForwardIterator.h"

namespace Axiom
{
    SideStepLeftSkeleton::Data skel[]
    {
        {4, -1, "Bone"},
        {5, 4, "Bone_L"},
        {6, 5, "Bone_L_001"},
        {7, 6, "Bone_L_002"},
        {8, 4, "Bone_R"},
        {9, 8, "Bone_R_001"},
        {10, 9, "Bone_R_002"},
        {11, 4, "Bone_001"}
    };

    SideStepLeftSkeleton::SideStepLeftSkeleton(Bone* bone, int _numBones)
        : mFirstBone(nullptr),
          mNumBones(_numBones)
    {
        privSetAnimationHierarchy(bone);
        assert(mFirstBone);
    }

    SideStepLeftSkeleton::~SideStepLeftSkeleton()
    {
    }

    GameObjectAnim* SideStepLeftSkeleton::GetFirstBone()
    {
        assert(mFirstBone);
        return mFirstBone;
    }

    GameObjectAnim* SideStepLeftSkeleton::privFindBoneByIndex(int index)
    {
        GameObjectAnim* pFound = nullptr;

        GameObjectAnim* pObj = GetFirstBone();

        // TODO - add test bed for an interator of a tree with only one node
        if (pObj->mIndex == index)
        {
            pFound = pObj;
        }
        else
        {
            PCSTreeForwardIterator pIter(pObj);
            PCSNode* pNode = pIter.First();
            GameObjectAnim* pGameObj = nullptr;

            // walks the anim node does the pose for everything that
            while (pNode != nullptr)
            {
                assert(pNode);
                // Update the game object
                pGameObj = (GameObjectAnim*)pNode;
                if (pGameObj->mIndex == index)
                {
                    pFound = pGameObj;
                    break;
                }
                pNode = pIter.Next();
            }
        }

        return pFound;
    }

    void SideStepLeftSkeleton::privSetAnimationHierarchy(Bone* bone)
    {
        assert(bone);

        // Mesh
        Mesh* MeshArray[8];

        MeshArray[0] = MeshNodeMan::Find(Mesh::Name::Bone);
        MeshArray[1] = MeshNodeMan::Find(Mesh::Name::Bone_L);
        MeshArray[2] = MeshNodeMan::Find(Mesh::Name::Bone_L_001);
        MeshArray[3] = MeshNodeMan::Find(Mesh::Name::Bone_L_002);
        MeshArray[4] = MeshNodeMan::Find(Mesh::Name::Bone_R);
        MeshArray[5] = MeshNodeMan::Find(Mesh::Name::Bone_R_001);
        MeshArray[6] = MeshNodeMan::Find(Mesh::Name::Bone_R_002);
        MeshArray[7] = MeshNodeMan::Find(Mesh::Name::Bone_001);

        // Load Shader 
        Shader* pShaderObject_textureLight = ShaderObjectNodeMan::Find(Shader::Name::LightTexture);
        assert(pShaderObject_textureLight);

        // GraphicsObject for a specific instance
        GraphicsObject* pGraphicsObj;

        // Create GameObject
        Vec3 color(1, 1, 1);
        Vec3 pos(1, 1, 1);

        //---------------------------------------
        // ChickenBot
        //---------------------------------------

        Texture* pTex = TextureNodeMan::Find(Texture::Name::ChickenBot);

        // Add A Dummy pivot object
        Mesh* pMeshNull = MeshNodeMan::Find(Mesh::Name::NULL_MESH);
        assert(pMeshNull);

        Shader* pShaderNull = ShaderObjectNodeMan::Find(Shader::Name::NullShader);
        assert(pShaderNull);

        pGraphicsObj = new NullGraphicsObject(pMeshNull, pShaderNull);
        GameObjectBasic* pPivot = new GameObjectBasic(pGraphicsObj);
        pPivot->SetName("Pivot");
        pPivot->DrawDisable();
        pPivot->mDeltaX = 0.003f;
        pPivot->SetScale(100, 100, 100);
        pPivot->SetTrans(0, 2, -8);

        // Add Bones in Hierarchy
        GameObjectMan::Add(pPivot, GameObjectMan::GetRoot());

        GameObjectAnim* pGameObj;

        // Root animation is treated differently
        for (int i = 0; i < 1; i++)
        {
            pGraphicsObj = new LightTextureGraphicsObject(MeshArray[i], pShaderObject_textureLight, pTex, color, pos);
            pGameObj = new GameObjectAnimSkin(pGraphicsObj, bone);
            pGameObj->SetIndex(skel[i].index);
            pGameObj->SetName(skel[i].name);

            GameObjectMan::Add(pGameObj, pPivot);
            mFirstBone = pGameObj;
        }

        for (int i = 1; i < mNumBones - 4; i++)
        {
            pGraphicsObj = new LightTextureGraphicsObject(MeshArray[i], pShaderObject_textureLight, pTex, color, pos);
            pGameObj = new GameObjectAnimSkin(pGraphicsObj, bone);
            pGameObj->SetIndex(skel[i].index);
            pGameObj->SetName(skel[i].name);

            GameObjectAnim* pParent = privFindBoneByIndex(skel[i].parentIndex);
            GameObjectMan::Add(pGameObj, pParent);
        }
    }
}
