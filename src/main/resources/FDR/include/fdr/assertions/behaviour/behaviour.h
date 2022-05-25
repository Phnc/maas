#pragma once

#include <vector>

#include <fdr/lts/events.h>
#include <fdr/lts/machine.h>
#include <fdr/lts/node.h>

namespace FDR
{
namespace Assertions
{
/// A particular path through a Machine, often leading to an interesting state.
///
/// A behaviour represents a single path in the state machine such that the last
/// state exhibits something interesting. For example, if this Behaviour is
/// actually a TraceBehaviour, then this means that last state can perform a
/// particular event. If this TraceBehaviour came from a trace refinement
/// assertion, then this means that the event was not allowed by the
/// specification.
class Behaviour
{
public:
    virtual ~Behaviour();

    Behaviour(const Behaviour&) = delete;
    Behaviour& operator=(const Behaviour&) = delete;

    /// The machine in which the behaviour occurs.
    std::shared_ptr<LTS::Machine> machine() const;

    /// The sequence of nodes leading to the behaviour.
    ///
    /// This includes the node at which the behaviour occurs. If
    /// node_path()[i] is null there are three possible reasons:
    ///
    /// 1. The machine did not perform an event, i.e. trace()[i-1] ==
    ///    LTS::INVALID_EVENT.
    /// 2. The node cannot be represented. This can occasionally happen
    ///    when unwinding compressions.
    /// 3. The machine has not been turned on yet. For example, consider
    ///    the process P = Q ; R. A behaviour of P has two sub-behaviours,
    ///    and the behaviour for R will start with a null node because R is
    ///    inactive (formally, off) until Q has terminated. In this case,
    ///    trace()[j] == LTS::INVALID_EVENT for all j < i.
    const std::vector<std::shared_ptr<LTS::Node>>& node_path() const;

    /// Returns the sequence of events that led to this behaviour.
    ///
    /// These are the events that cause transitions between different nodes
    /// in node_path(). Note that this can include LTS::INVALID_EVENT, which
    /// indicates that the machine did not perform any event.
    const std::vector<LTS::CompiledEvent>& trace() const;

protected:
    Behaviour(const std::shared_ptr<LTS::Machine>& machine, const std::vector<std::shared_ptr<LTS::Node>>& node_path,
              const std::vector<LTS::CompiledEvent>& events);

private:
    struct Data;

    friend class DebugContext;
    friend struct BehaviourFactory;
    std::unique_ptr<Data> data;
};

}  // end Assertions
}  // end FDR
