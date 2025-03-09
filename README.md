# CMC-Market-Report

Creates a market portfolio from CMC Confirmations 

## Required Packages
cmake
build-essential
wxWidgets (version 3.2 or higher)
CURL
OpenSSL 
nlohmann/json
libxlsxwriter

### Linux Install
sudo apt update
sudo apt install -y build-essential cmake
sudo apt install -y libwxgtk3.2-dev
sudo apt install -y libcurl4-openssl-dev
sudo apt install -y nlohmann-json3-dev
sudo apt install -y libzip-dev

### Windows Install
#### Install MSYS2 from https://www.msys2.org/
#### Then open MSYS2 MINGW64 terminal and run:

1. pacman -Syu
2. pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-gcc mingw-w64-x86_64-make
3. pacman -S mingw-w64-x86_64-wxWidgets
4. pacman -S mingw-w64-x86_64-curl mingw-w64-x86_64-openssl
5. pacman -S mingw-w64-x86_64-nlohmann-json
6. pacman -S mingw-w64-x86_64-libxlsxwriter
7. pacman -S mingw-w64-x86_64-libzip

### Downloading Trade Confirmations
1. Go to the CMC-Market website
2. Navigate to Account -> Confirmations
3. Under "Select file format", choose "Excel (CSV)"
4. Click "Open Advanced Search"
5. Set "Start Date" to your earliest share trade date
6. Click "Search" to find all your trade history
7. Click "Download" to save the CSV file

## Run
In project directory:
mkdir build
cd build
cmake ..
Linux: make
Windows: cmake --build .
./main
