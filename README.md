# Bookfiler™ Recognize
A QT5 widget for word recognition in images, PDF, and word documents.

# Dependencies
* Boost
* Tesseract

# Build

## linux

download and install OGRE3D 1.12 manually.

```shell
sudo apt-get install libxinerama-dev
sudo apt-get install libxrandr-dev
sudo apt-get install libxcursor-dev
sudo apt-get install libxi-dev
sudo apt-get install libx11-dev
sudo apt-get install libxaw7-dev
sudo apt-get install libglew-dev
sudo apt-get install libtesseract-dev libleptonica-dev liblept5
```

modules/libhocrEditModuleLibShared.so.1.0.0 exception fix:
```shell
sudo cp /usr/lib/x86_64-linux-gnu/libzzip-0.so.13.0.62 /usr/lib/x86_64-linux-gnu/libzzip.so.13
```
