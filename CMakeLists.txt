cmake_minimum_required(VERSION 3.22.1)
project(YourProjectName VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_EXTENSIONS OFF)

if(WIN32)
    add_compile_options(-Wall -g)
    set(MSYS2_PATH "C:/msys64/mingw64")
    set(CMAKE_PREFIX_PATH ${MSYS2_PATH})
    
    set(wxWidgets_INCLUDE_DIRS 
        "${MSYS2_PATH}/lib/wx/include/msw-unicode-3.2" 
        "${MSYS2_PATH}/include/wx-3.2")
    add_compile_definitions(WXUSINGDLL __WXMSW__)

    find_library(WX_CORE_LIB libwx_mswu_core-3.2.dll.a PATHS "${MSYS2_PATH}/lib" REQUIRED)
    find_library(WX_BASE_LIB libwx_baseu-3.2.dll.a PATHS "${MSYS2_PATH}/lib" REQUIRED)
    set(wxWidgets_LIBRARIES ${WX_CORE_LIB} ${WX_BASE_LIB})
    
    set(PLATFORM_LIBS comctl32 winmm)
    
    find_library(XLSXWRITER_LIBRARY xlsxwriter PATHS "${MSYS2_PATH}/lib" REQUIRED)
    find_path(XLSXWRITER_INCLUDE_DIR xlsxwriter.h PATHS "${MSYS2_PATH}/include" REQUIRED)
    else()
    add_compile_options(-Wall -Werror -g -O)
    
    find_package(wxWidgets 3.2 REQUIRED COMPONENTS core base net)
    include(${wxWidgets_USE_FILE})
    set(PLATFORM_LIBS)
    find_package(PkgConfig QUIET)
    
    find_library(XLSXWRITER_LIBRARY xlsxwriter REQUIRED)
    find_path(XLSXWRITER_INCLUDE_DIR xlsxwriter.h REQUIRED)
endif()
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
target_include_directories(services PUBLIC ${XLSXWRITER_INCLUDE_DIR})

target_link_libraries(services
    CURL::libcurl
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
    ${XLSXWRITER_LIBRARY}
    nlohmann_json::nlohmann_json
)

add_executable(main ${MAIN_SOURCES})

if(WIN32)
    target_include_directories(main PRIVATE ${wxWidgets_INCLUDE_DIRS})
endif()

target_link_libraries(main services ${wxWidgets_LIBRARIES} ${PLATFORM_LIBS})

add_executable(serviceTest src/cpp/services/serviceTest.cpp)
target_link_libraries(serviceTest services)

install(TARGETS main serviceTest RUNTIME DESTINATION bin)