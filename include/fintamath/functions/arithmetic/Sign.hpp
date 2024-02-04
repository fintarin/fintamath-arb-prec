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

class Sign final : public IFunctionCRTP<INumber, Sign, INumber> {
public:
  Sign() = default;

  std::string toString() const override {
    return "sign";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Sign;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiSignSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Sign, signExpr);

}
