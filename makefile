# Kevin Haryo Kuncoro
# kevinhyokun91@gmail.com

include :=\
	-Ibox2d \
	-Iraylib/ \
	-Itinyxml2/ \
	-IkhkFramework/

lib :=\
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

src :=\
	khkFramework/*.cpp

obj :=\
	khkFramework/obj/*.o

all:
	g++ -o main main.cpp $(include) $(lib)

debug:
	g++ -g -o main main.cpp $(include) $(lib) 

run:
	make all
	./main

obj:
	make -C khkFramework/build

objrun:
	make obj
	make run
