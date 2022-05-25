#pragma once

#include <memory>

#include <fdr/error.h>

namespace FDR
{
/// Thrown whenever a cancellation is detected.
///
/// Note that this is not guaranteed to be thrown if the cancellation is not
/// picked up in time.
class CancelledError : public Error
{
public:
    CancelledError();
};

/// Allows cancellation of a running task to be requested.
///
/// Many of the tasks in FDR, such as checking a refinement assertion can be
/// long-running, and thus may need to be cancelled before their natural
/// completion. Cancellers allow this by supplying a cancel() method that
/// requests cancellation of a certain task, which will endeavour to return as
/// soon as it is safe to do so.
///
/// For example, a refinement assertion may be cancelled by using code similar
/// to the following:
///
/// \code{.cpp}
/// std::shared_ptr<Assertion> assertion = ...;
/// std::unique_ptr<Canceller> canceller(new Canceller());
/// std::thread refinement_thread([&canceller, assertion]){
///     try {
///         assertion->execute(canceller.get());
///     }
///     catch (const CancellerError&) {
///         std::cout << "Cancellation took place." << std::endl;
///     }
/// }
///
/// // .. perform some other task
///
/// // Cancel the refinement check
/// canceller.cancel();
/// // Wait for the cancellation to complete.
/// refinement_thread.join();
/// \endcode
///
/// If you do not wish to allow for cancellation, then nullptr can always be
/// passed to any function in place of a Canceller.
class Canceller
{
public:
    /// Creates a new canceller.
    Canceller();
    ~Canceller();

    Canceller(const Canceller&) = delete;
    Canceller& operator=(const Canceller&) = delete;

    /// Returns true if this canceller has been cancelled.
    bool cancelled() const;

    /// Mark this canceller as cancelled.
    ///
    /// This is NOT safe to call from a signal handler.
    void cancel();

private:
    struct Data;
    std::unique_ptr<Data> data;

    friend struct CancellerHelper;
};

}  // end FDR
