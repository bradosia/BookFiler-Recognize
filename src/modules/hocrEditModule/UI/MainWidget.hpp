/*
 * @name hOCR Edit Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief QT5 Widget for editing hOCR files
 */

#ifndef HOCR_EDIT_MODULE_MAIN_WIDGET_H
#define HOCR_EDIT_MODULE_MAIN_WIDGET_H

// Config
#include "../core/config.hpp"

// C++
#include <iostream>
#include <memory>

#include <QX11Info>

/* Dear ImGui 1.75
 * License: MIT
 */
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>

/* Ogre3D 1.12.2
 * License: MIT
 */
#include <OgreFrameListener.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreTextureManager.h>
// basically does #include <GL/glew.h>
#include <RenderSystems/GL/OgreGLRenderSystem.h>
#include <RenderSystems/GL/OgreGLTexture.h>

// Local Project
#include "imgui_impl_bookfilerWidget.hpp"
#include "../Interface.hpp"

/*
 * hocrEditModule
 */
namespace hocrEditModule {

class MainWidget : public HocrEditWidget, public Ogre::FrameListener {

public:
  MainWidget();
  ~MainWidget();
  // Interface
  bool initGraphics(std::shared_ptr<bookfiler::WidgetData>);
  bool render(std::shared_ptr<bookfiler::WidgetData>);

  // Custom
  void setImage(std::shared_ptr<bookfiler::Pixmap> pixmap);
  void setOverlayText(
      std::shared_ptr<std::vector<std::shared_ptr<bookfiler::HocrWord>>>
          wordList);
  void setStyle1();
  void addDrawArrow();

  std::shared_ptr<bookfiler::Pixmap> image_pixmap;
  std::shared_ptr<std::vector<std::shared_ptr<bookfiler::HocrWord>>>
      overlayWordList;
  ImFont *fontArialTitle;
  ImFont *fontArialText;
  Ogre::Root *root;

protected:
  void initializeGL();

private:
  // Our state
  ImVec4 clear_color;
  // Decide GL+GLSL versions
#if __APPLE__
  // GL 3.2 + GLSL 150
  const char *glsl_version = "#version 150";
#else
  // GL 3.0 + GLSL 130
  const char *glsl_version = "#version 130";
  unsigned int textureName = 1;
  unsigned int glID = 0;
#endif
};

} // namespace hocrEditModule

#endif
// end HOCR_EDIT_MODULE_MAIN_WIDGET_H
