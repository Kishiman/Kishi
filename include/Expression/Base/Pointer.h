#pragma once
// Pointer rapper that encapsulate a pointer to a class T
template <typename T> struct Ptr {

public:
  Ptr(const T *p) : ptr(p) {}
  Ptr(T *p) : ptr(p) {}
  Ptr(void *p) : ptr(static_cast<T *>(p)) {}
  Ptr(const T &obj) : ptr(const_cast<T *>(&obj)) {}
  Ptr(T &obj) : ptr(&obj) {}
  virtual ~Ptr() = default;
  T *operator->() const { return ptr; };
  T &operator*() const { return (*ptr); };
  operator T &() const { return (*ptr); };
  template <typename Z> operator Ptr<Z>() const {
    return Ptr<Z>(static_cast<Z *>(ptr));
  };
  template <typename Z> operator Z &() const { return static_cast<Z &>(*ptr); };
  template <typename Z> operator Z *() const { return static_cast<Z *>(ptr); };

private:
  T *ptr;
};