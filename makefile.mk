# Compiler options
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Source files
SRCS = D:/Desktop/Assembler/src/utils/generalUtils/Utilities.cpp \
	   D:/Desktop/Assembler/src/algorithm/preAssembler/macro/Macro.cpp \
	   D:/Desktop/Assembler/src/algorithm/preAssembler/macroTable/MacroTable.cpp \
       D:/Desktop/Assembler/src/algorithm/preAssembler/preAssembler.cpp \
       D:/Desktop/Assembler/src/symbolTable/SymbolTable.cpp \
       D:/Desktop/Assembler/src/firstRide/FirstRide.cpp \
       D:/Desktop/Assembler/src/secondRide/SecondRide.cpp \
       D:/Desktop/Assembler/src/utilRide2/UtilRide2.cpp \
       D:/Desktop/Assembler/src/outputFiles/OutputFiles.cpp \
       D:/Desktop/Assembler/src/assembler/assembler.cpp \
       D:/Desktop/Assembler/src/debugger/Debugger.cpp \
       D:/Desktop/Assembler/src/dataUtils/DataUtils.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = assembler

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
