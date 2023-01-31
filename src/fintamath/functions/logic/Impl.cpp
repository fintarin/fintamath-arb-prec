#include "fintamath/functions/logic/Impl.hpp"

#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

MathObjectPtr Impl::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(!cast<Boolean>(argsVect.front().get()) || cast<Boolean>(argsVect.back().get()));
}

}