CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror 
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

CFILES = main.c strutil.c pruebas_alumno.c testing.c cola.c operaciones.c
HFILES = strutil.h testing.h cola.h operaciones.h

EXEC_S = tp1
PADRON = 102914

GREPFILES = grep.c cola.c
EXEC_GREP = grep

DCFILES = dc.c pila.c strutil.c operaciones.c
EXEC_DC = dc

build_grep: $(GREPFILES)
	$(CC) $(CFLAGS) -o $(EXEC_GREP) $(GREPFILES)

grep: build_grep
	./$(EXEC_GREP)

build_dc: $(DCFILES)
	$(CC) $(CFLAGS) -o $(EXEC_DC) $(DCFILES)

build: $(CFILES)
	$(CC) $(CFLAGS) -o $(EXEC_S) $(CFILES)

run: build
	./$(EXEC_S)

valgrind: build
	valgrind $(VFLAGS) ./$(EXEC_S)

gdb: build
	gdb $(GDBFLAGS) ./$(EXEC_S)

runtime: build
	time ./$(EXEC_S)

clean:
	rm -f *.o $(EXEC_S)

zip:
	zip $(PADRON).zip $(CFILES) $(HFILES)

entregar: build
	$(MAKE) run; test $$? -eq 0
	$(MAKE) valgrind; test $$? -eq 0
	$(MAKE) clean
	zip $(PADRON).zip $(CFILES) $(HFILES)
	@echo "Perfecto, no falla ni pierde memoria"
	@echo "El zip esta listo para entregar"
