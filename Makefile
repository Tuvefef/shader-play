CC := gcc
BIN := shader
SRC := src/main.c src/usp/glad.c src/usp/window.c src/usp/shader.c
CFLAGS := -I./include -Wall -Wextra
LDFLAGS := -lGL -lglfw -lm

all: $(BIN)
$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LDFLAGS)

run: $(BIN)
	./$(BIN) 

clean:
	rm -f $(BIN)

.PHONY: all clean