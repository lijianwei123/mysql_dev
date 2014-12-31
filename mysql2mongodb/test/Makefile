#client makefile
CC = g++

INC = -I ../base -I ../
OPT = -Wall -Wno-deprecated -DDEBUG -g -lrt  -lpthread `mysql_config --libs` `pkg-config --cflags --libs libmongoc-1.0`

SrcDir = .
SRCS = $(foreach dir,$(SrcDir),$(wildcard $(dir)/*.cpp))
OBJS = $(SRCS:%.cpp=%.o) ../base/libbase.a 

TEST = test_syncStruct

all: $(TEST)

$(TEST): $(OBJS)
	$(CC)  $(OPT) -o $@ $(OBJS)

%.o:%.cpp
	$(CC) $(OPT) $(INC) -c $< -o $@ 

clean:
	rm -f $(TEST) *.o
