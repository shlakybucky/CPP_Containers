#include "s21_set.h"

#include <gtest/gtest.h>

#include <iostream>

TEST(SetTest, DefaultConstructor) {
  s21::Set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(SetTest, InitializerListConstructor) {
  s21::Set<int> s = {1, 2, 3};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(SetTest, CopyConstructor) {
  s21::Set<int> s1 = {1, 2, 3};
  s21::Set<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, MoveConstructor) {
  s21::Set<int> s1 = {1, 2, 3};
  s21::Set<int> s2(std::move(s1));
  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, Insert) {
  s21::Set<int> s;
  auto result1 = s.insert(1);
  EXPECT_TRUE(result1.second);
  EXPECT_EQ(result1.first->first, 1);

  auto result2 = s.insert(2);
  EXPECT_TRUE(result2.second);
  EXPECT_EQ(result2.first->first, 2);

  auto result3 = s.insert(1);
  EXPECT_FALSE(result3.second);
  EXPECT_EQ(result3.first->first, 1);

  EXPECT_EQ(s.size(), 2);
}

TEST(SetTest, Erase) {
  s21::Set<int> s = {1, 2, 3};
  auto it = s.find(2);
  s.erase(it);
  EXPECT_EQ(s.size(), 2);
  EXPECT_FALSE(s.contains(2));
}

TEST(SetTest, Clear) {
  s21::Set<int> s = {1, 2, 3};
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(SetTest, Swap) {
  s21::Set<int> s1 = {1, 2, 3};
  s21::Set<int> s2 = {4, 5, 6};
  s1.swap(s2);

  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, Merge) {
  s21::Set<int> s1 = {1, 2, 3};
  s21::Set<int> s2 = {3, 4, 5};
  s1.merge(s2);

  EXPECT_EQ(s1.size(), 5);
  EXPECT_EQ(s2.size(), 0);
  EXPECT_TRUE(s1.contains(1));
  EXPECT_TRUE(s1.contains(2));
  EXPECT_TRUE(s1.contains(3));
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
}

TEST(SetTest, Find) {
  s21::Set<int> s = {1, 2, 3};
  auto it = s.find(2);
  EXPECT_EQ(it->first, 2);

  it = s.find(4);
  EXPECT_EQ(it, s.end());
}

TEST(SetTest, Contains) {
  s21::Set<int> s = {1, 2, 3};
  EXPECT_TRUE(s.contains(2));
  EXPECT_FALSE(s.contains(4));
}

TEST(SetTest, InsertMany) {
  s21::Set<int> s;
  auto result = s.insert_many(1, 2, 3, 1, 4);

  EXPECT_EQ(s.size(), 4);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(4));

  ASSERT_EQ(result.size(), 5);
  EXPECT_EQ(result[0].first->first, 1);
  EXPECT_TRUE(result[0].second);
  EXPECT_EQ(result[1].first->first, 2);
  EXPECT_TRUE(result[1].second);
  EXPECT_EQ(result[2].first->first, 3);
  EXPECT_TRUE(result[2].second);
  EXPECT_EQ(result[3].first->first, 1);
  EXPECT_FALSE(result[3].second);
  EXPECT_EQ(result[4].first->first, 4);
  EXPECT_TRUE(result[4].second);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}