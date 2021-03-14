#pragma once

#include "./Expression.h"
#include "./Pointer.h"
template <typename T> struct Symbol : public T {
  DOWNSOLVEOVERRIDE(Symbol)
  virtual void DownSolve() override {
    // UE_LOG(LogTemp, Warning, TEXT("Symbol downsolve (%d) upsolve(%d)"), this,
    // express);
    if (express != nullptr)
      express->UpSolve();
  };
  Symbol(T *exp) : express(exp){};
  Symbol(Ptr<T> exp) : express(exp.operator->()){};
  Symbol(const T *exp) : express(const_cast<T *>(exp)){};
  Symbol(Symbol &&other) : express(other.express) {
    // UE_LOG(LogTemp, Warning, TEXT("calling Clone constructor %d"), this);
    other.express = nullptr;
  }
  Symbol(Symbol &other) : Symbol(std::move(other)) {}
  virtual void *Clone() override {
    T *result = static_cast<T *>(express);
    express = nullptr;
    return static_cast<T *>(result->Clone());
  }

protected:
  T *express;
};

#define SYMBOL(S, T)                                                           \
public:                                                                        \
  using base = Symbol<T>;                                                      \
  S(T *exp) : base(exp){};                                                     \
  S(Ptr<T> exp) : base(exp){};                                                 \
  S(base &&other) : base(other){};                                             \
  S(base &other) : base(other){};                                              \
  S(S &&other) : base(other){};                                                \
  S(S &other) : base(other){};                                                 \
  S &operator=(Ptr<T> exp) {                                                   \
    base::express = exp.operator->();                                          \
    return *this;                                                              \
  }