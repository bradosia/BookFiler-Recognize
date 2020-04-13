/* Dear ImGui 1.75
 * License: MIT
 */
#include <imgui/imgui.h>

// Local Project
#include "imgui_impl_bookfilerWidget.hpp"

// Data
enum BookfilerWidgetClientApi {
  BookfilerWidgetClientApi_Unknown,
  BookfilerWidgetClientApi_OpenGL,
  BookfilerWidgetClientApi_Vulkan
};

static bool g_MouseJustPressed[5] = {false, false, false, false, false};

bool ImGui_ImplBookfilerWidget_InitForOpenGL(
    std::shared_ptr<bookfiler::WidgetData> widgetData) {
  // Setup back-end capabilities flags
  ImGuiIO &io = ImGui::GetIO();
  io.BackendFlags |=
      ImGuiBackendFlags_HasMouseCursors; // We can honor GetMouseCursor() values
                                         // (optional)
  io.BackendFlags |=
      ImGuiBackendFlags_HasSetMousePos; // We can honor io.WantSetMousePos
                                        // requests (optional, rarely used)
  io.BackendPlatformName = "imgui_impl_BookfilerWidget";

  // Keyboard mapping. ImGui will use those indices to peek into the
  // io.KeysDown[] array.
  io.KeyMap[ImGuiKey_Tab] = BOOKFILER_IO_VK_TAB;
  io.KeyMap[ImGuiKey_LeftArrow] = BOOKFILER_IO_VK_LEFT;
  io.KeyMap[ImGuiKey_RightArrow] = BOOKFILER_IO_VK_RIGHT;
  io.KeyMap[ImGuiKey_UpArrow] = BOOKFILER_IO_VK_UP;
  io.KeyMap[ImGuiKey_DownArrow] = BOOKFILER_IO_VK_DOWN;
  io.KeyMap[ImGuiKey_PageUp] = BOOKFILER_IO_VK_PRIOR;
  io.KeyMap[ImGuiKey_PageDown] = BOOKFILER_IO_VK_NEXT;
  io.KeyMap[ImGuiKey_Home] = BOOKFILER_IO_VK_HOME;
  io.KeyMap[ImGuiKey_End] = BOOKFILER_IO_VK_END;
  io.KeyMap[ImGuiKey_Insert] = BOOKFILER_IO_VK_INSERT;
  io.KeyMap[ImGuiKey_Delete] = BOOKFILER_IO_VK_DELETE;
  io.KeyMap[ImGuiKey_Backspace] = BOOKFILER_IO_VK_BACK;
  io.KeyMap[ImGuiKey_Space] = BOOKFILER_IO_VK_SPACE;
  io.KeyMap[ImGuiKey_Enter] = BOOKFILER_IO_VK_RETURN;
  io.KeyMap[ImGuiKey_Escape] = BOOKFILER_IO_VK_ESCAPE;
  // io.KeyMap[ImGuiKey_KeyPadEnter] = BOOKFILER_IO_VK_RETURN;
  io.KeyMap[ImGuiKey_A] = 'A';
  io.KeyMap[ImGuiKey_C] = 'C';
  io.KeyMap[ImGuiKey_V] = 'V';
  io.KeyMap[ImGuiKey_X] = 'X';
  io.KeyMap[ImGuiKey_Y] = 'Y';
  io.KeyMap[ImGuiKey_Z] = 'Z';

  io.SetClipboardTextFn = widgetData->setClipboardTextFn;
  io.GetClipboardTextFn = widgetData->getClipboardTextFn;
#if defined(_WIN32)
  io.ImeWindowHandle = (void *)widgetData->winId;
#endif
  return true;
}

void ImGui_ImplBookfilerWidget_Shutdown() {}

static void ImGui_ImplBookfilerWidget_UpdateMousePosAndButtons(
    std::shared_ptr<bookfiler::WidgetData> widgetData) {
  // Update buttons
  ImGuiIO &io = ImGui::GetIO();
  for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) {
    // If a mouse press event came, always pass it as "mouse held this frame",
    // so we don't miss click-release events that are shorter than 1 frame.
    io.MouseDown[i] = g_MouseJustPressed[i] || widgetData->mouseDown[i];
    g_MouseJustPressed[i] = false;
  }

  // Update mouse position
  const ImVec2 mouse_pos_backup = io.MousePos;
  io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
#ifdef __EMSCRIPTEN__
  const bool focused = true; // Emscripten
#else
  const bool focused = widgetData->windowFocused;
#endif
  if (focused) {
    if (io.WantSetMousePos) {
      widgetData->mousePosX = mouse_pos_backup.x;
      widgetData->mousePosY = mouse_pos_backup.y;
    } else {
      io.MousePos = ImVec2(widgetData->mousePosX, widgetData->mousePosY);
    }
  }
}

static void ImGui_ImplBookfilerWidget_UpdateMouseCursor(
    std::shared_ptr<bookfiler::WidgetData> widgetData) {
  ImGuiIO &io = ImGui::GetIO();
}

static void ImGui_ImplBookfilerWidget_UpdateGamepads(
    std::shared_ptr<bookfiler::WidgetData> widgetData) {
  ImGuiIO &io = ImGui::GetIO();
}

void ImGui_ImplBookfilerWidget_NewFrame(
    std::shared_ptr<bookfiler::WidgetData> widgetData) {
  ImGuiIO &io = ImGui::GetIO();
  IM_ASSERT(io.Fonts->IsBuilt() &&
            "Font atlas not built! It is generally built by the renderer "
            "back-end. Missing call to renderer _NewFrame() function? e.g. "
            "ImGui_ImplOpenGL3_NewFrame().");

  // Setup display size (every frame to accommodate for window resizing)
  io.DisplaySize = ImVec2(widgetData->displaySizeX, widgetData->displaySizeY);
  io.DisplayFramebufferScale = ImVec2(widgetData->displayFramebufferScale,
                                      widgetData->displayFramebufferScale);

  // Setup time step
  io.DeltaTime = widgetData->deltaTime;

  ImGui_ImplBookfilerWidget_UpdateMousePosAndButtons(widgetData);
  ImGui_ImplBookfilerWidget_UpdateMouseCursor(widgetData);

  // Update game controllers (if enabled and available)
  ImGui_ImplBookfilerWidget_UpdateGamepads(widgetData);

  io.MouseWheelH = widgetData->mouseWheelX;
  io.MouseWheel = widgetData->mouseWheelY;
}
