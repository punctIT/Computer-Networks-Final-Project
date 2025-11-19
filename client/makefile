CXX = g++ -std=c++23

# Include path
INCLUDES = \
    -I/usr/include/x86_64-linux-gnu/qt6 \
    -I/usr/include/x86_64-linux-gnu/qt6/QtCore \
    -I/usr/include/x86_64-linux-gnu/qt6/QtGui \
    -I/usr/include/x86_64-linux-gnu/qt6/QtWidgets

# Linker flags
LIBS = -lQt6Core -lQt6Gui -lQt6Widgets

TARGET_DIR = target
TARGET = $(TARGET_DIR)/program

SRC := $(shell find src -name "*.cpp")

all: $(TARGET)

$(TARGET): $(SRC) | $(TARGET_DIR)
	$(CXX) $(INCLUDES) -o $(TARGET) $(SRC) $(LIBS)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

clean:
	rm -rf $(TARGET_DIR)
