#ifndef S21_STACK_H
#define S21_STACK_H

#include "../s21_list/s21_list.h"

namespace s21 {

template <class T>
class stack : public s21::list<T> {
 public:
  using value_type = typename s21::list<T>::value_type;
  using reference = typename s21::list<T>::reference;
  using const_reference = typename s21::list<T>::const_reference;
  using size_type = typename s21::list<T>::size_type;

  // constructors and a destructor
  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();

  // operators
  stack &operator=(stack &&s);

  // access to the top element
  const_reference top();

  // capacity
  using list<T>::empty;
  using list<T>::size;

  // modifiers
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  // bonus
  template <typename... Args>
  void insert_many_back(Args &&...args);
};

}  // namespace s21

// constructors and a destructor
template <class value_type>
s21::stack<value_type>::stack() : s21::list<value_type>() {}

template <class value_type>
s21::stack<value_type>::stack(std::initializer_list<value_type> const &items)
    : list<value_type>(items) {}

template <class value_type>
s21::stack<value_type>::stack(const stack &s) : s21::list<value_type>(s) {}

template <class value_type>
s21::stack<value_type>::stack(stack &&s)
    : s21::list<value_type>(std::move(s)) {}

template <class value_type>
s21::stack<value_type>::~stack() {
  s21::list<value_type>::clear();
}

template <class value_type>
typename s21::stack<value_type>::stack &s21::stack<value_type>::operator=(
    stack &&s) {
  if (this != &s) {
    list<value_type>::operator=(std::move(s));
  }
  return *this;
}

// general methods
template <class value_type>
typename s21::stack<value_type>::const_reference s21::stack<value_type>::top() {
  return s21::list<value_type>::back();
}

template <class value_type>
void s21::stack<value_type>::push(const_reference value) {
  s21::list<value_type>::push_back(value);
}

template <class value_type>
void s21::stack<value_type>::pop() {
  s21::list<value_type>::pop_back();
}

template <class value_type>
void s21::stack<value_type>::swap(stack &other) {
  s21::list<value_type>::swap(other);
}

template <class value_type>
template <typename... Args>
void s21::stack<value_type>::insert_many_back(Args &&...args) {
  s21::list<value_type>::insert_many_back(args...);
}

#endif
#ifndef S21_STACK_H
#define S21_STACK_H

#include "../s21_list/s21_list.h"

namespace s21 {

template <class T>
class stack : public s21::list<T> {
 public:
  using value_type = typename s21::list<T>::value_type;
  using reference = typename s21::list<T>::reference;
  using const_reference = typename s21::list<T>::const_reference;
  using size_type = typename s21::list<T>::size_type;

  // constructors and a destructor
  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();

  // operators
  stack &operator=(stack &&s);

  // access to the top element
  const_reference top();

  // capacity
  using list<T>::empty;
  using list<T>::size;

  // modifiers
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  // bonus
  template <typename... Args>
  void insert_many_back(Args &&...args);
};

}  // namespace s21

// constructors and a destructor
template <class value_type>
s21::stack<value_type>::stack() : s21::list<value_type>() {}

template <class value_type>
s21::stack<value_type>::stack(std::initializer_list<value_type> const &items)
    : list<value_type>(items) {}

template <class value_type>
s21::stack<value_type>::stack(const stack &s) : s21::list<value_type>(s) {}

template <class value_type>
s21::stack<value_type>::stack(stack &&s)
    : s21::list<value_type>(std::move(s)) {}

template <class value_type>
s21::stack<value_type>::~stack() {
  s21::list<value_type>::clear();
}

template <class value_type>
typename s21::stack<value_type>::stack &s21::stack<value_type>::operator=(
    stack &&s) {
  if (this != &s) {
    list<value_type>::operator=(std::move(s));
  }
  return *this;
}

// general methods
template <class value_type>
typename s21::stack<value_type>::const_reference s21::stack<value_type>::top() {
  return s21::list<value_type>::back();
}

template <class value_type>
void s21::stack<value_type>::push(const_reference value) {
  s21::list<value_type>::push_back(value);
}

template <class value_type>
void s21::stack<value_type>::pop() {
  s21::list<value_type>::pop_back();
}

template <class value_type>
void s21::stack<value_type>::swap(stack &other) {
  s21::list<value_type>::swap(other);
}

template <class value_type>
template <typename... Args>
void s21::stack<value_type>::insert_many_back(Args &&...args) {
  s21::list<value_type>::insert_many_back(args...);
}

#endif