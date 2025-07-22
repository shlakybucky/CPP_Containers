CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -g
TEST_FLAGS = -o test -lgtest
OS = $(shell uname -s)

ifeq ($(OS), Linux)
	TEST_FLAGS += -lpthread
endif

all: test

test: clean
	$(CXX) $(CXXFLAGS) s21_multiset_test.cc $(TEST_FLAGS)
	./test

gcov: clean
	$(CXX) --coverage $(CXXFLAGS) s21_multiset_test.cc $(TEST_FLAGS)
	./test
	@lcov -t "test" -o s21_test.info --no-external -c -d . --ignore-errors mismatch
	@genhtml -o report s21_test.info
	@open ./report/index.html

style:
	clang-format -style=Google -i *.cc *.h
clean:
	@rm -f test
	@rm -rf *.dSYM
	@rm -f *.gcda
	@rm -f *.gcno
	@rm -f s21_test.info
	@rm -rf report
	@rm -f *.o *.a