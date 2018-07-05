VPATH = work
objects = main.o kbd.o commands.o display.o insert.o
edit:  $(objects)
	@echo cc -o edit $(objects)
main.o : main.c defs.h
	@echo cc -c main.c
kbd.o : kbd.c defs.h command.h
	@echo cc -c kbd.c
commands.o : command.c defs.h command.h
	@echo cc -c commands.c
display.o : display.c defs.h buffer.h
	@echo cc -c display.c
insert.o : insert.c defs.h buffer.h
	@echo cc -c insert.c
