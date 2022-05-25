#pragma once

#include <fdr/assertions/assertion.h>
#include <fdr/lts/machine.h>
#include <fdr/lts/semantic_model.h>

namespace FDR
{
namespace Assertions
{
/// An assertion about processes.
class PropertyAssertion : public Assertion
{
public:
    PropertyAssertion(const PropertyAssertion& assertion) = delete;
    PropertyAssertion& operator=(const PropertyAssertion& assertion) = delete;

    /// The process that this assertion is about.
    ///
    /// This property is only available after the assertion has been
    /// compiled, which occurs during Assertion::execute().
    std::shared_ptr<LTS::Machine> machine() const;

    /// The semantic model this check has been performed in.
    LTS::SemanticModel semantic_model() const;

protected:
    PropertyAssertion();

    friend struct AssertionFactory;
};

}  // end Assertions
}  // end FDR
