#pragma once

#include <vector>

#include <fdr/lts/events.h>
#include <fdr/tasks/canceller.h>

namespace FDR
{
namespace LTS
{
class Node;

/// A single transition of a Machine.
class Transition
{
public:
    /// Creates a new, empty transition.
    Transition();

    /// Creates a transition with the given label and destination.
    Transition(CompiledEvent event, const std::shared_ptr<Node>& destination);

    /// The label of the arc this transition represents.
    CompiledEvent event() const;

    /// The destination of the arc.
    const std::shared_ptr<Node>& destination() const;

private:
    CompiledEvent event_;
    std::shared_ptr<Node> destination_;
};

/// A compiled state machine (a GLTS).
///
/// Note that the methods that are used to visit transitions of this machine are
/// not high-performance. If you are interested in such an interface please
/// contact us.
///
/// This MUST not be subclassed.
class Machine
{
public:
    Machine()
    {
    }
    virtual ~Machine(){};

    Machine(const Machine&) = delete;
    Machine& operator=(const Machine& machine) = delete;

    /// Returns the root, i.e. initial, node of this state machine.
    virtual std::shared_ptr<Node> root_node() const = 0;

    /// The set of events that the node can perform immediately.
    ///
    /// @param node The node to return the initials of. If this node is not
    ///     a node of this machine, the result is undefined.
    virtual std::vector<CompiledEvent> initials(const Node& node) const = 0;

    /// The set of states reachable from the given node via the given event.
    ///
    /// @param node The node to return the afters of. If this node is not
    ///     a node of this machine, the result is undefined.
    /// @param event The event for which destinations are required.
    ///     Must not be LTS::INVALID_EVENT.
    virtual std::vector<std::shared_ptr<Node>> afters(const Node& node, const CompiledEvent event) const = 0;

    /// The set of minimal acceptances of the given node.
    ///
    /// Note that if has_minimal_acceptance_labellings() is false, then this
    /// is equal to {initials()} providing initials() does not contain a
    /// tau, and is equal to {} if it does contain a tau.
    ///
    /// @param node The node to return the minimal acceptances of. If this
    ///     node is not a node of this machine, the result is undefined.
    virtual std::vector<std::vector<CompiledEvent>> minimal_acceptances(const Node& node) const = 0;

    /// The transitions available from the given node.
    virtual std::vector<Transition> transitions(const Node& node) const = 0;

    /// True if the state is considered to diverge.
    ///
    /// This will either be because the node is explicitly divergent
    /// and this machine has divergence labellings, or because there is
    /// a cycle of taus reachable from this state via other taus.
    ///
    /// @param node The node to test for divergence.
    /// @param canceller Since this is a long running operation, an optional
    ///     canceller may be provided to prematurely terminate computation.
    ///
    /// @throws CancelledError if the computation is cancelled before
    ///     a result is computed.
    virtual bool is_divergent(const Node& node, Canceller* canceller) const = 0;

    /// Returns the set of events used by this Machine.
    ///
    /// This set contains at least all of those events that are performable
    /// in some reachable state, but under some circumstances, may also
    /// include events that were in the definition of the machine, but are
    /// not performable in any reachable state.
    ///
    /// @param include_tau If true tau will be included in the alphabet, if
    ///     tau can be performed by this machine.
    ///
    /// @returns A set representing the alphabet.
    virtual std::vector<CompiledEvent> alphabet(bool include_tau) const = 0;

    /// Is the state labelled as explicitly divergent.
    virtual bool is_explicitly_divergent(const Node& node) const = 0;

    /// Does this GLTS have explicit divergence labels.
    ///
    /// If this is false, is_explicitly_divergent will always be false.
    virtual bool has_divergence_labellings() const = 0;

    /// Does this GLTS have explicit minimal acceptance labels.
    ///
    /// If this is false, minimal_acceptances will return {initials} if
    /// initials contains no tau, and {} otherwise.
    virtual bool has_minimal_acceptance_labellings() const = 0;
};

}  // end LTS
}  // end FDR
