#include "UIs/soundController.hpp"

void SoundControllerUI::init(Sound *o_sound)
{
    this->sound = o_sound;
}

void SoundControllerUI::render()
{
    if (!showController) return;

    bool modified = false;

    ImGui::SetNextWindowSize(ImVec2(170, 55));
    ImGui::Begin("Sound Controller", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
    ImGui::SetWindowFontScale(0.6f);
    modified |= ImGui::SliderInt("Music", &this->musicVolume, 0, 100, "%i");
    modified |= ImGui::SliderInt("SFX", &this->sfxVolume, 0, 100, "%i");
    ImGui::End();

    if (modified)
        this->sound->updateVolumes(this->musicVolume, this->sfxVolume);
}
