#include <gtest/gtest.h>

#include <iostream>

#include "s21_queue.h"

//////////////////////////////int constructor/////////////////////////////////
TEST(constructors, def_int_1) {
  s21::queue<int> l_int;
  ASSERT_TRUE(l_int.empty());
  ASSERT_EQ(l_int.size(), 0U);
}

TEST(constructors, def_int_2) {
  s21::queue<int> l_int{5, 4, 3, 2, 1};
  ASSERT_EQ(l_int.front(), 5);
  ASSERT_EQ(l_int.size(), 5U);
}

TEST(constructors, def_int_4) {
  s21::queue<int> l_int_1{5, 4, 3, 2, 1};
  s21::queue<int> l_int_2{l_int_1};

  ASSERT_EQ(l_int_2.front(), 5);
  ASSERT_EQ(l_int_2.size(), 5U);
}

TEST(constructors, def_int_5) {
  s21::queue<int> l_int_1{5, 4, 3, 2, 1};
  s21::queue<int> l_int_2{std::move(l_int_1)};

  ASSERT_EQ(l_int_2.front(), 5);
  ASSERT_EQ(l_int_2.size(), 5U);
  ASSERT_TRUE(l_int_1.empty());
  ASSERT_EQ(l_int_1.size(), 0U);
}

//////////////////////////////double constructor/////////////////////////////
TEST(constructors, def_double_1) {
  s21::queue<double> l_double;
  ASSERT_TRUE(l_double.empty());
  ASSERT_EQ(l_double.size(), 0U);
}

TEST(constructors, def_double_3) {
  s21::queue<double> l_double{5.55, 4.44, 3.33, 2.22, 1.11};
  ASSERT_EQ(l_double.front(), 5.55);
  ASSERT_EQ(l_double.size(), 5U);
}

TEST(constructors, def_double_4) {
  s21::queue<double> l_double_1{5.55, 4.44, 3.33, 2.22, 1.11};
  s21::queue<double> l_double_2{l_double_1};
  ASSERT_EQ(l_double_2.front(), 5.55);
  ASSERT_EQ(l_double_2.size(), 5U);
}

TEST(constructors, def_double_5) {
  s21::queue<double> l_double_1{5.55, 4.44, 3.33, 2.22, 1.11};
  s21::queue<double> l_double_2{std::move(l_double_1)};
  ASSERT_EQ(l_double_2.front(), 5.55);
  ASSERT_EQ(l_double_2.size(), 5U);
  ASSERT_TRUE(l_double_1.empty());
  ASSERT_EQ(l_double_1.size(), 0U);
}

/////////////////////////////string constructor///////////////////////////////
TEST(constructors, def_string_1) {
  s21::queue<std::string> l_string;
  ASSERT_TRUE(l_string.empty());
}

TEST(constructors, def_string_3) {
  s21::queue<std::string> l_string{"Hello", "Hi", "Hiychiki", "Chao"};
  ASSERT_EQ(l_string.front(), "Hello");
  ASSERT_EQ(l_string.size(), 4U);
}

TEST(constructors, def_string_4) {
  s21::queue<std::string> l_string_1{"Hello", "Hi", "Hiychiki", "Chao"};
  s21::queue<std::string> l_string_2{l_string_1};
  ASSERT_EQ(l_string_2.front(), "Hello");
  ASSERT_EQ(l_string_2.size(), 4U);
}

TEST(constructors, def_string_5) {
  s21::queue<std::string> l_string_1{"Hi", "Hey", "Hello"};
  s21::queue<std::string> l_string_2{std::move(l_string_1)};
  ASSERT_EQ(l_string_2.front(), "Hi");
  ASSERT_EQ(l_string_2.size(), 3U);
  ASSERT_TRUE(l_string_1.empty());
  ASSERT_EQ(l_string_1.size(), 0U);
}

/////////////////////////////////////empty///////////////////////////////////
TEST(queue_empty, empty_int_1) {
  s21::queue<int> l_1;
  ASSERT_TRUE(l_1.empty());
}

TEST(queue_empty, empty_double_1) {
  s21::queue<double> l_1;
  ASSERT_TRUE(l_1.empty());
}

TEST(queue_empty, empty_string_1) {
  s21::queue<std::string> l_1;
  ASSERT_TRUE(l_1.empty());
}

////////////////////////////////// size///////////////////////////////////////
TEST(queue_size, size_int_1) {
  s21::queue<int> l_1{1, 2, 3};
  EXPECT_EQ(l_1.size(), 3);
}

TEST(queue_size, size_double_1) {
  s21::queue<double> l_1{1.1, 2.2, 3.3};
  EXPECT_EQ(l_1.size(), 3);
}

TEST(queue_size, size_string_1) {
  s21::queue<std::string> l_1{"hi", "hi"};
  EXPECT_EQ(l_1.size(), 2);
}
/////////////////////////////////operator=////////////////////////////////////

//= with no nullptr
TEST(queue_assign, ass_int_1) {
  s21::queue<int> l_1{1, 2, 3};
  s21::queue<int> l_2{6, 5, 4};
  l_1 = std::move(l_2);
  EXPECT_EQ(l_1.front(), 6);
  EXPECT_EQ(l_1.size(), 3);
}

TEST(queue_assign, ass_double_1) {
  s21::queue<double> l_1{1.1, 2.2, 3.3};
  s21::queue<double> l_2{6.6, 5.5, 4.4};
  l_1 = std::move(l_2);
  EXPECT_EQ(l_1.front(), 6.6);
  EXPECT_EQ(l_1.size(), 3);
}

TEST(queue_assign, ass_string_1_1) {
  s21::queue<std::string> l_1{"hey", "hi", "hello"};
  s21::queue<std::string> l_2{"hello", "phphphp", "hiii"};

  l_1 = std::move(l_2);
  EXPECT_EQ(l_1.front(), "hello");
  EXPECT_EQ(l_1.size(), 3);
}

///////////////////////////const_reference_front()///////////////////////////////////////

TEST(queue_front, front_int_1) {
  s21::queue<int> l_1{1, 2, 3};
  ASSERT_EQ(l_1.front(), 1);
}

TEST(queue_front, front_double_1) {
  s21::queue<double> l_1{1.1, 2.2, 3.3};
  ASSERT_EQ(l_1.front(), 1.1);
}

TEST(queue_front, front_string_1) {
  s21::queue<std::string> l_1{"pr", "pu", "pa"};
  ASSERT_EQ(l_1.front(), "pr");
}

///////////////////////////const_reference_back()///////////////////////////////////////

TEST(queue_back, back_int_1) {
  s21::queue<int> l_1{1, 2, 3};
  ASSERT_EQ(l_1.back(), 3);
}

TEST(queue_back, back_double_1) {
  s21::queue<double> l_1{1.1, 2.2, 3.3};
  ASSERT_EQ(l_1.back(), 3.3);
}

TEST(queue_front, back_string_1) {
  s21::queue<std::string> l_1{"pr", "pu", "pa"};
  ASSERT_EQ(l_1.back(), "pa");
}

////////////////////////////////////push//////////////////////////////////////////

TEST(queue_push, push_int_1) {
  s21::queue<int> l_1{1, 2, 3};
  l_1.push(7);
  ASSERT_EQ(l_1.front(), 1);
  ASSERT_EQ(l_1.back(), 7);
}

TEST(queue_push, push_double_1) {
  s21::queue<double> l_1{1.1, 2.2, 3.3};
  l_1.push(7.7);
  ASSERT_EQ(l_1.front(), 1.1);
  ASSERT_EQ(l_1.back(), 7.7);
}

TEST(queue_push, push_string_1) {
  s21::queue<std::string> l_1{"pr", "pu", "pa"};
  l_1.push("piu");
  ASSERT_EQ(l_1.front(), "pr");
  ASSERT_EQ(l_1.back(), "piu");
}

///////////////////////////////////////pop/////////////////////////////////////////

TEST(queue_pop, pop_int_1) {
  s21::queue<int> l_1{1, 2, 3, 7};
  l_1.pop();
  ASSERT_EQ(l_1.size(), 3);
  ASSERT_EQ(l_1.front(), 2);
}

TEST(queue_pop, pop_double_1) {
  s21::queue<double> l_1{1.1, 2.2, 3.3, 7.7};
  l_1.pop();
  ASSERT_EQ(l_1.size(), 3);
  ASSERT_EQ(l_1.front(), 2.2);
}

TEST(queue_pop, pop_string_1) {
  s21::queue<std::string> l_1{"pr", "pu", "pa", "piu"};
  l_1.pop();
  ASSERT_EQ(l_1.size(), 3);
  ASSERT_EQ(l_1.front(), "pu");
}

//////////////////////////////////////swap////////////////////////////////////////////////

TEST(queue_swap, swap_int_1) {
  s21::queue<int> l_1{1, 2, 3};
  s21::queue<int> l_2{4, 5, 6, 7};

  s21::queue<int>::size_type size_1 = l_1.size();
  s21::queue<int>::size_type size_2 = l_2.size();

  l_1.swap(l_2);

  ASSERT_EQ(l_1.size(), size_2);
  ASSERT_EQ(l_2.size(), size_1);
  ASSERT_EQ(l_1.front(), 4);
  ASSERT_EQ(l_1.back(), 7);
  ASSERT_EQ(l_2.front(), 1);
  ASSERT_EQ(l_2.back(), 3);
}

TEST(queue_swap, swap_double_1) {
  s21::queue<double> l_1{1.1, 2.2, 3.3};
  s21::queue<double> l_2{4.4, 5.5, 6.6, 7.7};

  s21::queue<double>::size_type size_1 = l_1.size();
  s21::queue<double>::size_type size_2 = l_2.size();

  l_1.swap(l_2);

  ASSERT_EQ(l_1.size(), size_2);
  ASSERT_EQ(l_2.size(), size_1);
  ASSERT_EQ(l_1.front(), 4.4);
  ASSERT_EQ(l_1.back(), 7.7);
  ASSERT_EQ(l_2.front(), 1.1);
  ASSERT_EQ(l_2.back(), 3.3);
}

TEST(queue_swap, swap_string_1) {
  s21::queue<std::string> l_1{"hello", "hi", "nihao"};
  s21::queue<std::string> l_2{"goodbye", "bye", "chao", "aloha"};

  s21::queue<std::string>::size_type size_1 = l_1.size();
  s21::queue<std::string>::size_type size_2 = l_2.size();

  l_1.swap(l_2);

  ASSERT_EQ(l_1.size(), size_2);
  ASSERT_EQ(l_2.size(), size_1);
  ASSERT_EQ(l_1.back(), "aloha");
  ASSERT_EQ(l_2.back(), "nihao");
  ASSERT_EQ(l_1.front(), "goodbye");
  ASSERT_EQ(l_2.front(), "hello");
}

/////////////////////////////insert_many/////////////////////////////////
TEST(queue_insert_many_back, insert_int_1) {
  s21::queue<int> l_1({1, 2, 3});
  l_1.insert_many_back(4, 5, 6);

  EXPECT_TRUE(l_1.back() == 6);

  EXPECT_TRUE(l_1.front() == 1);
  l_1.pop();
  EXPECT_TRUE(l_1.front() == 2);
  l_1.pop();
  EXPECT_TRUE(l_1.front() == 3);
  l_1.pop();
  EXPECT_TRUE(l_1.front() == 4);
  l_1.pop();
  EXPECT_TRUE(l_1.front() == 5);
  l_1.pop();
  EXPECT_TRUE(l_1.front() == 6);
}

TEST(queue_insert_many_back, insert_double_1) {
  s21::queue<double> l_1({1.1, 2.2, 3.3});
  l_1.insert_many_back(4.4, 5.5, 6.6);

  EXPECT_TRUE(l_1.back() == 6.6);

  EXPECT_TRUE(l_1.front() == 1.1);
  l_1.pop();
  EXPECT_TRUE(l_1.front() == 2.2);
  l_1.pop();
  EXPECT_TRUE(l_1.front() == 3.3);
  l_1.pop();
  EXPECT_TRUE(l_1.front() == 4.4);
  l_1.pop();
  EXPECT_TRUE(l_1.front() == 5.5);
  l_1.pop();
  EXPECT_TRUE(l_1.front() == 6.6);
}

TEST(queue_insert_many_back, insert_string_1) {
  s21::queue<std::string> l_1{"hi", "hello", "aloha"};
  l_1.insert_many_back("po", "pi", "pu");

  EXPECT_TRUE(l_1.back() == "pu");

  EXPECT_TRUE(l_1.front() == "hi");
  l_1.pop();
  EXPECT_TRUE(l_1.front() == "hello");
  l_1.pop();
  EXPECT_TRUE(l_1.front() == "aloha");
  l_1.pop();
  EXPECT_TRUE(l_1.front() == "po");
  l_1.pop();
  EXPECT_TRUE(l_1.front() == "pi");
  l_1.pop();
  EXPECT_TRUE(l_1.front() == "pu");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}