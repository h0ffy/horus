# jue sep 30 03:32:25 CET 2016
all: $(EXE)

$(EXE): $(OBJ)
	mkdir bin
	cd gurru_loader/
	make
	cd ../
	cd gurrukit/
	make
	cd ../bin
	ls

clean:
	rm -rf bin

clean-all:
	rm -rf bin


