/*
 * @name BookFiler Recognize
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Text recognition viewer, editor, and analyzer.

 * Icons and images owned by their respective owners
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

// Config
#include "../core/config.hpp"

// C++
#include <memory>

// bradosia libraries 1.0
#include <ModuleManager/ModuleManager.hpp>
#include <SettingsManager/SettingsManager.hpp>

// Modules
#include <hocrEditModule/Interface.hpp>
#include <RecognizeModule/Interface.hpp>
#include <moduleHttpBeast/Interface.hpp>
#include <moduleOcrTesseract/Interface.hpp>
#include <modulePdfMupdf/Interface.hpp>
#include <TextRecognizeDatabase/Interface.hpp>

// Local Project
#include "ui_main.hpp"
#include "renderWidget.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow(){ 
      for (auto widgetPtr : centralQWidgetPtrs) {
        widgetPtr->setParent(nullptr);
      }
  };
  void loadModules();
  void hocrEditModuleLoaded();
  void recognizeModuleLoaded();
  void allModulesLoaded();

private:
  unsigned int modulesLoadedNum;
  unsigned int modulesLoadedTotalNum;
  std::unique_ptr<Ui::main> ui;
  std::shared_ptr<hocrEditModule::ModuleInterface> hocrEditModule;
  std::shared_ptr<bookfiler::RecognizeInterface> recognizeModule;
  std::shared_ptr<bookfiler::Http> httpModule;
  std::shared_ptr<bookfiler::OcrInterface> ocrModule;
  std::shared_ptr<bookfiler::PdfInterface> pdfModule;
  std::shared_ptr<bookfiler::OcrDatabaseInterface> recognizeDatabaseModule;
  std::vector<std::shared_ptr<QWidget>> centralQWidgetPtrs;
  std::shared_ptr<bradosia::ModuleManager> moduleManagerPtr;
  std::shared_ptr<bradosia::SettingsManager> settingsManagerPtr;
  std::shared_ptr<hocrEditModule::HocrEditWidget> hocrEditWidget;
  std::shared_ptr<RenderWidget> renderWidget;
  std::shared_ptr<bookfiler::RecognizeModel> recognizeModel;
};
#endif // MAIN_WINDOW_H
