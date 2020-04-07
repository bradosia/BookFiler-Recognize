/*
 * @name hOCR Edit Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief QT5 Widget for editing hOCR files
 */

/*
 * piwebapi-ucdavis 1.0
 */
#include "MainWidget.hpp"

/*
 * hocrEditModule
 */
namespace hocrEditModule {

MainWidget::MainWidget() {
  this->setObjectName("Hocr Edit Widget");
  setImageSlot = std::bind(&hocrEditModule::MainWidget::setImage, this,
                           std::placeholders::_1);
  textUpdateSlot = std::bind(&hocrEditModule::MainWidget::setOverlayText, this,
                             std::placeholders::_1);

  // Use OpenGL 3 Core Profile
  QSurfaceFormat glFormat;
  glFormat.setVersion(3, 3);
  glFormat.setProfile(QSurfaceFormat::NoProfile);
  glFormat.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
  setFormat(glFormat);
};
MainWidget::~MainWidget(){};

void MainWidget::initializeGL() {
  initializeOpenGLFunctions();
  QtImGui::initialize(this);
}

void MainWidget::paintEvent(QPaintEvent *event) {
  context()->makeCurrent(context()->surface());
  renderLoop();
  context()->swapBuffers(context()->surface());
}

void MainWidget::setImage(std::shared_ptr<bookfiler::Pixmap> pixmap) {
  if (pixmap == nullptr) {
    return;
  }
#if HOCR_EDIT_MODULE_SET_IMAGE_DEBUG
  std::cout << "hocrEditModule::MainWidget::setImage: \nwidth=" << pixmap->width
            << " height=" << pixmap->height
            << " pixelBytes=" << pixmap->pixelBytes << "\n";
#endif
  image_pixmap = pixmap;

  // Create a OpenGL texture identifier
  glGenTextures(1, &image_texture);
  glBindTexture(GL_TEXTURE_2D, image_texture);

  // Setup filtering parameters for display
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Upload pixels into texture
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  if (pixmap->pixelBytes == 1) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pixmap->width/6, pixmap->height/6, 0,
                 GL_RGB, GL_UNSIGNED_INT, pixmap->dataUINT);
  } else if (pixmap->pixelBytes == 4) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pixmap->width, pixmap->height, 0,
                 GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, pixmap->dataUINT);
  } else {
#if HOCR_EDIT_MODULE_SET_IMAGE_DEBUG
    std::cout
        << "hocrEditModule::MainWidget::setImage NO GL MATCH: \npixelBytes="
        << pixmap->pixelBytes << "\n";
#endif
  }
  /* Request Draw Update
   */
  update();
}

void MainWidget::setOverlayText(
    std::shared_ptr<std::vector<std::shared_ptr<bookfiler::HocrWord>>>
        wordList) {
  overlayWordList = wordList;
  update();
}

void MainWidget::renderLoop() {
  QtImGui::newFrame();

  ImGuiStyle &style = ImGui::GetStyle();

  // frame rounding
  style.WindowRounding = 0.0f;
  style.ChildRounding = 0.0f;
  style.FrameRounding = 0.0f;
  style.GrabRounding = 0.0f;
  style.PopupRounding = 0.0f;
  style.ScrollbarRounding = 0.0f;

  // frame padding
  style.WindowPadding = ImVec2(0, 0);
  style.FramePadding = ImVec2(0, 0);
  style.DisplayWindowPadding = ImVec2(0, 0);
  style.DisplaySafeAreaPadding = ImVec2(0, 0);

  // 1. Show the big demo window (Most of the sample code is in
  // ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear
  // ImGui!).
  // if (show_demo_window)
  //  ImGui::ShowDemoWindow(&show_demo_window);

  // 2. Show a simple window that we create ourselves. We use a Begin/End pair
  // to created a named window.
  {
    ImGui::SetNextWindowPos(ImVec2(0, 0), 0);
    ImGui::SetNextWindowSize(
        ImVec2(this->size().width(), this->size().height()), 0);
    ImGui::Begin("Hello, world!", new bool(false),
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav |
                     ImGuiWindowFlags_NoBackground);

    /* Draw the image
     */
    if (image_pixmap) {
      float scaleFactor = 1;
      if (image_pixmap->width > this->width()) {
        scaleFactor = (float)this->width() / image_pixmap->width;
      }
      ImGui::Image((void *)(intptr_t)image_texture,
                   ImVec2(image_pixmap->width * scaleFactor,
                          image_pixmap->height * scaleFactor));
    }

    /* Draw the overlay text
     */
    /*if (overlayWordList) {
      for (auto wordPtr : *overlayWordList) {
        // ImGui::SetNextWindowPos(ImVec2(wordPtr->x0, wordPtr->y0), 0);
        ImGui::SetNextWindowPos(ImVec2(50, 50), 0);
        ImGui::SetNextWindowSize(ImVec2(wordPtr->w, wordPtr->h), 0);
        ImGui::Begin("Hello, world!", new bool(false),
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoTitleBar |
                         ImGuiWindowFlags_MenuBar |
                         ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav |
                         ImGuiWindowFlags_NoBackground);
        ImGui::Text(wordPtr->value.c_str());
        ImGui::End();
      }
    }*/

    ImGui::Text("hOCR Edit Module\nAdd an image and double click the path in "
                "the list on the left to begin.");

    ImGui::End();
  }

  /* Draw the overlay text
   */
  {
    if (overlayWordList) {
      for (auto wordPtr : *overlayWordList) {
        ImGui::SetNextWindowPos(ImVec2(wordPtr->x0 / 10, wordPtr->y0 / 10), 0);
        // ImGui::SetNextWindowPos(ImVec2(0, 0), 0);
        ImGui::SetNextWindowSize(ImVec2(wordPtr->w, wordPtr->h), 0);
        ImGui::Begin("Hello, world!", new bool(false),
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoTitleBar |
                         ImGuiWindowFlags_MenuBar |
                         ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav |
                         ImGuiWindowFlags_NoBackground);
        ImGui::Text(wordPtr->value.c_str());
        ImGui::End();
      }
    }
  }

  // 3. Show another simple window.
  /*if (show_another_window) {
    ImGui::Begin(
        "Another Window",
        &show_another_window); // Pass a pointer to our bool variable (the
                               // window will have a closing button that will
                               // clear the bool when clicked)
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me"))
      show_another_window = false;
    ImGui::End();
  }*/

  // Do render before ImGui UI is rendered
  glViewport(0, 0, width(), height());
  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);

  ImGui::Render();

  // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  // QGLWidget::swapBuffers automatically done after repaint
}

void MainWidget::renderLoopSwap() {
  context()->makeCurrent(context()->surface());
  renderLoop();
  context()->swapBuffers(context()->surface());
}

void MainWidget::mouseMoveEvent(QMouseEvent *event) { update(); }

void MainWidget::mousePressEvent(QMouseEvent *event) { update(); }

void MainWidget::mouseReleaseEvent(QMouseEvent *event) { update(); }

void MainWidget::wheelEvent(QWheelEvent *event) { update(); }

} // namespace hocrEditModule
