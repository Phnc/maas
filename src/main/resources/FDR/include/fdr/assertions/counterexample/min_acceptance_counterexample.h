#pragma once

#include <fdr/assertions/counterexample/refinement_counterexample.h>

namespace FDR
{
namespace Assertions
{
/// A counterexample demonstrating how a failures refinement check failed.
///
/// In this case the specification Behaviour is guaranteed to be a
/// LTS::Behaviour::Irrelevant, whilst the implementation Behaviour is
/// guaranteed to be a LTS::Behaviour::MinAcceptance.
class MinAcceptanceCounterexample : public RefinementCounterexample
{
public:
    MinAcceptanceCounterexample(const std::shared_ptr<Behaviour>& specification,
                                const std::shared_ptr<Behaviour>& implementation);

    /// The set of events the implementation is guaranteed to be accepted.
    ///
    /// The erroneous set of events that are accepted by the implementation,
    /// but is not a superset of any of the specification acceptances.
    const std::vector<LTS::CompiledEvent>& min_acceptance() const;
};

}  // end Assertions
}  // end FDR
