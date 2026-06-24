CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# OpenSSL
OPENSSL_CFLAGS := $(shell pkg-config --cflags openssl)
OPENSSL_LIBS   := $(shell pkg-config --libs openssl)

CXXFLAGS += $(OPENSSL_CFLAGS)

TARGET = app

SRCS = main.cpp usage.cpp
OBJS = $(SRCS:.cpp=.o)

# ★依存ファイル（.d）を自動生成
DEPS = $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(OPENSSL_LIBS)

# ★ここが重要（依存関係付きコンパイル）
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# ★依存ファイルを読み込む
-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

re: clean all