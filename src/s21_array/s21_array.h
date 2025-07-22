#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <memory>
#include <utility>

namespace s21 {
template <class T, std::size_t sz_>
class array {
 public:
  // type, переопределения типо
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;
  using const_iterator = const value_type *;
  using size_type = std::size_t;

  // functions
  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);  // copy
  array(array &&a);       // move
  ~array();

  array &operator=(const array &a);
  // assignment operator overload for moving object
  array &operator=(array &&a) noexcept;

  // access, публичные методы для доступа к элементам класса
  reference at(size_type pos) {  // bounds check
    if (pos >= size()) throw std::out_of_range("Array index is out of range");
    return data_[pos];
  }

  reference operator[](size_type pos) { return data_[pos]; }

  T &operator[](size_type pos) const { return data_[pos]; }

  const_reference front() { return data_[0]; }
  const_reference back() { return data_[size() - 1]; }
  T *data() { return data_; }  // прямой доступ к базовому массиву

  // iterator
  iterator begin() { return data_; }
  iterator end() { return data_ + sz_; }

  const_iterator cbegin() const { return data_; }
  const_iterator cend() const { return data_ + sz_; }

  // capacity, публ методы для доступа к информации о наполнении контейнера
  bool empty() const;
  size_type size() const { return sz_; }
  size_type max_size() const { return sz_; }

  void swap(array &other) noexcept;
  // assigns the given value value to all elements in the container.
  void fill(const_reference value);

 private:
  value_type data_[sz_];
};

}  // namespace s21

template <typename value_type, std::size_t sz_>
s21::array<value_type, sz_>::array() {}

template <typename value_type, std::size_t sz_>
s21::array<value_type, sz_>::array(
    std::initializer_list<value_type> const &items) {
  size_type i = 0;
  for (auto const &item : items) {
    if (i < sz_) {
      data_[i++] = item;
    } else {
      break;
    }
  }
}

template <typename value_type, std::size_t sz_>
s21::array<value_type, sz_>::array(const array &a) {
  for (size_type i = 0; i < sz_; ++i) {
    data_[i] = a.data_[i];
  }
}

template <typename value_type, std::size_t sz_>
s21::array<value_type, sz_>::array(array &&a) {
  for (size_type i = 0; i < sz_; ++i) {
    data_[i] = std::move(a.data_[i]);
  }
}

template <typename value_type, std::size_t sz_>
s21::array<value_type, sz_>::~array() {}

template <typename value_type, std::size_t sz_>
bool s21::array<value_type, sz_>::empty() const {
  return sz_ == 0;
}

template <typename value_type, std::size_t sz_>
s21::array<value_type, sz_> &s21::array<value_type, sz_>::operator=(
    const array &a) {
  if (this != &a) {
    for (size_t i = 0; i < sz_; ++i) {
      data_[i] = a.data_[i];
    }
  }
  return *this;
}

template <typename value_type, std::size_t sz_>
s21::array<value_type, sz_> &s21::array<value_type, sz_>::operator=(
    array &&a) noexcept {
  if (this != &a) {
    this->swap(a);
  }
  return *this;
}

template <typename value_type, std::size_t sz_>
void s21::array<value_type, sz_>::swap(array &other) noexcept {
  for (size_type i = 0; i < sz_; ++i) {
    value_type temp = std::move(data_[i]);
    data_[i] = std::move(other.data_[i]);
    other.data_[i] = std::move(temp);
  }
}

template <typename value_type, std::size_t sz_>
void s21::array<value_type, sz_>::fill(const_reference value) {
  for (size_type i = 0; i < sz_; ++i) {
    data_[i] = value;
  }
}