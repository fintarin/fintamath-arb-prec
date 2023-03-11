#include "fintamath/functions/arithmetic/UnaryPlus.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> UnaryPlus::call(const ArgumentsVector &argsVect) const {
  return +cast<IArithmetic>(argsVect.front().get());
}

}
