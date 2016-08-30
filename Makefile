#Executable
TARGET=gen-java
W32_TARGET=genjav32


#Source files
SRCS	=  src/class-decl.c src/util.c src/statics.c src/main.c    

#Object files
OBJS	=  src/class-decl.o src/util.o src/statics.o src/main.o

#Linker arguments

CFLAGS	= -Wall -ansi -pedantic -Wbad-function-cast  -Wmissing-declarations -Wmissing-prototypes -Wnested-externs -Wstrict-prototypes
	
all: depend build win32

# Produce the oject files from the source 
build: $(OBJS)
    
	clear
	echo "Building"
	echo $(TARGET)
	gcc $(CFLAGS) -o $(TARGET) $(OBJS) -lz

win32:
	clear
	echo "Building win32 version "
	echo $(TARGET)
	i386-mingw32msvc-gcc $(CFLAGS) $(SRCS) -o $(W32_TARGET)

clean:
	clear
	echo "Building "
	echo $(TARGET)
	rm -f $(OBJS)
	rm -f $(TARGET)
	rm -f $(W32_TARGET)
	rm -f .depend
	rm -f src/*.?~

depend:	$(SRCS)
	clear 
	echo "Assessing dependencies for "
	echo $(TARGET)
	gcc -MM $(SRCS) > .depend

-include .depend
