#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include <utility>
#include <vector>

#include "../tree/avl_tree.h"

namespace s21 {

template <typename K, typename V>
class Multiset {
 public:
  using key_type = K;
  using value_type = std::pair<const K, V>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename AVLTree<K, V>::iterator;
  using const_iterator = typename AVLTree<K, V>::const_iterator;
  using size_type = size_t;

 private:
  AVLTree<K, V> tree;

 public:
  Multiset() = default;

  Multiset(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item.first, item.second);
    }
  }

  Multiset(const Multiset& ms) : tree(ms.tree) {}

  Multiset(Multiset&& ms) noexcept : tree(std::move(ms.tree)) {}

  ~Multiset() = default;

  Multiset& operator=(Multiset&& ms) noexcept {
    if (this != &ms) {
      tree = std::move(ms.tree);
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

  iterator insert(const K& key, const V& value = V()) {
    auto node = tree.find(key);
    if (node != tree.end()) {
      node.current->count++;
      return node;
    } else {
      return tree.insert({key, value});
    }
  }

  iterator erase(iterator pos) { return tree.erase(pos); }

  void swap(Multiset& other) { std::swap(tree, other.tree); }

  void merge(Multiset& other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(it->first, it->second);
    }
    other.clear();
  }

  size_type count(const K& key) const {
    auto node = tree.find(key);
    return node != tree.end() ? node.current->count : 0;
  }

  iterator find(const K& key) const { return tree.find(key); }

  bool contains(const K& key) const { return tree.find(key) != tree.end(); }

  std::pair<const_iterator, const_iterator> equal_range(const K& key) const {
    const_iterator lower = lower_bound(key);
    const_iterator upper = upper_bound(key);
    return {lower, upper};
  }

  const_iterator lower_bound(const K& key) const {
    const_iterator it = cbegin();
    for (; it != cend(); ++it) {
      if (it->first >= key) {
        break;
      }
    }
    return it;
  }

  const_iterator upper_bound(const K& key) const {
    const_iterator it = cbegin();
    for (; it != cend(); ++it) {
      if (it->first > key) {
        break;
      }
    }
    return it;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> result;
    result.reserve(sizeof...(args));

    auto insert_helper = [&](const value_type& value) {
      auto it = insert(value.first, value.second);
      result.emplace_back(it, true);
    };

    (insert_helper(std::forward<Args>(args)), ...);

    return result;
  }
};

}  // namespace s21

#endif  // S21_MULTISET_H