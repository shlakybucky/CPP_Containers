#include <gtest/gtest.h>

#include <iostream>

#include "s21_stack.h"

//////////////////////////////int constructor/////////////////////////////////
TEST(constructors, def_int_1) {
  s21::stack<int> l_int;
  ASSERT_TRUE(l_int.empty());
  ASSERT_EQ(l_int.size(), 0U);
}

TEST(constructors, def_int_2) {
  s21::stack<int> l_int{5, 4, 3, 2, 1};
  ASSERT_EQ(l_int.top(), 1);
  ASSERT_EQ(l_int.size(), 5U);
}

TEST(constructors, def_int_4) {
  s21::stack<int> l_int_1{5, 4, 3, 2, 1};
  s21::stack<int> l_int_2{l_int_1};

  ASSERT_EQ(l_int_2.top(), 1);
  ASSERT_EQ(l_int_2.size(), 5U);
}

TEST(constructors, def_int_5) {
  s21::stack<int> l_int_1{5, 4, 3, 2, 1};
  s21::stack<int> l_int_2{std::move(l_int_1)};

  ASSERT_EQ(l_int_2.top(), 1);
  ASSERT_EQ(l_int_2.size(), 5U);
  ASSERT_TRUE(l_int_1.empty());
  ASSERT_EQ(l_int_1.size(), 0U);
}

//////////////////////////////double constructor/////////////////////////////
TEST(constructors, def_double_1) {
  s21::stack<double> l_double;
  ASSERT_TRUE(l_double.empty());
  ASSERT_EQ(l_double.size(), 0U);
}

TEST(constructors, def_double_3) {
  s21::stack<double> l_double{5.55, 4.44, 3.33, 2.22, 1.11};
  ASSERT_EQ(l_double.top(), 1.11);
  ASSERT_EQ(l_double.size(), 5U);
}

TEST(constructors, def_double_4) {
  s21::stack<double> l_double_1{5.55, 4.44, 3.33, 2.22, 1.11};
  s21::stack<double> l_double_2{l_double_1};
  ASSERT_EQ(l_double_2.top(), 1.11);
  ASSERT_EQ(l_double_2.size(), 5U);
}

TEST(constructors, def_double_5) {
  s21::stack<double> l_double_1{5.55, 4.44, 3.33, 2.22, 1.11};
  s21::stack<double> l_double_2{std::move(l_double_1)};
  ASSERT_EQ(l_double_2.top(), 1.11);
  ASSERT_EQ(l_double_2.size(), 5U);
  ASSERT_TRUE(l_double_1.empty());
  ASSERT_EQ(l_double_1.size(), 0U);
}

/////////////////////////////string constructor///////////////////////////////
TEST(constructors, def_string_1) {
  s21::stack<std::string> l_string;
  ASSERT_TRUE(l_string.empty());
}

TEST(constructors, def_string_3) {
  s21::stack<std::string> l_string{"Hello", "Hi", "Hiychiki", "Chao"};
  ASSERT_EQ(l_string.top(), "Chao");
  ASSERT_EQ(l_string.size(), 4U);
}

TEST(constructors, def_string_4) {
  s21::stack<std::string> l_string_1{"Hello", "Hi", "Hiychiki", "Chao"};
  s21::stack<std::string> l_string_2{l_string_1};
  ASSERT_EQ(l_string_2.top(), "Chao");
  ASSERT_EQ(l_string_2.size(), 4U);
}

TEST(constructors, def_string_5) {
  s21::stack<std::string> l_string_1{"Hi", "Hey", "Hello"};
  s21::stack<std::string> l_string_2{std::move(l_string_1)};
  ASSERT_EQ(l_string_2.top(), "Hello");
  ASSERT_EQ(l_string_2.size(), 3U);
  ASSERT_TRUE(l_string_1.empty());
  ASSERT_EQ(l_string_1.size(), 0U);
}

/////////////////////////////////////empty///////////////////////////////////
TEST(stack_empty, empty_int_1) {
  s21::stack<int> l_1;
  ASSERT_TRUE(l_1.empty());
}

TEST(stack_empty, empty_double_1) {
  s21::stack<double> l_1;
  ASSERT_TRUE(l_1.empty());
}

TEST(stack_empty, empty_string_1) {
  s21::stack<std::string> l_1;
  ASSERT_TRUE(l_1.empty());
}

// size
TEST(stack_size, size_int_1) {
  s21::stack<int> l_1{1, 2, 3};
  EXPECT_EQ(l_1.size(), 3);
}

TEST(stack_size, size_double_1) {
  s21::stack<double> l_1{1.1, 2.2, 3.3};
  EXPECT_EQ(l_1.size(), 3);
}

TEST(stack_size, size_string_1) {
  s21::stack<std::string> l_1{"hi", "hi"};
  EXPECT_EQ(l_1.size(), 2);
}
/////////////////////////////////operator=////////////////////////////////////

//= with no nullptr
TEST(stack_assign, ass_int_1) {
  s21::stack<int> l_1{1, 2, 3};
  s21::stack<int> l_2{6, 5, 4};
  l_1 = std::move(l_2);
  EXPECT_EQ(l_1.top(), 4);
}

TEST(stack_assign, ass_double_1) {
  s21::stack<double> l_1{1.1, 2.2, 3.3};
  s21::stack<double> l_2{6.6, 5.5, 4.4};
  l_1 = std::move(l_2);
  EXPECT_EQ(l_1.top(), 4.4);
}

TEST(stack_assign, ass_string_1_1) {
  s21::stack<std::string> l_1{"hey", "hi", "hello"};
  s21::stack<std::string> l_2{"hello", "phphphp", "hiii"};

  l_1 = std::move(l_2);
  EXPECT_EQ(l_1.top(), "hiii");
}

///////////////////////////const_reference_top()///////////////////////////////////////

TEST(stack_front, front_int_1) {
  s21::stack<int> l_1{1, 2, 3};
  ASSERT_EQ(l_1.top(), 3);
}

TEST(stack_front, front_double_1) {
  s21::stack<double> l_1{1.1, 2.2, 3.3};
  ASSERT_EQ(l_1.top(), 3.3);
}

TEST(stack_front, front_string_1) {
  s21::stack<std::string> l_1{"pr", "pu", "pa"};
  ASSERT_EQ(l_1.top(), "pa");
}

////////////////////////////////////push//////////////////////////////////////////

TEST(stack_push_back, push_back_int_1) {
  s21::stack<int> l_1{1, 2, 3};
  l_1.push(7);
  ASSERT_EQ(l_1.top(), 7);
}

TEST(stack_push_back, push_back_double_1) {
  s21::stack<double> l_1{1.1, 2.2, 3.3};
  l_1.push(7.7);
  ASSERT_EQ(l_1.top(), 7.7);
}

TEST(stack_push_back, push_back_string_1) {
  s21::stack<std::string> l_1{"pr", "pu", "pa"};
  l_1.push("piu");
  ASSERT_EQ(l_1.top(), "piu");
}

///////////////////////////////////////pop/////////////////////////////////////////

TEST(stack_pop_back, pop_back_int_1) {
  s21::stack<int> l_1{1, 2, 3, 7};
  l_1.pop();
  ASSERT_EQ(l_1.top(), 3);
}

TEST(stack_pop_back, pop_back_double_1) {
  s21::stack<double> l_1{1.1, 2.2, 3.3, 7.7};
  l_1.pop();
  ASSERT_EQ(l_1.top(), 3.3);
}

TEST(stack_pop_back, pop_back_string_1) {
  s21::stack<std::string> l_1{"pr", "pu", "pa", "piu"};
  l_1.pop();
  ASSERT_EQ(l_1.top(), "pa");
}

//////////////////////////////////////swap////////////////////////////////////////////////

TEST(stack_swap, swap_int_1) {
  s21::stack<int> l_1{1, 2, 3};
  s21::stack<int> l_2{4, 5, 6, 7};

  s21::stack<int>::size_type size_1 = l_1.size();
  s21::stack<int>::size_type size_2 = l_2.size();

  l_1.swap(l_2);

  ASSERT_EQ(l_1.size(), size_2);
  ASSERT_EQ(l_2.size(), size_1);
  ASSERT_EQ(l_1.top(), 7);
  ASSERT_EQ(l_2.top(), 3);
}

TEST(stack_swap, swap_double_1) {
  s21::stack<double> l_1{1.1, 2.2, 3.3};
  s21::stack<double> l_2{4.4, 5.5, 6.6, 7.7};

  s21::stack<double>::size_type size_1 = l_1.size();
  s21::stack<double>::size_type size_2 = l_2.size();

  l_1.swap(l_2);

  ASSERT_EQ(l_1.size(), size_2);
  ASSERT_EQ(l_2.size(), size_1);
  ASSERT_EQ(l_1.top(), 7.7);
  ASSERT_EQ(l_2.top(), 3.3);
}

TEST(stack_swap, swap_string_1) {
  s21::stack<std::string> l_1{"hello", "hi", "nihao"};
  s21::stack<std::string> l_2{"goodbye", "bye", "chao", "aloha"};

  s21::stack<std::string>::size_type size_1 = l_1.size();
  s21::stack<std::string>::size_type size_2 = l_2.size();

  l_1.swap(l_2);

  ASSERT_EQ(l_1.size(), size_2);
  ASSERT_EQ(l_2.size(), size_1);
  ASSERT_EQ(l_1.top(), "aloha");
  ASSERT_EQ(l_2.top(), "nihao");
}

/////////////////////////////insert_many/////////////////////////////////
TEST(stack_insert_many_back, insert_int_1) {
  s21::stack<int> l_1({1, 2, 3});
  l_1.insert_many_back(4, 5, 6);

  EXPECT_TRUE(l_1.top() == 6);
  l_1.pop();
  EXPECT_TRUE(l_1.top() == 5);
  l_1.pop();
  EXPECT_TRUE(l_1.top() == 4);
  l_1.pop();
  EXPECT_TRUE(l_1.top() == 3);
  l_1.pop();
  EXPECT_TRUE(l_1.top() == 2);
  l_1.pop();
  EXPECT_TRUE(l_1.top() == 1);
}

TEST(stack_insert_many_back, insert_double_1) {
  s21::stack<double> l_1({1.1, 2.2, 3.3});
  l_1.insert_many_back(4.4, 5.5, 6.6);

  EXPECT_TRUE(l_1.top() == 6.6);
  l_1.pop();
  EXPECT_TRUE(l_1.top() == 5.5);
  l_1.pop();
  EXPECT_TRUE(l_1.top() == 4.4);
  l_1.pop();
  EXPECT_TRUE(l_1.top() == 3.3);
  l_1.pop();
  EXPECT_TRUE(l_1.top() == 2.2);
  l_1.pop();
  EXPECT_TRUE(l_1.top() == 1.1);
}

TEST(stack_insert_many_back, insert_string_1) {
  s21::stack<std::string> l_1{"hi", "hello", "aloha"};
  l_1.insert_many_back("po", "pi", "pu");

  EXPECT_TRUE(l_1.top() == "pu");
  l_1.pop();
  EXPECT_TRUE(l_1.top() == "pi");
  l_1.pop();
  EXPECT_TRUE(l_1.top() == "po");
  l_1.pop();
  EXPECT_TRUE(l_1.top() == "aloha");
  l_1.pop();
  EXPECT_TRUE(l_1.top() == "hello");
  l_1.pop();
  EXPECT_TRUE(l_1.top() == "hi");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}