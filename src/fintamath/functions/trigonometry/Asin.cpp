#include "fintamath/functions/trigonometry/Asin.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Asin::call(const ArgumentsVector &argsVect) const {
  return asin(convert<Real>(argsVect.front())).toMinimalObject();
}

}
