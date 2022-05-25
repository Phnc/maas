#pragma once

#include <fdr/assertions/counterexample/refinement_counterexample.h>

namespace FDR
{
namespace Assertions
{
/// A counterexample demonstrating non determinism in a process.
///
/// A determinism assertion can fail for two reasons:
///
/// 1. If a semantic model that involves Divergences is used, because the
///    implementation diverges. In this case, the implementation behaviour will
///    be a LTS::Behaviour::Loop or LTS::Behaviour::ExplicitDivergence, whilst
///    the specification behaviour will be a LTS::Behaviour::Irrelevant.
/// 2. Because the process can both perform a trace tr^\<a>, and refuse a after
///    performing the trace tr. In this case, the implementation will be a
///    LTS::Behaviour::Trace, whilst the specification behaviour will be a
///    LTS::Behaviour::MinAcceptance that are of the above form.
///
/// In this case the specification Behaviour is guaranteed to be a
/// LTS::Behaviour::Irrelevant (since the specification is an internal FDR
/// process), whilst the implementation Behaviour is guaranteed to be a
/// LTS::Behaviour::MinAcceptance.
class DeterminismCounterexample : public RefinementCounterexample
{
public:
    DeterminismCounterexample(const std::shared_ptr<Behaviour>& specification,
                              const std::shared_ptr<Behaviour>& implementation);
};

}  // end Assertions
}  // end FDR
