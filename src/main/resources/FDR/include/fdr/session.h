#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <fdr/evaluator/evaluator_result.h>
#include <fdr/evaluator/event.h>
#include <fdr/evaluator/process_name.h>
#include <fdr/error.h>
#include <fdr/lts/events.h>
#include <fdr/lts/machine.h>
#include <fdr/lts/semantic_model.h>

namespace FDR
{
namespace Assertions
{
class Assertion;
class DeadlockFreeAssertion;
class DeterministicAssertion;
class DivergenceFreeAssertion;
class HasTraceAssertion;
class RefinementAssertion;

}  // end Assertions

/// Thrown when a file could not be loaded for some reason.
class FileLoadError : public Error
{
public:
    FileLoadError(const std::string& file_name, const std::string& error);

    /// The name of the file that was being loaded when the error occured.
    std::string file_name() const;

private:
    const std::string file_name_;
};

/// Thrown whenever an error in the user's input script is detected.
class InputFileError : public Error
{
public:
    InputFileError(const std::string& error);
};

/// A print statement in an input file.
class PrintStatement
{
public:
    PrintStatement();

    PrintStatement(const std::string& location, const std::string& expression);

    PrintStatement(const PrintStatement&) = default;
    PrintStatement& operator=(const PrintStatement&) = default;

    /// The expression that this print statement contains, i.e. the string
    /// after print.
    const std::string& expression() const;

    /// A representation of the location in the input file this expression
    /// is at.
    const std::string& source_location() const;

private:
    std::string expression_;
    std::string source_location_;
};

/// Encapsulates information about an input file.
///
/// A session allows CSP input files to be loaded, and then various data to be
/// extracted. For example, the assertions and print statements can be obtained,
/// and expressions can be evaluated.
class Session
{
public:
    /// Creates a new, empty session.
    ///
    /// Initially no file is loaded, so no print statements or assertions
    /// are available. Further, the only expressions that can be evaluated
    /// are those that involve only the standard CSPm functions.
    Session();
    ~Session();

    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;

    /// Loads a file into this session.
    ///
    /// This may only be called once on the session.
    ///
    /// @param file_path A path to a readable CSPm file.
    ///
    /// @throws FileLoadError when an error is encountered loading the file,
    ///     including type errors found when parsing the file.
    ///
    /// @returns A list of warnings generated during the load of the file.
    std::vector<std::string> load_file(const std::string& file_path);

    /// Loads the specified file using the specified contents strings.
    ///
    /// @param root_file_path The key of the root file in file_contents.
    /// @param file_contents A map that contains the contents of every file
    ///     that will be loaded whilst loading the root file.
    ///
    /// @throws FileLoadError when an error is encountered loading the file,
    ///     including type errors found when parsing the file.
    ///
    /// @returns A list of warnings that occured whilst loading the file.
    std::vector<std::string> load_strings_as_file(const std::string& root_file_path,
                                                  const std::map<std::string, std::string>& file_contents);

    /// The list of assertions that are loaded in this session.
    const std::vector<std::shared_ptr<Assertions::Assertion>>& assertions() const;

    /// The list of print statements in the input file.
    const std::vector<PrintStatement>& print_statements() const;

    /// Evaluates the expression, returning a string representation of the
    /// value.
    ///
    /// @param expression The expression to evaluate.
    /// @param canceller A canceller to cancel the compilation early, if
    ///     desired. May be nullptr.
    ///
    /// @throws CancelledError if the evaluation is cancelled.
    /// @throws InputFileError if an error is encountered whilst evaluating.
    Evaluator::EvaluatorResult<std::string> evaluate_expression(const std::string& expression,
                                                                Canceller* canceller) const;

    /// Evaluates an expression of type Proc into a state machine.
    ///
    /// @param expression The expression to attempt to compile. Must be
    ///     of type Proc.
    /// @param semantic_model The semantic model in which the process will
    ///     be compiled.
    /// @param canceller A canceller to cancel the compilation early, if
    ///     desired. May be nullptr.
    ///
    /// @throws CancelledError if the compilation is cancelled.
    /// @throws InputFileError if an error is encountered whilst converting
    ///     the expression into a state machine.
    Evaluator::EvaluatorResult<std::shared_ptr<LTS::Machine>> evaluate_process(const std::string& expression,
                                                                               const LTS::SemanticModel semantic_model,
                                                                               Canceller* canceller) const;

    /// Parses the given string as an assertion.
    ///
    /// @param assertion The assertion to be parsed. This should not include
    ///     assert, e.g. P [T= Q is valid, but assert P [T= Q is not.
    ///
    /// @throws CancelledError if the compilation is cancelled.
    /// @throws InputFileError if an error is encountered whilst parsing
    ///     the assertion.
    Evaluator::EvaluatorResult<std::shared_ptr<Assertions::Assertion>> parse_assertion(
        const std::string& assertion) const;

    /// Converts a raw event into the corresponding compiled event.
    LTS::CompiledEvent compile_event(const std::shared_ptr<Evaluator::Event>& event) const;

    /// Converts a compiled event into the original event.
    ///
    /// @param event The event to uncompile. This must not be
    ///     LTS::INVALID_EVENT.
    std::shared_ptr<Evaluator::Event> uncompile_event(const LTS::CompiledEvent event) const;

    /// As per uncompile_event, but uncompiles a list of events.
    std::vector<std::shared_ptr<Evaluator::Event>> uncompile_events(
        const std::vector<LTS::CompiledEvent>& events) const;

    /// The name the given machine was assigned in the input file, if any.
    ///
    /// @param machine The state machine to return the name of.
    ///
    /// @returns The name associated with the machine, or nullptr if there
    ///     is no name associated.
    std::shared_ptr<Evaluator::ProcessName> machine_name(const LTS::Machine& machine) const;

    /// The name the given machine node was assigned in the input file.
    ///
    /// @param machine The state machine to return the name of.
    ///
    /// @returns The name associated with the machine, or nullptr if none
    ///     is known.
    std::shared_ptr<Evaluator::ProcessName> machine_node_name(const LTS::Machine& machine, const LTS::Node& node) const;

private:
    struct Data;

    std::unique_ptr<Data> data;

    friend class Assertions::Assertion;
    friend class Assertions::DeadlockFreeAssertion;
    friend class Assertions::DeterministicAssertion;
    friend class Assertions::DivergenceFreeAssertion;
    friend class Assertions::HasTraceAssertion;
    friend class Assertions::RefinementAssertion;
};

}  // end FDR
