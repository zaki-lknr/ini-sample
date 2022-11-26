OBJS = main.o
TARGET = main.exe
# OPT = -mno-cygwin -mwindows
OPT = -mwindows
CC = x86_64-w64-mingw32-gcc

all: $(TARGET)

$(TARGET):  $(OBJS)
	$(CC) $(OPT) -o $@ $(OBJS)

.c.o:
	$(CC) -c $<

clean:
	-rm -f $(TARGET) $(OBJS) *~ \#* core

# dependency
main.o:  main.h
