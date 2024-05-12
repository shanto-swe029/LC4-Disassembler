# you must implement this makefile to create the following 8 targets for part 2 of the assignment:
# all, clean, clobber
# lc4
# lc4_disassembler.o, lc4_hash.o, lc4_loader.o, lc4_memory.o
#  lc4_memory.o lc4_hash.o lc4_loader.o lc4_dissassembler.o
all: clobber lc4

lc4:
	clang lc4_memory.c lc4_loader.c lc4_hash.c lc4_disassembler.c lc4.c -o lc4

lc4_dissassembler.o:
	# clang -g -c lc4_disassembler.c -o lc4_disassembler.o

lc4_hash.o:
	# clang -g -c lc4_hash.c -o lc4_hash.o

lc4_loader.o:
	# clang -g -c lc4_loader.c -o lc4_loader.o

lc4_memory.o:
	# clang -g -c lc4_memory.c -o lc4_memory.o

clean:
	rm -rf *.o

clobber: clean
	rm -rf lc4
