# 박범근 12161104 - Operating System Project 2


.SUFFIXES : .c .o

CC = gcc

LIBS = -lpthread

OBJ1 = synch_pthread.o
OBJ2 = synch_semaphore.o

SRCS = $(OBJ1: .o=.c) $(OBJ2: .o=.c)

all : synch_pthread synch_semaphore

synch_pthread : $(OBJ1)
			$(CC) -o synch_pthread $(OBJ1) $(LIBS)

synch_semaphore : $(OBJ2)
			$(CC) -o synch_semaphore $(OBJ2) $(LIBS)


depend:
	gccmakedep $(SRCS)
