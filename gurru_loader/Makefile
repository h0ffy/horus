# jue sep 30 03:32:25 CET 2016

CFLAGS = -O1 -g --std=c11 -Wl,--subsystem,windows 
LDFLAGS = -O1 -g -L/usr/x86_64-w64-mingw32/lib -mwindows -lwinhttp -lwininet -lntdll -lkernel32 -luser32 -Wl,--subsystem,windows -s
OBJ_MAIN = obj/main.o obj/security.o #obj/http.o #obj/inject.o
#OBJ_MODULES = obj/modules/module_agent.o 
OBJ = $(OBJ_MAIN) #$(OBJ_MODULES)
INCLUDE = /usr/x86_64-w64-mingw32/include
EXE = ../bin/gurru.exe
CC = x86_64-w64-mingw32-gcc
#CC = i686-w64-mingw32-gcc

all: $(EXE)

obj/main.o: src/main.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<

obj/security.o: src/security.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<

#obj/http.o: src/http.c	
#	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<

#obj/inject.o: src/inject.c
#	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<


$(EXE): $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $^

clean:
	rm $(OBJ)

clean-all:
	rm $(OBJ) $(EXE)


