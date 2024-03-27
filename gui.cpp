#pragma once

void GuiSetup(SDL_Window *Window, SDL_Renderer *Renderer)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(Window, Renderer);
    ImGui_ImplSDLRenderer2_Init(Renderer);

}

void GuiNewFrame()
{
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void GuiDestroy()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void ShowMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {

        { // FILE DROPDOWN
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Load ROM")) {}
                ImGui::EndMenu();
            }
        }

        { // HELP DROPDOWN
            if (ImGui::BeginMenu("Help"))
            {
                ImGui::EndMenu();
            }
        }

        ImGui::EndMainMenuBar();
    }
}
