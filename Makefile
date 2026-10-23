CC = gcc
CFLAGS = -Wall -Wextra -g -lm
TARGET = oasa
OBJS = main.o parser.o helpers.o api.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c parser.h helpers.h api.h
	$(CC) $(CFLAGS) -c main.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

helpers.o: helpers.c helpers.h parser.h
	$(CC) $(CFLAGS) -c helpers.c

api.o: api.c api.h helpers.h parser.h
	$(CC) $(CFLAGS) -c api.c

clean:
	rm -f $(OBJS) $(TARGET)
