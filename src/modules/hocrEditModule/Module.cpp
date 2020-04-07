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
}

ModuleExport::~ModuleExport() {}

void ModuleExport::init() { printf("File Tree Pane Module: init()\n"); }

std::shared_ptr<QWidget> ModuleExport::getWidget() {
  std::shared_ptr<QWidget> widget = std::make_shared<MainWidget>();
  return widget;
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
