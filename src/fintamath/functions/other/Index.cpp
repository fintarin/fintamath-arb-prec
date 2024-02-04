#include "fintamath/functions/other/Index.hpp"

#include <memory>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Index::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = cast<Variable>(argVect.front().get());
  const auto &rhs = cast<Integer>(argVect.back().get());

  return Variable(lhs.toString(), rhs).clone();
}

}
