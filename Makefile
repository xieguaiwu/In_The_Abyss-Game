CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra
OPTFLAGS := -O2
DBGFLAGS := -O0 -g -DDEBUG
LDFLAGS  :=
TARGET   := Abyss

SRCDIR   := src
INCDIR   := include
OBJDIR   := obj
DBGDIR   := obj/debug

SRCS     := $(wildcard $(SRCDIR)/*.cpp)
OBJS     := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DBGOBJS  := $(SRCS:$(SRCDIR)/%.cpp=$(DBGDIR)/%.o)

.PHONY: all debug clean distclean run

all: CXXFLAGS += $(OPTFLAGS)
all: $(TARGET)

debug: CXXFLAGS += $(DBGFLAGS)
debug: $(TARGET)-debug

# Release build
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $^ -o $@ $(LDFLAGS)

# Debug build
$(DBGDIR):
	mkdir -p $(DBGDIR)

$(DBGDIR)/%.o: $(SRCDIR)/%.cpp | $(DBGDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(TARGET)-debug: $(DBGOBJS)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $^ -o $@ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

run-debug: $(TARGET)-debug
	./$(TARGET)-debug

clean:
	rm -rf $(OBJDIR) $(DBGDIR) $(TARGET) $(TARGET)-debug
