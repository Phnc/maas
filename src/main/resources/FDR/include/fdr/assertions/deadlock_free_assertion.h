#pragma once

#include <fdr/assertions/property_assertion.h>

namespace FDR
{
namespace Assertions
{
/// An assertion that a process is deadlock free.
class DeadlockFreeAssertion : public PropertyAssertion
{
public:
    /// Construct a new deadlock-freedom assertion.
    ///
    /// @param session The session associated with machine
    /// @param machine The machine to check.
    /// @param model The semantic model in which to perform the check. An
    ///     exception may be thrown in Assertion::execute() if this is not
    ///     a valid model for this assertion.
    DeadlockFreeAssertion(const std::shared_ptr<Session>& session, const std::shared_ptr<LTS::Machine>& machine,
                          const LTS::SemanticModel model);
    ~DeadlockFreeAssertion();

    DeadlockFreeAssertion(const DeadlockFreeAssertion& assertion) = delete;
    DeadlockFreeAssertion& operator=(const DeadlockFreeAssertion& assertion) = delete;

private:
    DeadlockFreeAssertion();

    friend struct AssertionFactory;
};

}  // end Assertions
}  // end FDR
