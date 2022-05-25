#pragma once

#include <memory>
#include <vector>

namespace FDR
{
namespace Assertions
{
/// Represents progress through an assertion.
class Progress
{
public:
    virtual ~Progress();

    Progress(const Progress&) = delete;
    Progress& operator=(const Progress&) = delete;

protected:
    Progress();

    friend struct ProgressFactory;
};

/// Represents progress through a standard refinement check.
class BFSRefinementProgress : public Progress
{
public:
    ~BFSRefinementProgress();

    /// The number of plys (i.e. levels) of the breadth-first search.
    size_t plys() const;

    /// The total number of state pairs visited.
    size_t state_pairs_count() const;

    /// The total number of transitions visited.
    size_t transition_count() const;

private:
    BFSRefinementProgress();

    struct Data;
    std::unique_ptr<Data> data;

    friend struct ProgressFactory;
};

}  // end Assertions
}  // end FDR
