# Kevin Haryo Kuncoro
# kevinhyokun91@gmail.com

INCLUDE :=\
	-Ibox2d \
	-Iraylib/ \
	-Itinyxml2/ \
	-IkhkFramework/

LIB :=\
	-LkhkFramework/build/ \
	-lkhkFramework \
	-Ltinyxml2/ \
	-ltinyxml2 \
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

SRC :=\
	khkFramework/*.cpp

all:
	g++ -o main main.cpp $(INCLUDE) $(LIB)

debug:
	g++ -g -o main main.cpp $(INCLUDE) $(LIB)

run:
	make all
	./main

lib:
	make -C khkFramework/build

librun:
	make lib 
	make run
