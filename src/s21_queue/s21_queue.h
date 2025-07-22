#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "../s21_list/s21_list.h"

namespace s21 {
template <class T>
class queue : public s21::list<T> {
 public:
  using value_type = typename s21::list<T>::value_type;
  using reference = typename s21::list<T>::reference;
  using const_reference = typename s21::list<T>::const_reference;
  using size_type = typename s21::list<T>::size_type;

  // constructor and a destructor
  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();

  // operators
  queue &operator=(queue &&q);

  // element access
  const_reference front();
  const_reference back();

  // capacity
  using list<T>::empty;
  using list<T>::size;

  // modifiers
  void push(const_reference value);
  void pop();
  void swap(queue &other);

  // bonus part
  template <typename... Args>
  void insert_many_back(Args &&...args);
};
}  // namespace s21

template <class value_type>
s21::queue<value_type>::queue() : s21::list<value_type>() {}

template <class value_type>
s21::queue<value_type>::queue(std::initializer_list<value_type> const &items)
    : list<value_type>(items) {}

template <class value_type>
s21::queue<value_type>::queue(const queue &q) : s21::list<value_type>(q) {}

template <class value_type>
s21::queue<value_type>::queue(queue &&q)
    : s21::list<value_type>(std::move(q)) {}

template <class value_type>
s21::queue<value_type>::~queue() {
  s21::list<value_type>::clear();
}

template <class value_type>
typename s21::queue<value_type>::queue &s21::queue<value_type>::operator=(
    queue &&q) {
  if (this != &q) {
    list<value_type>::operator=(std::move(q));
  }
  return *this;
}

// element access
template <class value_type>
typename s21::queue<value_type>::const_reference
s21::queue<value_type>::front() {
  return s21::list<value_type>::front();
}

template <class value_type>
typename s21::queue<value_type>::const_reference
s21::queue<value_type>::back() {
  return s21::list<value_type>::back();
}

// modifiers
template <class value_type>
void s21::queue<value_type>::push(const_reference value) {
  s21::list<value_type>::push_back(value);
}

template <class value_type>
void s21::queue<value_type>::pop() {
  s21::list<value_type>::pop_front();
}

template <class value_type>
void s21::queue<value_type>::swap(queue &other) {
  s21::list<value_type>::swap(other);
}

template <class value_type>
template <typename... Args>
void s21::queue<value_type>::insert_many_back(Args &&...args) {
  s21::list<value_type>::insert_many_back(args...);
}

#endif