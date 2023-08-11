CC := gcc
CFLAGS := -Wall -Wextra -pedantic
LDFLAGS := -pthread
TARGET := libslog.a
SRCDIR := src
BUILDDIR := build
SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))

# Set Linux-specific build options
ifeq ($(shell uname -s),Linux)
	CFLAGS += -D_LINUX
endif

#  Set macOS-specific build options
ifeq ($(shell uname -s),Darwin)
	CFLAGS += -D_DARWIN
endif

.PHONY: all clean install remove

all: $(TARGET)

$(TARGET): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ 

install: $(TARGET)
	cp $(TARGET) /usr/lib/
	cp $(SRCDIR)/slog.h /usr/include/
	cp $(SRCDIR)/colors.h /usr/include/

remove:
	rm -f /usr/lib/$(TARGET)
	rm -f /usr/include/slog.h
	rm -f /usr/include/colors.h

clean:
	rm -rf $(BUILDDIR) $(TARGET)
