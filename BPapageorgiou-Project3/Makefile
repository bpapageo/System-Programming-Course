OBJS1	= webserver.o 
OBJS2	= webcrawler.o Trie.o Postlist.o clientserver.o highlight.o
OUT1	= myhttpd
OUT2	= mycrawler
CC		= g++
FLAGS	= -c -Wall -w

all: t1 t2

highlight.o:highlight.cpp structures.h
	$(CC) $(FLAGS) highlight.cpp
Postlist.o: Postlist.cpp structures.h
	$(CC) $(FLAGS) Postlist.cpp
Trie.o: Trie.cpp structures.h
	$(CC) $(FLAGS) Trie.cpp
clientserver.o: clientserver.cpp structures.h
	$(CC) $(FLAGS) clientserver.cpp
webserver.o: webserver.cpp structures.h
	$(CC) $(FLAGS) webserver.cpp
webcrawler.o: webcrawler.cpp structures.h
	$(CC) $(FLAGS) webcrawler.cpp
t1: $(OBJS1)
	$(CC) $(OBJS1) -o $(OUT1) -pthread
t2: $(OBJS2)
	$(CC) $(OBJS2) -o $(OUT2) -pthread

# clean up
clean:
	rm -f $(OBJS1) $(OUT1) 
	rm -f $(OBJS2) $(OUT2) 