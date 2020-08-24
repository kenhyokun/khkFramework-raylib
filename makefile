# Kevin Haryo Kuncoro
# kevinhyokun91@gmail.com

include :=\
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
	tinyxml2/*.o \
	khkFramework/objs/*.o

all:
	g++ -o main main.cpp $(obj) $(include) $(lib) 

run:
	make all
	./main

obj:
	make -C khkFramework/objs
