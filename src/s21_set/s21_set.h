#ifndef S21_SET_H
#define S21_SET_H

#include <initializer_list>
#include <utility>
#include <vector>

#include "../tree/avl_tree.h"

namespace s21 {

template <typename K>
class Set {
 public:
  using key_type = K;
  using value_type = K;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename AVLTree<key_type, bool>::iterator;
  using const_iterator = typename AVLTree<key_type, bool>::const_iterator;
  using size_type = size_t;

 private:
  AVLTree<key_type, bool> tree;

 public:
  Set() = default;

  Set(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }

  Set(const Set& s) : tree(s.tree) {}

  Set(Set&& s) noexcept : tree(std::move(s.tree)) {}

  ~Set() = default;

  Set& operator=(Set&& s) noexcept {
    if (this != &s) {
      tree = std::move(s.tree);
    }
    return *this;
  }

  iterator begin() { return tree.begin(); }

  iterator end() { return tree.end(); }

  const_iterator cbegin() const { return tree.cbegin(); }

  const_iterator cend() const { return tree.cend(); }

  bool empty() const { return tree.empty(); }

  size_type size() const { return tree.size(); }

  size_type max_size() const { return tree.max_size(); }

  void clear() { tree.clear(); }

  std::pair<iterator, bool> insert(const value_type& value) {
    auto it = tree.find(value);
    if (it != tree.end()) {
      return {it, false};
    } else {
      it = tree.insert({value, true});
      return {it, true};
    }
  }

  void erase(iterator pos) { tree.erase(pos); }

  void swap(Set& other) { std::swap(tree, other.tree); }

  void merge(Set& other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(it->first);
    }
    other.clear();
  }

  iterator find(const key_type& key) const { return tree.find(key); }

  bool contains(const key_type& key) const {
    return tree.find(key) != tree.end();
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> result;
    result.reserve(sizeof...(args));

    auto insert_helper = [&](const value_type& value) {
      auto [it, inserted] = insert(value);
      result.emplace_back(it, inserted);
    };

    (insert_helper(std::forward<Args>(args)), ...);

    return result;
  }
};

}  // namespace s21

#endif  // S21_SET_H