# Kevin Haryo Kuncoro
# kevinhyokun91@gmail.com

include :=\
	-Ibox2d/ \
	-Iraylib/ \
	-Itinyxml2/ \
	-IkhkFramework/

lib :=\
	-Lraylib/ \
	-lraylib \
	-lGL \
	-lm \
	-lpthread \
	-ldl \
	-lrt \
	-lX11

src :=\
	khkFramework/*.cpp

obj :=\
	box2d/obj/collision/*cpp.o \
	box2d/obj/common/*cpp.o \
	box2d/obj/dynamics/*cpp.o \
	box2d/obj/rope/*cpp.o \
	tinyxml2/*.o \
	khkFramework/obj/*.o

all:
	g++ -o main main.cpp $(obj) $(include) $(lib) 

run:
	make all
	./main

obj:
	make -C khkFramework/obj
