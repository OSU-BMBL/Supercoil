VER=0.1
DIST=supercoil$(VER)
PROGS=supercoil
SRCS=struct.c read_array.c get_options.c  main.c expression_analysis.c valleyDetect.c dynamic_programming.c
OBJS=$(SRCS:.c=.o) 
CC=gcc


LDFLAGS=-static  -lm
CFLAGS=-O3 -Wall -ansi -I.  -DVER=$(VER)

all: $(PROGS)

${PROGS}: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

.o:
	$(CC) $(CFLAGS) $< -o $@ 

clean:
	rm -f $(PROGS)
	rm -f *.o
	rm -f *.rules
	rm -f *.chars
	rm -f *.expansion
	rm -f *.detail
	rm -f *.valley

dist:
	$(MAKE) clean
	cd .. && tar czvf $(DIST).tar.gz $(DIST)/
test1:
	$(MAKE)
	./supercoil -i DATA/NC_000913.expr -j DATA/NC_000913.ptt  -o DATA/NC_000913.gi.operon -p DATA/NC_000913.pathway -n 0.3 -g 0.5 -t 15
test2:
	$(MAKE)
	./supercoil -i DATA/NC_000913.expr -j DATA/NC_000913.ptt  -o DATA/NC_000913.gi.operon -p DATA/NC_000913.pathway -a DATA/NC_000913.NAP -e DATA/NC_000913.HEG -D DATA/expression-value -n 0.3 -g 0.5 -t 15
test3: $(MAKE)
	./supercoil -i DATA/NC_000913.expr -j DATA/NC_000913.ptt  -o DATA/NC_000913.gi.operon -p DATA/NC_000913.pathway -a DATA/NC_000913.NAP -e DATA/NC_000913.HEG -D DATA/expression-value -M
