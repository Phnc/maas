#pragma once

#include <fdr/assertions/counterexample/property_counterexample.h>

namespace FDR
{
namespace Assertions
{
/// A counterexample to a divergence freedom assertion.
///
/// The behaviour is guaranteed to be a ExplicitDivergenceBehaviour or
/// LoopBehaviour indicating how the process can diverge.
class DivergenceCounterexample : public PropertyCounterexample
{
public:
    DivergenceCounterexample(const std::shared_ptr<Behaviour>& behaviour);
};

}  // end Assertions
}  // end FDR
