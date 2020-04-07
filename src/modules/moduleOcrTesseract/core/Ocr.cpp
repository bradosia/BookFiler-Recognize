/*
 * @name Filesystem Database Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief filesystem database and utilities
 */

// Local Project
#include "Ocr.hpp"

/*
 * bookfiler = BookFiler™
 */
namespace bookfiler {

OcrMonitorInternal::OcrMonitorInternal() {
  monitor = std::make_shared<ETEXT_DESC>();
}
OcrMonitorInternal::OcrMonitorInternal(std::shared_ptr<ETEXT_DESC> monitor_)
    : monitor(monitor_) {}
OcrMonitorInternal::~OcrMonitorInternal() {}
unsigned long OcrMonitorInternal::getAvailable() { return monitor->count; }
unsigned long OcrMonitorInternal::getTotal() { return monitor->progress; }

OcrInternal::OcrInternal() { api = std::make_shared<tesseract::TessBaseAPI>(); }
OcrInternal::~OcrInternal() {
  api->End();
  if (image != nullptr) {
    pixDestroy(&image);
  }
}

bool OcrInternal::openImageFile(std::string imagePath) {
  image = pixRead(imagePath.c_str());
  if (image == nullptr) {
    std::cout << "bookfiler::OcrInternal::openImageFile(" << imagePath
              << ") FAILED!\n";
    return false;
  }
  pixmap = std::make_shared<Pixmap>();
  pixmap->data = (unsigned char *)image->data;
  pixmap->dataUINT = image->data;
  pixmap->width = image->w;
  pixmap->height = image->h;
  pixmap->pixelBytes = image->d / 8;
  pixmap->widthBytes = pixmap->width * pixmap->pixelBytes;
  api->SetImage(image);
  return true;
}

bool OcrInternal::openImagePixmap(unsigned char *data, long width, long height,
                                  long pixelBytes) {
  return true;
}
bool OcrInternal::openImagePixmapPtr(std::shared_ptr<Pixmap>) { return true; }

std::shared_ptr<Pixmap> OcrInternal::getPixmap() {
  if (!pixmap) {
    pixmap = std::make_shared<Pixmap>();
  }
  return pixmap;
}

void OcrInternal::setMode(std::string) {
  std::string dataPath = "traineddata";
  std::string language = "eng";
  /*
   * OCR Engine modes:
   * 0    Legacy engine only.
   * 1    Neural nets LSTM engine only.
   * 2    Legacy + LSTM engines.
   * 3    Default, based on what is available.
   */
  // tesseract::OcrEngineMode oem = tesseract::OEM_TESSERACT_ONLY;
  tesseract::OcrEngineMode oem = tesseract::OEM_LSTM_ONLY;
  // tesseract::OcrEngineMode oem = tesseract::OEM_TESSERACT_LSTM_COMBINED;
  // tesseract::OcrEngineMode oem = tesseract::OEM_DEFAULT;
  /*
     * PSM_OSD_ONLY
     Orientation and script detection only.

     PSM_AUTO_OSD
     Automatic page segmentation with orientation and script detection. (OSD)

     PSM_AUTO_ONLY
     Automatic page segmentation, but no OSD, or OCR.

     PSM_AUTO
     Fully automatic page segmentation, but no OSD.

     PSM_SINGLE_COLUMN
     Assume a single column of text of variable sizes.

     PSM_SINGLE_BLOCK_VERT_TEXT
     Assume a single uniform block of vertically aligned text.

     PSM_SINGLE_BLOCK
     Assume a single uniform block of text. (Default.)
     */
  tesseract::PageSegMode psm = tesseract::PSM_AUTO_OSD;
  // tesseract::PageSegMode psm = tesseract::PSM_SINGLE_BLOCK;
  // Set the Page Segmentation mode
  if (api->Init(dataPath.c_str(), language.c_str(), oem)) {
    std::cout << "Could not initialize tesseract.\n";
  }
  api->SetPageSegMode(psm);
}

void OcrInternal::setType(std::string) {}
void OcrInternal::setLanguage(std::vector<std::string>) {
  std::string language = "eng+ell";
}
void OcrInternal::setDataPath(std::string) {}

void OcrInternal::recognize() {
  monitor = std::make_shared<OcrMonitorInternal>();
  std::thread t1(&OcrInternal::recognizeThread, this);
  t1.detach();
}

void OcrInternal::recognizeThread() {
  api->Recognize(monitor->monitor.get());
  /* returns a shared_ptr which shares ownership of *this
   * C++11 feature
   */
  recognizeCallback(shared_from_this());
}

void OcrInternal::onRecognizeDone(
    std::function<void(std::shared_ptr<Ocr>)> callback) {
  recognizeCallback = callback;
}
std::shared_ptr<OcrMonitor> OcrInternal::getRecognizeMonitor() {
  return monitor;
}
std::shared_ptr<OcrMonitor> OcrInternal::getHocrMonitor() { return monitor; }
std::string OcrInternal::getHocr() { return std::string(api->GetHOCRText(0)); }

void OcrInternal::setHttpInterface(std::shared_ptr<Http>) {}
void OcrInternal::installMode(std::string) {}
void OcrInternal::installType(std::string) {}
void OcrInternal::installLanguage(std::vector<std::string>) {}

} // namespace bookfiler
