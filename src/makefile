# Nome dell'eseguibile
TARGET = rr_tournament.exe

# Compilatore e flags
CC = gcc
CFLAGS = -Wall -I. -g

# File sorgente
SRCS = main.c tournament.c matchday.c queue.c match.c

# File oggetto (sostituisce .c con .o nei nomi dei file sorgente)
OBJS = $(SRCS:.c=.o)

# Regola principale per creare l'eseguibile
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regola per compilare i file oggetto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regola di pulizia
clean:
	rm -f $(OBJS)
