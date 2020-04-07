/*
 * @name BookFiler Recognize
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Text recognition viewer, editor, and analyzer.

 * Icons and images owned by their respective owners
 */

// C++
#include <thread>

/* QT 5.13.2-1
 * License: LGPLv3
 */
#include <QSurfaceFormat>
#include <QTimer>

// Local Project
#include "../core/config.hpp"
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  /* UI Setup
   */
  ui = std::make_unique<Ui::main>();
  ui->setupUi(this);
  this->setObjectName("MainWindow");

  /* Load modules in another thread and let them appear as they load.
   * This will give the illusion to the user that the load time is fast.
   * A splash screen or loading bar will make the program start up seem slow.
   *
   * EDIT: can't do this because QT gives error:
   * QObject: Cannot create children for a parent that is in a different thread.
   */
  modulesLoadedNum = 0;
  modulesLoadedTotalNum = 6;
  //std::thread loadModulesThread(&MainWindow::loadModules, this);
  //loadModulesThread.join();
  loadModules();

  // TODO: Thread these
  if (hocrEditModule) {
    hocrEditWidget = hocrEditModule->getWidget();
    // needed to prevent crashing on program exit
    centralQWidgetPtrs.push_back(hocrEditWidget);
  }
  hocrEditModuleLoaded();
  recognizeModuleLoaded();

  // TODO: Check if widgets need to be added on paint cycles
  if (hocrEditModule) {
    QSizePolicy policy = hocrEditWidget->sizePolicy();
    policy.setHorizontalStretch(2);
    hocrEditWidget->setSizePolicy(policy);
    ui->horizontalSplitter->addWidget(hocrEditWidget.get());
  }
}

void MainWindow::loadModules() {
#if MAIN_WINDOW_DEBUG
  std::cout << "MainWindow::loadModules() begin.\n";
#endif
  settingsManagerPtr = std::make_shared<bradosia::SettingsManager>();
  /* Module Load
   */
  moduleManagerPtr = std::make_shared<bradosia::ModuleManager>();
  moduleManagerPtr->addModuleInterface<hocrEditModule::ModuleInterface>(
      "hocrEditModule");
  moduleManagerPtr->addModuleInterface<bookfiler::RecognizeInterface>(
      "bookfilerRecognizeModule");
  moduleManagerPtr->addModuleInterface<bookfiler::Http>("bookfilerHttpModule");
  moduleManagerPtr->addModuleInterface<bookfiler::OcrInterface>(
      "bookfilerOcrModule");
  moduleManagerPtr->addModuleInterface<bookfiler::PdfInterface>(
      "bookfilerPdfModule");
  moduleManagerPtr->addModuleInterface<bookfiler::OcrDatabaseInterface>(
      "textRecognizeDatabaseModule");
  moduleManagerPtr->loadModules("modules");
  hocrEditModule = moduleManagerPtr->getModule<hocrEditModule::ModuleInterface>(
      "hocrEditModule");
  recognizeModule = moduleManagerPtr->getModule<bookfiler::RecognizeInterface>(
      "bookfilerRecognizeModule");
  httpModule =
      moduleManagerPtr->getModule<bookfiler::Http>("bookfilerHttpModule");
  ocrModule = moduleManagerPtr->getModule<bookfiler::OcrInterface>(
      "bookfilerOcrModule");
  pdfModule = moduleManagerPtr->getModule<bookfiler::PdfInterface>(
      "bookfilerPdfModule");
  recognizeDatabaseModule =
      moduleManagerPtr->getModule<bookfiler::OcrDatabaseInterface>(
          "textRecognizeDatabaseModule");
}

void MainWindow::hocrEditModuleLoaded() {
  if (hocrEditModule) {
    printf("FileTreePane Module Found\n");
    /* register widgets
     */
    hocrEditModule->init();
    /* register setting deploy
     */
    std::shared_ptr<rapidjson::Document> moduleRequest =
        std::make_shared<rapidjson::Document>();
    std::shared_ptr<std::unordered_map<
        std::string, std::function<void(std::shared_ptr<rapidjson::Document>)>>>
        moduleCallbackMap = std::make_shared<std::unordered_map<
            std::string,
            std::function<void(std::shared_ptr<rapidjson::Document>)>>>();
    hocrEditModule->registerSettings(moduleRequest, moduleCallbackMap);
    settingsManagerPtr->merge(moduleRequest, moduleCallbackMap);
    // Did all modules load yet?
    modulesLoadedNum += 5;
    if (modulesLoadedNum == modulesLoadedTotalNum) {
      allModulesLoaded();
    }
  }
}

void MainWindow::recognizeModuleLoaded() {
  if (recognizeModule) {
    // Did all modules load yet?
    modulesLoadedNum++;
    if (modulesLoadedNum == modulesLoadedTotalNum) {
      allModulesLoaded();
    }
  }
}

void MainWindow::allModulesLoaded() {
  // Module Hookup
  recognizeModule->setOcrModule(ocrModule);
  recognizeModule->setPdfModule(pdfModule);
  recognizeModel = recognizeModule->newModel();
  /* SIGNALS AND SLOTS HOOKUP
   */
  ui->filesSelectedSignal.connect(
      std::bind(&bookfiler::RecognizeModel::addPaths, recognizeModel.get(),
                std::placeholders::_1));
  ui->listItemActivatedSignal.connect(
      std::bind(&bookfiler::RecognizeModel::requestRecognize,
                recognizeModel.get(), std::placeholders::_1));
  /* Get the settings
   */
  settingsManagerPtr->deployFile(SETTINGS_FILE);
  /* SIGNALS AND SLOTS HOOKUP
   */
  // Ui::main must inherit QObject for slot to work.
  connect(ui->actionAbout, &QAction::triggered, ui.get(), &Ui::main::about);
  connect(ui->actionOpen, &QAction::triggered, ui.get(),
          &Ui::main::selectFiles);
  connect(ui->listWidget, &QListWidget::itemDoubleClicked, ui.get(),
          &Ui::main::listItemActivated);
  recognizeModel->imageUpdateSignal.connect(
      std::dynamic_pointer_cast<hocrEditModule::HocrEditWidget>(hocrEditWidget)
          ->setImageSlot);
  recognizeModel->textUpdateSignal.connect(
      std::dynamic_pointer_cast<hocrEditModule::HocrEditWidget>(hocrEditWidget)
          ->textUpdateSlot);
}
