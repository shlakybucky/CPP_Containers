CC = g++
FLAGS = -Wall -Werror -Wextra -std=c++17 -pedantic -g
OS := $(shell uname)
GSRC = $(wildcard *.cc)
GOBJ = $(GSRC:.cc=.o)
GFLAGS = -o s21_list_tests -lgtest

ifeq ($(OS), Linux)
	OPEN_CMD = open
	ADD_LIB += -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
endif

ifeq ($(OS), Darwin)
	OPEN_CMD = open
	ADD_LIB = -lcheck
endif

all: style check test clean

test:
	$(CC) $(FLAGS) $(GSRC) $(GFLAGS) $(ADD_LIB)
	./s21_list_tests

gcov:
	$(CC) $(FLAGS) --coverage $(GSRC) $(GFLAGS) $(ADD_LIB) -o s21_list_tests
	./s21_list_tests
	lcov -t "stest"  --ignore-errors mismatch,inconsistent -o test_cov.info --no-external -c -d .
	mkdir -p report
	mv test_cov.info report/coverage.info
	genhtml -q report/coverage.info -o report
	$(OPEN_CMD) ./report/index.html

lcov:
	brew install lcov

brew:
	cd
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

gtest:
	brew install googletest

style:
	clang-format -style=Google -i $(SRC) *.h $(GTEST_CC) *.h *.cc

check:
	clang-format -style=Google -n $(SRC) *.h $(GTEST_CC) *.h *.cc

clean:
	@rm -f *.gc*
	@rm -f coverage.info
	@rm -rf report
	@rm -f $(GOBJ) *.a
	@rm -rf s21_list_tests.dSYM
	@rm s21_list_tests

.PHONY: all test gcov clean style check