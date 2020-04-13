/*
 * @name hOCR Edit Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief QT5 Widget for editing hOCR files
 */

#ifndef HOCR_EDIT_MODULE_EXPORT_H
#define HOCR_EDIT_MODULE_EXPORT_H

// Config
#include "core/config.hpp"

// c++17
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>

/* boost 1.72.0
 * License: Boost Software License (similar to BSD and MIT)
 */
#include <boost/config.hpp> // for BOOST_SYMBOL_EXPORT

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 * License: MITs
 */
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/reader.h> // rapidjson::ParseResult
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

// Local Project
#include "Interface.hpp"
#include "UI/MainWidget.hpp"

/*
 * hocrEditModule
 */
namespace hocrEditModule {

/*
 * Plugin uses the MVC design pattern.
 * This is the controller, the view is a QT widget, and the model is the API
 * storage
 */
class ModuleExport : public ModuleInterface {
private:
  std::shared_ptr<MainWidget> editWidget;

public:
  ModuleExport();
  ~ModuleExport();

  void init();
  std::shared_ptr<HocrEditWidget> getWidget();
  void render(std::shared_ptr<bookfiler::WidgetData>);
  void initGraphics(std::shared_ptr<bookfiler::WidgetData>);
  void registerSettings(
      std::shared_ptr<rapidjson::Document> moduleRequest,
      std::shared_ptr<std::unordered_map<
          std::string,
          std::function<void(std::shared_ptr<rapidjson::Document>)>>>
          moduleCallbackMap);
};

// Exporting `my_namespace::module` variable with alias name `module`
// (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::module, module)`)
extern "C" BOOST_SYMBOL_EXPORT ModuleExport hocrEditModule;
ModuleExport hocrEditModule;

} // namespace hocrEditModule

#endif
// end HOCR_EDIT_MODULE_EXPORT_H
