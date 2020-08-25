# Kevin Haryo Kuncoro
# kevinhyokun91@gmail.com

include :=\
	-Ibox2d \
	-Iraylib/ \
	-Itinyxml2/ \
	-IkhkFramework/

lib :=\
	-Lraylib/ \
	-lraylib \
	-Lbox2d/ \
	-lbox2d \
	-lGL \
	-lm \
	-lpthread \
	-ldl \
	-lrt \
	-lX11

src :=\
	khkFramework/*.cpp

obj :=\
	tinyxml2/*.o \
	khkFramework/obj/*.o

all:
	g++ -o main main.cpp $(obj) $(include) $(lib) 

run:
	make all
	./main

obj:
	make -C khkFramework/obj

objrun:
	make obj
	make run
