# Compiler settings
CC = gcc
CFLAGS = -std=c99 -Wall -Werror
TARGET = worms.exe
SOURCE = worms.c

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

# Clean up generated files
clean:
	rm -f $(TARGET)

# Rebuild everything
rebuild: clean all

# Run the program after building
run: $(TARGET)
	./$(TARGET)