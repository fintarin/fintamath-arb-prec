#include "fintamath/expressions/DerivativeExpression.hpp"
#include "fintamath/expressions/EqvExpression.hpp"
#include "fintamath/expressions/Expression.hpp"

#include "fintamath/expressions/IndexExpression.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/expressions/SumExpression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/comparison/Less.hpp"
#include "fintamath/functions/comparison/LessEqv.hpp"
#include "fintamath/functions/comparison/More.hpp"
#include "fintamath/functions/comparison/MoreEqv.hpp"
#include "fintamath/functions/comparison/Neqv.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Equiv.hpp"
#include "fintamath/functions/logic/Impl.hpp"
#include "fintamath/functions/logic/Nequiv.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"
#include "fintamath/functions/other/Index.hpp"

namespace fintamath {

Parser::Map<ExpressionPtr, ArgumentsPtrVector &&> Expression::expressionBuildersMap;

}

using namespace fintamath;

namespace {

struct ExpressionConfig {
  ExpressionConfig() {
    Expression::registerExpressionBuilder<Add>([](ArgumentsPtrVector &&args) {
      auto expr = std::make_unique<SumExpression>();
      expr->addElement({std::move(args.front())});
      expr->addElement({std::move(args.back())});
      return expr;
    });

    Expression::registerExpressionBuilder<Sub>([](ArgumentsPtrVector &&args) {
      auto expr = std::make_unique<SumExpression>();
      expr->addElement({std::move(args.front())});
      expr->addElement({std::move(args.back()), true});
      return expr;
    });

    Expression::registerExpressionBuilder<Mul>([](ArgumentsPtrVector &&args) {
      auto expr = std::make_unique<MulExpression>();
      expr->addElement({std::move(args.front())});
      expr->addElement({std::move(args.back())});
      return expr;
    });

    Expression::registerExpressionBuilder<Div>([](ArgumentsPtrVector &&args) {
      auto expr = std::make_unique<MulExpression>();
      expr->addElement({std::move(args.front())});
      expr->addElement({std::move(args.back()), true});
      return expr;
    });

    Expression::registerExpressionBuilder<UnaryPlus>([](ArgumentsPtrVector &&args) {
      return std::make_unique<Expression>(std::move(args.front()));
    });

    Expression::registerExpressionBuilder<Eqv>([](ArgumentsPtrVector &&args) {
      return std::make_unique<EqvExpression>(Eqv(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerExpressionBuilder<Neqv>([](ArgumentsPtrVector &&args) {
      return std::make_unique<EqvExpression>(Neqv(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerExpressionBuilder<Less>([](ArgumentsPtrVector &&args) {
      return std::make_unique<EqvExpression>(Less(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerExpressionBuilder<More>([](ArgumentsPtrVector &&args) {
      return std::make_unique<EqvExpression>(More(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerExpressionBuilder<LessEqv>([](ArgumentsPtrVector &&args) {
      return std::make_unique<EqvExpression>(LessEqv(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerExpressionBuilder<MoreEqv>([](ArgumentsPtrVector &&args) {
      return std::make_unique<EqvExpression>(MoreEqv(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerExpressionBuilder<Derivative>([](ArgumentsPtrVector &&args) {
      return std::make_unique<DerivativeExpression>(std::move(args.front()));
    });

    Expression::registerExpressionBuilder<Index>([](ArgumentsPtrVector &&args) {
      return std::make_unique<IndexExpression>(std::move(args.front()), std::move(args.back()));
    });

    Expression::registerExpressionBuilder<Impl>([](ArgumentsPtrVector &&args) {
      MathObjectPtr &lhs = args.front();
      MathObjectPtr &rhs = args.back();

      MathObjectPtr notLhs = Expression::buildRawFunctionExpression(Not(), IFunction::buildArgsPtrVect(std::move(lhs)));

      return Expression::buildRawFunctionExpression(Or(),
                                                    IFunction::buildArgsPtrVect(std::move(notLhs), std::move(rhs)));
    });

    Expression::registerExpressionBuilder<Equiv>([](ArgumentsPtrVector &&args) {
      MathObjectPtr &lhs = args.front();
      MathObjectPtr &rhs = args.back();

      MathObjectPtr notLhs = Expression::buildRawFunctionExpression(Not(), IFunction::buildArgsPtrVect(lhs->clone()));
      MathObjectPtr notRhs = Expression::buildRawFunctionExpression(Not(), IFunction::buildArgsPtrVect(rhs->clone()));

      MathObjectPtr lhsAndRhs = Expression::buildRawFunctionExpression( //
          And(), IFunction::buildArgsPtrVect(std::move(lhs), std::move(rhs)));
      MathObjectPtr notLhsAndNotRhs = Expression::buildRawFunctionExpression( //
          And(), IFunction::buildArgsPtrVect(std::move(notLhs), std::move(notRhs)));

      return Expression::buildRawFunctionExpression(
          Or(), IFunction::buildArgsPtrVect(std::move(lhsAndRhs), std::move(notLhsAndNotRhs)));
    });

    Expression::registerExpressionBuilder<Nequiv>([](ArgumentsPtrVector &&args) {
      MathObjectPtr &lhs = args.front();
      MathObjectPtr &rhs = args.back();

      MathObjectPtr notLhs = Expression::buildRawFunctionExpression(Not(), IFunction::buildArgsPtrVect(lhs->clone()));
      MathObjectPtr notRhs = Expression::buildRawFunctionExpression(Not(), IFunction::buildArgsPtrVect(rhs->clone()));

      MathObjectPtr notLhsAndRhs = Expression::buildRawFunctionExpression( //
          And(), IFunction::buildArgsPtrVect(std::move(notLhs), std::move(rhs)));
      MathObjectPtr lhsAndNotRhs = Expression::buildRawFunctionExpression( //
          And(), IFunction::buildArgsPtrVect(std::move(lhs), std::move(notRhs)));

      return Expression::buildRawFunctionExpression(
          Or(), IFunction::buildArgsPtrVect(std::move(notLhsAndRhs), std::move(lhsAndNotRhs)));
    });
  }
};

const ExpressionConfig config;

}
