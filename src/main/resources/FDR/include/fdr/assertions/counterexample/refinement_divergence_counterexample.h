#pragma once

#include <fdr/assertions/counterexample/refinement_counterexample.h>

namespace FDR
{
namespace Assertions
{
/// A counterexample demonstrating how a process can diverge during a refinement
/// check.
///
/// In this case the specification behaviour is guaranteed to be a
/// IrrelevantBehaviour (ending in a non-divergent state of the specification),
/// whilst the implementation behaviour is guaranteed to be a
/// ExplicitDivergenceBehaviour or LoopBehaviour.
class RefinementDivergenceCounterexample : public RefinementCounterexample
{
public:
    RefinementDivergenceCounterexample(const std::shared_ptr<Behaviour>& specification,
                                       const std::shared_ptr<Behaviour>& implementation);
};

}  // end Assertions
}  // end FDR
