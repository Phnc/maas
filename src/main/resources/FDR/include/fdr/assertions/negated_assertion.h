#pragma once

#include <fdr/assertions/assertion.h>
#include <fdr/lts/machine.h>
#include <fdr/lts/semantic_model.h>

namespace FDR
{
namespace Assertions
{
/// A negated assertion.
///
/// This passes iff the inner assertion fails.
class NegatedAssertion : public Assertion
{
public:
    ~NegatedAssertion();

    NegatedAssertion(const NegatedAssertion& assertion) = delete;
    NegatedAssertion& operator=(const NegatedAssertion& assertion) = delete;

    /// The inner assertion, i.e. the assertion that is being negated.
    std::shared_ptr<Assertion> inner_assertion() const;

private:
    NegatedAssertion();

    friend struct AssertionFactory;
};

}  // end Assertions
}  // end FDR
