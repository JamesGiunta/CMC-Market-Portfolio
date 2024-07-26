CXX = g++
VCPKG_INCLUDE ?= /home/$(shell whoami)/vcpkg/installed/x64-linux/include
VCPKG_LIB ?= /home/$(shell whoami)/vcpkg/installed/x64-linux/lib

CXXFLAGS = -Wall -Werror -std=c++20 -g -O -I$(VCPKG_INCLUDE)
LDFLAGS = -O -L$(VCPKG_LIB)
LDLIBS = -lcurl -lssl -lcrypto -pthread -lxlsxwriter -lminizip -lz
SRC_DIR = src/cpp/services

dataRow.o:
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/dataRow.cpp -o $(SRC_DIR)/dataRow.o

serviceTest.o:
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/serviceTest.cpp -o $(SRC_DIR)/serviceTest.o

dataProcessing.o:
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/dataProcessing.cpp -o $(SRC_DIR)/dataProcessing.o

tradeOperations.o:
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/tradeOperations.cpp -o $(SRC_DIR)/tradeOperations.o

dataRetrieval.o:
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/dataRetrieval.cpp -o $(SRC_DIR)/dataRetrieval.o

excelWriter.o:
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/excelWriter.cpp -o $(SRC_DIR)/excelWriter.o

serviceTest: $(SRC_DIR)/serviceTest.o $(SRC_DIR)/dataProcessing.o $(SRC_DIR)/dataRow.o $(SRC_DIR)/tradeOperations.o $(SRC_DIR)/dataRetrieval.o $(SRC_DIR)/excelWriter.o
	$(CXX) $(LDFLAGS) -o serviceTest $^ $(LDLIBS)

clean:
	rm -f $(SRC_DIR)/*.o serviceTest