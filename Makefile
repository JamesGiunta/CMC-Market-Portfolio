CXX = g++
VCPKG_ROOT ?= /home/$(shell whoami)/vcpkg
VCPKG_INCLUDE ?= $(VCPKG_ROOT)/installed/x64-linux/include
VCPKG_LIB ?= $(VCPKG_ROOT)/installed/x64-linux/lib

WX_CONFIG = $(VCPKG_ROOT)/installed/x64-linux/tools/wxwidgets/wx-config
CXXFLAGS = -Wall -Werror -std=c++20 -g -O -I$(VCPKG_INCLUDE) $(shell $(WX_CONFIG) --cxxflags)
LDFLAGS = -O -L$(VCPKG_LIB)
LDLIBS = -lcurl -lssl -lcrypto -pthread -lxlsxwriter -lminizip -lz $(shell $(WX_CONFIG) --libs)
SRC_DIR = src/cpp
SRC_USERINTERFACE_DIR = src/cpp/userInterface
SRC_SERVICES_DIR = src/cpp/services

dataRow.o:
	$(CXX) $(CXXFLAGS) -c $(SRC_SERVICES_DIR)/dataRow.cpp -o $(SRC_SERVICES_DIR)/dataRow.o

serviceTest.o:
	$(CXX) $(CXXFLAGS) -c $(SRC_SERVICES_DIR)/serviceTest.cpp -o $(SRC_SERVICES_DIR)/serviceTest.o

dataProcessing.o:
	$(CXX) $(CXXFLAGS) -c $(SRC_SERVICES_DIR)/dataProcessing.cpp -o $(SRC_SERVICES_DIR)/dataProcessing.o

tradeOperations.o:
	$(CXX) $(CXXFLAGS) -c $(SRC_SERVICES_DIR)/tradeOperations.cpp -o $(SRC_SERVICES_DIR)/tradeOperations.o

dataRetrieval.o:
	$(CXX) $(CXXFLAGS) -c $(SRC_SERVICES_DIR)/dataRetrieval.cpp -o $(SRC_SERVICES_DIR)/dataRetrieval.o

excelWriter.o:
	$(CXX) $(CXXFLAGS) -c $(SRC_SERVICES_DIR)/excelWriter.cpp -o $(SRC_SERVICES_DIR)/excelWriter.o

corporateShareActions.o:
	$(CXX) $(CXXFLAGS) -c $(SRC_SERVICES_DIR)/corporateShareActions.cpp -o $(SRC_SERVICES_DIR)/corporateShareActions.o

app.o:
	$(CXX) $(CXXFLAGS) -c $(SRC_USERINTERFACE_DIR)/app.cpp -o $(SRC_USERINTERFACE_DIR)/app.o

mainFrame.o:
	$(CXX) $(CXXFLAGS) -c $(SRC_USERINTERFACE_DIR)/mainFrame.cpp -o $(SRC_USERINTERFACE_DIR)/mainFrame.o

serviceTest: $(SRC_SERVICES_DIR)/serviceTest.o $(SRC_SERVICES_DIR)/dataProcessing.o $(SRC_SERVICES_DIR)/dataRow.o $(SRC_SERVICES_DIR)/tradeOperations.o $(SRC_SERVICES_DIR)/dataRetrieval.o $(SRC_SERVICES_DIR)/excelWriter.o $(SRC_SERVICES_DIR)/corporateShareActions.o
	$(CXX) $(LDFLAGS) -o serviceTest $^ $(LDLIBS)

main: $(SRC_USERINTERFACE_DIR)/app.o $(SRC_USERINTERFACE_DIR)/mainFrame.o
	$(CXX) $(LDFLAGS) -o main $^ $(LDLIBS)

clean:
	rm -f $(SRC_SERVICES_DIR)/*.o $(SRC_USERINTERFACE_DIR)/*.o serviceTest main