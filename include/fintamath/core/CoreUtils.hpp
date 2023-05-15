#pragma once

#include <memory>

#include "fintamath/meta/Converter.hpp"

#define FINTAMATH_CONVERTIBLE()                                                                                        \
public:                                                                                                                \
  inline static const bool IS_CONVERTIBLE = true;                                                                      \
                                                                                                                       \
private:

namespace fintamath {

template <typename T, typename U = bool>
struct IsConvertible : std::false_type {};

template <typename T>
struct IsConvertible<T, decltype((void)T::IS_CONVERTIBLE, true)> : std::true_type {};

template <typename To>
To *cast(IMathObject *from) {
  return dynamic_cast<To *>(from);
}

template <typename To>
const To *cast(const IMathObject *from) {
  return dynamic_cast<const To *>(from);
}

template <typename To>
const To &cast(const IMathObject &from) {
  return dynamic_cast<const To &>(from);
}

template <typename To>
To &&cast(IMathObject &&from) {
  return dynamic_cast<To &&>(from);
}

template <typename To, typename From>
std::unique_ptr<To> cast(std::unique_ptr<From> &&from) {
  From *fromRawPtr = from.release();
  auto *toRawPtr = dynamic_cast<To *>(fromRawPtr);

  if (toRawPtr) {
    from = nullptr;
    return std::unique_ptr<To>(toRawPtr);
  }

  from.reset(fromRawPtr);

  return std::unique_ptr<To>();
}

template <typename To, typename From>
std::shared_ptr<To> cast(const std::shared_ptr<From> &from) {
  return std::dynamic_pointer_cast<To>(from);
}

template <typename To, typename From>
std::shared_ptr<const To> cast(const std::shared_ptr<const From> &from) {
  return std::dynamic_pointer_cast<const To>(from);
}

inline std::unique_ptr<IMathObject> convert(const IMathObject &to, const IMathObject &from) {
  return Converter::convert(to, from);
}

template <typename To>
To convert(const IMathObject &from) {
  static_assert(IsConvertible<To>::value, "To must be convertible");

  static const To to;
  auto res = convert(to, from);

  if (!res) {
    throw std::bad_cast();
  }

  return cast<To>(*res);
}

template <typename To>
bool is(const IMathObject *from) {
  return dynamic_cast<const To *>(from);
}

template <typename To>
bool is(const IMathObject &from) {
  return dynamic_cast<const To *>(&from);
}

template <typename To, typename From>
bool is(const std::unique_ptr<From> &from) {
  return dynamic_cast<const To *>(from.get());
}

template <typename To, typename From>
bool is(const std::shared_ptr<From> &from) {
  return std::dynamic_pointer_cast<To>(from) != nullptr;
}

template <typename To, typename From>
bool is(const std::shared_ptr<const From> &from) {
  return std::dynamic_pointer_cast<const To>(from) != nullptr;
}

template <typename To, typename From>
bool is(const std::reference_wrapper<From> &from) {
  return dynamic_cast<To *>(&from.get());
}

template <typename To, typename From>
bool is(const std::reference_wrapper<const From> &from) {
  return dynamic_cast<const To *>(&from.get());
}

}
