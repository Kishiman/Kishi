#pragma once
#include "./Expression.h"
#include "./Pointer.h"
/*
  An Expression that stores a pointer to one object of class T(derives from
  Expression)
*/
template <typename T> struct UnaryExpression : public T {
  DOWNSOLVEOVERRIDE(UnaryExpression)
  virtual void DownSolve() override {
    // UE_LOG(LogTemp, Warning, TEXT("Symbol downsolve (%d) upsolve(%d)"), this,
    // express);
    if (express != nullptr)
      express->UpSolve();
  };
  virtual void UpSolve() override {
    // UE_LOG(LogTemp, Warning, TEXT("UnaryExpression UpSolve (%d)'deleted'"),
    // this);
    delete this;
  }
  virtual void *Clone() override {
    express = static_cast<T *>(express->Clone());
    return this;
  }
  UnaryExpression(T *exp) : express(exp) {}
  UnaryExpression(Ptr<T> exp) : express(exp.operator->()) {}
  UnaryExpression(T &exp) : express(&exp) {}
  UnaryExpression(const T &exp) : express(&(SC_CAST(T, exp))) {}

protected:
  T *express;
};

#define UNARY(S, T)                                                            \
public:                                                                        \
  using base = UnaryExpression<T>;                                             \
  S(T *exp) : base(exp){};                                                     \
  S(Ptr<T> exp) : base(exp){};                                                 \
  S(T &exp) : base(exp){};                                                     \
  S(const T &exp) : base(exp){};
/*
  An Expression that stores a pointer to one object of class T (derives from
  Expression) and a parameter of type A
*/
template <typename T, typename A> struct UnaryExpression_A : public T {
  DOWNSOLVEOVERRIDE(UnaryExpression_A)
  virtual void DownSolve() override {
    // UE_LOG(LogTemp, Warning, TEXT("Symbol downsolve (%d) upsolve(%d)"), this,
    // express);
    if (express != nullptr)
      express->UpSolve();
  };
  virtual void UpSolve() override {
    // UE_LOG(LogTemp, Warning, TEXT("UnaryExpression UpSolve (%d)'deleted'"),
    // this);
    delete this;
  }
  virtual void *Clone() override {
    express = static_cast<T *>(express->Clone());
    return this;
  }
  UnaryExpression_A(T *exp, A a) : express(exp), a(a) {}
  UnaryExpression_A(Ptr<T> exp, A a) : express(exp.operator->()), a(a) {}
  UnaryExpression_A(T &exp, A a) : express(&exp), a(a) {}
  UnaryExpression_A(const T &exp, A a) : express(&(SC_CAST(T, exp))), a(a) {}

protected:
  T *express;
  A a;
};
#define UNARY_A(S, T, A)                                                       \
public:                                                                        \
  using base = UnaryExpression_A<T, A>;                                        \
  S(T *exp, A a) : base(exp, a){};                                             \
  S(Ptr<T> exp, A a) : base(exp, a){};                                         \
  S(T &exp, A a) : base(exp, a){};                                             \
  S(const T &exp, A a) : base(exp, a){};
