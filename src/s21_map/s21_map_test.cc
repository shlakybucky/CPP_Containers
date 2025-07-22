#include "s21_map.h"

#include <gtest/gtest.h>

#include <string>

using namespace s21;

TEST(MapTest, DefaultConstructor) {
  Map<int, std::string> map;
  EXPECT_TRUE(map.empty());
  EXPECT_EQ(map.size(), 0);
}

TEST(MapTest, InitializerListConstructor) {
  Map<int, std::string> map{{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_EQ(map[3], "three");
}

TEST(MapTest, CopyConstructor) {
  Map<int, std::string> map1{{1, "one"}, {2, "two"}};
  Map<int, std::string> map2(map1);
  EXPECT_EQ(map2.size(), 2);
  EXPECT_EQ(map2[1], "one");
  EXPECT_EQ(map2[2], "two");
}

TEST(MapTest, MoveConstructor) {
  Map<int, std::string> map1{{1, "one"}, {2, "two"}};
  Map<int, std::string> map2(std::move(map1));
  EXPECT_EQ(map2.size(), 2);
  EXPECT_EQ(map2[1], "one");
  EXPECT_EQ(map2[2], "two");
  EXPECT_TRUE(map1.empty());
}

TEST(MapTest, Insert) {
  Map<int, std::string> map;
  auto result1 = map.insert({1, "one"});
  EXPECT_TRUE(result1.second);
  EXPECT_EQ(result1.first->second, "one");

  auto result2 = map.insert({2, "two"});
  EXPECT_TRUE(result2.second);
  EXPECT_EQ(result2.first->second, "two");

  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map[2], "two");
}

TEST(MapTest, InsertOrAssign) {
  Map<int, std::string> map;
  auto result1 = map.insert_or_assign(1, "one");
  EXPECT_TRUE(result1.second);
  EXPECT_EQ(result1.first->second, "one");

  auto result2 = map.insert_or_assign(1, "new_one");
  EXPECT_FALSE(result2.second);
  EXPECT_EQ(result2.first->second, "new_one");

  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map[1], "new_one");
}

TEST(MapTest, Erase) {
  Map<int, std::string> map{{1, "one"}, {2, "two"}, {3, "three"}};
  auto it = map.find(2);
  map.erase(it);
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map[3], "three");
}

TEST(MapTest, Swap) {
  Map<int, std::string> map1{{1, "one"}, {2, "two"}};
  Map<int, std::string> map2{{3, "three"}, {4, "four"}};
  map1.swap(map2);
  EXPECT_EQ(map1.size(), 2);
  EXPECT_EQ(map1[3], "three");
  EXPECT_EQ(map1[4], "four");
  EXPECT_EQ(map2.size(), 2);
  EXPECT_EQ(map2[1], "one");
  EXPECT_EQ(map2[2], "two");
}

TEST(MapTest, Merge) {
  Map<int, std::string> map1{{1, "one"}, {2, "two"}};
  Map<int, std::string> map2{{3, "three"}, {4, "four"}};
  map1.merge(map2);
  EXPECT_EQ(map1.size(), 4);
  EXPECT_EQ(map1[1], "one");
  EXPECT_EQ(map1[2], "two");
  EXPECT_EQ(map1[3], "three");
  EXPECT_EQ(map1[4], "four");
  EXPECT_TRUE(map2.empty());
}

TEST(MapTest, Contains) {
  Map<int, std::string> map{{1, "one"}, {2, "two"}};
  EXPECT_TRUE(map.contains(1));
  EXPECT_TRUE(map.contains(2));
  EXPECT_FALSE(map.contains(3));
}

TEST(MapTest, At) {
  Map<int, std::string> map{{1, "one"}, {2, "two"}};
  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map.at(2), "two");
  EXPECT_THROW(map.at(3), std::out_of_range);
}

TEST(MapTest, OperatorBrackets) {
  Map<int, std::string> map;
  map[1] = "one";
  map[2] = "two";
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_EQ(map[3], "");
}

TEST(MapTest, Iterator) {
  Map<int, std::string> map{{1, "one"}, {2, "two"}, {3, "three"}};
  auto it = map.begin();
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, "one");
  ++it;
  EXPECT_EQ(it->first, 2);
  EXPECT_EQ(it->second, "two");
  ++it;
  EXPECT_EQ(it->first, 3);
  EXPECT_EQ(it->second, "three");
  ++it;
  EXPECT_EQ(it, map.end());
}

TEST(MapTest, ConstIterator) {
  const Map<int, std::string> map{{1, "one"}, {2, "two"}, {3, "three"}};
  auto it = map.begin();
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, "one");
  ++it;
  EXPECT_EQ(it->first, 2);
  EXPECT_EQ(it->second, "two");
  ++it;
  EXPECT_EQ(it->first, 3);
  EXPECT_EQ(it->second, "three");
  ++it;
  EXPECT_EQ(it, map.end());
}

TEST(MapTest, InsertMany) {
  s21::Map<int, int> map;

  auto results = map.insert_many(std::make_pair(1, 10), std::make_pair(2, 20),
                                 std::make_pair(3, 30));

  EXPECT_EQ(results.size(), 3);
  for (const auto& result : results) {
    EXPECT_TRUE(result.second);
  }

  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map[1], 10);
  EXPECT_EQ(map[2], 20);
  EXPECT_EQ(map[3], 30);

  results = map.insert_many(std::make_pair(1, 100), std::make_pair(4, 40));

  EXPECT_EQ(results.size(), 2);
  EXPECT_FALSE(results[0].second);
  EXPECT_TRUE(results[1].second);

  EXPECT_EQ(map.size(), 4);
  EXPECT_EQ(map[1], 10);
  EXPECT_EQ(map[4], 40);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}