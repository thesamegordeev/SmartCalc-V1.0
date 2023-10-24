CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -Wno-unused-parameter
SOURCE_BACKEND = backend/*.c
SOURCE_TEST = ./tests/SmartCalc_test.c
OBJ_FILES = *.o
PROJECT_NAME = SmartCalc
TST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit

all: install

install_quit:
	@mkdir build
	@cmake -B build
	@cd build && make
	@cp build/SmartCalc .

install: 
	@make -s install_quit
	@bash tools/runner.sh

uninstall: clean
	@rm $(PROJECT_NAME)
	@echo "Uninstalled"

reinstall:
	@make uninstall
	@make install 

dvi:
	@cd tools && doxygen
	@open tools/html/index.html 

dist:
	@make -s install_quit
	@tar -cf $(PROJECT_NAME).tar $(PROJECT_NAME)
	@rm -rf build tools/html && rm $(PROJECT_NAME)
	@echo "Done"
# EXTRACTING: tar -xvf SmartCalc.tar 

clean:
	@rm -rf build
	@rm -rf tools/html
	@rm -rf *.gc* tests/SmartCalc_test tests/*.gc*
	@rm -rf test_output gcov_report index.html
	@rm -rf $(PROJECT_NAME).a 

test: clean smartcalc.a
	@$(CC) $(CFLAGS) $(SOURCE_TEST) $(TST_LIBS) $(PROJECT_NAME).a -o tests/$(PROJECT_NAME)_test
	@cd tests && ./$(PROJECT_NAME)_test
	
gcov_report: add_coverage test
	@mkdir gcov_report
	@gcovr -r . --exclude=tests --html --html-details -s -o gcov_report/report.html
	@open gcov_report/report.html
	@make clean

smartcalc.a: $(SOURCE_BACKEND)
	@$(CC) $(CFLAGS) -c $(SOURCE_BACKEND)
	@ar -rcs $(PROJECT_NAME).a $(OBJ_FILES)
	@rm -f $(OBJ_FILES)

add_coverage:
	@$(eval CFLAGS+=--coverage)

clang-format:
	@cp ../materials/linters/.clang-format ./backend
	@cd backend && clang-format -n *.*
