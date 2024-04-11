CFLAGS= -lstdc++ -std=c++17 -Wall -Werror -Wextra
TEST= -lgtest test.cc
NAME_TEST=-o tests
CC=gcc

all: install

install:
	cd Calc && qmake && make && make clean && rm -rf MakeFile
	open Calc/UI.app

open:
	open Calc/UI.app

uninstall:
	rm -rf Calc/UI.app
	rm -rf Calc/.qmake.stash

clean:
	rm -rf tests
	rm -rf Archive_Calc_v2.0
	rm -rf Archive_Calc_v2.0.tgz

dvi:
	open dvi.html

dist:
	rm -rf Archive_Calc_v2.0/
	mkdir Archive_Calc_v2.0/
	mv ./Calc/UI.app Archive_Calc_v2.0/
	tar cvzf Archive_Calc_v2.0.tgz Archive_Calc_v2.0/
	rm -rf Archive_Calc_v2.0/

tests: clean
	$(CC) $(CFLAGS) Calc/model_calc.cc $(TEST) $(NAME_TEST)
	./tests