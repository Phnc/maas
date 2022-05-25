#pragma once

#include <fdr/assertions/counterexample/property_counterexample.h>

namespace FDR
{
namespace Assertions
{
/// A counterexample demonstrating how a process can deadlock.
///
/// The behaviour is guaranteed to be a MinAcceptanceBehaviour with a
/// min acceptance of {}.
class DeadlockCounterexample : public PropertyCounterexample
{
public:
    DeadlockCounterexample(const std::shared_ptr<Behaviour>& behaviour);
};

}  // end Assertions
}  // end FDR
