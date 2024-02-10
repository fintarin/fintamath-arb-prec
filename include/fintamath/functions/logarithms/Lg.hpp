#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Lg final : public IFunctionCRTP<INumber, Lg, INumber> {
public:
  Lg() = default;

  std::string toString() const override {
    return "lg";
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::Lg;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Lg, lgExpr);

}
