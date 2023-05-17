#include "fintamath/functions/hyperbolic/Atanh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Atanh::call(const ArgumentsRefVector &argsVect) const {
  return atanh(convert<Real>(argsVect.front().get())).toMinimalObject();
}

}
