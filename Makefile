CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c11
LDFLAGS :=

TARGET := libslog.a
SRC_DIR := src
BUILD_DIR := build
SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

PREFIX := /usr/local
LIB_DIR := $(PREFIX)/lib
INCLUDE_DIR := $(PREFIX)/include

.PHONY: all clean install remove

all: $(TARGET)

$(TARGET): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ 

install: $(TARGET)
	@echo "Installing library to $(LIB_DIR)..."
	@mkdir -p $(LIB_DIR) $(INCLUDE_DIR)
	cp $(TARGET) $(LIB_DIR)/
	cp $(SRC_DIR)/slog.h $(INCLUDE_DIR)/

remove:
	@echo "Removing installed files..."
	rm -f $(LIB_DIR)/$(TARGET)
	rm -f $(INCLUDE_DIR)/slog.h

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
