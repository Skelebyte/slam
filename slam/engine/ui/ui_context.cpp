#include "ui_context.hpp"

using namespace slam;
using namespace slam::ui;
using namespace slam::gfx;

void UIContext::Init(CRef<str> defaultFont) {
  if (Get().initialized == true)
    return;
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  Get().io = &ImGui::GetIO();

  ImGui::StyleColorsDark();

  ImGui_ImplSDL3_InitForOpenGL(Engine::GetWindow()->GetSDLWindow(),
                               Renderer::GetGLContext());
  ImGui_ImplOpenGL3_Init("#version 330");

  Get().io->Fonts->AddFontFromFileTTF(defaultFont.c_str(), 18);

  Get().elements = List<Element *>();

  Get().initialized = true;
}

void UIContext::Shutdown() {
  if (Get().initialized == true)
    return;

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
  Get().initialized = false;
}

ImGuiIO *UIContext::GetIO() {
  if (Get().initialized == false)
    return nullptr;

  return Get().io;
}

void UIContext::Update() {
  if (Get().initialized == false)
    return;

  Get().io->DisplaySize = ImVec2(Engine::GetWindow()->GetViewportSize().x,
                                 Engine::GetWindow()->GetViewportSize().y);
  ImGui::SetNextWindowPos(ImVec2(Engine::GetWindow()->GetViewportPosition().x,
                                 Engine::GetWindow()->GetViewportPosition().y));
  ImGui::SetNextWindowSize(ImVec2(Engine::GetWindow()->GetViewportSize().x,
                                  Engine::GetWindow()->GetViewportSize().y));

  ImGui::Begin("viewport", nullptr,
               ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);

  for (u32 i = 0; i < Get().elements.Size(); i++) {
    auto current = ImGui::GetCursorPos();
    ImGui::SetCursorPos(
        ImVec2(Get().elements[i]->position.x, Get().elements[i]->position.y));
    Get().elements[i]->Update();
    ImGui::SetCursorPos(current);
  }

  ImGui::End();
}

void UIContext::AddElement(Element *element) { Get().elements.Add(element); }