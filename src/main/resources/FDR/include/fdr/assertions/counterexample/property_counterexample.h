#pragma once

#include <fdr/assertions/counterexample/counterexample.h>
#include <fdr/assertions/behaviour/behaviour.h>

namespace FDR
{
namespace Assertions
{
/// A counterexample to a property assertion, such as deadlock freedom.
///
/// This has a single behaviour that shows how the specified machine can violate
/// a property assertion, such as deadlock freedom or divergence freedom.
class PropertyCounterexample : public Counterexample
{
public:
    /// The prohibited behaviour.
    const std::shared_ptr<Behaviour>& behaviour() const;

protected:
    PropertyCounterexample(const std::shared_ptr<Behaviour>& behaviour);

private:
    std::shared_ptr<Behaviour> behaviour_;
};

}  // end Assertions
}  // end FDR
