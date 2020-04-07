/*
 * @name BookFiler™ Module for OCR
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief OCR Module
 */

#ifndef BOOKFILER_MODULE_OCR_DATABASE_H
#define BOOKFILER_MODULE_OCR_DATABASE_H

// c++17
#include <functional>
#include <memory>
#include <string_view>
#include <vector>

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 * License: MITs
 */
#include <rapidjson/document.h>

/*
 * bookfiler = BookFiler™
 */
namespace bookfiler {

class OcrDatabaseInterface {
public:
  void init() { printf("OCR Database Module: init()\n"); }
  void registerSettings(
      std::shared_ptr<rapidjson::Document> moduleRequest,
      std::shared_ptr<std::unordered_map<
          std::string,
          std::function<void(std::shared_ptr<rapidjson::Document>)>>>
          moduleCallbackMap);
  void setSettings(std::shared_ptr<rapidjson::Value> data);
};

} // namespace bookfiler

#endif // end BOOKFILER_MODULE_OCR_DATABASE_H
