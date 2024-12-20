#include "MathEngine.h"
#include "GameObject.h"

#include "ColorByVertexGraphicsObject.h"
#include "ConstColorGraphicsObject.h"
#include "FlatTextureGraphicsObject.h"
#include "LightShader.h"
#include "LightTextureGraphicsObject.h"
#include "TextureNodeMan.h"

namespace Axiom
{
    GameObject::GameObject(GraphicsObject* graphicsObject)
        : mScale(new Scale())
          , mRot(new Quat())
          , mTrans(new Trans())
          , mGraphicsObject(graphicsObject)
          , mDrawEnable(true)
    {
        assert(graphicsObject);

        mWorld = new Mat4(Identity);
        assert(mWorld);
    }

    GameObject::~GameObject()
    {
        delete mScale;
        delete mTrans;
        delete mRot;
        delete mGraphicsObject;
        delete mWorld;
    }

    Mat4* GameObject::GetWorld() const
    {
        return mWorld;
    }

    void GameObject::SetPos(const Vec3& v) const
    {
        mTrans->set(v);
    }

    void GameObject::SetScale(const float scale) const
    {
        mScale->set(scale, scale, scale);
    }

    void GameObject::SetRot(const Quat& q)
    {
        *mRot = q;
    }

    void GameObject::SwapTexture(Texture* texture) const
    {
        if (mGraphicsObject->GetType() == Shader::Name::Light && texture)
        {
            ((LightTextureGraphicsObject*)mGraphicsObject)->mTexture = texture;
        }

        if (mGraphicsObject->GetType() == Shader::Name::FlatTexture && texture)
        {
            ((FlatTextureGraphicsObject*)mGraphicsObject)->mTexture = texture;
        }
    }

    void GameObject::SwapShader(Shader* shader)
    {
        Mesh* mesh = mGraphicsObject->GetModel();
        delete mGraphicsObject;

        Shader::Name type = shader->GetType();

        if (type == Shader::Name::Light)
        {
            Vec3 lightColor(1.0f, 1.0f, 1.0f);
            Vec3 lightPos(0.0f, 100.0f, -50.0f);

            lightColor *= 1.8f;
            mGraphicsObject = new LightTextureGraphicsObject(mesh, shader, TextureNodeMan::GetNext()->GetTexture(),
                                                             lightColor, lightPos);
        }
        else if (type == Shader::Name::FlatTexture)
        {
            mGraphicsObject = new FlatTextureGraphicsObject(mesh, shader, TextureNodeMan::GetNext()->GetTexture());
        }
        else if (type == Shader::Name::ColorByVertex)
        {
            mGraphicsObject = new ColorByVertexGraphicsObject(mesh, shader);
        }
        else if (type == Shader::Name::ConstColor)
        {
            mGraphicsObject = new ConstColorGraphicsObject(mesh, shader, Vec3(1.0f, 0.0f, 0.0f));
        }
    }

    GraphicsObject* GameObject::GetGraphicsObject()
    {
        return mGraphicsObject;
    }

    void GameObject::DrawEnable()
    {
        mDrawEnable = true;
    }

    void GameObject::DrawDisable()
    {
        mDrawEnable = false;
    }

    void GameObject::SetWorld(const Mat4* world) const
    {
        assert(world);
        *this->mWorld = *world;
    }

    void GameObject::Draw() const
    {
        // ---------------------------------------------
        //  Transfer data to the constant buffer
        //    CPU ---> GPU
        //    World, View, Projection Matrix
        //    Set Shader
        //    Render
        // ---------------------------------------------
        if (mDrawEnable)
        {
            mGraphicsObject->Render();
        }
    }
}
