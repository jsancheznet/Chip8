#pragma once

void UISetup(SDL_Window *Window, SDL_Renderer *Renderer)
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

void UIBeginFrame()
{
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void UIEndFrame()
{
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void UIDestroy()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void DrawRegistersWindow()
{
    ImGui::Begin("Demo window");
    ImGui::Button("Hello!");
    ImGui::End();
}

void DrawDemoWindow()
{
    bool yes = true; yes;
    ImGui::ShowDemoWindow(&yes);
}

void DrawMenuBar()
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
