# Define the compiler
CC = gcc

# Define the compiler flags
CFLAGS = -Wall -g

# Define the target executable
TARGET = JobInterviewRPG

# Define the source files
SRCS = main.c game.c combat.c graph.c save_load.c

# Define the object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile each source file to an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
