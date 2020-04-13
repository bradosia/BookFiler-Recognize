// dear imgui: Platform Binding for BookfilerWidget
// This needs to be used along with a Renderer (e.g. OpenGL3, Vulkan..)

#ifndef IMGUI_IMPL_BOOKFILER_WIDGET_H
#define IMGUI_IMPL_BOOKFILER_WIDGET_H

// C++
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

// Local Project
#include "BookfilerRenderWidget.hpp"

bool ImGui_ImplBookfilerWidget_InitForOpenGL(std::shared_ptr<bookfiler::WidgetData> widgetData);
void ImGui_ImplBookfilerWidget_Shutdown();
void ImGui_ImplBookfilerWidget_NewFrame(std::shared_ptr<bookfiler::WidgetData> widgetData);

#endif // end IMGUI_IMPL_BOOKFILER_WIDGET_H
