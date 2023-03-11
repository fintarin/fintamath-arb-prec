#include "fintamath/functions/comparison/Eqv.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Eqv::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(argsVect.front().get() == argsVect.back().get());
}

}
