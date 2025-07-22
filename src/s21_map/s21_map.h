#ifndef S21_MAP_H
#define S21_MAP_H

#include <stdexcept>
#include <utility>
#include <vector>

#include "../tree/avl_tree.h"

namespace s21 {
template <typename K, typename T>
class Map {
 public:
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename AVLTree<key_type, mapped_type>::iterator;
  using const_iterator =
      typename AVLTree<key_type, mapped_type>::const_iterator;
  using size_type = size_t;

 private:
  AVLTree<key_type, mapped_type> tree;

 public:
  Map() = default;

  Map(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      tree.insert(item);
    }
  }

  Map(const Map& other) : tree(other.tree) {}

  Map(Map&& other) noexcept : tree(std::move(other.tree)) {}

  ~Map() = default;

  Map& operator=(Map&& other) noexcept {
    if (this != &other) {
      tree = std::move(other.tree);
    }
    return *this;
  }

  T& at(const key_type& key) {
    auto it = tree.find(key);
    if (it == tree.end()) throw std::out_of_range("Key not found");
    return it->second;
  }

  T& operator[](const key_type& key) {
    auto it = tree.find(key);
    if (it == tree.end()) {
      it = tree.insert({key, mapped_type()});
    }
    return it->second;
  }

  iterator begin() { return tree.begin(); }

  const_iterator begin() const { return tree.cbegin(); }

  iterator end() { return tree.end(); }

  const_iterator end() const { return tree.cend(); }

  bool empty() const { return tree.empty(); }

  size_type size() const { return tree.size(); }

  size_type max_size() const { return tree.max_size(); }

  void clear() { tree.clear(); }

  std::pair<iterator, bool> insert(const value_type& value) {
    auto it = tree.find(value.first);
    if (it != tree.end()) return {it, false};
    it = tree.insert(value);
    return {it, true};
  }

  std::pair<iterator, bool> insert(const key_type& key,
                                   const mapped_type& obj) {
    return insert({key, obj});
  }

  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
    auto it = tree.find(key);
    if (it != tree.end()) {
      it->second = obj;
      return {it, false};
    }
    it = tree.insert({key, obj});
    return {it, true};
  }

  void erase(iterator pos) { tree.erase(pos); }

  void swap(Map& other) { std::swap(tree, other.tree); }

  void merge(Map& other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      if (tree.find(it->first) == tree.end()) {
        tree.insert(*it);
      }
    }
    other.clear();
  }

  bool contains(const key_type& key) const {
    return tree.find(key) != tree.end();
  }

  iterator find(const key_type& key) { return tree.find(key); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> results;
    (results.push_back(insert(std::forward<Args>(args))), ...);
    return results;
  }
};

}  // namespace s21

#endif  // S21_MAP_H