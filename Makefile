CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

OPENSSL_CFLAGS := $(shell pkg-config --cflags openssl)
OPENSSL_LIBS   := $(shell pkg-config --libs openssl)

TARGET = app

# ディレクトリ構成
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# ソース
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# オブジェクト
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# 依存ファイル
DEPS = $(OBJS:.o=.d)

# インクルードパス
CXXFLAGS += -I$(INC_DIR) $(OPENSSL_CFLAGS)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(OPENSSL_LIBS)

# ★ buildディレクトリに出力
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# buildディレクトリ作成
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

re: clean all