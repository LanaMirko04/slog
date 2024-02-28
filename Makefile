CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c17
LDFLAGS :=
TARGET := libslog.a
SRCDIR := src
BUILDDIR := build
SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))

.PHONY: all clean install remove

all: $(TARGET)

$(TARGET): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ 

install: $(TARGET)
	cp $(TARGET) /usr/local/lib/
	cp $(SRCDIR)/slog.h /usr/local/include/
	cp $(SRCDIR)/colors.h /usr/local/include/

remove:
	rm -f /usr/local/lib/$(TARGET)
	rm -f /usr/local/include/slog.h
	rm -f /usr/local/include/colors.h

clean:
	rm -rf $(BUILDDIR) $(TARGET)
