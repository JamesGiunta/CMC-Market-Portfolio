CXX = g++
CXXFLAGS = -Wall -Werror -std=c++20 -g -O -I/home/james/vcpkg/installed/x64-linux/include
LDFLAGS = -O -L/home/james/vcpkg/installed/x64-linux/lib
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

serviceTest: $(SRC_DIR)/serviceTest.o $(SRC_DIR)/dataProcessing.o $(SRC_DIR)/dataRow.o $(SRC_DIR)/tradeOperations.o $(SRC_DIR)/dataRetrieval.o
	$(CXX) $(LDFLAGS) -o serviceTest $^ $(LDLIBS)

clean:
	rm -f $(SRC_DIR)/*.o serviceTest