#pragma once

#include <fdr/assertions/behaviour/behaviour.h>

namespace FDR
{
namespace Assertions
{
/// A Behaviour that indicates the machine performed a prohibited event.
///
/// In this case, after performing trace(), the state machine can perform
/// error_event() which was not allowed according to the current specification.
class TraceBehaviour : public Behaviour
{
public:
    TraceBehaviour(const std::shared_ptr<LTS::Machine>& machine,
                   const std::vector<std::shared_ptr<LTS::Node>>& node_path,
                   const std::vector<LTS::CompiledEvent>& trace, const LTS::CompiledEvent error_event);

    /// The event considered to be disallowed.
    ///
    /// This is an event that can be performed by the machine in the last
    /// node of node_path(). It is guaranteed not to be LTS::INVALID_EVENT.
    LTS::CompiledEvent error_event() const;

private:
    const LTS::CompiledEvent error_event_;
};

}  // end Assertions
}  // end FDR
