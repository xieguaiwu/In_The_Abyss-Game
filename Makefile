# ============================================================================
# 在深渊 (In the Abyss) — 跨平台 Makefile
# 支持: Linux (g++), macOS (clang++), Windows (MinGW)
# ============================================================================

# ---- 平台自动检测 ----
UNAME_S  := $(shell uname -s)
UNAME_M  := $(shell uname -m)

# ---- 编译器自动选择 ----
ifeq ($(UNAME_S),Darwin)
  CXX      ?= clang++
  OS_NAME  := macos
else ifeq ($(UNAME_S),Linux)
  CXX      ?= g++
  OS_NAME  := linux
else ifneq ($(findstring MINGW,$(UNAME_S)),)
  CXX      ?= g++
  OS_NAME  := windows
else ifneq ($(findstring MSYS,$(UNAME_S)),)
  CXX      ?= g++
  OS_NAME  := windows
else
  CXX      ?= g++
  OS_NAME  := unknown
endif

# ---- 平台特定定义 ----
# macOS: _DARWIN_C_SOURCE 用于 TIOCGWINSZ 等 POSIX 扩展
# platform.h 中已包含此定义，此处冗余提供确保万无一失
ifeq ($(OS_NAME),macos)
  EXTRA_DEFS := -D_DARWIN_C_SOURCE
else
  EXTRA_DEFS :=
endif

# ---- 编译选项 ----
CXXFLAGS := -std=c++17 -Wall -Wextra $(EXTRA_DEFS)
OPTFLAGS := -O2

# Debug 标志：UBSan 仅当编译器支持时启用
ifeq ($(OS_NAME),linux)
  DBGFLAGS := -O0 -g -DDEBUG -fsanitize=undefined
else
  DBGFLAGS := -O0 -g -DDEBUG
endif

LDFLAGS  :=
TARGET   := Abyss

# ---- 目录 ----
SRCDIR   := src
INCDIR   := include
OBJDIR   := obj/$(OS_NAME)
DBGDIR   := obj/$(OS_NAME)/debug

# ---- 源文件（自动发现） ----
SRCS     := $(wildcard $(SRCDIR)/*.cpp)
OBJS     := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DBGOBJS  := $(SRCS:$(SRCDIR)/%.cpp=$(DBGDIR)/%.o)

# ---- 目标 ----
.PHONY: all debug clean distclean run run-debug info

all: CXXFLAGS += $(OPTFLAGS)
all: $(TARGET)

debug: CXXFLAGS += $(DBGFLAGS)
debug: $(TARGET)-debug

# ---- 编译 ----
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(DBGDIR):
	mkdir -p $(DBGDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(DBGDIR)/%.o: $(SRCDIR)/%.cpp | $(DBGDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# ---- 链接 ----
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $^ -o $@ $(LDFLAGS)

$(TARGET)-debug: $(DBGOBJS)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $^ -o $@ $(LDFLAGS)

# ---- 运行 ----
run: $(TARGET)
	./$(TARGET)

run-debug: $(TARGET)-debug
	./$(TARGET)-debug

# ---- 清理 ----
clean:
	rm -rf obj $(TARGET) $(TARGET)-debug

distclean: clean
	rm -f *.o

# ---- 诊断信息 ----
info:
	@echo "Platform:      $(OS_NAME) ($(UNAME_S) $(UNAME_M))"
	@echo "Compiler:      $(CXX)"
	@echo "CXXFLAGS:      $(CXXFLAGS)"
	@echo "Source files:  $(SRCS)"
	@echo "Target:        $(TARGET)"
	@echo ""
	@echo "Build:  make [debug] [-j<N>]"
	@echo "Run:    make run [run-debug]"
