#pragma once

#include <fdr/assertions/property_assertion.h>

namespace FDR
{
namespace Assertions
{
/// An assertion that the given machine is deterministic.
class DeterministicAssertion : public PropertyAssertion
{
public:
    /// Construct a new determinism assertion.
    ///
    /// @param session The session associated with machine
    /// @param machine The machine to check.
    /// @param model The semantic model in which to perform the check. An
    ///     exception may be thrown in Assertion::execute() if this is not
    ///     a valid model for this assertion.
    DeterministicAssertion(const std::shared_ptr<Session>& session, const std::shared_ptr<LTS::Machine>& machine,
                           const LTS::SemanticModel model);
    ~DeterministicAssertion();

    DeterministicAssertion(const DeterministicAssertion& assertion) = delete;
    DeterministicAssertion& operator=(const DeterministicAssertion& assertion) = delete;

private:
    DeterministicAssertion();

    friend struct AssertionFactory;
};

}  // end Assertions
}  // end FDR
