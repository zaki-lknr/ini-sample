OBJS = main.o
TARGET = main.exe
# OPT = -mno-cygwin -mwindows
OPT = -mwindows
CC = x86_64-w64-mingw32-gcc

CLI_TARGET = cli.exe
CLI_OBJS = cli.o

all: $(TARGET) $(CLI_TARGET)

$(TARGET):  $(OBJS)
	$(CC) $(OPT) -o $@ $(OBJS)
$(CLI_TARGET): $(CLI_OBJS)
	$(CC) -o $@ $(CLI_OBJS)

.c.o:
	$(CC) -c $<

clean:
	-rm -f $(TARGET) $(OBJS) $(CLI_TARGET) $(CLI_OBJS) *~ \#* core

# dependency
main.o:  main.h
