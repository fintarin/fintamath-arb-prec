#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class InvHyperbExpression : public IUnaryExpressionCRTP<InvHyperbExpression, true> {
public:
  explicit InvHyperbExpression(const IFunction &inFunc, const ArgumentPtr &inChild);

  static MathObjectType getTypeStatic() {
    return MathObjectType::InvHyperbExpression;
  }
};

}