#pragma once

#include <fdr/assertions/assertion.h>
#include <fdr/lts/machine.h>
#include <fdr/lts/semantic_model.h>

namespace FDR
{
namespace Assertions
{
/// An refinement assertion about two processes.
class RefinementAssertion : public Assertion
{
public:
    /// Constructs a new refinement assertion about the specified machines.
    ///
    /// @param session The session associated with the machines.
    /// @param specification The specification, or left hand, process.
    /// @param model The semantic model in which to perform the check.
    /// @param implementation The implementation, or right hand, process.
    RefinementAssertion(const std::shared_ptr<Session>& session, const std::shared_ptr<LTS::Machine>& specification,
                        const LTS::SemanticModel model, const std::shared_ptr<LTS::Machine>& implementation);
    ~RefinementAssertion();

    RefinementAssertion(const RefinementAssertion& assertion) = delete;
    RefinementAssertion& operator=(const RefinementAssertion& assertion) = delete;

    /// The implementation process.
    ///
    /// This property is only available after the assertion has been
    /// compiled, which occurs during Assertion::execute().
    std::shared_ptr<LTS::Machine> implementation() const;

    /// The semantic model this check has been performed in.
    LTS::SemanticModel model() const;

    /// The specification process.
    ///
    /// This property is only available after the assertion has been
    /// compiled, which occurs during Assertion::execute().
    std::shared_ptr<LTS::Machine> specification() const;

private:
    RefinementAssertion();

    friend struct AssertionFactory;
};

}  // end Assertions
}  // end FDR
