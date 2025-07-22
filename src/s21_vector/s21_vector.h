#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <memory>
#include <utility>

#include "../s21_list/s21_list.h"

namespace s21 {
template <class T>
class vector {
 public:
  // type, переопределения типо
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;
  using const_iterator = const value_type *;
  using size_type = std::size_t;

  // functions
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();

  vector &operator=(const vector &v);
  // assignment operator overload for moving object
  vector &operator=(vector &&v) noexcept;

  // access, публичные методы для доступа к элементам класса
  reference at(size_type pos) {  // bounds check
    if (pos >= size()) throw std::out_of_range("Vector index is out of range");
    return arr_[pos];
  }

  reference operator[](size_type pos) { return arr_[pos]; }

  T &operator[](size_type pos) const { return arr_[pos]; }

  const_reference front() { return arr_[0]; }
  const_reference back() { return arr_[size() - 1]; }
  T *data() { return arr_.get(); }  // прямой доступ к базовому массиву

  // iterator
  iterator begin() { return arr_.get(); }
  iterator end() { return arr_.get() + sz_; }

  // capacity, публ методы для доступа к информации о наполнении контейнера
  bool empty() const;
  size_type size() const { return sz_; }
  size_type max_size() const { return std::numeric_limits<size_type>::max(); }

  void reserve(size_type size);
  size_type capacity() const { return capacity_; }
  void shrink_to_fit();

  // modifiers
  void clear() {
    if (sz_ > 0) sz_ = 0, arr_ = nullptr;
  }

  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other) noexcept;

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    int index = pos - begin();
    iterator last_inserted_pos = nullptr;
    ((last_inserted_pos = insert(begin() + index++, std::forward<Args>(args))),
     ...);
    return last_inserted_pos;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    reserve(sz_ + sizeof...(args));
    ((insert(end(), std::forward<Args>(args))), ...);
  }

 private:
  std::unique_ptr<value_type[]> arr_;
  size_t capacity_;
  size_t sz_;
};

}  // namespace s21

template <typename value_type>
s21::vector<value_type>::vector() : arr_(nullptr), capacity_(0), sz_(0){};

template <typename value_type>
s21::vector<value_type>::vector(size_type n)
    : arr_(nullptr), capacity_(n), sz_(n) {
  arr_ = std::make_unique<value_type[]>(n);
}

template <typename value_type>
s21::vector<value_type>::vector(std::initializer_list<value_type> const &items)
    : arr_(nullptr), capacity_(items.size()), sz_(items.size()) {
  arr_ = std::make_unique<value_type[]>(items.size());
  size_type i = 0;
  for (auto const &item : items) {
    arr_[i++] = item;
  }
}

template <typename value_type>
s21::vector<value_type>::vector(const vector &v)
    : capacity_(v.capacity_), sz_(v.sz_) {
  arr_ = std::make_unique<value_type[]>(v.capacity_);
  for (size_type i = 0; i < sz_; ++i) {
    arr_[i] = v.arr_[i];
  }
}

template <typename value_type>
s21::vector<value_type>::vector(vector &&v)
    : arr_(nullptr), capacity_(0), sz_(0) {
  std::swap(v.capacity_, capacity_);
  std::swap(v.sz_, sz_);
  std::swap(v.arr_, arr_);
}

template <typename value_type>
s21::vector<value_type>::~vector() {}

template <typename value_type>
bool s21::vector<value_type>::empty() const {
  return sz_ == 0;
}

template <typename value_type>
s21::vector<value_type> &s21::vector<value_type>::operator=(const vector &v) {
  if (this != &v) {
    clear();
    if (v.size() > this->capacity()) {
      this->reserve(v.capacity_);
    }
    for (size_t i = 0; i < v.sz_; ++i) {
      arr_[i] = v.arr_[i];
    }
    sz_ = v.sz_;
    capacity_ = v.capacity_;
  }
  return *this;
}

template <typename value_type>
s21::vector<value_type> &s21::vector<value_type>::operator=(
    vector &&v) noexcept {
  if (this != &v) {
    clear();
    this->swap(v);
  }
  return *this;
}

template <typename value_type>
void s21::vector<value_type>::reserve(size_type size) {
  if (size <= capacity_) return;
  std::unique_ptr<value_type[]> temp_arr = std::make_unique<value_type[]>(size);
  for (size_type i = 0; i < sz_; ++i) {
    temp_arr[i] = std::move(arr_[i]);
  }
  arr_ = std::move(temp_arr);
  capacity_ = size;
}

template <typename value_type>
void s21::vector<value_type>::shrink_to_fit() {
  if (sz_ == capacity_) return;
  std::unique_ptr<value_type[]> temp_arr = std::make_unique<value_type[]>(sz_);
  for (size_type i = 0; i < sz_; ++i) {
    temp_arr[i] = std::move(arr_[i]);
  }
  arr_ = std::move(temp_arr);
  capacity_ = sz_;
}

template <typename value_type>
typename s21::vector<value_type>::iterator s21::vector<value_type>::insert(
    iterator pos, const_reference value) {
  if (pos < begin() || pos > begin() + capacity_)
    throw std::out_of_range("Vector index is out of range");
  size_type index = pos - begin();
  if (sz_ + 1 > capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);

  for (size_type i = sz_; i > index; --i) {
    arr_[i] = std::move(arr_[i - 1]);
  }

  arr_[index] = value;
  ++sz_;
  return begin() + index;
}

template <typename value_type>
void s21::vector<value_type>::erase(iterator pos) {
  if (pos < begin() || pos > begin() + capacity_)
    throw std::out_of_range("Vector index is out of range");
  size_type index = pos - begin();

  for (size_type i = index; i < sz_ - 1; ++i) {
    arr_[i] = std::move(arr_[i + 1]);
  }

  --sz_;
}

template <typename value_type>
void s21::vector<value_type>::push_back(const_reference value) {
  size_t one = 1;
  if (sz_ + one > capacity_) {
    reserve(capacity_ * 2);
  }
  arr_[sz_] = value;
  sz_++;
}

template <typename value_type>
void s21::vector<value_type>::pop_back() {
  if (size() > 0) {
    std::unique_ptr<value_type[]> temp_arr =
        std::make_unique<value_type[]>(sz_ - 1);
    for (size_type i = 0; i < sz_ - 1; ++i) {
      temp_arr[i] = std::move(arr_[i]);
    }
    arr_ = std::move(temp_arr);
    --sz_;
  }
}

template <typename value_type>
void s21::vector<value_type>::swap(vector &other) noexcept {
  std::unique_ptr<value_type[]> temp_arr = std::move(arr_);
  size_t temp_sz = sz_;
  size_t temp_capacity = capacity_;

  arr_ = std::move(other.arr_);
  sz_ = other.sz_;
  capacity_ = other.capacity_;

  other.arr_ = std::move(temp_arr);
  other.sz_ = temp_sz;
  other.capacity_ = temp_capacity;
}
