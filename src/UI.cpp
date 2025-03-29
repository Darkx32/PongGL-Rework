#include "UI.hpp"

SDL_AppResult UI::init(SDL_Window *window, SDL_GLContext glContext, int* ptrUpPoints, int* ptrDownPoints)
{
    startTime = SDL_GetTicks();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui::GetIO().IniFilename = nullptr;
    ImGui::GetIO().FontGlobalScale = 1.5f;

    ImGui_ImplSDL3_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 450");

    this->upPoints = ptrUpPoints;
    this->downPoints = ptrDownPoints;

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
        ImVec2 textSize = ImGui::CalcTextSize(this->startText);
        ImGui::SetNextWindowPos(ImVec2(WINDOW_SIZE[0] / 2.0f - textSize.x / 2.0f, WINDOW_SIZE[1] / 2.0f - textSize.y + 20.0f));
        ImGui::Begin("Start Window", nullptr, this->justTextFlags);
        ImGui::Text(this->startText);
        ImGui::End();
    }

    // FPS Window
    if (showFPS)
    {
        float fps = 1.0f / (dt * 10.f);

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::Begin("FPS", nullptr, this->justTextFlags);
        ImGui::Text("%i", static_cast<int>(round(fps) * 10.f));
        ImGui::End();
    }

    // Points text
    {
        ImVec2 upTextSize = ImGui::CalcTextSize(std::to_string(*this->upPoints).c_str());
        ImGui::SetNextWindowPos(ImVec2(WINDOW_SIZE[0] / 2.0f - upTextSize.x * 1.2f, 25.f));
        ImGui::Begin("Up Points", nullptr, this->justTextFlags);
        ImGui::Text("%i", *this->upPoints);
        ImGui::End();

        ImVec2 downTextSize = ImGui::CalcTextSize(std::to_string(*this->downPoints).c_str());
        ImGui::SetNextWindowPos(ImVec2(WINDOW_SIZE[0] / 2.0f - downTextSize.x * 1.2f, WINDOW_SIZE[1] - 35.f - downTextSize.y));
        ImGui::Begin("Down Points", nullptr, this->justTextFlags);
        ImGui::Text("%i", *this->downPoints);
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
