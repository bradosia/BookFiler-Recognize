/*
 * @name hOCR Edit Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief QT5 Widget for editing hOCR files
 */

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 * License: MITs
 */
#include <rapidjson/prettywriter.h>

// Local Project
#include "Module.hpp"

/*
 * hocrEditModule
 */
namespace hocrEditModule {

ModuleExport::ModuleExport() {
  std::cout << "hocrEditModule::ModuleExport::ModuleExport()" << std::endl;
}

ModuleExport::~ModuleExport() {}

void ModuleExport::init() {
  std::cout << "hocrEditModule::ModuleExport::init()" << std::endl;
}

std::shared_ptr<HocrEditWidget> ModuleExport::getWidget() {
  std::cout << "hocrEditModule::ModuleExport::getWidget BEGIN" << std::endl;
  /* Linux - Ubuntu error here:
   * Segmentation fault (core dumped)
   */
  editWidget = std::make_shared<MainWidget>();
  std::cout << "hocrEditModule::ModuleExport::getWidget END" << std::endl;
  return editWidget;
}

void ModuleExport::render(std::shared_ptr<bookfiler::WidgetData> widgetData) {
  editWidget->render(widgetData);
}

void ModuleExport::initGraphics(
    std::shared_ptr<bookfiler::WidgetData> widgetData) {
  editWidget->initGraphics(widgetData);
}

void ModuleExport::registerSettings(
    std::shared_ptr<rapidjson::Document> moduleRequest,
    std::shared_ptr<std::unordered_map<
        std::string, std::function<void(std::shared_ptr<rapidjson::Document>)>>>
        moduleCallbackMap) {
  moduleRequest->SetObject();
  moduleRequest->AddMember("treeData", "treeSet",
                           moduleRequest->GetAllocator());
  moduleRequest->AddMember("defaultDirectory", "defaultDirectoryCB",
                           moduleRequest->GetAllocator());
  /* Discovery:
   * Callbacks don't need to be declared in the module interface
   */
#if SETTINGS_DEBUG
  rapidjson::StringBuffer buffer;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
  moduleRequest.Accept(writer);
  std::cout << "Plugin JSON settings:\n" << buffer.GetString() << "\n";
  std::cout << "Plugin Callback Map:\n";
  for (auto pairs : pluginCallbackMap) {
    std::cout << "first:" << pairs.first << std::endl;
  }
#endif
}

} // namespace hocrEditModule
