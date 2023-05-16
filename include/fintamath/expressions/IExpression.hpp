#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/parser/Parser.hpp"
#include "fintamath/parser/Tokenizer.hpp"

namespace fintamath {

class IExpression : virtual public IMathObject {
public:
  virtual std::shared_ptr<IFunction> getFunction() const = 0;

  virtual ArgumentsPtrVector getChildren() const = 0;

  virtual void setChildren(const ArgumentsPtrVector &childVect) = 0;

  virtual std::vector<Variable> getVariablesUnsorted() const;

  std::vector<Variable> getVariables() const;

  virtual void setValuesOfVariables(const std::vector<Variable> &vars, const ArgumentsPtrVector &vals);

  std::unique_ptr<IMathObject> toMinimalObject() const final;

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IExpression, T>>>
  static void registerType() {
    Parser::registerType<T>(getParser());
  }

  static std::unique_ptr<IExpression> parse(const std::string &str) {
    return Parser::parse(getParser(), str);
  }

protected:
  static void compressChild(ArgumentPtr &child);

  static void simplifyChild(ArgumentPtr &child);

  static void preSimplifyChild(ArgumentPtr &child);

  static void postSimplifyChild(ArgumentPtr &child);

  static ArgumentPtr callFunction(const IFunction &func, const ArgumentsPtrVector &argPtrs);

  virtual ArgumentPtr preSimplify() const;

  virtual ArgumentPtr postSimplify() const;

  virtual ArgumentPtr simplify() const = 0;

private:
  static void simplifyConstant(ArgumentPtr &child);

  static bool isVariableUnique(const std::vector<Variable> &vars, const Variable &var);

private:
  static Parser::Vector<std::unique_ptr<IExpression>, const std::string &> &getParser();
};

template <typename Derived, bool isMultiFunction = false>
class IExpressionCRTP : virtual public IMathObjectCRTP<Derived>, virtual public IExpression {
public:
  bool equals(const Derived &rhs) const override {
    if constexpr (isMultiFunction) {
      if (*getFunction() != *rhs.getFunction()) {
        return false;
      }
    }

    ArgumentsPtrVector lhsChildren = getChildren();
    ArgumentsPtrVector rhsChildren = rhs.getChildren();

    if (lhsChildren.size() != rhsChildren.size()) {
      return false;
    }

    for (size_t i = 0; i < lhsChildren.size(); i++) {
      if (lhsChildren[i] != rhsChildren[i] && *lhsChildren[i] != *rhsChildren[i]) {
        return false;
      }
    }

    return true;
  }
};

}
