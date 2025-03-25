#include "UI.hpp"

SDL_AppResult UI::init(SDL_Window *window, SDL_GLContext glContext)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui::GetIO().IniFilename = nullptr;

    ImGui_ImplSDL3_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 450");

    return SDL_APP_CONTINUE;
}

SDL_AppResult UI::processEvents(SDL_Event *events)
{
    ImGui_ImplSDL3_ProcessEvent(events);

    return SDL_APP_CONTINUE;
}

SDL_AppResult UI::render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    {
        ImGui::Begin("Teste");
        ImGui::Text("Hello World");
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return SDL_APP_CONTINUE;
}

void UI::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}
