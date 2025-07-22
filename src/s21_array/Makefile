CC = g++
GCOVFLAGS = -fprofile-arcs -ftest-coverage
CFLAGS = -Wall -Wextra -Werror -std=c++17
TEST = *.cc
LIBFLAGS = -lgtest -lgtest_main
OS = $(shell uname)

ifeq ($(OS), Linux)
	LIBFLAGS = -lsubunit -lpthread -lrt -lm -lgtest -lgtest_main $(GCOVFLAGS)
endif

all: test

test: clean
	$(CC) $(CFLAGS) $(TEST)  $(MYPATH) $(LIBFLAGS) -o report_test
	./report_test

test_coverage: clean
	$(CC) $(CFLAGS) --coverage $(TEST)  $(MYPATH) $(LIBFLAGS) -o report_test
	./report_test

gcov: test_coverage
	@mkdir -p report
	lcov -t ./report_test -o report/report_test.info --no-external -c -d . --ignore-errors mismatch
	genhtml report/report_test.info -o report
	open report/index.html

valgrind: test
	valgrind --tool=memcheck --leak-check=yes ./report_test

leaks: test
	leaks -atExit -- ./report_test

format_check:
	clang-format -style=Google -n -i *.cc *.h

style:
	clang-format -style=Google -i *.cc *.h

clean:
	rm -rf ./report_test ./*.gcno ./*.gcda ./report/