#include <iostream>
#include <list>
#include <vector>

template <class T>
class chunk_allocator {
 public:
  using value_type = T;
  using pointer = T *;
  using const_pointer = const T *;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  template <class U>
  class rebind {
   public:
    using other = chunk_allocator<U>;
  };

  struct chunck {
    char *data;
    int position;
    chunck *previous;
    chunck *next;
    char *free;

    chunck() {
      data = new char[1024];
      position = 0;
      previous = nullptr;
      next = nullptr;
      free = data;
    }
  };

  chunck *current;
  int *counter;

  chunk_allocator() {
    current = nullptr;
    counter = new int;
    *counter = 1;
  }

  chunk_allocator(const chunk_allocator &a) {
    current = a.current;
    counter = a.counter;
    ++(*counter);
  }

  chunk_allocator &operator=(const chunk_allocator &a) {
    current = a.current;
    counter = a.counter;
    ++(*counter);
    return *this;
  }

  pointer allocate(size_t n) {
    if (n * sizeof(T) > 1024) {
      return nullptr;
    } else if (current == nullptr) {
      current = new chunck;
      current->position += n * sizeof(T);
      return reinterpret_cast<T *>(current->data);
    } else if (n * sizeof(T) <= 1024 - current->position) {
      current->free = current->data + current->position;
      current->position += n * sizeof(T);
      return reinterpret_cast<T *>(current->free);
    } else {
      chunck *cur = current->previous;
      while (cur != nullptr) {
        if (n * sizeof(T) <= 1024 - cur->position) {
          cur->free = cur->data + cur->position;
          cur->position += n * sizeof(T);
          return reinterpret_cast<T *>(cur->free);
        }
        cur = cur->previous;
      }
      cur = current;
      current = new chunck;
      current->previous = cur;
      cur->next = current;
      current->position += n * sizeof(T);
      return reinterpret_cast<T *>(current->free);
    }
  }

  void deallocate(pointer p, size_t n) { return; }
  void construct(pointer p, const_reference t) { new (p) T(t); }
  void destroy(pointer p) { p->~T(); }

  ~chunk_allocator() {
    --(*counter);
    if (*counter == 0) {
      while (current != nullptr) {
        delete[] current->data;
        current = current->previous;
      }
    }
  }
};

int main() {
  chunk_allocator<int> al;
  chunk_allocator<int> al2;
  chunk_allocator<int> al3;
  al3 = al2 = al;
  std::vector<int, decltype(al)> vec;
  for (int i = 0; i < 150; ++i) {
    vec.push_back(i);
  }
  std::list<int, decltype(al)> lst;
  for (int i = 0; i < 150; ++i) {
    lst.push_back(i);
  }
  std::vector<int, decltype(al)> vec1;
  for (int i = 0; i < 100; ++i) {
    vec1.push_back(100 - i);
  }
  std::vector<int, decltype(al)> vec2(100);
  return 0;
}