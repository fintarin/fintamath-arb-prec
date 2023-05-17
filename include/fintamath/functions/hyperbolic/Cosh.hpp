#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Cosh : public IFunctionCRTP<INumber, Cosh, INumber> {
public:
  Cosh() = default;

  std::string toString() const override {
    return "cosh";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Cosh;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
