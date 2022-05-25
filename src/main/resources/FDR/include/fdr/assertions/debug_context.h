#pragma once

#include <memory>
#include <vector>

#include <fdr/assertions/behaviour/behaviour.h>
#include <fdr/tasks/canceller.h>
#include <fdr/tasks/progress_reporter.h>

namespace FDR
{
namespace Assertions
{
class PropertyCounterexample;
class RefinementCounterexample;

/// Allows counterexamples to be divided into behaviours of component processes.
///
/// Given a counterexample, FDR allows it to be divided into sub-behaviours of
/// components, thus allowing a form of debugging to occur. A DebugContext
/// is what performs this division. It is also responsible for fully aligning
/// any counterexamples that are found (i.e. it ensures that the traces of all
/// behaviours are the same length, so that if two different behaviours both
/// have an event not equal to LTS::INVALID_EVENT at index i, they must
/// synchronise).
class DebugContext
{
public:
    /// Creates a new debug context from a refinement check.
    ///
    /// This must be initialised using initialise before any other methods
    /// are called.
    ///
    /// @param counterexample The counterexample that is going to be
    ///     divided.
    /// @param elide_uninteresting_behaviours If true, FDR will elide any
    ///     'uninteresting' behaviours from the debug tree. An uninteresting
    ///     behaviour is defined as any behaviour that results from an
    ///     uninteresting compression. The FDR user interface elides
    ///     uninteresting defaults.
    DebugContext(const Assertions::RefinementCounterexample& counterexample, bool elide_uninteresting_behaviours);

    /// Creates a new debug context from a property check.
    ///
    /// This must be initialised using initialise before any other methods
    /// are called.
    ///
    /// @param counterexample The counterexample that is going to be
    ///     divided.
    /// @param elide_uninteresting_behaviours If true, FDR will elide any
    ///     'uninteresting' behaviours from the debug tree. An uninteresting
    ///     behaviour is defined as any behaviour that results from an
    ///     uninteresting compression. The FDR user interface elides
    ///     uninteresting defaults.
    DebugContext(const Assertions::PropertyCounterexample& counterexample, bool elide_uninteresting_behaviours);

    virtual ~DebugContext();

    DebugContext(DebugContext&) = delete;
    DebugContext& operator=(DebugContext&) = delete;

    /// Initialises the behaviour debug context.
    ///
    /// This must be called before any other methods are.
    ///
    /// @throws CancelledException if the canceller was cancelled before
    ///     this returns.
    void initialise(Canceller* canceller);

    /// Returns the identity of the task under which all tasks in this assertion will be created under.
    ///
    /// This will be a valid TaskId as soon as the DebugContext has been created.
    TaskId root_task_id() const;

    /// The top-level behaviours.
    ///
    /// If this was created using a RefinementCounterexample, this will have
    /// two behaviours, the first of which is for the specification machine
    /// and the second is for the implementation. If this was created using
    /// a PropertyCounterexample, this will have a single behaviour of the
    /// machine.
    std::vector<std::shared_ptr<Behaviour>> root_behaviours() const;

    /// Returns the children of the given behaviour.
    ///
    /// @param behaviour The behaviour to return the children of. Must be
    ///     a behaviour that has been returned by a method of this class.
    std::vector<std::shared_ptr<Behaviour>> behaviour_children(const Behaviour& behaviour) const;

    /// The union of the alphabets of all the machines in this debug tree.
    ///
    /// In some sense, this is the set of events that it makes sense to
    /// interpret this over.
    std::vector<LTS::CompiledEvent> full_alphabet() const;

    /// Assuming that behaviour.trace()[index] == TAU, returns the behaviour
    /// that performs the event, if any.
    ///
    /// For example, if the tau is a tau resulting from hiding, this will
    /// return the behaviour in the tree who actually performed the
    /// non-hidden event. If the tau results from non-determinism, then
    /// this will return nullptr.
    ///
    /// @param behaviour The behaviour in which to reveal the tau. Must be
    ///     a behaviour that has been returned by a method of this class.
    /// @param index The index of the tau in the behaviour trace to reveal.
    std::shared_ptr<Behaviour> reveal_tau(const Behaviour& behaviour, unsigned int index) const;
    
    /// Reveals all taus in the given trace.
    ///
    /// This looks at the trace of the specified behaviour, and for any indicies such that
    /// behaviour.trace()[index] == TAU and such that the tau resulted from hiding, computes the event that was hidden.
    /// This is equivalent to calling reveal_tau on each index.
    ///
    /// @param behaviour The behaviour in which to reveal the tau. Must be
    ///     a behaviour that has been returned by a method of this class.
    std::vector<LTS::CompiledEvent> reveal_taus_in_trace(const Behaviour& behaviour) const;
private:
    struct Data;

    std::unique_ptr<Data> data;
};

}  // end Assertions
}  // end FDR
