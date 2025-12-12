CXX = g++ -std=c++23

INCLUDES = -Iinclude -I/usr/include/nlohmann

TARGET_DIR = target
TARGET = $(TARGET_DIR)/program

SRC := $(shell find src -name "*.cpp")

LIBS = -lsqlite3

all: $(TARGET)

$(TARGET): $(SRC) | $(TARGET_DIR)
	# 3. Adaugam $(INCLUDES) in comanda de compilare
	$(CXX) $(INCLUDES) -o $(TARGET) $(SRC) $(LIBS)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

clean:
	rm -rf $(TARGET_DIR)