# Should: gcc file.c -o file; recursively.
# Goal of makefile is to create program files from each .c file. (assume .c files are all main)

# Future Edites
# Should edit where it takes headers of a file and have that as a prerequisite for noticing when it is not up to date (changes in headers)

# the commands and flags
CC = gcc
CFLAGS = -Wall
LINK = $(IDIR) $(LDIR) $(LLIB)

#shorthand; (gcc -Wall) ... [files] -o program
COMPILE = $(CC) $(CFLAGS) $(LINK)

# Files i/o
HDRS = $(wildcard *.h)
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
PROGS = $(SRCS:.c=)

IDIR = -I/usr/local/include
LDIR = -L/usr/local/lib
LLIB = -lwiringPi -lwiringPiDev -lpthread -lm -lcrypt -lrt -lccgi #libccgi.a libccgi ccgi.h ccgi
#TARGET= program



# MY RULES
# 1st rule / default target
default: all 
#TODO: edit default and all. Only make main and website files.
#TODO: remember to make clean before making files. This is in case someone turns off/on program.
#TODO: daemon should make build then execute interrupt
#TBD: Add DNS to make this program available online. Clean up before making live.

#Rule: build all essentials
build: interrupt mystyle.css formYoutube formhandleYoutube
	sudo touch ./bin/urlList
	sudo touch ./bin/ISPLAYING
	sudo chmod ug+rwx checkIsPlaying
	sudo chmod ug+rw ./bin/urlList
	

# Rule: compile all .c files in current dir into respective program name into bin folder
all: $(PROGS)


%: %.c
	-mkdir bin && chmod ug+rwx bin/ &
	$(CC) $(CFLAGS) $< -o ./bin/$@ $(LINK)
#above line need program first and linking last since using a static lib (libccgi.a) --cannot use $(COMPILE)


clean:
	-rm -rf bin/ obj/ lib/ thirdPartyRef/
