#pragma once

#include <cstdint>

namespace FDR
{
namespace LTS
{
/// Represents a semantic model in which assertions can be performed.
enum class SemanticModel : std::uint8_t
{
    Default = 0,
    Traces = 1,
    Failures = 2,
    FailuresDivergences = 3,
    Refusals = 4,
    RefusalsDivergences = 5,
    Revivals = 6,
    RevivalsDivergences = 7,
};

}  // end LTS
}  // end FDR
