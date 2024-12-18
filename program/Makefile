# Compiler and flags
CXX = g++  # Change to clang++ if you're using Clang
CXXFLAGS = -std=c++11 -Wall  # Compiler flags

# Get the output file name from the command line arguments (default to 'output')
OUTPUT = $(if $(output),$(output),output)

# Find all .cpp files in the current directory and generate a list of .o files
SRC = $(wildcard *.cpp)  # All .cpp files in the current directory
OBJ = $(SRC:.cpp=.o)      # Convert .cpp files to .o (object files)

# Default target to build when you just run 'make'
all: $(OUTPUT)

# Rule to link the object files into the final executable
$(OUTPUT): $(OBJ)
	$(CXX) $(OBJ) -o $(OUTPUT)

# Rule to compile each .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files (object files and executable) for Windows (using PowerShell commands)
clean:
	del /q $(OBJ) $(OUTPUT).exe
