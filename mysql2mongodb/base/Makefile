CC = g++

OPT = -g -DDEBUG -Wall -Wno-deprecated  -lpthread `mysql_config --libs`

SrcDir = .
SRCS = $(foreach dir,$(SrcDir),$(wildcard $(dir)/*.cpp))
OBJS = $(SRCS:%.cpp=%.o) cJSON.o   mysql.o 

LIBBASE = libbase.a 

all: $(LIBBASE)

$(LIBBASE): $(OBJS)
	ar -rs $@ $(OBJS)

%.o:%.cpp
	$(CC) $(OPT) -c $< -o $@ 
%.o:%.c
	gcc -g -DDEBUG -c $< -o $@

clean:
	rm -f $(LIBBASE) *.o

