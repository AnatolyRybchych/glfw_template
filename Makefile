
CC 						= g++
CARGS					= -c -g -Wpedantic -Wall -Iextern/GLFW/include/ -Iextern/glad/include/


#link all objects together
build:  objects/main.o objects/glad.o
	@$(CC) -g -o run.exe $+ extern/GLFW/lib-mingw-w64/libglfw3.a -lgdi32 -lopengl32
	@echo $@ : $+

objects/main.o:./src/main.cpp
	@echo $@ : $+
	@$(CC) $(CARGS) -o $@ $+

#glad lib
objects/glad.o: extern/glad/src/glad.c
	@echo $@ : $+
	@$(CC) -c -Iextern/glad/include/  -o $@ $+


#make args
gdb: build
	gdb run.exe

run: build
	run.exe
