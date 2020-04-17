/*
 * @name BookFiler™ Module for PDF
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief PDF Module
 */

#ifndef BOOKFILER_MODULE_PDF_H
#define BOOKFILER_MODULE_PDF_H

// c++17
#include <functional>
#include <memory>
#include <vector>

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 * License: MITs
 */
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>

/*
 * bookfiler = BookFiler™
 */
namespace bookfiler {

#ifndef BOOKFILER_PIXMAP_H
#define BOOKFILER_PIXMAP_H
class Pixmap {
public:
  unsigned char * data;
  /* @param width pixel width
   * @param height pixel height
   * @param pixelBytes bytes in a pixel. Usually 8, 24 or 32.
   */
  long width;
  long height;
  long pixelBytes;
};
#endif // end BOOKFILER_PIXMAP_H

class PdfMonitor {
public:
    unsigned long available, total;
};

class Pdf {
public:
  void openFile(std::string);
  int getPagesTotal();
  void render(int pageNum);
  std::shared_ptr<PdfMonitor> getRenderMonitor();
  std::shared_ptr<Pixmap> getPixmap(int pageNum);
};

class PdfInterface {
public:
  virtual void init() = 0;
  virtual void registerSettings(
      std::shared_ptr<rapidjson::Document> moduleRequest,
      std::shared_ptr<std::unordered_map<
          std::string,
          std::function<void(std::shared_ptr<rapidjson::Document>)>>>
          moduleCallbackMap) = 0;
  virtual void setSettings(std::shared_ptr<rapidjson::Value> data) = 0;
  virtual std::shared_ptr<Pdf> newPdf() = 0;
};

} // namespace bookfiler

#endif // end BOOKFILER_MODULE_PDF_H
