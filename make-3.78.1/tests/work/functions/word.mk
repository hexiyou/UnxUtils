string  := word.pl general_test2.pl   FORCE.pl word.pl generic_test.perl MAKEFILES_variable.pl 
string2 := $(string) $(string) $(string) $(string) $(string) $(string) $(string)
string3 := $(string2) $(string2) $(string2) $(string2) $(string2) $(string2) $(string2)
string4 := $(string3) $(string3) $(string3) $(string3) $(string3) $(string3) $(string3)
all: 
	@echo $(words $(string)) 
	@echo $(words $(string4)) 
	@echo $(word 1, $(string)) 
	@echo $(word 100, $(string)) 
	@echo $(word 1, $(string)) 
	@echo $(word 1000, $(string3)) 
	@echo $(wordlist 3, 4, $(string)) 
	@echo $(wordlist 4, 3, $(string)) 
	@echo $(wordlist 1, 6, $(string)) 
	@echo $(wordlist 7, 5, $(string)) 
	@echo $(wordlist 100, 110, $(string)) 
	@echo $(wordlist 7, 10, $(string2)) 
