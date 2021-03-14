#pragma once
#include "../../Compatibility.h"
#include "../../Data.h"
#include "../../KishiAPI.h"
#include "../../Traits.h"
#include <memory>

// The Base class for Expression
template <typename T> struct Expression {

  virtual ~Expression() {
    // UE_LOG(LogTemp, Warning, TEXT("Expression Destractor (%d)'deleted'"),
    // this);
  }
  /*
UpSolve is called by another expression that depends on when destructed.
Example: c=a+b
~c() => c.DownSolve()=> a.UpSolve(); b.UpSolve();
The expression is harmless by default
*/
  virtual void UpSolve() {
    // UE_LOG(LogTemp, Warning, TEXT("Expression UpSolve (%d)'Harmless'"),
    // this);
  }
  /*
DownSolve is called by the expression when it is destructed. It aims to solve
its dependencies if needed Example: c=a+b ~c() => c.DownSolve()=> a.UpSolve();
b.UpSolve(); The expression is harmless by default
*/
  virtual void DownSolve() = 0;
  virtual void *Clone() = 0;
};

#define DOWNSOLVEOVERRIDE(S)                                                   \
public:                                                                        \
  virtual ~S() { DownSolve(); }

#define CLONEOVERRIDE(S)                                                       \
public:                                                                        \
  S(S &other) = default;                                                       \
  S(const S &other) = default;                                                 \
  virtual void *Clone() override { return new S(*this); }
