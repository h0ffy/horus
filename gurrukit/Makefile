# jue sep 30 03:32:25 CET 2016

CFLAGS = -g --std=c11 -c -DBUILDING_GURRUKIT_DLL -Wattributes -static -static-libgcc
CPPFLAGS = -g --std=c++11 -c -Wattributes -fpermissive -static -static-libgcc
#LDFLAGS = -g -L/usr/x86_64-w64-mingw32/lib -mdll -mwindows -lwow64 -lwinhttp -lwininet -lntdll -lkernel32 -luser32 -Wl,--out-implib,obj/libgurrkit.a -Wattributes -lwow64win -lm -fno-builtin -fno-stack-protector -Os 
LDFLAGS = -g -L/usr/i686-w64-mingw32/lib -mdll -mwindows -lwinhttp -lwininet -lntdll -lkernel32 -luser32 -Wl,--out-implib,obj/libgurrkit.a -Wattributes -lm -fno-builtin -fno-stack-protector -Os --enable-auto-import -static-libgcc -static
INCLUDE = /usr/i686-w64-mingw32/include
EXE = ../bin/gurrukit.dll
CC = i686-w64-mingw32-gcc
CPP = i686-w64-mingw32-g++
#CC = i686-w64-mingw32-gcc

OBJ_MAIN = obj/dllmain.o obj/memory.o obj/info.o obj/hook.o obj/hooking.o obj/misc.o obj/MyFunction.o obj/ReflectiveLoader.o obj/regextract.o obj/reply.o obj/sys.o obj/gurru.o obj/slre.o obj/process.o obj/nt.o
OBJ = $(OBJ_MAIN) #$(OBJ_MODULES)



all: $(EXE)


obj/ReflectiveLoader.o: src/ReflectiveLoader.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<

obj/dllmain.o: src/dllmain.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<

obj/MyFunction.o: src/MyFunction.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<

obj/memory.o: src/memory.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<

obj/hook.o: src/hook.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<

obj/misc.o: src/misc.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<

obj/info.o: src/info.cpp	
	$(CPP) -c $(CPPFLAGS) -o $@ -I$(INCLUDE) $<

obj/cmd.o: src/cmd.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<

obj/crypto.o: src/crypto.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<

obj/gurru.o: src/gurru.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<
obj/hooking.o: src/hooking.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<
obj/http.o: src/http.c
	$(CC) -c $(CLAGS) -o $@ -I$(INCLUDE) $<
obj/regextract.o: src/regextract.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<
obj/reply.o: src/reply.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<
obj/sys.o: src/sys.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<
obj/gurru.o: src/gurru.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<
obj/slre.o: src/slre/slre.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<
obj/process.o: src/process.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<
obj/nt.o: src/nt.c
	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<

#obj/inject.o: src/inject.c
#	$(CC) -c $(CFLAGS) -o $@ -I$(INCLUDE) $<


$(EXE): $(OBJ)
	$(CPP) -o $@ $(LDFLAGS) $^

clean:
	rm $(OBJ)

clean-all:
	rm $(OBJ) $(EXE)


