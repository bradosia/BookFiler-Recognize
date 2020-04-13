/*
 * @name hOCR Edit Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief QT5 Widget for editing hOCR files
 */

#ifndef HOCR_EDIT_MODULE_H
#define HOCR_EDIT_MODULE_H

// c++11
#include <functional>
#include <memory>
#include <unordered_map>

/* boost 1.72.0
 * License: Boost Software License (similar to BSD and MIT)
 */
#include <boost/signals2.hpp>

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 * License: MITs
 */
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>

#ifndef BOOKFILER_PIXMAP_H
#define BOOKFILER_PIXMAP_H
namespace bookfiler {
class Pixmap {
public:
  unsigned char *data;
  // created for debugging
  unsigned int *dataUINT;
  /* @param width pixel width
   * @param height pixel height
   * @param widthBytes The number of bytes in each scan line.
   * @param pixelBytes bytes in a pixel. Usually 8, 24 or 32.
   */
  long width;
  long height;
  long widthBytes;
  long bitsPerPixel;
  long informat;
  long samplesPerPixel;
};
} // namespace bookfiler
#endif // end BOOKFILER_PIXMAP_H

#ifndef BOOKFILER_HOCR_WORD_H
#define BOOKFILER_HOCR_WORD_H
namespace bookfiler {
class HocrWord {
public:
  /* BoundingBox
   * http://kba.cloud/hocr-spec/1.2/#bbox
   */
  unsigned int x0, y0, x1, y1, w, h;
  std::string value;
  std::string id;
  // http://kba.cloud/hocr-spec/1.2/#x_wconf
  float confidence;
};
} // namespace bookfiler
#endif // end BOOKFILER_HOCR_WORD_H

#ifndef BOOKFILER_WIDGET_DATA_H
#define BOOKFILER_WIDGET_DATA_H
namespace bookfiler {

class WidgetData {
public:
  int displaySizeX, displaySizeY, displayFramebufferScale, mousePosX, mousePosY,
      mouseWheelX, mouseWheelY;
  double deltaTime;
  std::string addInputCharacter;
  bool keyCtrl, keyShift, keyAlt, keySuper, windowFocused;
  std::unordered_map<int, bool> mouseDown;
  std::unordered_map<int, bool> keysDown;
  void (*setClipboardTextFn)(void *, const char *);
  const char *(*getClipboardTextFn)(void *);
  void *winId;
};

class WidgetMouseEvent {
public:
  int x, y;
};

class WidgetKeyEvent {
public:
  int x, y;
};

} // namespace bookfiler
#endif // end BOOKFILER_WIDGET_DATA_H

/*
 * hocrEditModule
 */
namespace hocrEditModule {

class HocrEditWidget {
public:
  virtual bool initGraphics(std::shared_ptr<bookfiler::WidgetData>) = 0;
  virtual bool render(std::shared_ptr<bookfiler::WidgetData>) = 0;

  /* TODO: direct methods for IO
   */

  virtual void setImage(std::shared_ptr<bookfiler::Pixmap> pixmap) = 0;
  std::function<void(std::shared_ptr<bookfiler::Pixmap>)> setImageSlot;
  std::function<void(
      std::shared_ptr<std::vector<std::shared_ptr<bookfiler::HocrWord>>>)>
      textUpdateSlot;
  boost::signals2::signal<bool()> updateSignal;
};

class ModuleInterface {
public:
  /* need to make virtual method() = 0
   * because of error:
   * undefined reference to `vtable for hocrEditModule::ModuleInterface'
   */
  virtual void init() = 0;
  virtual void registerSettings(
      std::shared_ptr<rapidjson::Document>,
      std::shared_ptr<std::unordered_map<
          std::string,
          std::function<void(std::shared_ptr<rapidjson::Document>)>>>) = 0;
  virtual std::shared_ptr<HocrEditWidget> getWidget() = 0;
  virtual void render(std::shared_ptr<bookfiler::WidgetData>) = 0;
  virtual void initGraphics(std::shared_ptr<bookfiler::WidgetData>) = 0;
};

} // namespace hocrEditModule

#endif
// end HOCR_EDIT_MODULE_H
