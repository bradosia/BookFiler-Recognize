/*
 * @name hOCR Edit Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief QT5 Widget for editing hOCR files
 */

#ifndef HOCR_EDIT_MODULE_H
#define HOCR_EDIT_MODULE_H

// c++17
#include <functional>
#include <memory>
#include <unordered_map>

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 * License: MITs
 */
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QWidget>

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
  long pixelBytes;
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

/*
 * hocrEditModule
 */
namespace hocrEditModule {

class HocrEditWidget {
public:
  void setImage(std::shared_ptr<bookfiler::Pixmap> pixmap);
  std::function<void(std::shared_ptr<bookfiler::Pixmap>)> setImageSlot;
  std::function<void(std::shared_ptr<std::vector<std::shared_ptr<bookfiler::HocrWord>>>)>
      textUpdateSlot;
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
  virtual std::shared_ptr<QWidget> getWidget() = 0;
  void setModel(std::shared_ptr<QWidget>);
};

} // namespace hocrEditModule

#endif
// end HOCR_EDIT_MODULE_H
