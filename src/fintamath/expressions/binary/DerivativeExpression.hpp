#pragma once

#include "fintamath/expressions/IBinaryExpression.hpp"

namespace fintamath {

class DerivativeExpression : public IBinaryExpressionCRTP<DerivativeExpression> {
public:
  explicit DerivativeExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild);

protected:
  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr derivativeSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);
};

}