ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: stat_main.o
	$(CC) -o test_stat stat_main.o

dr_main.o: stat_main.c
	$(CC) -c stat_main.c

run:
	./test_stat

memcheck:
	valgrind --leak-check=yes ./test_stat

clean:
	rm *.o
	rm *~
