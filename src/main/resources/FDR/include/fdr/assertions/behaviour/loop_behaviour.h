#pragma once

#include <fdr/assertions/behaviour/behaviour.h>

namespace FDR
{
namespace Assertions
{
/// A behaviour that performs some trace, and then repeats a suffix.
///
/// This is used to represent divergences.
class LoopBehaviour : public Behaviour
{
public:
    LoopBehaviour(const std::shared_ptr<LTS::Machine>& machine,
                  const std::vector<std::shared_ptr<LTS::Node>>& node_path,
                  const std::vector<LTS::CompiledEvent>& trace, const unsigned int loop_index);

    /// The index at which the trace repeats.
    ///
    /// If this method returns i then node_path()[i..) can be appeneded to
    /// the end of node_path() repeatably (equally, for trace).
    unsigned int loop_index() const;

private:
    const unsigned int loop_index_;
};

}  // end Assertions
}  // end FDR
