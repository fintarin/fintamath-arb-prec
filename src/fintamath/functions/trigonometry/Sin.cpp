#include "fintamath/functions/trigonometry/Sin.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Sin::toString() const {
    return "sin";
  }

  MathObjectPtr Sin::operator()(const MathObject &rhs) const {
    const int64_t defaultPrecision = 45;
    if (!rhs.instanceOf<Number>()) {
      throw std::invalid_argument("Rhs must be Number");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(sin(newRhs->to<Rational>(), defaultPrecision));
  }

  MathObjectPtr Sin::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Sin::operator()(argsVect.at(0).get());
  }
}