#include <gtest/gtest.h>

#include <iostream>
#include <list>

#include "s21_list.h"

//////////////////////////////int constructor/////////////////////////////////
TEST(constructors, def_int_1) {
  s21::list<int> l_int;
  ASSERT_TRUE(l_int.empty());
  ASSERT_EQ(l_int.size(), 0U);
}

TEST(constructors, def_int_2) {
  s21::list<int> l_int(5);
  ASSERT_EQ(l_int.front(), 0U);
  ASSERT_EQ(l_int.back(), 0U);
  ASSERT_EQ(l_int.size(), 5U);

  s21::list<int>::ListIterator iter = l_int.begin();
  for (int i = 0; i < 5; i++) {
    ASSERT_EQ(*iter, 0);
    ++iter;
  }
}

TEST(constructors, def_int_3) {
  s21::list<int> l_int{5, 4, 3, 2, 1};
  ASSERT_EQ(l_int.front(), 5U);
  ASSERT_EQ(l_int.back(), 1U);
  ASSERT_EQ(l_int.size(), 5U);

  s21::list<int>::ListIterator iter = l_int.begin();
  for (int i = 5; i > 0; i--) {
    ASSERT_EQ(*iter, i);
    ++iter;
  }
}

TEST(constructors, def_int_4) {
  s21::list<int> l_int_1{5, 4, 3, 2, 1};
  s21::list<int> l_int_2{l_int_1};

  s21::list<int>::ListIterator iter = l_int_2.begin();
  for (int i = 5; i > 0; i--) {
    ASSERT_EQ(*iter, i);
    ++iter;
  }
}

TEST(constructors, def_int_5) {
  s21::list<int> l_int_1{5, 4, 3, 2, 1};
  s21::list<int> l_int_2{std::move(l_int_1)};

  s21::list<int>::ListIterator iter = l_int_2.begin();
  for (int i = 5; i > 0; i--) {
    ASSERT_EQ(*iter, i);
    ++iter;
  }

  ASSERT_TRUE(l_int_1.empty());
  ASSERT_EQ(l_int_1.size(), 0U);
}

//////////////////////////////double constructor/////////////////////////////
TEST(constructors, def_double_1) {
  s21::list<double> l_double;
  ASSERT_TRUE(l_double.empty());
  ASSERT_EQ(l_double.size(), 0U);
}

TEST(constructors, def_double_2) {  // not right
  s21::list<double> l_double(5);
  s21::list<double>::ListIterator iter = l_double.begin();
  for (int i = 5; i > 0; i--) {
    ASSERT_EQ(*iter, 0.0);
    ++iter;
  }
}

TEST(constructors, def_double_3) {
  s21::list<double> l_double{5.55, 4.44, 3.33, 2.22, 1.11};
  ASSERT_EQ(l_double.front(), 5.55);
  ASSERT_EQ(l_double.back(), 1.11);
  ASSERT_EQ(l_double.size(), 5U);

  s21::list<double>::ListIterator iter = l_double.begin();
  ++iter;
  ASSERT_EQ(*iter, 4.44);
  ++iter;
  ASSERT_EQ(*iter, 3.33);
  ++iter;
  ASSERT_EQ(*iter, 2.22);
}

TEST(constructors, def_double_4) {
  s21::list<double> l_double_1{5.55, 4.44, 3.33, 2.22, 1.11};
  s21::list<double> l_double_2{l_double_1};

  s21::list<double>::ListIterator iter = l_double_2.begin();
  ASSERT_EQ(*iter, 5.55);
  ++iter;
  ASSERT_EQ(*iter, 4.44);
  ++iter;
  ASSERT_EQ(*iter, 3.33);
  ++iter;
  ASSERT_EQ(*iter, 2.22);
  ++iter;
  ASSERT_EQ(*iter, 1.11);
}

TEST(constructors, def_double_5) {
  s21::list<double> l_double_1{5.55, 4.44, 3.33, 2.22, 1.11};
  s21::list<double> l_double_2{std::move(l_double_1)};

  s21::list<double>::ListIterator iter = l_double_2.begin();
  ASSERT_EQ(*iter, 5.55);
  ++iter;
  ASSERT_EQ(*iter, 4.44);
  ++iter;
  ASSERT_EQ(*iter, 3.33);
  ++iter;
  ASSERT_EQ(*iter, 2.22);
  ++iter;
  ASSERT_EQ(*iter, 1.11);

  ASSERT_TRUE(l_double_1.empty());
  ASSERT_EQ(l_double_1.size(), 0U);
}

/////////////////////////////string constructor///////////////////////////////
TEST(constructors, def_string_1) {
  s21::list<std::string> l_string;
  ASSERT_TRUE(l_string.empty());
}

TEST(constructors, def_string_2) {
  s21::list<std::string> l_string(5);
  ASSERT_EQ(l_string.size(), 5U);

  s21::list<std::string>::ListIterator iter = l_string.begin();
  for (int i = 5; i > 0; i--) {
    ASSERT_EQ(*iter, "");
    ++iter;
  }
}

TEST(constructors, def_string_3) {
  s21::list<std::string> l_string{"Hello", "Hi", "Hiychiki", "Chao"};
  ASSERT_EQ(l_string.front(), "Hello");
  ASSERT_EQ(l_string.back(), "Chao");
  ASSERT_EQ(l_string.size(), 4U);

  s21::list<std::string>::ListIterator iter = l_string.begin();
  ++iter;
  ASSERT_EQ(*iter, "Hi");
  ++iter;
  ASSERT_EQ(*iter, "Hiychiki");
}

TEST(constructors, def_string_4) {
  s21::list<std::string> l_string_1{"Hello", "Hi", "Hiychiki", "Chao"};
  s21::list<std::string> l_string_2{l_string_1};

  s21::list<std::string>::ListIterator iter = l_string_2.begin();
  ASSERT_EQ(*iter, "Hello");
  ++iter;
  ASSERT_EQ(*iter, "Hi");
  ++iter;
  ASSERT_EQ(*iter, "Hiychiki");
  ++iter;
  ASSERT_EQ(*iter, "Chao");
}

TEST(constructors, def_string_5) {
  s21::list<std::string> l_string_1{"Hi", "Hey", "Hello"};
  s21::list<std::string> l_string_2{std::move(l_string_1)};

  s21::list<std::string>::ListIterator iter = l_string_2.begin();
  ASSERT_EQ(*iter, "Hi");
  ++iter;
  ASSERT_EQ(*iter, "Hey");
  ++iter;
  ASSERT_EQ(*iter, "Hello");

  ASSERT_TRUE(l_string_1.empty());
  ASSERT_EQ(l_string_1.size(), 0U);
}

// compare original list with mine

/////////////////////////////////////empty///////////////////////////////////
TEST(list_empty, empty_int_1) {
  s21::list<int> l_int_1;
  std::list<int> l_int_2;
  EXPECT_EQ(l_int_1.empty(), l_int_2.empty());
}

TEST(list_empty, empty_double_1) {
  s21::list<double> l_double_1;
  std::list<double> l_double_2;
  EXPECT_EQ(l_double_1.empty(), l_double_2.empty());
}

TEST(list_empty, empty_string_1) {
  s21::list<std::string> l_1;
  std::list<std::string> l_2;
  EXPECT_EQ(l_1.empty(), l_2.empty());
}

// size
TEST(list_size, size_int_1) {
  s21::list<int> l_1{1, 2, 3};
  std::list<int> l_2{1, 2, 3};
  EXPECT_EQ(l_1.size(), l_2.size());
}

TEST(list_size, size_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  std::list<double> l_2{1.1, 2.2, 3.3};
  EXPECT_EQ(l_1.size(), l_2.size());
}

TEST(list_size, size_string_1) {
  s21::list<std::string> l_1{"hi", "hi"};
  std::list<std::string> l_2{"hi", "hi"};
  EXPECT_EQ(l_1.size(), l_2.size());
}

// max_size
// TEST(list_max_size, max_size_int_1) {
//   s21::list<int> l_1{1, 2, 3};
//   std::list<int> l_2{1, 2, 3};
//   EXPECT_EQ(l_1.max_size(), l_2.max_size());
// }

// TEST(list_max_size, max_size_double_1) {
//   s21::list<double> l_1{1.1, 2.2, 3.3};
//   std::list<double> l_2{1.1, 2.2, 3.3};
//   EXPECT_EQ(l_1.max_size(), l_2.max_size());
// }

// TEST(list_max_size, max_size_string_1) {
//   s21::list<std::string> l_1{"hi", "hi"};
//   std::list<std::string> l_2{"hi", "hi"};
//   EXPECT_EQ(l_1.max_size(), l_2.max_size());
// }

// clear
TEST(list_clear, clear_int_1) {
  s21::list<int> l_1{1, 2, 3};
  std::list<int> l_2{1, 2, 3};
  l_1.clear();
  l_2.clear();
  EXPECT_EQ(l_1.empty(), l_2.empty());
}

TEST(list_clear, clear_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  std::list<double> l_2{1.1, 2.2, 3.3};
  l_1.clear();
  l_2.clear();
  EXPECT_EQ(l_1.empty(), l_2.empty());
}

TEST(list_clear, clear_string_1) {
  s21::list<std::string> l_1{"hi", "hi"};
  std::list<std::string> l_2{"hi", "hi"};
  l_1.clear();
  l_2.clear();
  EXPECT_EQ(l_1.empty(), l_2.empty());
}

/////////////////////////////////operators////////////////////////////////////

//= with no nullptr
TEST(list_clear, clear_int_1_1) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int> l_2{3, 2, 1};

  s21::list<int>::ListIterator iter_1 = l_1.begin();
  s21::list<int>::ListIterator iter_2 = l_2.begin();

  iter_1 = iter_2;
  EXPECT_EQ(iter_1, iter_2);
}

TEST(list_clear, clear_int_2_2) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int> l_2{3, 2, 1};

  s21::list<int>::ListIterator iter_1 = l_1.begin();
  s21::list<int>::ListIterator iter_2 = l_2.begin();

  iter_1 = iter_2;
  EXPECT_EQ(iter_1, iter_2);
}

TEST(list_clear, clear_double_1_1) {
  s21::list<double> l_1{1, 2, 3};
  s21::list<double> l_2{3, 2, 1};

  s21::list<double>::ListIterator iter_1 = l_1.begin();
  s21::list<double>::ListIterator iter_2 = l_2.begin();

  iter_1 = iter_2;
  EXPECT_EQ(iter_1, iter_2);
}

TEST(list_clear, clear_double_2_2) {
  s21::list<double> l_1{1, 2, 3};
  s21::list<double> l_2{3, 2, 1};

  s21::list<double>::ListIterator iter_1 = l_1.begin();
  s21::list<double>::ListIterator iter_2 = l_2.begin();

  iter_1 = iter_2;
  EXPECT_EQ(iter_1, iter_2);
}

TEST(list_clear, clear_string_1_1) {
  s21::list<std::string> l_1{"hey", "hi", "hello"};
  s21::list<std::string> l_2{"hello", "phphphp", "hiii"};

  s21::list<std::string>::ListIterator iter_1 = l_1.begin();
  s21::list<std::string>::ListIterator iter_2 = l_2.begin();

  iter_1 = iter_2;
  EXPECT_EQ(iter_1, iter_2);
}

TEST(list_clear, clear_string_2_2) {
  s21::list<std::string> l_1{"hey", "hi", "hello"};
  s21::list<std::string> l_2{"hello", "phphphp", "hiii"};

  s21::list<std::string>::ListIterator iter_1 = l_1.begin();
  s21::list<std::string>::ListIterator iter_2 = l_2.begin();

  iter_1 = iter_2;
  EXPECT_EQ(iter_1, iter_2);
}

//////////////////////////////operator++////////////////////////////////

TEST(list_increment, inc_int_1) {
  s21::list<int> l_1{1, 2, 3};

  s21::list<int>::ListIterator iter_1 = l_1.begin();
  iter_1++;
  ASSERT_EQ(*iter_1, 2);
}

TEST(list_increment, inc_int_2) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int>::ListIterator iter_1 = l_1.begin();
  iter_1++;
  iter_1++;
  iter_1++;
  EXPECT_THROW(iter_1++, std::runtime_error);
}

TEST(list_increment, inc_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};

  s21::list<double>::ListIterator iter_1 = l_1.begin();
  iter_1++;
  ASSERT_EQ(*iter_1, 2.2);
}

TEST(list_increment, inc_double_2) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  s21::list<double>::ListIterator iter_1 = l_1.begin();
  iter_1++;
  iter_1++;
  iter_1++;
  EXPECT_THROW(iter_1++, std::runtime_error);
}

TEST(list_increment, inc_string_1) {
  s21::list<std::string> l_1{"pr", "pu", "pa"};
  s21::list<std::string>::ListIterator iter_1 = l_1.begin();
  iter_1++;
  ASSERT_EQ(*iter_1, "pu");
}

TEST(list_increment, inc_string_2) {
  s21::list<std::string> l_1{"pr", "pu", "pa"};
  s21::list<std::string>::ListIterator iter_1 = l_1.begin();
  iter_1++;
  iter_1++;
  iter_1++;
  EXPECT_THROW(iter_1++, std::runtime_error);
}

//////////////////////////////////////operator--///////////////////////////////////////////

TEST(list_decrement, dec_int_1) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int>::ListIterator iter_1 = l_1.end();
  iter_1--;
  ASSERT_EQ(*iter_1, 2);
}

TEST(list_decrement, dec_int_2) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int>::ListIterator iter_1 = l_1.end();
  iter_1--;
  iter_1--;
  iter_1--;
  EXPECT_THROW(iter_1--, std::runtime_error);
}

TEST(list_decrement, dec_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};

  s21::list<double>::ListIterator iter_1 = l_1.end();
  iter_1--;
  ASSERT_EQ(*iter_1, 2.2);
}

TEST(list_decrement, dec_double_2) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  s21::list<double>::ListIterator iter_1 = l_1.end();
  iter_1--;
  iter_1--;
  iter_1--;
  EXPECT_THROW(iter_1--, std::runtime_error);
}

TEST(list_decrement, dec_string_1) {
  s21::list<std::string> l_1{"pr", "pu", "pa"};
  s21::list<std::string>::ListIterator iter_1 = l_1.end();
  iter_1--;
  ASSERT_EQ(*iter_1, "pu");
}

TEST(list_decrement, dec_string_2) {
  s21::list<std::string> l_1{"pr", "pu", "pa"};
  s21::list<std::string>::ListIterator iter_1 = l_1.end();
  iter_1--;
  iter_1--;
  iter_1--;
  EXPECT_THROW(iter_1--, std::runtime_error);
}

////////////////////////////////////operator==////////////////////////////////////////////

TEST(list_eq, eq_int_1) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int>::ListIterator iter_1 = l_1.end();
  s21::list<int>::ListIterator iter_2 = l_1.end();
  ASSERT_TRUE(iter_1 == iter_2);
}

TEST(list_eq, eq_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  s21::list<double>::ListIterator iter_1 = l_1.begin();
  s21::list<double>::ListIterator iter_2 = l_1.begin();
  ASSERT_TRUE(iter_1 == iter_2);
}

TEST(list_eq, eq_string_1) {
  s21::list<std::string> l_1{"pr", "pu", "pa"};
  s21::list<std::string>::ListIterator iter_1 = l_1.begin();
  iter_1++;
  s21::list<std::string>::ListIterator iter_2 = l_1.begin();
  iter_2++;
  ASSERT_TRUE(iter_1 == iter_2);
}

/////////////////////////////////////operator!=///////////////////////////////////////////

TEST(list_not_eq, not_eq_int_1) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int>::ListIterator iter_1 = l_1.end();
  iter_1++;
  s21::list<int>::ListIterator iter_2 = l_1.end();
  ASSERT_TRUE(iter_1 != iter_2);
}

TEST(list_not_eq, not_eq_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  s21::list<double>::ListIterator iter_1 = l_1.begin();
  iter_1++;
  s21::list<double>::ListIterator iter_2 = l_1.begin();
  ASSERT_TRUE(iter_1 != iter_2);
}

TEST(list_not_eq, not_eq_string_1) {
  s21::list<std::string> l_1{"pr", "pu", "pa"};
  s21::list<std::string>::ListIterator iter_1 = l_1.begin();
  iter_1++;
  s21::list<std::string>::ListIterator iter_2 = l_1.begin();
  ASSERT_TRUE(iter_1 != iter_2);
}

////////////////////////////////////operator*////////////////////////////////////////////

TEST(list_deferencing, deferencing_int_1) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int>::ListIterator iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, 1);
  iter_1++;
  ASSERT_EQ(*iter_1, 2);
  iter_1++;
  ASSERT_EQ(*iter_1, 3);
}

TEST(list_deferencing, deferencing_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  s21::list<double>::ListIterator iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, 1.1);
  iter_1++;
  ASSERT_EQ(*iter_1, 2.2);
  iter_1++;
  ASSERT_EQ(*iter_1, 3.3);
}

TEST(list_deferencing, deferencing_string_1) {
  s21::list<std::string> l_1{"pr", "pu", "pa"};
  s21::list<std::string>::ListIterator iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, "pr");
  iter_1++;
  ASSERT_EQ(*iter_1, "pu");
  iter_1++;
  ASSERT_EQ(*iter_1, "pa");
}

///////////////////////////const_reference
/// front()///////////////////////////////////////

TEST(list_front, front_int_1) {
  s21::list<int> l_1{1, 2, 3};
  ASSERT_EQ(l_1.front(), 1);
}

TEST(list_front, front_int_2) {
  s21::list<int> l_1;
  EXPECT_THROW(l_1.front(), std::out_of_range);
}

TEST(list_front, front_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  ASSERT_EQ(l_1.front(), 1.1);
}

TEST(list_front, front_double_2) {
  s21::list<double> l_1;
  EXPECT_THROW(l_1.front(), std::out_of_range);
}

TEST(list_front, front_string_1) {
  s21::list<std::string> l_1{"pr", "pu", "pa"};
  ASSERT_EQ(l_1.front(), "pr");
}

TEST(list_front, front_string_2) {
  s21::list<std::string> l_1;
  EXPECT_THROW(l_1.front(), std::out_of_range);
}

/////////////////////////////////const_reference
/// back()///////////////////////////////////

TEST(list_back, back_int_1) {
  s21::list<int> l_1{1, 2, 3};
  ASSERT_EQ(l_1.back(), 3);
}

TEST(list_back, back_int_2) {
  s21::list<int> l_1;
  EXPECT_THROW(l_1.back(), std::out_of_range);
}

TEST(list_back, back_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  ASSERT_EQ(l_1.back(), 3.3);
}

TEST(list_back, back_double_2) {
  s21::list<double> l_1;
  EXPECT_THROW(l_1.back(), std::out_of_range);
}

TEST(list_back, back_string_1) {
  s21::list<std::string> l_1{"pr", "pu", "pa"};
  ASSERT_EQ(l_1.back(), "pa");
}

TEST(list_back, back_string_2) {
  s21::list<std::string> l_1;
  EXPECT_THROW(l_1.back(), std::out_of_range);
}

////////////////////////////////////iterator
/// begin()/////////////////////////////////////

TEST(list_iterator, begin_int_1) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int>::ListIterator iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, 1);
}

TEST(list_iterator, begin_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  s21::list<double>::ListIterator iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, 1.1);
}

TEST(list_iterator, begin_string_1) {
  s21::list<std::string> l_1{"pr", "pu", "pa"};
  s21::list<std::string>::ListIterator iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, "pr");
}

/////////////////////////////////iterator
/// end()///////////////////////////////////////////

TEST(list_iterator, end_int_1) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int>::ListIterator iter_1 = l_1.end();
  ASSERT_EQ(*iter_1, 3);
}

TEST(list_iterator, end_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  s21::list<double>::ListIterator iter_1 = l_1.end();
  ASSERT_EQ(*iter_1, 3.3);
}

TEST(list_iterator, end_string_1) {
  s21::list<std::string> l_1{"pr", "pu", "pa"};
  s21::list<std::string>::ListIterator iter_1 = l_1.end();
  ASSERT_EQ(*iter_1, "pa");
}

////////////////////////////////////iterator
/// insert///////////////////////////////////////

TEST(list_iterator, insert_int_1) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int>::ListIterator iter_1 = l_1.begin();
  l_1.insert(iter_1, 7);
  iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, 7);
  iter_1++;
  ASSERT_EQ(*iter_1, 1);
}

TEST(list_iterator, insert_int_2) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int>::ListIterator iter_1 = l_1.end();
  l_1.insert(iter_1, 7);
  iter_1 = l_1.end();
  ASSERT_EQ(*iter_1, 7);
  iter_1--;
  ASSERT_EQ(*iter_1, 3);
}

/*TEST(list_iterator, insert_int_3) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int>::ListIterator iter_1 = l_1.begin();
  iter_1++;
  iter_1 = l_1.insert(iter_1, 7);
  iter_1 = l_1.begin();

  ASSERT_EQ(*iter_1, 1);
  iter_1++;
  ASSERT_EQ(*iter_1, 7);
  iter_1++;
  ASSERT_EQ(*iter_1, 2);
}
*/

// TEST(list_iterator, insert_int_3) {
//   s21::list<int> l_1{1, 2, 3};
//   s21::list<int>::ListIterator iter_1 = l_1.begin();
//   iter_1++;
//   iter_1 = l_1.insert(iter_1, 7);  // Обновляем итератор после вставки
//   ASSERT_EQ(*iter_1, 7);
//   iter_1++;
//   ASSERT_EQ(*iter_1, 2);
// }

TEST(list_iterator, insert_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  s21::list<double>::ListIterator iter_1 = l_1.begin();
  l_1.insert(iter_1, 7.7);
  iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, 7.7);
  iter_1++;
  ASSERT_EQ(*iter_1, 1.1);
}

TEST(list_iterator, insert_double_2) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  s21::list<double>::ListIterator iter_1 = l_1.end();
  l_1.insert(iter_1, 7.7);
  iter_1 = l_1.end();
  ASSERT_EQ(*iter_1, 7.7);
  iter_1--;
  ASSERT_EQ(*iter_1, 3.3);
}

// TEST(list_iterator, insert_double_3) {
//   s21::list<double> l_1{1.1, 2.2, 3.3};
//   s21::list<double>::ListIterator iter_1 = l_1.begin();
//   iter_1++;
//   l_1.insert(iter_1, 7.7);
//   iter_1 = l_1.begin();
//   iter_1++;
//   ASSERT_EQ(*iter_1, 7.7);
//   iter_1++;
//   ASSERT_EQ(*iter_1, 1.1);
// }

TEST(list_iterator, insert_string_1) {
  s21::list<std::string> l_1{"pr", "pu", "pa"};
  s21::list<std::string>::ListIterator iter_1 = l_1.begin();
  l_1.insert(iter_1, "piu");
  iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, "piu");
  iter_1++;
  ASSERT_EQ(*iter_1, "pr");
}

TEST(list_iterator, insert_string_2) {
  s21::list<std::string> l_1{"pr", "pu", "pa"};
  s21::list<std::string>::ListIterator iter_1 = l_1.end();
  l_1.insert(iter_1, "piu");
  iter_1 = l_1.end();
  ASSERT_EQ(*iter_1, "piu");
  iter_1--;
  ASSERT_EQ(*iter_1, "pa");
}

// TEST(list_iterator, insert_string_3) {
//   s21::list<std::string> l_1{"pr", "pu", "pa"};
//   s21::list<std::string>::ListIterator iter_1 = l_1.begin();
//   iter_1++;
//   l_1.insert(iter_1, "piu");
//   iter_1 = l_1.begin();
//   iter_1++;
//   ASSERT_EQ(*iter_1, "piu");
//   iter_1--;
//   ASSERT_EQ(*iter_1, "pr");
// }

///////////////////////////////////erase///////////////////////////////////////////////////

TEST(list_erase, erase_int_1) {
  s21::list<int> l_1{7, 1, 2, 3};
  s21::list<int>::ListIterator iter_1 = l_1.begin();
  l_1.erase(iter_1);
  iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, 1);
}

TEST(list_erase, erase_int_2) {
  s21::list<int> l_1{1, 2, 3, 7};
  s21::list<int>::ListIterator iter_1 = l_1.end();
  l_1.erase(iter_1);
  iter_1 = l_1.end();
  ASSERT_EQ(*iter_1, 3);
}

TEST(list_erase, erase_int_3) {
  s21::list<int> l_1{1, 2, 7, 3};
  s21::list<int>::ListIterator iter_1 = l_1.end();
  iter_1--;
  l_1.erase(iter_1);
  iter_1 = l_1.end();
  iter_1--;
  ASSERT_EQ(*iter_1, 2);
}

TEST(list_erase, erase_double_1) {
  s21::list<double> l_1{7.7, 1.1, 2.2, 3.3};
  s21::list<double>::ListIterator iter_1 = l_1.begin();
  l_1.erase(iter_1);
  iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, 1.1);
}

TEST(list_erase, erase_double_2) {
  s21::list<double> l_1{1.1, 2.2, 3.3, 7.7};
  s21::list<double>::ListIterator iter_1 = l_1.end();
  l_1.erase(iter_1);
  iter_1 = l_1.end();
  ASSERT_EQ(*iter_1, 3.3);
}

TEST(list_erase, erase_double_3) {
  s21::list<double> l_1{1.1, 2.2, 7.7, 3.3};
  s21::list<double>::ListIterator iter_1 = l_1.end();
  iter_1--;
  l_1.erase(iter_1);
  iter_1 = l_1.end();
  iter_1--;
  ASSERT_EQ(*iter_1, 2.2);
}

TEST(list_erase, erase_string_1) {
  s21::list<std::string> l_1{"piu", "pr", "pu", "pa"};
  s21::list<std::string>::ListIterator iter_1 = l_1.begin();
  l_1.erase(iter_1);
  iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, "pr");
}

TEST(list_erase, erase_string_2) {
  s21::list<std::string> l_1{"pr", "pu", "pa", "piu"};
  s21::list<std::string>::ListIterator iter_1 = l_1.end();
  l_1.erase(iter_1);
  iter_1 = l_1.end();
  ASSERT_EQ(*iter_1, "pa");
}

TEST(list_erase, erase_string_3) {
  s21::list<std::string> l_1{"pr", "pu", "piu", "pa"};
  s21::list<std::string>::ListIterator iter_1 = l_1.end();
  iter_1--;
  l_1.erase(iter_1);
  iter_1 = l_1.end();
  iter_1--;
  ASSERT_EQ(*iter_1, "pu");
}

////////////////////////////////////push_back//////////////////////////////////////////

TEST(list_push_back, push_back_int_1) {
  s21::list<int> l_1{1, 2, 3};
  l_1.push_back(7);
  ASSERT_EQ(l_1.back(), 7);
}

TEST(list_push_back, push_back_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  l_1.push_back(7.7);
  ASSERT_EQ(l_1.back(), 7.7);
}

TEST(list_push_back, push_back_string_1) {
  s21::list<std::string> l_1{"pr", "pu", "pa"};
  l_1.push_back("piu");
  ASSERT_EQ(l_1.back(), "piu");
}

///////////////////////////////////////pop_back/////////////////////////////////////////

TEST(list_pop_back, pop_back_int_1) {
  s21::list<int> l_1{1, 2, 3, 7};
  l_1.pop_back();
  ASSERT_EQ(l_1.back(), 3);
}

TEST(list_pop_back, pop_back_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3, 7.7};
  l_1.pop_back();
  ASSERT_EQ(l_1.back(), 3.3);
}

TEST(list_pop_back, pop_back_string_1) {
  s21::list<std::string> l_1{"pr", "pu", "pa", "piu"};
  l_1.pop_back();
  ASSERT_EQ(l_1.back(), "pa");
}

//////////////////////////////////////push_front/////////////////////////////////////////

TEST(list_push_front, push_front_int_1) {
  s21::list<int> l_1{1, 2, 3};
  l_1.push_front(7);
  ASSERT_EQ(l_1.front(), 7);
}

TEST(list_push_front, push_front_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  l_1.push_front(7.7);
  ASSERT_EQ(l_1.front(), 7.7);
}

TEST(list_push_front, push_front_string_1) {
  s21::list<std::string> l_1{"pr", "pu", "pa"};
  l_1.push_front("piu");
  ASSERT_EQ(l_1.front(), "piu");
}

/////////////////////////////////////pop_front/////////////////////////////////////////

TEST(list_pop_front, pop_front_int_1) {
  s21::list<int> l_1{7, 1, 2, 3};
  l_1.pop_front();
  ASSERT_EQ(l_1.front(), 1);
}

TEST(list_pop_front, pop_front_double_1) {
  s21::list<double> l_1{7.7, 1.1, 2.2, 3.3};
  l_1.pop_front();
  ASSERT_EQ(l_1.front(), 1.1);
}

TEST(list_pop_front, pop_front_string_1) {
  s21::list<std::string> l_1{"piu", "pr", "pu", "pa"};
  l_1.pop_front();
  ASSERT_EQ(l_1.front(), "pr");
}

//////////////////////////////////////swap////////////////////////////////////////////////

TEST(list_swap, swap_int_1) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int> l_2{4, 5, 6, 7};

  s21::list<int>::ListIterator iter_1 = l_1.begin();
  s21::list<int>::ListIterator iter_11 = l_1.end();
  s21::list<int>::ListIterator iter_2 = l_2.begin();
  s21::list<int>::ListIterator iter_22 = l_2.end();
  s21::list<int>::size_type size_1 = l_1.size();
  s21::list<int>::size_type size_2 = l_2.size();

  l_1.swap(l_2);

  s21::list<int>::ListIterator iter_1_1 = l_1.begin();
  s21::list<int>::ListIterator iter_1_2 = l_1.end();
  s21::list<int>::ListIterator iter_2_1 = l_2.begin();
  s21::list<int>::ListIterator iter_2_2 = l_2.end();

  ASSERT_EQ(l_1.size(), size_2);
  ASSERT_EQ(l_2.size(), size_1);

  ASSERT_EQ(iter_1, iter_2_1);
  ASSERT_EQ(iter_11, iter_2_2);
  ASSERT_EQ(iter_2, iter_1_1);
  ASSERT_EQ(iter_22, iter_1_2);
}

TEST(list_swap, swap_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  s21::list<double> l_2{4.4, 5.5, 6.6, 7.7};

  s21::list<double>::ListIterator iter_1 = l_1.begin();
  s21::list<double>::ListIterator iter_11 = l_1.end();
  s21::list<double>::ListIterator iter_2 = l_2.begin();
  s21::list<double>::ListIterator iter_22 = l_2.end();
  s21::list<double>::size_type size_1 = l_1.size();
  s21::list<double>::size_type size_2 = l_2.size();

  l_1.swap(l_2);

  s21::list<double>::ListIterator iter_1_1 = l_1.begin();
  s21::list<double>::ListIterator iter_1_2 = l_1.end();
  s21::list<double>::ListIterator iter_2_1 = l_2.begin();
  s21::list<double>::ListIterator iter_2_2 = l_2.end();

  ASSERT_EQ(l_1.size(), size_2);
  ASSERT_EQ(l_2.size(), size_1);

  ASSERT_EQ(iter_1, iter_2_1);
  ASSERT_EQ(iter_11, iter_2_2);
  ASSERT_EQ(iter_2, iter_1_1);
  ASSERT_EQ(iter_22, iter_1_2);
}

TEST(list_swap, swap_string_1) {
  s21::list<std::string> l_1{"hello", "hi", "nihao"};
  s21::list<std::string> l_2{"goodbye", "bye", "chao", "aloha"};

  s21::list<std::string>::ListIterator iter_1 = l_1.begin();
  s21::list<std::string>::ListIterator iter_11 = l_1.end();
  s21::list<std::string>::ListIterator iter_2 = l_2.begin();
  s21::list<std::string>::ListIterator iter_22 = l_2.end();
  s21::list<std::string>::size_type size_1 = l_1.size();
  s21::list<std::string>::size_type size_2 = l_2.size();

  l_1.swap(l_2);

  s21::list<std::string>::ListIterator iter_1_1 = l_1.begin();
  s21::list<std::string>::ListIterator iter_1_2 = l_1.end();
  s21::list<std::string>::ListIterator iter_2_1 = l_2.begin();
  s21::list<std::string>::ListIterator iter_2_2 = l_2.end();

  ASSERT_EQ(l_1.size(), size_2);
  ASSERT_EQ(l_2.size(), size_1);

  ASSERT_EQ(iter_1, iter_2_1);
  ASSERT_EQ(iter_11, iter_2_2);
  ASSERT_EQ(iter_2, iter_1_1);
  ASSERT_EQ(iter_22, iter_1_2);
}

////////////////////////////////////////merge////////////////////////////////////////////

TEST(list_merge, merge_int_1) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int> l_2{4, 5, 6, 7};

  l_1.merge(l_2);

  s21::list<int>::ListIterator iter_1 = l_1.begin();

  for (int i = 0; i < 7; i++) {
    ASSERT_EQ(*iter_1, (i + 1));
    iter_1++;
  }

  ASSERT_EQ(l_1.size(), 7);
  ASSERT_TRUE(l_2.empty());
}

TEST(list_merge, merge_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  s21::list<double> l_2{4.4, 5.5, 6.6, 7.7};

  l_1.merge(l_2);

  s21::list<double>::ListIterator iter_1 = l_1.begin();

  ASSERT_EQ(*iter_1, 1.1);
  iter_1++;
  ASSERT_EQ(*iter_1, 2.2);
  iter_1++;
  ASSERT_EQ(*iter_1, 3.3);
  iter_1++;
  ASSERT_EQ(*iter_1, 4.4);
  iter_1++;
  ASSERT_EQ(*iter_1, 5.5);
  iter_1++;
  ASSERT_EQ(*iter_1, 6.6);
  iter_1++;
  ASSERT_EQ(*iter_1, 7.7);

  ASSERT_EQ(l_1.size(), 7);

  ASSERT_TRUE(l_2.empty());
}

TEST(list_merge, merge_string_1) {
  s21::list<std::string> l_1{"a", "c", "b"};
  s21::list<std::string> l_2{"e", "f", "d", "g"};

  l_1.merge(l_2);

  s21::list<std::string>::ListIterator iter_1 = l_1.begin();

  ASSERT_EQ(*iter_1, "a");
  iter_1++;
  ASSERT_EQ(*iter_1, "c");
  iter_1++;
  ASSERT_EQ(*iter_1, "b");
  iter_1++;
  ASSERT_EQ(*iter_1, "e");
  iter_1++;
  ASSERT_EQ(*iter_1, "f");
  iter_1++;
  ASSERT_EQ(*iter_1, "d");
  iter_1++;
  ASSERT_EQ(*iter_1, "g");

  ASSERT_EQ(l_1.size(), 7);

  ASSERT_TRUE(l_2.empty());
}

//////////////////////////////////////splice///////////////////////////////////////////

TEST(list_splice, splice_int_1) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int> l_2{4, 5, 6, 7};

  s21::list<int>::ListIterator iter_1 = l_1.begin();
  iter_1++;

  l_1.splice(iter_1, l_2);

  iter_1 = l_1.begin();

  ASSERT_EQ(*iter_1, 1);
  iter_1++;
  ASSERT_EQ(*iter_1, 4);
  iter_1++;
  ASSERT_EQ(*iter_1, 5);
  iter_1++;
  ASSERT_EQ(*iter_1, 6);
  iter_1++;
  ASSERT_EQ(*iter_1, 7);
  iter_1++;
  ASSERT_EQ(*iter_1, 2);
  iter_1++;
  ASSERT_EQ(*iter_1, 3);

  ASSERT_EQ(l_1.size(), 7);
  ASSERT_EQ(l_2.size(), 0);
}

TEST(list_splice, splice_int_2) {
  s21::list<int> l_1{1, 2, 3};
  s21::list<int> l_2{};
  s21::list<int>::ListIterator iter_1 = l_1.begin();

  EXPECT_THROW(l_1.splice(iter_1, l_2), std::invalid_argument);
}

TEST(list_splice, splice_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  s21::list<double> l_2{4.4, 5.5, 6.6, 7.7};

  s21::list<double>::ListIterator iter_1 = l_1.begin();
  iter_1++;

  l_1.splice(iter_1, l_2);

  iter_1 = l_1.begin();

  ASSERT_EQ(*iter_1, 1.1);
  iter_1++;
  ASSERT_EQ(*iter_1, 4.4);
  iter_1++;
  ASSERT_EQ(*iter_1, 5.5);
  iter_1++;
  ASSERT_EQ(*iter_1, 6.6);
  iter_1++;
  ASSERT_EQ(*iter_1, 7.7);
  iter_1++;
  ASSERT_EQ(*iter_1, 2.2);
  iter_1++;
  ASSERT_EQ(*iter_1, 3.3);

  ASSERT_EQ(l_1.size(), 7);
  ASSERT_EQ(l_2.size(), 0);
}

TEST(list_splice, splice_double_2) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  s21::list<double> l_2{};
  s21::list<double>::ListIterator iter_1 = l_1.begin();

  EXPECT_THROW(l_1.splice(iter_1, l_2), std::invalid_argument);
}

TEST(list_splice, splice_string_1) {
  s21::list<std::string> l_1{"he", "ha", "hi"};
  s21::list<std::string> l_2{"pr", "pu", "po", "piu"};

  s21::list<std::string>::ListIterator iter_1 = l_1.begin();
  iter_1++;

  l_1.splice(iter_1, l_2);

  iter_1 = l_1.begin();

  ASSERT_EQ(*iter_1, "he");
  iter_1++;
  ASSERT_EQ(*iter_1, "pr");
  iter_1++;
  ASSERT_EQ(*iter_1, "pu");
  iter_1++;
  ASSERT_EQ(*iter_1, "po");
  iter_1++;
  ASSERT_EQ(*iter_1, "piu");
  iter_1++;
  ASSERT_EQ(*iter_1, "ha");
  iter_1++;
  ASSERT_EQ(*iter_1, "hi");

  ASSERT_EQ(l_1.size(), 7);
  ASSERT_EQ(l_2.size(), 0);
}

TEST(list_splice, splice_string_2) {
  s21::list<std::string> l_1{"he", "ha", "hi"};
  s21::list<std::string> l_2{};
  s21::list<std::string>::ListIterator iter_1 = l_1.begin();

  EXPECT_THROW(l_1.splice(iter_1, l_2), std::invalid_argument);
}

/////////////////////////////////////reverse/////////////////////////////////////////////

TEST(list_reverse, rev_int_1) {
  s21::list<int> l_1{1, 2, 3};
  l_1.reverse();
  s21::list<int>::ListIterator iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, 3);
  iter_1++;
  ASSERT_EQ(*iter_1, 2);
  iter_1++;
  ASSERT_EQ(*iter_1, 1);
}

TEST(list_reverse, rev_int_2) {
  s21::list<int> l_1{1};
  //   l_1.push_back(2);
  EXPECT_THROW(l_1.reverse(), std::invalid_argument);
}

TEST(list_reverse, rev_double_1) {
  s21::list<double> l_1{1.1, 2.2, 3.3};
  l_1.reverse();
  s21::list<double>::ListIterator iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, 3.3);
  iter_1++;
  ASSERT_EQ(*iter_1, 2.2);
  iter_1++;
  ASSERT_EQ(*iter_1, 1.1);
}

TEST(list_reverse, rev_double_2) {
  s21::list<int> l_1{1};
  //   l_1.push_back(2.2);
  EXPECT_THROW(l_1.reverse(), std::invalid_argument);
}

TEST(list_reverse, rev_string_1) {
  s21::list<std::string> l_1{"hi", "hello", "chao"};
  l_1.reverse();
  s21::list<std::string>::ListIterator iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, "chao");
  iter_1++;
  ASSERT_EQ(*iter_1, "hello");
  iter_1++;
  ASSERT_EQ(*iter_1, "hi");
}

TEST(list_reverse, rev_string_2) {
  s21::list<std::string> l_1{1};
  //   l_1.push_back("hi");
  EXPECT_THROW(l_1.reverse(), std::invalid_argument);
}

////////////////////////////////////////unique///////////////////////////////////////////

TEST(list_unique, unique_int_1) {
  s21::list<int> l_1{1, 1, 1, 2, 2, 3, 3, 3, 3};
  l_1.unique();
  s21::list<int>::ListIterator iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, 1);
  iter_1++;
  ASSERT_EQ(*iter_1, 2);
  iter_1++;
  ASSERT_EQ(*iter_1, 3);
}

TEST(list_unique, unique_int_2) {
  s21::list<int> l_1{1};
  //   l_1.push_back(2);
  EXPECT_THROW(l_1.unique(), std::invalid_argument);
}

TEST(list_unique, unique_double_1) {
  s21::list<double> l_1{1.1, 1.1, 1.1, 2.2, 2.2, 3.3, 3.3, 3.3, 3.3};
  l_1.unique();
  s21::list<double>::ListIterator iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, 1.1);
  iter_1++;
  ASSERT_EQ(*iter_1, 2.2);
  iter_1++;
  ASSERT_EQ(*iter_1, 3.3);
}

TEST(list_unique, unique_double_2) {
  s21::list<double> l_1{1};
  //   l_1.push_back(2.2);
  EXPECT_THROW(l_1.unique(), std::invalid_argument);
}

TEST(list_unique, unique_string_1) {
  s21::list<std::string> l_1{"hi", "hi", "hello", "hello", "chao", "chao"};
  l_1.unique();
  s21::list<std::string>::ListIterator iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, "hi");
  iter_1++;
  ASSERT_EQ(*iter_1, "hello");
  iter_1++;
  ASSERT_EQ(*iter_1, "chao");
}

TEST(list_unique, unique_string_2) {
  s21::list<std::string> l_1{};
  l_1.push_back("hello");
  EXPECT_THROW(l_1.unique(), std::invalid_argument);
}

///////////////////////////////////////////sort//////////////////////////////////////////

TEST(list_sort, sort_int_1) {
  s21::list<int> l_1{3, 1, 4, 2, 5};
  l_1.sort();
  s21::list<int>::ListIterator iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, 1);
  iter_1++;
  ASSERT_EQ(*iter_1, 2);
  iter_1++;
  ASSERT_EQ(*iter_1, 3);
  iter_1++;
  ASSERT_EQ(*iter_1, 4);
  iter_1++;
  ASSERT_EQ(*iter_1, 5);
}

TEST(list_sort, sort_double_1) {
  s21::list<double> l_1{3.3, 1.1, 4.4, 2.2, 5.5};
  l_1.sort();
  s21::list<double>::ListIterator iter_1 = l_1.begin();
  ASSERT_EQ(*iter_1, 1.1);
  iter_1++;
  ASSERT_EQ(*iter_1, 2.2);
  iter_1++;
  ASSERT_EQ(*iter_1, 3.3);
  iter_1++;
  ASSERT_EQ(*iter_1, 4.4);
  iter_1++;
  ASSERT_EQ(*iter_1, 5.5);
}

// TEST(list_sort, sort_string_1) {
//   s21::list<std::string> l_1{"h", "hhhh", "hh", "hhhhh", "hhh"};
//   l_1.sort();
//   s21::list<std::string>::ListIterator iter_1 = l_1.begin();
//   ASSERT_EQ(*iter_1, "h");
//   iter_1++;
//   ASSERT_EQ(*iter_1, "hh");
//   iter_1++;
//   ASSERT_EQ(*iter_1, "hhh");
//   iter_1++;
//   ASSERT_EQ(*iter_1, "hhhh");
//   iter_1++;
//   ASSERT_EQ(*iter_1, "hhhhh");
// }

// TEST(list_sort, sort_string_2) {
//   s21::list<std::string> l_1{"h", "aa", "hhh", "bb"};
//   l_1.sort();
//   s21::list<std::string>::ListIterator iter_1 = l_1.begin();
//   ASSERT_EQ(*iter_1, "aa");
//   iter_1++;
//   ASSERT_EQ(*iter_1, "bb");
//   iter_1++;
//   ASSERT_EQ(*iter_1, "h");
//   iter_1++;
//   ASSERT_EQ(*iter_1, "hhh");
// }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}