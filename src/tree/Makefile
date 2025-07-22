CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror
GTEST_DIR = /usr/local/lib

all: test

test: clean tree_test
	./tree_test

tree_test:
	$(CXX) $(CXXFLAGS) -I$(GTEST_DIR)/include -L$(GTEST_DIR) -lgtest -lgtest_main -pthread tree_test.cc -o tree_test

clean:
	rm -f tree_test