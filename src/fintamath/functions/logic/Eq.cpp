#include "fintamath/functions/logic/Eq.hpp"

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {
  Eq::Eq() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string Eq::toString() const {
    return "=";
  }

  std::string Eq::getClassName() const {
    return "Eq";
  }

  MathObjectPtr Eq::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return INumber::parse(int64_t(argsVect.at(0).get() == argsVect.at(1).get()));
  }
}
