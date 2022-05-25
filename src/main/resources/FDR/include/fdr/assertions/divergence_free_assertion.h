#pragma once

#include <fdr/assertions/property_assertion.h>

namespace FDR
{
namespace Assertions
{
/// An assertion that the given machine is divergence free.
class DivergenceFreeAssertion : public PropertyAssertion
{
public:
    /// Construct a new divergence-freedom assertion.
    ///
    /// @param session The session associated with machine
    /// @param machine The machine to check.
    /// @param model The semantic model in which to perform the check. An
    ///     exception may be thrown in Assertion::execute() if this is not
    ///     a valid model for this assertion.
    DivergenceFreeAssertion(const std::shared_ptr<Session>& session, const std::shared_ptr<LTS::Machine>& machine,
                            const LTS::SemanticModel model);
    ~DivergenceFreeAssertion();

    DivergenceFreeAssertion(const DivergenceFreeAssertion& assertion) = delete;
    DivergenceFreeAssertion& operator=(const DivergenceFreeAssertion& assertion) = delete;

private:
    DivergenceFreeAssertion();

    friend struct AssertionFactory;
};

}  // end Assertions
}  // end FDR
