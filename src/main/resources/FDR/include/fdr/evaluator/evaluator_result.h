#pragma once

#include <string>
#include <vector>

namespace FDR
{
namespace Evaluator
{
/// Represents the result of evaluating something.
template <class R>
class EvaluatorResult
{
public:
    EvaluatorResult(const std::vector<std::string>& warnings, const R& result) : result_(result), warnings_(warnings)
    {
    }

    EvaluatorResult(const EvaluatorResult<R>&) = default;
    EvaluatorResult<R>& operator=(const EvaluatorResult<R>&) = default;

    /// The result that was obtained during the evaluation.
    const R& result() const
    {
        return result_;
    }

    /// The list of warnings generated when evaluating the expression.
    const std::vector<std::string>& warnings() const
    {
        return warnings_;
    }

private:
    R result_;
    std::vector<std::string> warnings_;
};

}  // end Evaluator
}  // end FDR
