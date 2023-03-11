#include "fintamath/functions/arithmetic/Inv.hpp"

#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Inv::call(const ArgumentsVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return ONE / rhs;
}

}