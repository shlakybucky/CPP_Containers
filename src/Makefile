all: test

test: clean
	cd s21_array && make test
	cd s21_list && make test
	cd s21_map && make test
	cd s21_multiset && make test
	cd s21_queue && make test
	cd s21_set && make test
	cd s21_stack && make test
	cd s21_vector && make test

gcov:
	cd s21_array && make gcov
	cd s21_list && make gcov
	cd s21_map && make gcov
	cd s21_multiset && make gcov
	cd s21_queue && make gcov
	cd s21_set && make gcov
	cd s21_stack && make gcov
	cd s21_vector && make gcov

format_check:
	cd s21_array && make format_check

style:
	cd s21_array && make style

clean:
	cd s21_array && make clean
	cd s21_list && make clean
	cd s21_map && make clean
	cd s21_multiset && make clean
	cd s21_queue && make clean
	cd s21_set && make clean
	cd s21_stack && make clean
	cd s21_vector && make clean