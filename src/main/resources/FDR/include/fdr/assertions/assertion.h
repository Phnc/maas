#pragma once

#include <memory>
#include <vector>

#include <fdr/error.h>
#include <fdr/tasks/progress_reporter.h>

namespace FDR
{
class Canceller;
class Session;

namespace Assertions
{
class Counterexample;
class Progress;

/// An assertion about processes.
///
/// For example, this may represent a deadlock freedom or refinement assertion.
class Assertion
{
public:
    virtual ~Assertion();

    Assertion(const Assertion& assertion) = delete;
    Assertion& operator=(const Assertion& assertion) = delete;

    /// Checks the given assertion.
    ///
    /// This is idempotent, and may be called harmlessly multiple times.
    ///
    /// @param canceller A canceller object that can be used to cancel an
    ///     in-progress check. If cancellation is not required, NULL may
    ///     be passed instead.
    ///
    /// @throws CancelledError if the canceller was cancelled during the
    ///     check.
    /// @throws CompilationError if the assertion could not be compiled
    ///     (i.e. converted into FDR's internal data structures) as a result
    ///     of an error detected in the input file.
    void execute(Canceller* canceller);

    /// A list of counterexamples, if the assertion failed.
    ///
    /// May only be called after execute() has returned.
    ///
    /// Note that if passed() is false does not necessarily imply that
    /// there are counterexamples. For example, if the assertion is negated
    /// then the inner assertion passing will not generate any
    /// counterexamples.
    const std::vector<std::shared_ptr<Counterexample>>& counterexamples() const;

    /// If the assertion has been executed, true iff the assertion passed.
    ///
    /// This may only be called once execute has returned.
    bool passed() const;

    /// Reports statistics about the assertion's progress.
    ///
    /// @returns an appropriate progress representation, or nullptr if
    ///     no progress information is available.
    std::shared_ptr<Progress> progress() const;

    /// Returns a string representation of this assertion.
    ///
    /// This will be a pretty-printed version of the assertion in the
    /// original input file.
    std::string to_string() const;

    /// Returns the identity of the task under which all tasks in this assertion will be created under.
    ///
    /// This will be INVALID_TASK until execute() has been called.
    TaskId root_task_id() const;

protected:
    Assertion();

    friend struct AssertionFactory;
    friend Session;

    struct Data;
    std::shared_ptr<Data> data;
};

}  // end Assertions
}  // end FDR
