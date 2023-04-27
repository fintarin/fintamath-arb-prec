#include "fintamath/expressions/IBinaryExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"

namespace fintamath {

string IBinaryExpression::toString() const {
  return binaryOperatorToString(*cast<IOperator>(getFunction()), {lhsChild, rhsChild});
}

shared_ptr<IFunction> IBinaryExpression::getFunction() const {
  return func;
}

ArgumentsPtrVector IBinaryExpression::getChildren() const {
  return {lhsChild, rhsChild};
}

ArgumentPtr IBinaryExpression::preSimplify() const {
  auto simpl = cast<IBinaryExpression>(clone());
  preSimplifyChild(simpl->lhsChild);
  preSimplifyChild(simpl->rhsChild);
  return simpl;
}

ArgumentPtr IBinaryExpression::postSimplify() const {
  auto simpl = cast<IBinaryExpression>(clone());
  postSimplifyChild(simpl->lhsChild);
  postSimplifyChild(simpl->rhsChild);

  if (ArgumentPtr res = callFunction(*simpl->func, {simpl->lhsChild, simpl->rhsChild})) {
    return res;
  }

  return simpl;
}

ArgumentPtr IBinaryExpression::simplify() const {
  ArgumentPtr simpl = cast<IBinaryExpression>(clone());
  preSimplifyChild(simpl);
  postSimplifyChild(simpl);
  return simpl;
}

void IBinaryExpression::setChildren(const ArgumentsPtrVector &childVect) {
  if (childVect.size() != 2) {
    return;
  }

  lhsChild = childVect[0];
  rhsChild = childVect[1];
}

}
