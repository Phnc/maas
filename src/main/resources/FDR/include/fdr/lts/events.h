#pragma once

namespace FDR
{
namespace LTS
{
/// An event in a constructed GLTS.
typedef unsigned int CompiledEvent;

enum
{
    /// A special event that indicates 'nothing happened'.
    ///
    /// For example, if this appears in a Behaviour trace, then this indicates
    /// that the particular component did not participate in the event
    /// performed.
    INVALID_EVENT = 0,

    /// The special tau event.
    TAU = 1,
};

}  // end LTS
}  // end FDR
