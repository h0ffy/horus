# jue sep 30 03:32:25 CET 2016
all: $(EXE)

$(EXE): $(OBJ)
	cd gurru_loader/
	make
	cd ../
	cd gurrukit/
	make
	cd ../bin
	ls

clean:
	rm bin/*

clean-all:
	rm bin/*


