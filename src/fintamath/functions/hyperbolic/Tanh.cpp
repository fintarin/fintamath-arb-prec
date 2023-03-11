#include "fintamath/functions/hyperbolic/Tanh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Tanh::call(const ArgumentsVector &argsVect) const {
  return tanh(convert<Real>(argsVect.front())).toMinimalObject();
}

}
