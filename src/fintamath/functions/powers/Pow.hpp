#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {
  class Pow : public IOperatorCRTP<Pow, IArithmetic, IArithmetic> {
  public:
    Pow();

    std::string toString() const override;

    std::string getClassName() const override;

  protected:
    MathObjectPtr call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
  };
}
