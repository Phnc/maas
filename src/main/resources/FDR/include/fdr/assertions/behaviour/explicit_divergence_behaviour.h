#pragma once

#include <fdr/assertions/behaviour/behaviour.h>

namespace FDR
{
namespace Assertions
{
/// A path to a state that is marked as explicitly divergent.
///
/// In this case machine()->has_divergence_markings() will be true.
class ExplicitDivergenceBehaviour : public Behaviour
{
public:
    ExplicitDivergenceBehaviour(const std::shared_ptr<LTS::Machine>& machine,
                                const std::vector<std::shared_ptr<LTS::Node>>& node_path,
                                const std::vector<LTS::CompiledEvent>& events);
};

}  // end Assertions
}  // end FDR
