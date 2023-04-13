#include "fintamath/expressions/binary/CompExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

CompExpression::CompExpression(const IOperator &oper, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild)
    : IBinaryExpressionCRTP(oper, lhsChild, rhsChild) {
}

string CompExpression::toString() const {
  if (isSolution) {
    if (const auto lhsExpr = cast<IExpression>(lhsChild); lhsExpr && *lhsExpr->getFunction() == Add()) {
      ArgumentsPtrVector sumChildren = lhsExpr->getChildren();

      ArgumentPtr solLhs = sumChildren.front();

      if (is<Variable>(solLhs)) {
        sumChildren.erase(sumChildren.begin());

        ArgumentPtr solRhs = makeFunctionExpression(Neg(), {sumChildren});

        if (const auto solRhsExpr = cast<IExpression>(solRhs)) {
          if (solRhsExpr->getVariables().empty()) {
            return CompExpression(cast<IOperator>(*func), solLhs, solRhs).toString();
          }
        }
        else {
          return CompExpression(cast<IOperator>(*func), solLhs, solRhs).toString();
        }
      }
    }
  }

  return IBinaryExpression::toString();
}

ArgumentPtr CompExpression::preSimplify() const {
  if (auto rhsInt = cast<Integer>(rhsChild); !rhsInt || *rhsInt != ZERO) {
    ArgumentPtr resLhs = makeFunctionExpression(Sub(), {lhsChild, rhsChild});
    return std::make_shared<CompExpression>(cast<IOperator>(*func), resLhs, ZERO.clone());
  }

  return {};
}

void CompExpression::markAsSolution() {
  isSolution = true;
}

}
