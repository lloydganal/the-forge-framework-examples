//#pragma comment(lib, "XInput.lib")

#if defined(_WIN32) && !defined(_WINDOWS)
#define _WINDOWS
#endif
#include <Common_3/OS/Interfaces/IApp.h>
#define VULKAN
#include <Common_3/OS/Interfaces/IInput.h>
//#include <Common_3/Renderer/IRenderer.h>

#include <iostream>

using TF_IApp = IApp;

void test_button_any() { int a = 0; }

void tf_add_input_action(uint32_t binding, InputActionCallback function_ptr, void* user_data_ptr) {
    InputActionDesc action_desc = {};
    action_desc.mBinding = binding;
    action_desc.pFunction = function_ptr;
    action_desc.pUserData = user_data_ptr;
    addInputAction(&action_desc);
};

class MyApp : public TF_IApp {
  public:
    MyApp() {
        mSettings.mWidth = 800;
        mSettings.mHeight = 600;
    }

    ~MyApp() {}

    bool Init() {
        fsSetPathForResourceDir(pSystemFileIO, RM_CONTENT, RD_SHADER_SOURCES, "Shaders");
        fsSetPathForResourceDir(pSystemFileIO, RM_DEBUG, RD_SHADER_BINARIES, "CompiledShaders");
        fsSetPathForResourceDir(pSystemFileIO, RM_CONTENT, RD_GPU_CONFIG, "GPUCfg");
        fsSetPathForResourceDir(pSystemFileIO, RM_CONTENT, RD_TEXTURES, "Textures");
        fsSetPathForResourceDir(pSystemFileIO, RM_CONTENT, RD_FONTS, "Fonts");
        fsSetPathForResourceDir(pSystemFileIO, RM_DEBUG, RD_SCREENSHOTS, "Screenshots");
        fsSetPathForResourceDir(pSystemFileIO, RM_CONTENT, RD_SCRIPTS, "Scripts");

        // RendererDesc settings = {0};
        // settings.mApi = RendererApi::RENDERER_API_VULKAN;
        // initRenderer(GetName(), &settings, &m_renderer);
        // if (!m_renderer) {
        //    return false;
        //}

        if (!initInputSystem(pWindow)) {
            return false;
        }

        InputActionDesc action_desc = {InputBindings::BUTTON_EXIT, [](InputActionContext* ctx) {
                                           requestShutdown();
                                           return true;
                                       }};
        addInputAction(&action_desc);

        action_desc = {
            InputBindings::FLOAT_RIGHTSTICK,
            [](InputActionContext* ctx) {
                std::cout << (float)ctx->mFloat2.getX() << ":" << ctx->mFloat2.getY() << std::endl;
                return true;
            },
            NULL,
        };
        addInputAction(&action_desc);

        action_desc = {
            InputBindings::FLOAT_LEFTSTICK,
            [](InputActionContext* ctx) {
                std::cout << (float)ctx->mFloat2.getX() << ":" << ctx->mFloat2.getY() << std::endl;
                return true;
            },
            NULL,
        };
        addInputAction(&action_desc);

        tf_add_input_action(
            InputBindings::BUTTON_KEYY,
            [](InputActionContext* ctx) {
                std::cout << "Key : Y" << std::endl;
                return true;
            },
            nullptr);

        tf_add_input_action(
            InputBindings::BUTTON_DPAD_DOWN,
            [](InputActionContext* ctx) {
                if (ctx->mPhase == InputActionPhase::INPUT_ACTION_PHASE_PERFORMED) {
                    std::cout << "DOWN" << std::endl;
                }
                return true;
            },
            nullptr);

        tf_add_input_action(
            InputBindings::BUTTON_DPAD_LEFT,
            [](InputActionContext* ctx) {
                std::cout << "LEFT" << std::endl;
                return true;
            },
            nullptr);

        tf_add_input_action(
            InputBindings::BUTTON_DPAD_RIGHT,
            [](InputActionContext* ctx) {
                std::cout << "RIGHT" << std::endl;
                return true;
            },
            nullptr);

        tf_add_input_action(
            InputBindings::BUTTON_DPAD_UP,
            [](InputActionContext* ctx) {
                std::cout << "UP" << std::endl;
                return true;
            },
            nullptr);

        return true;
    };

    void Exit() {
        exitInputSystem();
        // exitRenderer(m_renderer);
    };

    bool Load() { return true; };

    void Unload(){};

    void Update(float deltaTime) { updateInputSystem(mSettings.mWidth, mSettings.mHeight); };

    void Draw(){};

    const char* GetName() { return "TheForge-Integration"; };

  private:
    // Renderer* m_renderer;
};

DEFINE_APPLICATION_MAIN(MyApp)
