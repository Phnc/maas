#pragma once

#include <fdr/assertions/counterexample/refinement_counterexample.h>

namespace FDR
{
namespace Assertions
{
/// A counterexample demonstrating how a trace refinement check failed.
///
/// In this case the specification Behaviour is guaranteed to be a
/// LTS::Behaviour::Irrelevant, whilst the implementation Behaviour is
/// guaranteed to be a LTS::Behaviour::Trace.
class TraceCounterexample : public RefinementCounterexample
{
public:
    TraceCounterexample(const std::shared_ptr<Behaviour>& specification,
                        const std::shared_ptr<Behaviour>& implementation);

    /// The event the implementation performed the specification could not.
    LTS::CompiledEvent error_event() const;
};

}  // end Assertions
}  // end FDR
