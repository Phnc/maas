#pragma once

#include <fdr/assertions/counterexample/counterexample.h>
#include <fdr/assertions/behaviour/behaviour.h>

namespace FDR
{
namespace Assertions
{
/// A counterexample to a refinement assertion.
///
/// This has two behaviours. Generally, the specification behaviour is not of
/// interest (the only exception is when the counterexample is a
/// Counterexample::Divergence), whilst the implementation behaviour exhibits
/// some behaviour of the implementation that is not allowed by the
/// specification process (e.g. an event the implementation can perform that
/// the specification cannot, in the case of a trace behaviour).
class RefinementCounterexample : public Counterexample
{
public:
    /// The behaviour of the implementation process.
    const std::shared_ptr<Behaviour>& implementation_behaviour() const;

    /// The behaviour of the specification process.
    const std::shared_ptr<Behaviour>& specification_behaviour() const;

protected:
    RefinementCounterexample(const std::shared_ptr<Behaviour>& specification,
                             const std::shared_ptr<Behaviour>& implementation);

private:
    std::shared_ptr<Behaviour> specification;
    std::shared_ptr<Behaviour> implementation;
};

}  // end Assertions
}  // end FDR
