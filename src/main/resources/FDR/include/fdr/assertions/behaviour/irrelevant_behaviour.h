#pragma once

#include <fdr/assertions/behaviour/behaviour.h>

namespace FDR
{
namespace Assertions
{
/// A path that is irrelevant to debugging the current counterexample.
///
/// For example, in assert STOP [T= STOP ||| a -> STOP, the STOP on the left
/// hand side of the interleave is irrelevant to the failure of the assertion,
/// and thus is represented using an IrrelevantBehaviour.
///
/// This also comes up as the beahviour of the specification process.
class IrrelevantBehaviour : public Behaviour
{
public:
    IrrelevantBehaviour(const std::shared_ptr<LTS::Machine>& machine,
                        const std::vector<std::shared_ptr<LTS::Node>>& node_path,
                        const std::vector<LTS::CompiledEvent>& trace);
};

}  // end Assertions
}  // end FDR
