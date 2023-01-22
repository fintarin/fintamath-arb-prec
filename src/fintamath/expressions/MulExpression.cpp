#include "fintamath/expressions/MulExpression.hpp"

#include <algorithm>
#include <memory>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/AddExpression.hpp"
#include "fintamath/expressions/EqvExpression.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

const MulExpression::Polynom &MulExpression::getPolynom() const {
  return mulPolynom;
}

MulExpression::MulExpression(const IMathObject &rhs) {
  if (rhs.instanceof <MulExpression>()) {
    *this = rhs.to<MulExpression>();
    return;
  }
  mulPolynom.emplace_back(Element{rhs.clone(), false});
}

uint16_t MulExpression::getBaseOperatorPriority() const {
  return (uint16_t)IOperator::Priority::Multiplication;
}

void MulExpression::setPrecision(uint8_t precision) {
  for (auto &child : mulPolynom) {
    child.setPrecision(precision);
  }
}

std::string MulExpression::tryPutInBrackets(const MathObjectPtr &obj) {
  if (obj->instanceof <AddExpression>()) {
    return "(" + obj->toString() + ")";
  }
  return tryPutInBracketsIfNeg(obj);
}

std::string MulExpression::toString() const {
  std::string result;
  if (!mulPolynom.empty() && mulPolynom.at(0).inverted) {
    result += '1';
  }
  for (const auto &var : mulPolynom) {
    result += var.inverted ? '/' : '*';
    result += tryPutInBrackets(var.info);
  }
  if (!result.empty() && !mulPolynom.at(0).inverted) {
    result.erase(result.begin());
  }
  return result;
}

MulExpression::Element::Element(const Element &rhs) : inverted(rhs.inverted) {
  info = rhs.info->clone();
}

void MulExpression::Element::simplify(bool isPrecise) {
  if (info->instanceof <IExpression>()) {
    // TODO: remove this condition when polynomial division is implemented
    if (info->instanceof <Expression>() && info->to<Expression>().getInfo()->instanceof <Pow>()) {
      if (auto tmpSimpl = info->to<IExpression>().simplify(isPrecise); !tmpSimpl->instanceof <AddExpression>()) {
        info = tmpSimpl->clone();
        return;
      }
      return;
    }
    info = info->to<IExpression>().simplify(isPrecise);
    return;
  }
  if (info->instanceof <IConstant>()) {
    auto constant = (*castPtr<IConstant>(info->clone()))();
    if (!isPrecise || !constant->instanceof <INumber>() || constant->to<INumber>().isPrecise()) {
      info = constant->clone();
      return;
    }
    info = info->simplify();
  }
  info = info->simplify();
}

MulExpression::Element &MulExpression::Element::operator=(const Element &rhs) {
  if (this != &rhs) {
    info = rhs.info->clone();
    inverted = rhs.inverted;
  }
  return *this;
}

void MulExpression::Element::setPrecision(uint8_t precision) {
  if (info->instanceof <INumber>()) {
    info = Converter::convert(*info, Real())->to<Real>().precise(precision).clone();
  }

  if (info->instanceof <IExpression>()) {
    auto copyExpr = castPtr<IExpression>(info->clone());
    copyExpr->setPrecision(precision);
    info = copyExpr->clone();
  }

  if (info->instanceof <IConstant>()) {
    info = (*castPtr<IConstant>(info->clone()))();
    if (info->instanceof <INumber>()) {
      info = Converter::convert(*info, Real())->to<Real>().precise(precision).clone();
    }
  }
}

MulExpression::MulExpression(const TokenVector &tokens) {
  parse(tokens);
}

MulExpression::MulExpression(Polynom inMulPolynom) : mulPolynom(std::move(inMulPolynom)) {
  mulPolynom = compressTree();
}

void MulExpression::parse(const TokenVector &tokens) {
  int lastSignPosition = -1;
  for (size_t i = 0; i < tokens.size(); i++) {
    if (skipBrackets(tokens, i)) {
      i--;
      continue;
    }
    if (tokens.at(i) != "*" && tokens.at(i) != "/") {
      continue;
    }
    if (i == tokens.size() - 1) {
      throw InvalidInputException(Tokenizer::tokensToString(tokens));
    }
    lastSignPosition = (int)i;
  }
  if (lastSignPosition == -1) {
    throw InvalidInputException(Tokenizer::tokensToString(tokens));
  }

  auto leftExpr = IExpression::parse(TokenVector(tokens.begin(), tokens.begin() + (long)lastSignPosition));
  auto rightExpr = IExpression::parse(TokenVector(tokens.begin() + (long)lastSignPosition + 1, tokens.end()));

  if (!leftExpr || !rightExpr) {
    throw InvalidInputException(Tokenizer::tokensToString(tokens));
  }

  mulPolynom.emplace_back(Element(leftExpr->clone()));
  mulPolynom.emplace_back(Element(rightExpr->clone(), tokens.at(lastSignPosition) == "/"));

  *this = MulExpression(compressTree());
}

MulExpression::Element::Element(const MathObjectPtr &info, bool inverted) : info(info->clone()), inverted(inverted) {
}

MulExpression::Polynom MulExpression::compressExpression() const {
  Polynom newPolynom;
  for (auto &child : mulPolynom) {
    if (child.info->instanceof <Expression>()) {
      auto childExpr = child.info->to<Expression>();
      newPolynom.emplace_back(Element(childExpr.compress(), child.inverted));
    } else {
      newPolynom.emplace_back(child);
    }
  }
  return newPolynom;
}

std::vector<MulExpression::Element> MulExpression::Element::getMulPolynom() const {
  if (info->instanceof <MulExpression>()) {
    Polynom result;
    auto mulExpr = info->to<MulExpression>();
    for (auto &child : mulExpr.mulPolynom) {
      result.emplace_back(Element{child.info->clone(), (bool)((unsigned)child.inverted ^ (unsigned)inverted)});
    }
    return result;
  }
  return {*this};
}

MathObjectPtr MulExpression::Element::toMathObject(bool isPrecise) const {
  auto copy = *this;
  if (copy.inverted) {
    copy.info = Pow()(*info->clone(), Integer(-1));
    copy.simplify(isPrecise);
    return copy.info->clone();
  }
  copy.simplify(isPrecise);
  return copy.info->clone();
}

MulExpression::Polynom MulExpression::compressTree() const {
  Polynom newPolynom;
  Polynom vect = compressExpression();
  for (const auto &child : vect) {
    auto pushPolynom = child.getMulPolynom();
    for (auto &pushChild : pushPolynom) {
      newPolynom.emplace_back(pushChild);
    }
  }
  return newPolynom;
}

void MulExpression::addElement(const Element &elem) {
  mulPolynom.emplace_back(elem);
}

MathObjectPtr MulExpression::simplify() const {
  return simplify(true);
}

MathObjectPtr MulExpression::simplify(bool isPrecise) const {
  auto exprObj = MulExpression(compressTree());

  for (auto &obj : exprObj.mulPolynom) { // TODO: find a better solution
    if (obj.info->instanceof <EqvExpression>()) {
      throw InvalidInputException(toString());
    }
  }

  if (exprObj.mulPolynom.size() == 1) {
    return exprObj.mulPolynom.at(0).toMathObject(isPrecise);
  }

  for (auto &obj : exprObj.mulPolynom) {
    obj.simplify(isPrecise);
  }

  if (!exprObj.mulPolynom.empty()) { // TODO move to IExpression
    static const Mul func;
    for (size_t i = 0; i < exprObj.mulPolynom.size() - 1; i++) {
      validateFunctionArgs(func, {*exprObj.mulPolynom.at(i).info, *exprObj.mulPolynom.at(i + 1).info});
    }
  }

  exprObj.simplifyPolynom();

  if (exprObj.mulPolynom.size() == 1) {
    return exprObj.mulPolynom.at(0).toMathObject(isPrecise);
  }

  return exprObj.clone();
}

MulExpression::Polynom MulExpression::mulNumbers(const Polynom &numVect) {
  Expression result = 1;
  for (const auto &elem : numVect) {
    if (elem.inverted) {
      result.getInfo() = Div()(*result.getInfo(), *elem.info);
    } else {
      result.getInfo() = Mul()(*result.getInfo(), *elem.info);
    }
  }
  return {{result.simplify(), false}};
}

MulExpression::Polynom convertAddPolynomToMul(const AddExpression::Polynom &polynom) {
  MulExpression::Polynom result;
  for (const auto &elem : polynom) {
    result.emplace_back(MulExpression::Element(elem.info->clone(), elem.inverted));
  }
  return result;
}

AddExpression::Polynom convertMulPolynomToAdd(const MulExpression::Polynom &polynom) {
  AddExpression::Polynom result;
  for (const auto &elem : polynom) {
    result.emplace_back(AddExpression::Element(elem.info->clone(), elem.inverted));
  }
  return result;
}

MulExpression::Polynom MulExpression::multiplicateTwoBraces(const Polynom &lhs, const Polynom &rhs) {
  Polynom result;
  for (const auto &lhsElem : lhs) {
    for (const auto &rhsElem : rhs) {
      auto polynom = lhsElem.info->to<MulExpression>().getPolynom();
      polynom.emplace_back(Element{rhsElem.info->clone()});
      result.emplace_back(
          Element{std::make_unique<MulExpression>(polynom), (bool)(lhsElem.inverted ^ rhsElem.inverted)});
    }
  }
  return result;
}

void MulExpression::multiplicateBraces(const Polynom &addVect, Polynom &positive, Polynom &negative) {
  Polynom result{MulExpression({Integer(1)}).clone()};
  Polynom inverted{MulExpression({Integer(1)}).clone()};

  for (const auto &addExpr : addVect) {
    if (addExpr.inverted) {
      inverted =
          multiplicateTwoBraces(inverted, convertAddPolynomToMul(addExpr.info->to<AddExpression>().getPolynom()));
    } else {
      result = multiplicateTwoBraces(result, convertAddPolynomToMul(addExpr.info->to<AddExpression>().getPolynom()));
    }
  }

  positive = result;
  negative = inverted;
}

bool sortFunc(const MulExpression::Element &lhs, const MulExpression::Element &rhs) {
  return lhs.info->toString() < rhs.info->toString();
}

struct MulExpression::ObjectPow {
  MathObjectPtr obj;
  AddExpression pow;

  ObjectPow(const MathObjectPtr &obj) : obj(obj->clone()) {
  }

  ObjectPow(const ObjectPow &objPow) : obj(objPow.obj->clone()), pow(objPow.pow) {
  }

  MathObjectPtr getPowIfInteger() const {
    auto polynom = pow.getPolynom();
    if (polynom.size() != 1) {
      return nullptr;
    }
    auto powValue = polynom.at(0).info->clone();
    *powValue = polynom.at(0).inverted ? *Neg()(*powValue) : *powValue;
    if (powValue->instanceof <Integer>()) {
      return powValue;
    }
    return nullptr;
  }

  MathObjectPtr getPowIfSingle() const {
    auto polynom = pow.getPolynom();
    if (polynom.size() != 1) {
      return nullptr;
    }
    auto powValue = polynom.at(0).info->clone();
    *powValue = polynom.at(0).inverted ? *Neg()(*powValue) : *powValue;
    return powValue;
  }

  void simplifyPow() {
    pow = AddExpression(*pow.simplify());
  }
};

void MulExpression::sortPowObjects(Objects &objs, Polynom &powVect, Polynom &addVect, Polynom &literalVect,
                                   Polynom &funcVect) {
  for (auto &obj : objs) {
    obj.simplifyPow();
    if (auto numObj = obj.getPowIfInteger()) {
      auto num = numObj->to<Integer>();
      if (num == 0) {
        continue;
      }
      if (obj.obj->instanceof <ILiteral>()) {
        if ((num == 1) || (num == -1)) {
          literalVect.emplace_back(Element(obj.obj->clone(), num == -1));
          continue;
        }
        powVect.emplace_back(Element(Pow()(*obj.obj, num)));
        continue;
      }

      if (obj.obj->instanceof <Expression>()) {
        if ((num == 1) || (num == -1)) {
          funcVect.emplace_back(Element(obj.obj->clone(), num == -1));
          continue;
        }
        powVect.emplace_back(Element(Pow()(*obj.obj, num)));
        continue;
      }

      if (obj.obj->instanceof <INumber>()) {
        powVect.emplace_back(Element(Pow()(*obj.obj, num)));
        continue;
      }

      auto oldNum = num;
      if (num < 0) {
        num = -num;
      }
      for (Integer i = 0; i < num; i++) {
        addVect.emplace_back(Element(obj.obj->clone(), oldNum < 0));
      }
      continue;
    }

    if (auto exprObj = obj.getPowIfSingle()) {
      powVect.emplace_back(Element(Pow()(*obj.obj, *exprObj)));
    } else {
      powVect.emplace_back(Element(Pow()(*obj.obj, obj.pow)));
    }
  }
}

void MulExpression::simplifyPow(Polynom &powVect, Polynom &addVect, Polynom &literalVect, Polynom &funcVect) {
  Objects objects;
  for (const auto &addObj : addVect) {
    bool added = false;
    for (auto &obj : objects) {
      if (obj.obj->toString() == addObj.info->toString()) {
        obj.pow.addElement({std::make_unique<Integer>(1), addObj.inverted});
        added = true;
        break;
      }
    }
    if (added) {
      continue;
    }
    ObjectPow obj(addObj.info);
    obj.pow.addElement({std::make_unique<Integer>(1), addObj.inverted});
    objects.emplace_back(obj);
  }

  for (const auto &litObj : literalVect) {
    bool added = false;
    for (auto &obj : objects) {
      if (obj.obj->toString() == litObj.info->toString()) {
        obj.pow.addElement({std::make_unique<Integer>(1), litObj.inverted});
        added = true;
        break;
      }
    }
    if (added) {
      continue;
    }
    ObjectPow obj(litObj.info);
    obj.pow.addElement({std::make_unique<Integer>(1), litObj.inverted});
    objects.emplace_back(obj);
  }

  for (const auto &funcObj : funcVect) {
    bool added = false;
    for (auto &obj : objects) {
      if (obj.obj->toString() == funcObj.info->toString()) {
        obj.pow.addElement({std::make_unique<Integer>(1), funcObj.inverted});
        added = true;
        break;
      }
    }
    if (added) {
      continue;
    }
    ObjectPow obj(funcObj.info);
    obj.pow.addElement({std::make_unique<Integer>(1), funcObj.inverted});
    objects.emplace_back(obj);
  }

  for (const auto &powObj : powVect) {
    bool added = false;
    auto expr = powObj.info->to<Expression>();

    auto leftValue = expr.getChildren().at(0)->clone();
    auto rightValue = expr.getChildren().at(1)->clone();
    for (auto &obj : objects) {
      if (obj.obj->toString() == leftValue->toString()) {
        obj.pow.addElement({rightValue->clone(), powObj.inverted});
        added = true;
        break;
      }
    }
    if (added) {
      continue;
    }
    ObjectPow obj(leftValue);
    obj.pow.addElement({rightValue->clone(), powObj.inverted});
    objects.emplace_back(obj);
  }

  powVect.clear();
  literalVect.clear();
  addVect.clear();
  funcVect.clear();

  sortPowObjects(objects, powVect, addVect, literalVect, funcVect);
}

void MulExpression::sortPolynom(const Polynom &vect, Polynom &numVect, Polynom &addVect, Polynom &literalVect,
                                Polynom &funcVect, Polynom &powVect) {
  for (const auto &child : vect) {
    if (child.info->instanceof <AddExpression>()) {
      addVect.emplace_back(child);
      continue;
    }
    if (child.info->instanceof <Expression>()) {
      if (auto exprInfo = (child.info->to<Expression>()).getInfo()->clone(); exprInfo->instanceof <Pow>()) {
        powVect.emplace_back(child);
        continue;
      }
      funcVect.emplace_back(child);
      continue;
    }
    if (child.info->instanceof <IArithmetic>()) {
      numVect.emplace_back(child);
      continue;
    }
    if (child.info->instanceof <ILiteral>()) {
      literalVect.emplace_back(child);
      continue;
    }
  }
}

void MulExpression::multiplicatePolynom(Polynom &vect, Polynom &positive, Polynom &negative) {
  for (const auto &el : vect) {
    if (el.inverted) {
      negative = multiplicateTwoBraces(negative, {Element(el.info->clone())});
    } else {
      positive = multiplicateTwoBraces(positive, {el});
    }
  }
}

void MulExpression::simplifyPolynom() {
  auto numVect = Polynom();
  auto powVect = Polynom();
  auto literalVect = Polynom();
  auto addVect = Polynom();
  auto funcVect = Polynom();

  sortPolynom(mulPolynom, numVect, addVect, literalVect, funcVect, powVect);
  mulPolynom.clear();

  Polynom tmpVect = openPowMulExpression(powVect);
  powVect.clear();

  sortPolynom(tmpVect, numVect, addVect, literalVect, funcVect, powVect);

  numVect = mulNumbers(numVect);
  if (numVect.size() == 1 && numVect.at(0).info->instanceof <IComparable>() &&
                                                                numVect.at(0).info->to<IComparable>() == Integer(0)) {
    mulPolynom = numVect;
    return;
  }

  simplifyPow(powVect, addVect, literalVect, funcVect);

  Polynom positive;
  Polynom negative;

  if (!addVect.empty()) {
    multiplicateBraces(addVect, positive, negative);
    // TODO: positive divide by negative
    multiplicatePolynom(literalVect, positive, negative);
    multiplicatePolynom(funcVect, positive, negative);
    multiplicatePolynom(numVect, positive, negative);
    multiplicatePolynom(powVect, positive, negative);

    addVect.clear();
    numVect.clear();

    bool positiveAdded = false;
    bool negativeAdded = false;
    if (!positive.empty()) {
      auto addExpr = AddExpression(convertMulPolynomToAdd(positive)).simplify();
      if (!addExpr->instanceof <INumber>()) {
        mulPolynom.emplace_back(Element{addExpr->clone()});
        positiveAdded = true;
      } else {
        numVect.emplace_back(addExpr->clone());
      }
    }
    if (!negative.empty()) {
      auto addExpr = AddExpression(convertMulPolynomToAdd(negative)).simplify();
      if (!addExpr->instanceof <INumber>()) {
        mulPolynom.emplace_back(Element(addExpr->clone(), true));
        negativeAdded = true;
      } else {
        numVect.emplace_back(Element(addExpr->clone(), true));
      }
    }
    if (positiveAdded && negativeAdded) {
      return;
    }
    numVect = mulNumbers(numVect);
    if (numVect.at(0).info->toString() != "1" || mulPolynom.empty()) {
      pushPolynomToPolynom<MulExpression>(mulPolynom, numVect);
      mulPolynom = numVect;
      return;
    }
    return;
  }

  std::sort(funcVect.begin(), funcVect.end(), sortFunc);
  std::sort(powVect.begin(), powVect.end(), sortFunc);
  std::sort(literalVect.begin(), literalVect.end(), sortFunc);
  std::sort(addVect.begin(), addVect.end(), sortFunc);

  pushPolynomToPolynom<MulExpression>(funcVect, mulPolynom);
  pushPolynomToPolynom<MulExpression>(powVect, mulPolynom);
  pushPolynomToPolynom<MulExpression>(addVect, mulPolynom);
  pushPolynomToPolynom<MulExpression>(literalVect, mulPolynom);
  if (numVect.at(0).info->toString() != "1" || mulPolynom.empty()) {
    pushPolynomToPolynom<MulExpression>(mulPolynom, numVect);
    mulPolynom = numVect;
  }
}

MulExpression::Polynom MulExpression::openPowMulExpression(const Polynom &powVect) {
  Polynom newPowVect;

  for (const auto &pow : powVect) {
    auto expr = pow.info->to<Expression>();
    auto left = expr.getChildren().at(0)->clone();
    if (!left->instanceof <MulExpression>()) {
      newPowVect.emplace_back(pow);
      continue;
    }
    auto right = expr.getChildren().at(1)->clone();
    auto mulExpr = left->to<MulExpression>();
    for (const auto &child : mulExpr.mulPolynom) {
      newPowVect.emplace_back(Element{Pow()(*child.info, *right), child.inverted});
    }
  }
  return newPowVect;
}

std::vector<MathObjectPtr> MulExpression::getVariables() const {
  std::vector<MathObjectPtr> result;
  for (const auto &child : mulPolynom) {
    if (child.info->instanceof <Variable>()) {
      result.emplace_back(child.info->clone());
      continue;
    }
    if (child.info->instanceof <IExpression>()) {
      auto addResult = child.info->to<IExpression>().getVariables();
      for (const auto &add : addResult) {
        result.emplace_back(add->clone());
      }
    }
  }
  return result;
}

MathObjectPtr MulExpression::getPowCoefficient(const MathObjectPtr &powValue) const {
  for (const auto &child : mulPolynom) {
    if (child.info->instanceof <Expression>() && child.info->to<Expression>().getInfo()->instanceof <Pow>()) {
      auto rightVal = child.info->to<Expression>().getChildren().at(1)->clone();
      if (rightVal->instanceof <IComparable>() && powValue->instanceof
          <IComparable>() && rightVal->to<IComparable>() == powValue->to<IComparable>()) {
        return mulPolynom.at(0).info->clone();
      }
    }
    if (powValue->instanceof <IComparable>() && powValue->to<IComparable>() == Integer(1)) {
      if (child.info->instanceof <Variable>()) {
        return mulPolynom.at(0).info->clone();
      }
    }
  }
  return nullptr;
}

MathObjectPtr MulExpression::getPow() const {
  Integer maxValue(0);
  for (const auto &child : mulPolynom) {
    if (child.info->instanceof <Expression>()) {
      if (child.info->to<Expression>().getInfo()->instanceof <Pow>()) {
        auto rightVal = child.info->to<Expression>().getChildren().at(1)->clone();
        if (rightVal->instanceof <Integer>() && rightVal->to<Integer>() > maxValue) {
          maxValue = rightVal->to<Integer>();
        }
      }
    }
  }
  return maxValue.clone();
}

}
