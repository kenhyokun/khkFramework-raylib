# Kevin Haryo Kuncoro
# kevinhyokun91@gmail.com

INCLUDE :=\
	-I../third_party/box2d \
	-I../third_party/raylib \
	-I../third_party/tinyxml2 \
	-I../third_party/confini \
	-I../third_party/json \
	-I../khkFramework

LIB :=\
	-L../khkFramework/build \
	-L../third_party/tinyxml2 \
	-L../third_party/confini \
	-L../third_party/raylib \
	-L../third_party/box2d \
	-lkhkFramework \
	-ltinyxml2 \
	-lconfini \
	-lraylib \
	-lbox2d \
	-lGL \
	-lm \
	-lpthread \
	-ldl \
	-lrt \
	-lX11

# CURR_PROJECT := contact_callback.cpp
CURR_PROJECT := basic_node.cpp

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
