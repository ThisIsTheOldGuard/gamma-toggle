# Компилятор и флаги
CC = gcc
CFLAGS = -O2 -Wall -Wextra -I./include
LDFLAGS = -lgdi32 -mwindows

# Имена файлов
TARGET = gamma-toggle.exe
SRC_DIR = src
RES_DIR = res
OBJ_DIR = build

# Файлы
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/gamma.c
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/gamma.o $(OBJ_DIR)/app.o

# Правило по умолчанию
all: $(OBJ_DIR) $(TARGET)

# Создание папки для объектных файлов
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Сборка финального exe
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Компиляция C файлов
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция ресурсного файла (иконки)
$(OBJ_DIR)/app.o: $(RES_DIR)/app.rc
	windres $< -o $@

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean