#include "fintamath/functions/trigonometry/Acoth.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Acoth::call(const ArgumentsVector &argsVect) const {
  return acoth(convert<Real>(argsVect.front())).simplify();
}

}
