all: compile_all gb_emu

debug: compile_all tests.o
	gcc out/main.o out/instructions.o out/registers.o out/system.o out/graphics.o out/tile.o out/tests.o -lSDL2 -lSDL2main -o out/binary -g

make_dir:
	mkdir -p out

compile_all: make_dir main.o instructions.o registers.o system.o graphics.o tile.o

gb_emu: 
	gcc out/main.o out/instructions.o out/registers.o out/system.o out/graphics.o out/tile.o -lSDL2 -lSDL2main -o out/binary

main.o:
	gcc main.c -c -o out/main.o

instructions.o:
	gcc instructions.c -c -o out/instructions.o

registers.o:
	gcc registers.c -c -o out/registers.o

system.o:
	gcc system.c -c -o out/system.o

graphics.o:
	gcc graphics.c -c -o out/graphics.o

tile.o:
	gcc gb-bytes-to-image/tile.c -c -o out/tile.o

tests.o:
	gcc tests.c -c -o out/tests.o

clean:
	rm -rf out/
