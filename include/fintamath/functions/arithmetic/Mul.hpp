#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Mul final : public IFunctionCRTP<IArithmetic, Mul, IArithmetic> {
  FINTAMATH_CLASS_BODY(Mul)

public:
  std::string toString() const override {
    return "mul";
  }

  static constexpr bool isVariadicStatic() {
    return true;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Mul, mulExpr);

}
