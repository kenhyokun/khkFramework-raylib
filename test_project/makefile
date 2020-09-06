# Kevin Haryo Kuncoro
# kevinhyokun91@gmail.com

INCLUDE :=\
	-I../third_party/box2d \
	-I../third_party/raylib \
	-I../third_party/tinyxml2 \
	-I../khkFramework

LIB :=\
	-L../khkFramework/build \
	-L../third_party/tinyxml2 \
	-L../third_party/raylib \
	-L../third_party/box2d \
	-lkhkFramework \
	-ltinyxml2 \
	-lraylib \
	-lbox2d \
	-lGL \
	-lm \
	-lpthread \
	-ldl \
	-lrt \
	-lX11

CURR_PROJECT := contact_callback.cpp

all:
	g++ -o main $(CURR_PROJECT) $(INCLUDE) $(LIB)

debug:
	g++ -g -o main $(CURR_PROJECT) $(INCLUDE) $(LIB)

run:
	make all
	./main

lib:
	make -C ../khkFramework/build

librun:
	make lib 
	make run
