#pragma once
#include "./Expression.h"
#include "./Pointer.h"
/*
  An Expression that stores pointers to two objects of class T (derives from
  Expression)
*/
template <typename T> struct BinaryExpression : public T {
  DOWNSOLVEOVERRIDE(BinaryExpression)
  virtual void DownSolve() override {
    // UE_LOG(LogTemp, Warning, TEXT("BINARY downsolve (%d) upsolve(%d),
    // upsolve(%d)"), this, a, b);

    if (a != nullptr)
      a->UpSolve();
    if (b != nullptr)
      b->UpSolve();
  }
  virtual void UpSolve() override {
    // UE_LOG(LogTemp, Warning, TEXT("BinaryExpression UpSolve (%d)'deleted'"),
    // this);
    delete this;
  }
  BinaryExpression(T *a, T *b) : a(a), b(b){};
  BinaryExpression(Ptr<T> a, Ptr<T> b) : a(a.operator->()), b(b.operator->()){};
  BinaryExpression(T &a, T &b) : a(&a), b(&b){};
  BinaryExpression(const T &a, const T &b)
      : a(&(SC_CAST(T, a))), b(&(SC_CAST(T, b))){};
  virtual void *Clone() override {
    a = static_cast<T *>(a->Clone());
    b = static_cast<T *>(b->Clone());
    return this;
  }

protected:
  T *a;
  T *b;
};

#define BINARY(S, T)                                                           \
public:                                                                        \
  using base = BinaryExpression<T>;                                            \
  S(T *a, T *b) : base(a, b){};                                                \
  S(Ptr<T> a, Ptr<T> b) : base(a, b){};                                        \
  S(T &a, T &b) : base(a, b){};                                                \
  S(const T &a, const T &b) : base(a, b){};
/*
  An Expression that stores pointers to two objects of class T (derives from
  Expression) and a parameter of type C
*/
template <typename T, typename C> struct BinaryExpression_A : public T {
  DOWNSOLVEOVERRIDE(BinaryExpression_A)
  virtual void DownSolve() override {
    // UE_LOG(LogTemp, Warning, TEXT("BINARY downsolve (%d) upsolve(%d),
    // upsolve(%d)"), this, a, b);

    if (a != nullptr)
      a->UpSolve();
    if (b != nullptr)
      b->UpSolve();
  }
  virtual void UpSolve() override {
    // UE_LOG(LogTemp, Warning, TEXT("BinaryExpression_A UpSolve
    // (%d)'deleted'"), this);
    delete this;
  }
  BinaryExpression_A(T *a, T *b, C c) : a(a), b(b), c(c){};
  BinaryExpression_A(Ptr<T> a, Ptr<T> b, C c)
      : a(a.operator->()), b(b.operator->()), c(c){};
  BinaryExpression_A(T &a, T &b, C c) : a(&a), b(&b), c(c){};
  BinaryExpression_A(const T &a, const T &b, C c)
      : a(&(SC_CAST(T, a))), b(&(SC_CAST(T, b))), c(c){};

  virtual void *Clone() override {
    a = static_cast<T *>(a->Clone());
    b = static_cast<T *>(b->Clone());
    return this;
  }

protected:
  T *a;
  T *b;
  C c;
};

#define BINARY_A(S, T, C)                                                      \
public:                                                                        \
  using base = BinaryExpression_A<T, C>;                                       \
  S(T *a, T *b, C c) : base(a, b, c){};                                        \
  S(Ptr<T> a, Ptr<T> b, C c) : base(a, b, c){};                                \
  S(T &a, T &b, C c) : base(a, b, c){};                                        \
  S(const T &a, const T &b, C c) : base(a, b, c){};
/*
  An Expression that stores pointers to two objects of class A and B (both
  derives from Expression)
*/
template <typename A, typename B, typename T>
struct HBinaryExpression : public T {
  DOWNSOLVEOVERRIDE(HBinaryExpression)

  virtual void DownSolve() override {
    // UE_LOG(LogTemp, Warning, TEXT("HBINARY downsolve (%d) upsolve(%d),
    // upsolve(%d)"), this, a, b);

    if (a != nullptr)
      a->UpSolve();
    if (b != nullptr)
      b->UpSolve();
  }
  virtual void UpSolve() override {
    // UE_LOG(LogTemp, Warning, TEXT("HBinaryExpression UpSolve (%d)'deleted'"),
    // this);
    delete this;
  }
  HBinaryExpression(A *a, B *b) : a(a), b(b){};
  HBinaryExpression(Ptr<A> a, Ptr<B> b)
      : a(a.operator->()), b(b.operator->()){};
  HBinaryExpression(A &a, B &b) : a(&a), b(&b){};
  HBinaryExpression(const T &a, const T &b)
      : a(&(SC_CAST(A, a))), b(&(SC_CAST(B, b))){};

  virtual void *Clone() override {
    a = static_cast<A *>(a->Clone());
    b = static_cast<B *>(b->Clone());
    return this;
  }

protected:
  A *a;
  B *b;
};

#define HBINARY(S, A, B, T)                                                    \
public:                                                                        \
  using base = HBinaryExpression<A, B, T>;                                     \
  S(A *a, B *b) : base(a, b){};                                                \
  S(Ptr<A> a, Ptr<B> b) : base(a, b){};                                        \
  S(A &a, B &b) : base(a, b){};                                                \
  S(const A &a, const B &b) : base(a, b){};

/*
  Symbol of a class T that derives from expression is the type to be used
  directly to handle dynamically allocated expressions. exmaple:
  EXPRESSION::Symbol a=new SUBCLASSOFEXPRESSION(...);
*/