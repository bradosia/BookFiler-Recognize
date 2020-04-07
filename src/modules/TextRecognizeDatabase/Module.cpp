/*
 * @name Filesystem Database Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief filesystem database and utilities
 */

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 * License: MITs
 */
#include <rapidjson/prettywriter.h>

// Local Project
#include "Module.hpp"

/*
 * bookfiler = BookFiler™
 */
namespace bookfiler {

/* Export is handled in the Module.cpp file because of redefinition errors.
 * Module.hpp is included more than once.
 *
 * Exporting `my_namespace::module` variable with alias name `module`
 * (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::module, module)`)
 */
extern "C" BOOST_SYMBOL_EXPORT ModuleExport textRecognizeDatabaseModule;
ModuleExport textRecognizeDatabaseModule;

ModuleExport::ModuleExport() {
}

ModuleExport::~ModuleExport() {
}

void ModuleExport::registerSettings(
    std::shared_ptr<rapidjson::Document> moduleRequest,
    std::shared_ptr<std::unordered_map<
        std::string, std::function<void(std::shared_ptr<rapidjson::Document>)>>>
        moduleCallbackMap) {
  moduleRequest->SetObject();
  moduleRequest->AddMember("FilesystemDatabase", "FilesystemDatabaseCB",
                           moduleRequest->GetAllocator());
  moduleCallbackMap->insert(
      {"FilesystemDatabaseCB",
       std::bind(&ModuleExport::setSettings, this, std::placeholders::_1)});
}

void ModuleExport::setSettings(std::shared_ptr<rapidjson::Value> data) {
#if MODULE_EXPORT_SET_SETTINGS_DEBUG
  rapidjson::StringBuffer buffer;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
  data->Accept(writer);
  std::cout << "bookfiler::ModuleExport::setSettings:\n"
            << buffer.GetString() << std::endl;
#endif
}

} // namespace FSDB
