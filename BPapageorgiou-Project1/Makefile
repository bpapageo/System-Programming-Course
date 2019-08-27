OBJS	= main.o Trie.o Postlist.o qsort.o highlight.o
OUT	= minisearch
CC		= g++
FLAGS	= -c -Wall -w

all: t1

highlight.o:highlight.cpp structures.h
	$(CC) $(FLAGS) highlight.cpp
qsort.o: qsort.cpp structures.h
	$(CC) $(FLAGS) qsort.cpp
Postlist.o: Postlist.cpp structures.h
	$(CC) $(FLAGS) Postlist.cpp
Trie.o: Trie.cpp structures.h
	$(CC) $(FLAGS) Trie.cpp
main.o: main.cpp structures.h
	$(CC) $(FLAGS) main.cpp
t1: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

# clean up
clean:
	rm -f $(OBJS) $(OUT)
