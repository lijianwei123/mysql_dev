#client makefile
CC = g++

INC = -I ../base -I ../
OPT = -g -Wall -DDEBUG  -Wno-deprecated  `mysql_config --libs` `pkg-config --cflags --libs libmongoc-1.0`
DEP = ../base/libbase.a

TEST = test_syncStruct

all: $(TEST)

$(TEST): ./test_syncStruct.cpp  ../syncStruct.cpp
	$(CC)  $(INC) $(OPT) $^ $(DEP) -o $@

clean:
	rm -f $(TEST) *.o
