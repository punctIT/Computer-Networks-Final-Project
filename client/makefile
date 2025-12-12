CXX = g++

TARGET_DIR = target
TARGET = $(TARGET_DIR)/program

SRC := $(shell find src -name "*.cpp")
MOC_HEADERS := src/frontend/page_system/Page.h \
			   src/frontend/page_system/Popup.h \
			   src/server_request/DataRequester.h \
			   src/frontend/widgets/AlertPopup.h
 

MOCS := $(MOC_HEADERS:src/%.h=$(TARGET_DIR)/moc_%.cpp)

MOC = /usr/lib/qt6/libexec/moc 


CXXFLAGS = -I/usr/include/x86_64-linux-gnu/qt6 \
           -I/usr/include/x86_64-linux-gnu/qt6/QtWidgets \
           -I/usr/include/x86_64-linux-gnu/qt6/QtCore \
		   -I/usr/include/x86_64-linux-gnu/qt6/QtCharts \
		   -I/usr/include/x86_64-linux-gnu/qt6/QtGui \
           -std=c++23


LIBS = -lsqlite3 -lQt6Widgets -lQt6Core -lQt6Gui -lQt6Charts 


all: $(TARGET) 

$(TARGET): $(SRC) $(MOCS) | $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(MOCS) $(LIBS)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)


$(TARGET_DIR)/moc_%.cpp: src/%.h | $(TARGET_DIR)
	mkdir -p $(dir $@)
	$(MOC) $< -o $@

clean:
	rm -rf $(TARGET_DIR)