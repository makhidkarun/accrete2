# Makefile for "accrete2", a star system and planet generator

#    To make a version for debugging or tracing, uncomment this line:
#CFLAGS = -g

# In the following CFLAGS line, keep or remove the respective flags.
#    For those machines in which the rand() function returns a long int, put
# a LONG_RAND flag into the CFLAGS line that you use. 
# For example, Red Hat Linux uses a long int, so keep -DLONG_RAND
# But an SGI may return a 16-bit number from rand(), so remove -DLONG_RAND
#    In addition, if you would like accrete2 to create moons for
# planets based on accretion of a planetary disk, keep the -DMOON flag
#CFLAGS = -O -DLONG_RAND -DMOON

CFLAGS = -O

#    These two lines should always be uncommented:
OBJS = accrete.o enviro.o display.o utils.o
LIBS = -lm


accrete2: main.o $(OBJS)
	cc $(CFLAGS) -o accrete2 main.o $(OBJS) $(LIBS)
	@echo "accrete2 made"

accrete.o: accrete.c const.h structs.h
	cc -c $(CFLAGS) accrete.c

enviro.o: enviro.c const.h structs.h
	cc -c $(CFLAGS) enviro.c

display.o: display.c const.h structs.h
	cc -c $(CFLAGS) display.c

utils.o: utils.c const.h
	cc -c $(CFLAGS) utils.c

main.o: main.c const.h structs.h
	cc -c $(CFLAGS) main.c

clean:
	rm -f *.o accrete2

lint:
	lint -abchp main.c accrete.c enviro.c display.c utils.c

SHARFILES = README acctete2.mak Makefile main.c accrete.c enviro.c display.c utils.c const.h structs.h

shar: $(SHARFILES)
	shar -abcCs $(SHARFILES) >accrete2.shar

