#pragma once

#include <fdr/assertions/behaviour/behaviour.h>

namespace FDR
{
namespace Assertions
{
/// A Behaviour that events in a state with a disallowed minimal acceptance.
///
/// For example, a deadlock is represented by a minimal acceptance behaviour
/// that ends with a state with a minimal acceptance of an empty set.
class MinAcceptanceBehaviour : public Behaviour
{
public:
    MinAcceptanceBehaviour(const std::shared_ptr<LTS::Machine>& machine,
                           const std::vector<std::shared_ptr<LTS::Node>>& node_path,
                           const std::vector<LTS::CompiledEvent>& trace,
                           const std::vector<LTS::CompiledEvent>& min_acceptance);

    /// The erroneous minimal acceptance.
    const std::vector<LTS::CompiledEvent>& min_acceptance() const;

private:
    const std::vector<LTS::CompiledEvent> min_acceptance_;
};

}  // end Assertions
}  // end FDR
