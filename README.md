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
https://cmake.org/download/ (Between 3.22.1 and 3.5)

git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg install wxwidgets:x64-windows
.\vcpkg install curl:x64-windows openssl:x64-windows
.\vcpkg install nlohmann-json:x64-windows
.\vcpkg install libxlsxwriter:x64-windows
.\vcpkg install libzip:x64-windows

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
make
./main