#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Abs : public IFunctionCRTP<INumber, Abs, INumber> {
public:
  Abs() = default;

  std::string toString() const override {
    return "abs";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsVector &argsVect) const override;
};

}
