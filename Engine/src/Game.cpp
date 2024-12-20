#include <d3d11.h>

#include "Game.h"
#include "Engine.h"
#include "MathEngine.h"
#include "Camera.h"
#include "Colors.h"
#include "GameObject.h"
#include "Shader.h"
#include "GameObjectMan.h"
#include "MeshNodeMan.h"
#include "MeshProto.h"
#include "CameraNodeMan.h"
#include "ShaderObjectNodeMan.h"
#include "DirectXDeviceMan.h"
#include "FlatTextureShader.h"
#include "LightShader.h"
#include "TextureNodeMan.h"
#include "GameObjectFactory.h"
#include "WalkAnim.h"
#include "WalkAnimController.h"
#include "RunAnimController.h"
#include "HitLeftAnimController.h"
#include "HitBackAnimController.h"
#include "SideStepLeftAnimController.h"
#include "AnimControllerNodeMan.h"
#include "AnimDemoInput.h"

namespace Axiom
{
    Game::Game(const char* const name, int width, int height)
        : Engine(name, width, height)
    {
        this->mGlobalTimer.Tic();
        this->mIntervalTimer.Tic();
    }

    Game::~Game()
    {
    }

    //-----------------------------------------------------------------------------
    // Game::LoadContent()
    //		Load all content needed for the engine,
    //	    such as objects, graphics, etc.
    //-----------------------------------------------------------------------------
    bool Game::LoadContent()
    {
        CameraNodeMan::Create();
        MeshNodeMan::Create();
        TextureNodeMan::Create();
        ShaderObjectNodeMan::Create();
        GameObjectMan::Create();
        AnimControllerNodeMan::Create();

        // ---------------------------------
        //  Camera - Setup
        // ---------------------------------
        Camera* camera = new Camera();

        camera->SetViewport(0, 0, this->mWindowWidth, this->mWindowHeight);

        camera->SetOrientAndPosition(Vec3(1.0f, 0.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(-1.0f, 12.0f, 10.0f));
        camera->SetPerspective(35.0f, float(camera->GetScreenWidth()) / float(camera->GetScreenHeight()), 1.0f,
                               10000.0f);
        camera->UpdateCamera();

        CameraNodeMan::Add(Camera::Name::FrontCamera, camera);
        CameraNodeMan::SetActive(Camera::Name::FrontCamera);

        // Load meshes
        GameObjectFactory factory;

        // Low poly
        factory.CreateProtoGameObject("Bone.proto.azul", Vec3(0.0f, 0.0f, 0.0f), Quat(Rot1::X, 0), 0, Mesh::Name::Bone);
        factory.CreateProtoGameObject("Bone_001.proto.azul", Vec3(0.0f, 0.0f, 0.0f), Quat(Rot1::X, 0), 0,
                                      Mesh::Name::Bone_001);
        factory.CreateProtoGameObject("Bone_L.proto.azul", Vec3(0.0f, 0.0f, 0.0f), Quat(Rot1::X, 0), 0,
                                      Mesh::Name::Bone_L);
        factory.CreateProtoGameObject("Bone_L_001.proto.azul", Vec3(0.0f, 0.0f, 0.0f), Quat(Rot1::X, 0), 0,
                                      Mesh::Name::Bone_L_001);
        factory.CreateProtoGameObject("Bone_L_002.proto.azul", Vec3(0.0f, 0.0f, 0.0f), Quat(Rot1::X, 0), 0,
                                      Mesh::Name::Bone_L_002);
        factory.CreateProtoGameObject("Bone_R.proto.azul", Vec3(0.0f, 0.0f, 0.0f), Quat(Rot1::X, 0), 0,
                                      Mesh::Name::Bone_R);
        factory.CreateProtoGameObject("Bone_R_001.proto.azul", Vec3(0.0f, 0.0f, 0.0f), Quat(Rot1::X, 0), 0,
                                      Mesh::Name::Bone_R_001);
        factory.CreateProtoGameObject("Bone_R_002.proto.azul", Vec3(0.0f, 0.0f, 0.0f), Quat(Rot1::X, 0), 0,
                                      Mesh::Name::Bone_R_002);

        Shader* flatShader = new FlatTextureShader(Shader::Name::FlatTexture);
        Shader* lightShader = new LightShader(Shader::Name::LightTexture);

        ShaderObjectNodeMan::Add(flatShader);
        ShaderObjectNodeMan::Add(lightShader);

        AnimTime delta = 0.5f * AnimTime(AnimTime::Duration::FILM_24_FRAME);

        WalkAnimController* pWalkAnimController = new WalkAnimController(delta);
        AnimControllerNodeMan::Add(AnimController::Name::Walk, pWalkAnimController);

        RunAnimController* runAnimController = new RunAnimController(delta);
        AnimControllerNodeMan::Add(AnimController::Name::Run, runAnimController);

        HitLeftAnimController* hitLeftAnimController = new HitLeftAnimController(delta);
        AnimControllerNodeMan::Add(AnimController::Name::HitLeft, hitLeftAnimController);

        HitBackAnimController* hitBackAnimController = new HitBackAnimController(delta);
        AnimControllerNodeMan::Add(AnimController::Name::HitBack, hitBackAnimController);

        SideStepLeftAnimController* sideStepLeftAnimController = new SideStepLeftAnimController(delta);
        AnimControllerNodeMan::Add(AnimController::Name::SideStepLeft, sideStepLeftAnimController);

        return true;
    }

    //-----------------------------------------------------------------------------
    // Game::Update()
    //      Called once per frame, update data, transformations, etc
    //      Input, AI, Physics, Animation, and Graphics
    //-----------------------------------------------------------------------------

    void Game::Update(float deltaTime)
    {
        CameraNodeMan::Update(deltaTime);

        AnimDemoInput();

        AnimControllerNodeMan::Update();

        GameObjectMan::Update(this->mGlobalTimer.Toc());
    }

    //-----------------------------------------------------------------------------
    // Game::Render()
    //		This function is called once per frame
    //	    Use this for draw graphics to the screen.
    //      Only do rendering here
    //-----------------------------------------------------------------------------
    void Game::Render()
    {
        this->SetDefaultTargetMode();
        GameObjectMan::Draw();
    }

    //-----------------------------------------------------------------------------
    // Game::UnLoadContent()
    //       unload content (resources loaded above)
    //       unload all content that was loaded before the Engine Loop started
    //-----------------------------------------------------------------------------
    void Game::UnloadContent()
    {
        AnimControllerNodeMan::Destroy();
        GameObjectMan::Destroy();
        ShaderObjectNodeMan::Destroy();
        TextureNodeMan::Destroy();
        MeshNodeMan::Destroy();
        CameraNodeMan::Destroy();
        DirectXDeviceMan::Destroy();
    }

    //------------------------------------------------------------------
    // Game::ClearBufferFunc()
    // Allows user to change the way the clear buffer function works
    // 
    // Clear the color and depth buffers.
    //------------------------------------------------------------------
    void Game::ClearDepthStencilBuffer()
    {
#ifdef _DEBUG
        const Vec4 ClearColor = Colors::LightGray;
#else
		const Vec4 ClearColor = Axiom::Colors::Wheat;
#endif
        float clearDepth = 1.0f;
        uint8_t clearStencil = 0;
        g_d3dDeviceContext->ClearRenderTargetView(g_d3dRenderTargetView, (const float*)&ClearColor);
        g_d3dDeviceContext->ClearDepthStencilView(g_d3dDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
                                                  clearDepth, clearStencil);
    }
}
