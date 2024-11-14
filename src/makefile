# Executable name
TARGET = rr_tournament.exe

# Compiler and flags
CC = gcc
CFLAGS = -Wall -I. -g

# Source files
SRCS = main.c tournament.c matchday.c queue.c match.c

# Object files
OBJS = $(SRCS:.c=.o)

# Main rule to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS)
