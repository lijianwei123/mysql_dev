CC = g++ 
CFLAGS = -g  -fPIC -Wl,-rpath,/usr/local/mysql-replication-listener/lib  \
-L/usr/local/mysql-replication-listener/lib \
-lreplication \
-I/usr/local/mysql-replication-listener/include

TARGET = monitor

SRCS = monitor.cpp

OBJS = $(SRCS:.cpp=.o)


$(TARGET): $(SRCS)
	$(CC)  $(CFLAGS) $^ -o $(TARGET)

%.o: %.cpp
	$(CC) -o $@ -c $<

clean:
	rm -rf *.o $(TARGET)

.PHONY: clean
