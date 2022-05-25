#pragma once

#include <fdr/assertions/behaviour/behaviour.h>

namespace FDR
{
namespace Assertions
{
class TraceBehaviour;

/// A behaviour of a machine that has been executed several times.
///
/// For example consider the process loop(P) where loop(P) = P ; loop(P).
/// Clearly, it is possible for a Behaviour to require P to be executed
/// multiple times. Any such Behaviour will be represented by a
/// SegmentedBehaviour, where each segment is actually a TraceBehaviour, where
/// TraceBehaviour::error_event() indicates the event that causes the next
/// segment to be started (in the above case it would be tick, indicating
/// termination). The actual erroroneous behaviour is stored in last(), which
/// could be a MinAcceptanceBehaviour etc (but is guaranteed not to be a
/// SegmentedBehaviour itself).
class SegmentedBehaviour : public Behaviour
{
public:
    SegmentedBehaviour(const std::shared_ptr<LTS::Machine>& machine,
                       const std::vector<std::shared_ptr<LTS::Node>>& node_path,
                       const std::vector<LTS::CompiledEvent>& trace, const std::shared_ptr<Behaviour>& behaviour,
                       const std::vector<std::shared_ptr<TraceBehaviour>>& prior_sections);

    /// The actual erroneous behaviour, which is the very last segment.
    std::shared_ptr<Behaviour> last() const;

    /// The segments that lead up to last().
    ///
    /// Each segment is a TraceBehaviour whose TraceBehaviour::error_event()
    /// indicates how the next segment is started.
    std::vector<std::shared_ptr<TraceBehaviour>> prior_sections() const;

private:
    const std::shared_ptr<Behaviour> last_;
    const std::vector<std::shared_ptr<TraceBehaviour>> prior_sections_;
};

}  // end Assertions
}  // end FDR
