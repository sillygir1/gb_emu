all: gb_emu

debug:
	# debug with tests and debug stuff ig

make_dir:
	mkdir -p out

gb_emu: make_dir main.o instructions.o registers.o system.o
	gcc out/main.o out/instructions.o out/registers.o out/system.o `sdl2-config --cflags --libs` -o out/binary

main.o:
	gcc main.c -c -o out/main.o

instructions.o:
	gcc instructions.c -c -o out/instructions.o

registers.o:
	gcc registers.c -c -o out/registers.o

system.o:
	gcc system.c -c -o out/system.o

tests.o:
	gcc tests.c -c -o out/tests.o

clean:
	rm -rf out/