#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IPolynomExpression : virtual public IExpression {
public:
  string toString() const override;

  shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const final;

  void setChildren(const ArgumentsPtrVector &childVect) final;

  virtual void addElement(const ArgumentPtr &element) = 0;

protected:
  using FunctionsVector =
      std::vector<std::function<ArgumentPtr(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild)>>;

  virtual ArgumentPtr preSimplify(size_t lhsChildNum, size_t rhsChildNum) const;

  virtual ArgumentPtr postSimplify(size_t lhsChildNum, size_t rhsChildNum) const;

  ArgumentPtr simplify() const final;

  virtual FunctionsVector getSimplifyFunctions() const;

  virtual string childToString(const ArgumentPtr &child, bool isFirst = false) const;

  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

  virtual bool isTermsOrderInversed() const;

  virtual bool isComparableOrderInversed() const;

protected:
  /**
   * @brief
   *
   * @param lhs
   * @param rhs
   * @return -1 if we should not swap the arguments
   * @return  1 if we should swap the arguments
   * @return  0 if this comparator fails
   */
  virtual int comparatorOverride(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const;

  shared_ptr<IFunction> func;

  ArgumentsPtrVector children;

private:
  void preSimplifyRec();

  void postSimplifyRec();

  void globalSimplifyRec();

  void sort();

  /**
   * @brief
   *
   * @param lhs
   * @param rhs
   * @return -1 if we should not swap the arguments
   * @return  1 if we should swap the arguments
   * @return  0 if this comparator fails
   */
  int comparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const;

  /**
   * @brief
   *
   * @param lhsVariables
   * @param rhsVariables
   * @return -1 if we should not swap the arguments
   * @return  1 if we should swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorLiterals(const ArgumentsPtrVector &lhsVariables, const ArgumentsPtrVector &rhsVariables) const;

  /**
   * @brief
   *
   * @param lhsChildren
   * @param rhsChildren
   * @return -1 if we should not swap the arguments
   * @return  1 if we should swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorChildren(const ArgumentsPtrVector &lhsChildren, const ArgumentsPtrVector &rhsChildren) const;

  /**
   * @brief
   *
   * @param lhsExpr
   * @param rhsExpr
   * @return -1 if we should not swap the arguments
   * @return  1 if we should swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorFunctions(const std::shared_ptr<const IExpression> &lhsExpr,
                          const std::shared_ptr<const IExpression> &rhsExpr) const;

  /**
   * @brief
   *
   * @param lhs
   * @param rhs
   * @return -1 if we should not swap the arguments
   * @return  1 if we should swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorTerms(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const;
};

template <typename Derived>
class IPolynomExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IPolynomExpression {
public:
  explicit IPolynomExpressionCRTP(const IFunction &func, const ArgumentsPtrVector &children) {
    this->func = cast<IFunction>(func.clone());

    for (const auto &child : children) {
      addElement(child);
    }
  }

  void addElement(const ArgumentPtr &element) final {
    ArgumentPtr elem = element;
    compressChild(elem);

    ArgumentsPtrVector elemPolynom;

    if (auto expr = cast<Derived>(elem)) {
      elemPolynom = expr->children;
    }

    if (!elemPolynom.empty()) {
      for (auto &child : elemPolynom) {
        children.emplace_back(child);
      }
    }
    else {
      children.emplace_back(elem);
    }
  }
};

}
