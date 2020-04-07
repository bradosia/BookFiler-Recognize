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

/* Dear ImGui 1.75
 * License: MIT
 */
#include <imgui/imgui.h>

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QApplication>
#include <QOffscreenSurface>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLWidget>
#include <QSurfaceFormat>
#include <QTimer>

/* QtImGui for imgui 1.62
 * License: MIT
 */
#include <qtimgui/QtImGui.h>

// Local Project
#include "../Interface.hpp"

/*
 * hocrEditModule
 */
namespace hocrEditModule {

class MainWidget : public QOpenGLWidget,
                   private QOpenGLExtraFunctions,
                   public HocrEditWidget {
  Q_OBJECT

public:
  MainWidget();
  ~MainWidget();
  void setImage(std::shared_ptr<bookfiler::Pixmap> pixmap);
  void setOverlayText(
      std::shared_ptr<std::vector<std::shared_ptr<bookfiler::HocrWord>>>
          wordList);
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void renderLoop();
  void renderLoopSwap();

  GLuint image_texture;
  std::shared_ptr<bookfiler::Pixmap> image_pixmap;
  std::shared_ptr<std::vector<std::shared_ptr<bookfiler::HocrWord>>>
      overlayWordList;
  QOpenGLFramebufferObject *m_fbo;
  QOffscreenSurface *m_backsurface;

protected:
  void initializeGL() override;
  void paintEvent(QPaintEvent *event);

private:
  // Our state
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};

} // namespace hocrEditModule

#endif
// end HOCR_EDIT_MODULE_MAIN_WIDGET_H
