#pragma once

#include <fdr/assertions/property_assertion.h>

namespace FDR
{
namespace Assertions
{
/// An assertion that a process has a certain trace.
class HasTraceAssertion : public PropertyAssertion
{
public:
    /// Construct a new has trace assertion.
    ///
    /// @param session The session associated with machine
    /// @param machine The machine to check.
    /// @param model The semantic model in which to perform the check. An
    ///     exception may be thrown in Assertion::execute() if this is not
    ///     a valid model for this assertion.
    /// @param trace The trace to check can be performed by the machine.
    HasTraceAssertion(const std::shared_ptr<Session>& session, const std::shared_ptr<LTS::Machine>& machine,
                      const LTS::SemanticModel model, const std::vector<LTS::CompiledEvent>& trace);
    ~HasTraceAssertion();

    HasTraceAssertion(const HasTraceAssertion& assertion) = delete;
    HasTraceAssertion& operator=(const HasTraceAssertion& assertion) = delete;

private:
    HasTraceAssertion();

    friend struct AssertionFactory;
};

}  // end Assertions
}  // end FDR
