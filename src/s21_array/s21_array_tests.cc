#include <gtest/gtest.h>

#include "./s21_array.h"

TEST(ARRAY, ConstructorInitializerList) {
  s21::array<int, 3> myArray = {1, 2, 3};
  EXPECT_EQ(myArray[0], 1);
  EXPECT_EQ(myArray[1], 2);
  EXPECT_EQ(myArray[2], 3);
}

TEST(ARRAY, CopyConstructor) {
  s21::array<int, 3> sourceArray = {4, 5, 6};
  s21::array<int, 3> myArray(sourceArray);
  EXPECT_EQ(myArray[0], 4);
  EXPECT_EQ(myArray[1], 5);
  EXPECT_EQ(myArray[2], 6);
}

TEST(ARRAY, MoveConstructor) {
  s21::array<int, 3> sourceArray = {7, 8, 9};
  s21::array<int, 3> myArray(std::move(sourceArray));
  EXPECT_EQ(myArray[0], 7);
  EXPECT_EQ(myArray[1], 8);
  EXPECT_EQ(myArray[2], 9);
}

TEST(ARRAY, CopyAssignmentOperator) {
  s21::array<int, 3> sourceArray = {10, 11, 12};
  s21::array<int, 3> myArray = {1, 2, 3};
  myArray = sourceArray;
  EXPECT_EQ(myArray[0], 10);
  EXPECT_EQ(myArray[1], 11);
  EXPECT_EQ(myArray[2], 12);
}

TEST(ARRAY, MoveAssignmentOperator) {
  s21::array<int, 3> sourceArray = {13, 14, 15};
  s21::array<int, 3> myArray = {4, 5, 6};
  myArray = std::move(sourceArray);
  EXPECT_EQ(myArray[0], 13);
  EXPECT_EQ(myArray[1], 14);
  EXPECT_EQ(myArray[2], 15);
}

TEST(ArrayTest, AtMethod) {
  s21::array<int, 3> myArray = {1, 2, 3};
  EXPECT_EQ(myArray.at(0), 1);
  EXPECT_EQ(myArray.at(1), 2);
  EXPECT_EQ(myArray.at(2), 3);

  EXPECT_THROW(myArray.at(3), std::out_of_range);
}

TEST(ARRAY, IndexOperator) {
  s21::array<int, 3> myArray = {4, 5, 6};
  EXPECT_EQ(myArray[0], 4);
  EXPECT_EQ(myArray[1], 5);
  EXPECT_EQ(myArray[2], 6);
}

TEST(ARRAY, FrontMethod) {
  s21::array<int, 3> myArray = {7, 8, 9};
  EXPECT_EQ(myArray.front(), 7);
}

TEST(ARRAY, BackMethod) {
  s21::array<int, 3> myArray = {10, 11, 12};
  EXPECT_EQ(myArray.back(), 12);
}

TEST(ARRAY, DataMethod) {
  s21::array<int, 3> myArray = {13, 14, 15};
  const int* dataArray = myArray.data();
  EXPECT_EQ(dataArray[0], 13);
  EXPECT_EQ(dataArray[1], 14);
  EXPECT_EQ(dataArray[2], 15);
}

TEST(ARRAY, BeginEndMethods) {
  s21::array<int, 3> myArray = {1, 2, 3};
  auto it = myArray.begin();
  EXPECT_EQ(*it, 1);

  it = myArray.end();
  EXPECT_NE(it, myArray.begin());
}

TEST(ARRAY, CBeginCEndMethods) {
  const s21::array<int, 3> myArray = {4, 5, 6};
  auto it = myArray.cbegin();
  EXPECT_EQ(*it, 4);

  it = myArray.cend();
  EXPECT_NE(it, myArray.cbegin());
}

TEST(ARRAY, EmptyMethod) {
  s21::array<int, 3> myArray;
  EXPECT_FALSE(myArray.empty());

  myArray = {7, 8, 9};
  EXPECT_FALSE(myArray.empty());
}

TEST(ARRAY, SizeMethod) {
  s21::array<int, 3> myArray = {10, 11, 12};
  EXPECT_EQ(myArray.size(), 3);
}

TEST(ARRAY, MaxSizeMethod) {
  s21::array<int, 3> myArray = {13, 14, 15};
  EXPECT_EQ(myArray.max_size(), 3);
}

TEST(ARRAY, SwapMethod) {
  s21::array<int, 3> myArray1 = {16, 17, 18};
  s21::array<int, 3> myArray2 = {19, 20, 21};
  myArray1.swap(myArray2);

  EXPECT_EQ(myArray1[0], 19);
  EXPECT_EQ(myArray1[1], 20);
  EXPECT_EQ(myArray1[2], 21);

  EXPECT_EQ(myArray2[0], 16);
  EXPECT_EQ(myArray2[1], 17);
  EXPECT_EQ(myArray2[2], 18);
}

TEST(ARRAY, FillMethod) {
  s21::array<int, 3> myArray;
  myArray.fill(22);

  EXPECT_EQ(myArray[0], 22);
  EXPECT_EQ(myArray[1], 22);
  EXPECT_EQ(myArray[2], 22);
}
