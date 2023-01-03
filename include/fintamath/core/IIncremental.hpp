#pragma once

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

class IIncremental;
using IncrementalPtr = std::unique_ptr<IIncremental>;

class IIncremental : virtual public IMathObject {
public:
  friend IIncremental &operator++(IIncremental &rhs);

  friend IIncremental &operator--(IIncremental &rhs);

  friend IncrementalPtr operator++(IIncremental &lhs, int);

  friend IncrementalPtr operator--(IIncremental &lhs, int);

protected:
  virtual IIncremental &increaseAbstract() = 0;

  virtual IIncremental &decreaseAbstract() = 0;
};

inline IIncremental &operator++(IIncremental &rhs) {
  return rhs.increaseAbstract();
}

inline IIncremental &operator--(IIncremental &rhs) {
  return rhs.decreaseAbstract();
}

inline IncrementalPtr operator++(IIncremental &lhs, int) {
  auto tmp = lhs.clone();
  auto res = castPtr<IIncremental>(tmp);
  lhs.increaseAbstract();
  return res;
}

inline IncrementalPtr operator--(IIncremental &lhs, int) {
  auto tmp = lhs.clone();
  auto res = castPtr<IIncremental>(tmp);
  lhs.decreaseAbstract();
  return res;
}

template <typename Derived>
class IIncrementalCRTP : virtual public IMathObjectCRTP<Derived>, virtual public IIncremental {
public:
  Derived &operator++() {
    return increase();
  }

  Derived &operator--() {
    return decrease();
  }

  Derived operator++(int) {
    auto tmp = Derived(to<Derived>());
    increase();
    return tmp;
  }

  Derived operator--(int) {
    auto tmp = Derived(to<Derived>());
    decrease();
    return tmp;
  }

protected:
  virtual Derived &increase() = 0;

  virtual Derived &decrease() = 0;

  IIncremental &increaseAbstract() final {
    increase();
    return *this;
  }

  IIncremental &decreaseAbstract() final {
    decrease();
    return *this;
  }
};

}
