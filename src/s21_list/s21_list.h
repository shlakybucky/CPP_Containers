#ifndef S21_LIST_H
#define S21_LIST_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>

namespace s21 {
template <class T>
class list {
 public:
  using size_type = std::size_t;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;

  class ListIterator;
  class ListConstIterator;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  // list constrcutors
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l);
  ~list();

  // list element access
  const_reference front();
  const_reference back();

  // methods
  void clear();
  void pop_front();
  void pop_back();
  void swap(list& other);
  void merge(list& other);
  void reverse();
  void unique();
  void sort();
  bool empty() const;
  void copy(const list& l);
  void swap(list&& l);
  void erase(iterator pos);
  void push_back(const_reference value);
  void push_front(const_reference value);
  iterator insert(iterator pos, const_reference value);
  void splice(const_iterator pos, list& other);
  size_type size() const { return Size; }
  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(Node);
  }
  list<value_type>& operator=(list&& l) noexcept;

  // Iterator
  iterator begin() { return iterator(head); }
  iterator end() { return iterator(tail); }
  const_iterator begin() const { return const_iterator(head); }
  const_iterator end() const { return const_iterator(tail); }

  // bonus part
  template <typename... Args>
  void insert_many_front(Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

 private:
  class Node {
   public:
    Node* pNext;
    Node* pPrev;
    value_type value;
    Node(value_type val = value_type(), Node* next = nullptr,
         Node* prev = nullptr)
        : pNext{next}, pPrev{prev}, value{val} {}
  };
  Node* head;
  Node* tail;
  size_type Size;

 public:
  class ListIterator {
   private:
    Node* ptr;

   public:
    // constructors and a destructor
    ListIterator() : ptr{nullptr} {}
    ListIterator(Node* other_ptr) : ptr{other_ptr} {}
    ListIterator(const ListIterator& other) : ptr(other.ptr) {}

    // operators
    ListIterator& operator=(const ListIterator& other);
    list<value_type>& operator=(list&& l) noexcept;
    bool operator!=(const ListIterator& other) const;
    bool operator==(const ListIterator& other) const;
    ListIterator& operator++();
    ListIterator operator++(int);
    ListIterator& operator--();
    ListIterator operator--(int);
    value_type& operator*();

    friend class list;
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator(ListIterator other) : ListIterator(other) {}
    const_reference operator*() const { return ListIterator::operator*(); }
  };
};
}  // namespace s21

// contructors and a destructor
template <typename value_type>
s21::list<value_type>::list() : head{nullptr}, tail{nullptr}, Size{0} {}

template <typename value_type>
s21::list<value_type>::list(size_type n)
    : list() /*head{nullptr}, tail{nullptr}, Size{0}*/ {
  if (n > max_size() || n <= 0) {
    throw std::out_of_range("Incorrect amount of elements");
  } else {
    for (size_type i = 0; i < n; i++) {
      push_back(value_type{});  // needed to check value in nodes
    }
  }
}

template <typename value_type>
s21::list<value_type>::list(std::initializer_list<value_type> const& items)
    : head{nullptr}, tail{nullptr}, Size{0} {
  for (const auto& i : items) {
    push_back(i);
  }
}

template <typename value_type>
s21::list<value_type>::list(const list& l)
    : head{nullptr}, tail{nullptr}, Size{0} {
  this->copy(l);
}

template <typename value_type>
s21::list<value_type>::list(list&& l) {
  swap(std::move(l));
}

template <typename value_type>
s21::list<value_type>::~list() {
  s21::list<value_type>::clear();
}

// general methods
template <typename value_type>
void s21::list<value_type>::push_back(const_reference value) {
  if (head == nullptr) {
    head = new Node(value);
    tail = head;
  } else {
    Node* newNode = new Node(value);
    tail->pNext = newNode;
    newNode->pPrev = tail;
    tail = newNode;
  }
  Size++;
}

template <typename value_type>
void s21::list<value_type>::push_front(const_reference value) {
  Node* newNode = new Node(value, head, nullptr);
  if (head) {
    head->pPrev = newNode;
  } else {
    tail = newNode;
  }
  head = newNode;
  Size++;
}

template <typename value_type>
void s21::list<value_type>::pop_front() {
  if (!empty()) {
    Node* tmp = head;
    head = head->pNext;
    if (head) {
      head->pPrev = nullptr;
    } else {
      tail = nullptr;
    }
    delete tmp;
    Size--;
  } else {
    throw std::runtime_error("List is already empty");
  }
}

template <class value_type>
void s21::list<value_type>::pop_back() {
  if (empty()) {
    throw std::runtime_error("List is empty");
  }
  if (Size > 1) {
    Node* tmp = tail->pPrev;
    delete tail;
    tail = tmp;
    tail->pNext = nullptr;
  } else {
    clear();
  }
  Size--;
}

template <typename value_type>
void s21::list<value_type>::clear() {
  while (Size) {
    pop_front();
  }
}

template <typename value_type>
bool s21::list<value_type>::empty() const {
  return head == nullptr;
}

template <class value_type>
void s21::list<value_type>::reverse() {
  if (empty() || Size == 1) {
    throw std::invalid_argument("List is empty or contains only one element");
  }
  Node* curr = head;

  while (curr != nullptr) {
    Node* tmp = curr->pPrev;
    Node* nextnode = curr->pNext;
    curr->pNext = tmp;
    curr = nextnode;
  }
  std::swap(head, tail);
  tail->pNext = nullptr;
}

template <class value_type>
void s21::list<value_type>::unique() {
  if (empty() || Size < 2) {
    throw std::invalid_argument("List is empty or contains only one element");
  }
  iterator curr = begin();
  iterator next = curr;
  ++next;
  while (next != nullptr) {
    if (*curr == *next) {
      erase(next);
      next = curr;
      ++next;
    } else {
      curr = next;
      ++next;
    }
  }
}

template <class value_type>
typename s21::list<value_type>::const_reference s21::list<value_type>::front() {
  if (empty()) {
    throw std::out_of_range("List is empty or doesn't exist");
  } else {
    return head->value;
  }
}

template <class value_type>
typename s21::list<value_type>::const_reference s21::list<value_type>::back() {
  if (empty()) {
    throw std::out_of_range("List is empty or doesn't exist");
  } else {
    return tail->value;
  }
}

// supporting funcs
template <typename value_type>
void s21::list<value_type>::copy(const list& l) {
  Node* newNode = l.head;
  while (newNode) {
    push_back(newNode->value);
    newNode = newNode->pNext;
  }
  Size = l.Size;
}

template <class value_type>
void s21::list<value_type>::swap(list&& l) {
  head = l.head;
  tail = l.tail;
  Size = l.Size;

  l.head = nullptr;
  l.tail = nullptr;
  l.Size = 0;
}

template <class value_type>
void s21::list<value_type>::swap(list& other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(Size, other.Size);
}

template <class value_type>
void s21::list<value_type>::merge(list& other) {
  if (this != &other && !other.empty()) {
    while (!other.empty()) {
      push_back(*other.begin());
      other.erase(other.begin());
    }
  }
}

template <class value_type>
void s21::list<value_type>::sort() {
  if (Size < 2) {
    return;
  }

  for (iterator iter = begin(); iter != nullptr; ++iter) {
    value_type val = *iter;
    iterator next = iter;
    ++next;
    erase(iter);
    iterator insertt = begin();
    while (insertt != nullptr && *insertt <= val) {
      ++insertt;
    }
    insert(insertt, val);
    iter = next;
  }
}

template <class value_type>
typename s21::list<value_type>::iterator s21::list<value_type>::insert(
    iterator pos, const_reference value) {
  Node* tmp = nullptr;
  iterator itr;

  if (empty()) {
    tmp = new Node(value, nullptr, nullptr);
    head = tmp;
    tail = tmp;
  } else if (pos == begin()) {
    tmp = new Node(value, head, nullptr);
    head->pPrev = tmp;
    head = tmp;
  } else if (pos == end()) {
    tmp = new Node(value, nullptr, tail);
    tail->pNext = tmp;
    tail = tmp;
  } else {
    tmp = new Node(value, pos.ptr, pos.ptr->pPrev);
    pos.ptr->pPrev->pNext = tmp;
    pos.ptr->pPrev = tmp;
  }

  itr = iterator(tmp);
  Size++;
  return itr;
}

template <class value_type>
void s21::list<value_type>::erase(iterator pos) {
  if (empty() || pos.ptr == nullptr) {
    throw std::out_of_range("List is empty or doesn't exist");
  }
  if (pos.ptr == head) {
    pop_front();
  } else if (pos.ptr == tail) {
    pop_back();
  } else {
    Node* tmp = pos.ptr;
    tmp->pPrev->pNext = tmp->pNext;
    tmp->pNext->pPrev = tmp->pPrev;
    pos.ptr = tmp->pPrev;
    delete tmp;
    this->Size--;
  }
}

template <class value_type>
void s21::list<value_type>::splice(const_iterator pos, list& other) {
  if (other.empty() || pos == nullptr) {
    throw std::invalid_argument("List is empty or doesn't exist");
  }

  while (!other.empty()) {
    insert(pos, other.front());
    other.pop_front();
  }
}

// Iterator operators
template <typename value_type>
bool s21::list<value_type>::ListIterator::operator!=(
    const ListIterator& other) const {
  return ptr != other.ptr;
}

template <typename value_type>
bool s21::list<value_type>::ListIterator::operator==(
    const ListIterator& other) const {
  return ptr == other.ptr;
}

template <typename value_type>
typename s21::list<value_type>::ListIterator&
s21::list<value_type>::ListIterator::operator=(const ListIterator& other) {
  if (this != &other) {
    ptr = other.ptr;
  }
  return *this;
}

template <typename value_type>
s21::list<value_type>& s21::list<value_type>::operator=(list&& l) noexcept {
  if (this != &l) {
    clear();
    head = l.head;
    tail = l.tail;
    Size = l.Size;
    l.head = nullptr;
    l.tail = nullptr;
    l.Size = 0;
  }
  return *this;
}

template <typename value_type>
typename s21::list<value_type>::ListIterator&
s21::list<value_type>::ListIterator::operator++() {
  if (!ptr) {
    throw std::runtime_error("There is no such element");
  }
  this->ptr = ptr->pNext;
  return *this;
}

template <typename value_type>
typename s21::list<value_type>::ListIterator
s21::list<value_type>::ListIterator::operator++(int) {
  if (!ptr) {
    throw std::runtime_error("There is no such element");
  }
  s21::list<value_type>::ListIterator tmp = *this;
  this->ptr = ptr->pNext;
  return tmp;
}

template <typename value_type>
typename s21::list<value_type>::ListIterator&
s21::list<value_type>::ListIterator::operator--() {
  if (!ptr) {
    throw std::runtime_error("There is no such element");
  }
  this->ptr = ptr->pPrev;
  return *this;
}

template <typename value_type>
typename s21::list<value_type>::ListIterator
s21::list<value_type>::ListIterator::operator--(int) {
  if (!ptr) {
    throw std::runtime_error("There is no such element");
  }
  s21::list<value_type>::ListIterator tmp = *this;
  this->ptr = ptr->pPrev;
  return tmp;
}

template <typename value_type>
typename s21::list<value_type>::value_type&
s21::list<value_type>::ListIterator::operator*() {
  if (!ptr) {
    throw std::out_of_range("The value is empty");
  }
  return ptr->value;
}

// bonus part
template <class value_type>
template <typename... Args>
typename s21::list<value_type>::iterator s21::list<value_type>::insert_many(
    const_iterator pos, Args&&... args) {
  iterator iter = pos;
  (insert(iter, std::forward<Args>(args)), ...);
  return iter;
}

template <class value_type>
template <typename... Args>
void s21::list<value_type>::insert_many_front(Args&&... args) {
  (push_front(std::forward<Args>(args)), ...);
}

template <class value_type>
template <typename... Args>
void s21::list<value_type>::insert_many_back(Args&&... args) {
  (push_back(std::forward<Args>(args)), ...);
}

#endif