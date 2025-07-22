#include <gtest/gtest.h>

#include "s21_vector.h"

TEST(vector, Constructor) {
  s21::vector<std::string> s21vector;
  ASSERT_EQ(s21vector.capacity(), 0);
  ASSERT_EQ(s21vector.size(), 0);
  ASSERT_TRUE(s21vector.empty());
}

TEST(vector, ConstructorWithSize) {
  s21::vector<std::string> s21vector(5);
  ASSERT_EQ(s21vector.capacity(), 5);
  ASSERT_EQ(s21vector.size(), 5);
  ASSERT_FALSE(s21vector.empty());
}

TEST(vector, ConstructorWithInitializerList) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  ASSERT_EQ(s21vector.capacity(), 5);
  ASSERT_EQ(s21vector.size(), 5);
  ASSERT_FALSE(s21vector.empty());
  for (size_t i = 0; i < s21vector.size(); ++i) {
    ASSERT_EQ(s21vector[i], i + 1);
  }
}

TEST(vector, CopyConstructor) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  s21::vector<int> s21vector2(s21vector);
  ASSERT_EQ(s21vector2.capacity(), s21vector.capacity());
  ASSERT_EQ(s21vector2.size(), s21vector.size());
  ASSERT_FALSE(s21vector2.empty());
  for (size_t i = 0; i < s21vector2.size(); ++i) {
    ASSERT_EQ(s21vector2[i], s21vector[i]);
  }
}

TEST(vector, MoveConstructor) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  s21::vector<int> s21vector2(std::move(s21vector));
  ASSERT_EQ(s21vector.capacity(), 0);
  ASSERT_EQ(s21vector.size(), 0);
  ASSERT_TRUE(s21vector.empty());
  ASSERT_EQ(s21vector2.capacity(), 5);
  ASSERT_EQ(s21vector2.size(), 5);
  ASSERT_FALSE(s21vector2.empty());
  for (size_t i = 0; i < s21vector2.size(); ++i) {
    ASSERT_EQ(s21vector2[i], i + 1);
  }
}

TEST(vector, AssignmentOperatorCopy) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  s21::vector<int> s21vector2;
  s21vector2 = s21vector;
  ASSERT_EQ(s21vector2.capacity(), s21vector.capacity());
  ASSERT_EQ(s21vector2.size(), s21vector.size());
  ASSERT_FALSE(s21vector2.empty());
  for (size_t i = 0; i < s21vector2.size(); ++i) {
    ASSERT_EQ(s21vector2[i], s21vector[i]);
  }
}

TEST(vector, AssignmentOperatorMove) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  s21::vector<int> s21vector2;
  s21vector2 = std::move(s21vector);
  ASSERT_EQ(s21vector.capacity(), 0);
  ASSERT_EQ(s21vector.size(), 0);
  ASSERT_TRUE(s21vector.empty());
  ASSERT_EQ(s21vector2.capacity(), 5);
  ASSERT_EQ(s21vector2.size(), 5);
  ASSERT_FALSE(s21vector2.empty());
  for (size_t i = 0; i < s21vector2.size(); ++i) {
    ASSERT_EQ(s21vector2[i], i + 1);
  }
}

TEST(vector, FrontAndBack) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  ASSERT_EQ(s21vector.front(), 1);
  ASSERT_EQ(s21vector.back(), 5);
}

TEST(vector, Data) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  int *data = s21vector.data();
  for (size_t i = 0; i < s21vector.size(); ++i) {
    ASSERT_EQ(data[i], s21vector[i]);
  }
}

TEST(vector, BeginAndEnd) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  auto begin = s21vector.begin();
  auto end = s21vector.end();
  size_t count = 0;
  for (auto it = begin; it != end; ++it) {
    ASSERT_EQ(*it, s21vector[count]);
    ++count;
  }
}

TEST(vector, MaxSize) {
  s21::vector<int> s21vector;
  // Так как наш класс не использует выделение динамической памяти напрямую,
  // максимальный размер вектора будет зависеть от ограничений операционной
  // системы. Вместо этого, мы можем установить максимальный размер равным
  // максимальному значению size_t.
  ASSERT_EQ(s21vector.max_size(), std::numeric_limits<size_t>::max());
}

TEST(vector, Reserve) {
  s21::vector<int> s21vector;
  s21vector.reserve(100);
  ASSERT_GE(s21vector.capacity(), 100);
}

TEST(vector, ShrinkToFit) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  s21vector.reserve(100);
  s21vector.shrink_to_fit();
  ASSERT_EQ(s21vector.capacity(), 5);
}

TEST(vector, Clear) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  s21vector.clear();
  ASSERT_TRUE(s21vector.empty());
}

TEST(vector, Insert) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  auto it = s21vector.begin() + 2;
  s21vector.insert(it, 10);
  ASSERT_EQ(s21vector[2], 10);
}

TEST(vector, Erase) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  auto it = s21vector.begin() + 2;
  s21vector.erase(it);
  ASSERT_EQ(s21vector[2], 4);
}

TEST(vector, PushBack) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  s21vector.push_back(6);
  ASSERT_EQ(s21vector.back(), 6);
}

TEST(vector, PopBack) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  s21vector.pop_back();
  ASSERT_EQ(s21vector.back(), 4);
}

TEST(vector, InsertMany) {
  s21::vector<int> vec{1, 2, 3};
  vec.insert_many(vec.begin() + 1, 10, 20,
                  30);  // вставляем 10, 20, 30 на позицию после 1
  ASSERT_EQ(vec.size(), 6);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 10);
  ASSERT_EQ(vec[2], 20);
  ASSERT_EQ(vec[3], 30);
  ASSERT_EQ(vec[4], 2);
  ASSERT_EQ(vec[5], 3);
}

TEST(vector, InsertManyBack) {
  s21::vector<int> vec{1, 2, 3};
  vec.insert_many_back(4, 5, 6);  // добавляем 4, 5, 6 в конец
  ASSERT_EQ(vec.size(), 6);
  ASSERT_EQ(vec[3], 4);
  ASSERT_EQ(vec[4], 5);
  ASSERT_EQ(vec[5], 6);
}

TEST(vector, InsertManyEdgeCases) {
  s21::vector<int> vec;
  vec.insert_many_back(1, 2, 3, 4, 5);  // добавляем в пустой вектор
  ASSERT_EQ(vec.size(), 5);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
  ASSERT_EQ(vec[3], 4);
  ASSERT_EQ(vec[4], 5);
}
