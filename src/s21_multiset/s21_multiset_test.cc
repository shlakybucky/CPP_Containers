#include "s21_multiset.h"

#include <gtest/gtest.h>

TEST(MultisetTest, InitializerListConstructor) {
  s21::Multiset<int, int> ms{{1, 0}, {2, 0}, {2, 0}, {3, 0}, {3, 0}, {3, 0}};
  EXPECT_EQ(ms.size(), 6);
  EXPECT_FALSE(ms.empty());
}

TEST(MultisetTest, Insert) {
  s21::Multiset<int, int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);
  ms.insert(3);
  ms.insert(3);
  ms.insert(3);

  EXPECT_EQ(ms.size(), 6);
  EXPECT_EQ(ms.count(1), 1);
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(3), 3);
}

TEST(MultisetTest, Erase) {
  s21::Multiset<int, int> ms{{1, 0}, {2, 0}, {2, 0}, {3, 0}, {3, 0}, {3, 0}};
  auto it = ms.find(2);
  ms.erase(it);
  EXPECT_EQ(ms.size(), 5);
  EXPECT_EQ(ms.count(2), 1);

  it = ms.find(3);
  ms.erase(it);
  EXPECT_EQ(ms.size(), 4);
  EXPECT_EQ(ms.count(3), 2);
}

TEST(MultisetTest, Find) {
  s21::Multiset<int, int> ms{{1, 0}, {2, 0}, {2, 0}, {3, 0}, {3, 0}, {3, 0}};
  auto it = ms.find(2);
  EXPECT_NE(it, ms.end());
  EXPECT_EQ(it->first, 2);

  it = ms.find(4);
  EXPECT_EQ(it, ms.end());
}

TEST(MultisetTest, Iteration) {
  s21::Multiset<int, int> ms{{1, 0}, {2, 0}, {2, 0}, {3, 0}, {3, 0}, {3, 0}};
  std::vector<int> expected = {1, 2, 2, 3, 3, 3};
  std::vector<int> actual;

  for (auto it = ms.begin(); it != ms.end(); ++it) {
    actual.push_back(it->first);
  }

  EXPECT_EQ(actual, expected);
}

TEST(MultisetTest, Clear) {
  s21::Multiset<int, int> ms{{1, 0}, {2, 0}, {2, 0}, {3, 0}, {3, 0}, {3, 0}};
  ms.clear();
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);
}

TEST(MultisetTest, Swap) {
  s21::Multiset<int, int> ms1{{1, 0}, {2, 0}, {2, 0}};
  s21::Multiset<int, int> ms2{{3, 0}, {3, 0}, {3, 0}};

  ms1.swap(ms2);

  EXPECT_EQ(ms1.size(), 3);
  EXPECT_EQ(ms2.size(), 3);
  EXPECT_EQ(ms1.count(3), 3);
  EXPECT_EQ(ms2.count(2), 2);
}

TEST(MultisetTest, Merge) {
  s21::Multiset<int, int> ms1{{1, 0}, {2, 0}, {2, 0}};
  s21::Multiset<int, int> ms2{{3, 0}, {3, 0}, {3, 0}};

  ms1.merge(ms2);

  EXPECT_EQ(ms1.size(), 6);
  EXPECT_EQ(ms2.size(), 0);
  EXPECT_EQ(ms1.count(1), 1);
  EXPECT_EQ(ms1.count(2), 2);
  EXPECT_EQ(ms1.count(3), 3);
}

TEST(MultisetTest, EqualRange) {
  s21::Multiset<int, int> ms{{1, 0}, {2, 0}, {2, 0}, {3, 0}, {3, 0}, {3, 0}};
  auto range = ms.equal_range(2);
  int count = 0;

  for (auto it = range.first; it != range.second; ++it) {
    count++;
  }

  EXPECT_EQ(count, 2);
}

TEST(MultisetTest, LowerBound) {
  s21::Multiset<int, int> ms{{1, 0}, {2, 0}, {2, 0}, {3, 0}, {3, 0}, {3, 0}};
  auto it = ms.lower_bound(2);
  EXPECT_EQ(it->first, 2);

  it = ms.lower_bound(4);
  EXPECT_EQ(it, ms.cend());
}

TEST(MultisetTest, UpperBound) {
  s21::Multiset<int, int> ms{{1, 0}, {2, 0}, {2, 0}, {3, 0}, {3, 0}, {3, 0}};
  auto it = ms.upper_bound(2);
  EXPECT_EQ(it->first, 3);

  it = ms.upper_bound(4);
  EXPECT_EQ(it, ms.cend());
}

TEST(MultisetTest, InsertMany) {
  s21::Multiset<int, int> ms;

  auto result = ms.insert_many(std::make_pair(1, 2), std::make_pair(2, 3),
                               std::make_pair(3, 4));

  for (const auto& pair : result) {
    std::cout << "Inserted: " << pair.first->first << ", " << pair.first->second
              << " - " << (pair.second ? "Success" : "Failure") << std::endl;
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}