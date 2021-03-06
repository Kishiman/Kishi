#pragma once

#include <functional>
#include <memory>
#include <vector>

#define THIS static_cast<const T &>(*this)
#define CCTHIS const_cast<T &>(*this)
#define CC_THIS(X) const_cast<X *>(this)
#define SCTHIS(X) const_cast<X &>(static_cast<const X &>(*this))
#define SC_CAST(T, ref) const_cast<T &>(static_cast<const T &>(*ref))
