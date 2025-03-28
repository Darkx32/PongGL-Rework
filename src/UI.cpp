#include "UI.hpp"

SDL_AppResult UI::init(SDL_Window *window, SDL_GLContext glContext)
{
    startTime = SDL_GetTicks();

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

SDL_AppResult UI::render(float& dt)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    // Start Window
    if (!hasStarted)
    {
        ImVec2 windowSize = ImGui::CalcTextSize(this->startText);
        ImGui::SetNextWindowPos(ImVec2(WINDOW_SIZE[0] / 2.0f - windowSize.x / 2.0f, WINDOW_SIZE[1] / 2.0f - windowSize.y + 20.0f));
        ImGui::Begin("Start Window", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::Text(this->startText);
        ImGui::End();
    }

    // FPS Window
    if (showFPS)
    {
        float fps = 1.0f / dt;

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::Text("%.1f", ceilf(fps));
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
