cmake_minimum_required(VERSION 3.22.1)
project(YourProjectName VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_EXTENSIONS OFF)

add_compile_options(-Wall -Werror -g -O)


find_package(wxWidgets 3.2 REQUIRED COMPONENTS core base net)
find_package(Threads REQUIRED)
find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)
find_package(nlohmann_json QUIET)

set(SERVICES_SOURCES
    src/cpp/services/dataRow.cpp
    src/cpp/services/dataProcessing.cpp
    src/cpp/services/tradeOperations.cpp
    src/cpp/services/dataRetrieval.cpp
    src/cpp/services/excelWriter.cpp
    src/cpp/services/corporateShareActions.cpp
)

set(MAIN_SOURCES
    src/cpp/userInterface/app.cpp
    src/cpp/userInterface/mainFrame.cpp
    src/cpp/userInterface/shareSplitController.cpp
    src/cpp/userInterface/shareNameChangeController.cpp
    src/cpp/userInterface/shareTakeoverController.cpp
    src/cpp/userInterface/generateReportController.cpp
)

add_library(services STATIC ${SERVICES_SOURCES})

target_link_libraries(services
    CURL::libcurl
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
    ZLIB::ZLIB
    xlsxwriter
    minizip
    nlohmann_json::nlohmann_json
)

add_executable(main ${MAIN_SOURCES})
include(${wxWidgets_USE_FILE})
target_link_libraries(main
    services
    ${wxWidgets_LIBRARIES}
)

add_executable(serviceTest src/cpp/services/serviceTest.cpp)
target_link_libraries(serviceTest services)

install(TARGETS main serviceTest RUNTIME DESTINATION bin)