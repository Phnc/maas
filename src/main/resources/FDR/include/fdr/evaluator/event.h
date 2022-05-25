#pragma once

#include <functional>
#include <memory>
#include <vector>

namespace FDR
{
class Session;

namespace Evaluator
{
/// An uncompiled event.
///
/// This represents an event as viewed before conversion into a LTS. The main
/// difference to LTS::CompiledEvent is that this can be pretty-printed (i.e.
/// converted into a string), but it is less efficient.
///
/// This MUST not be subclassed.
class Event
{
public:
    Event(){};
    virtual ~Event(){};

    Event(const Event& event) = delete;
    Event& operator=(const Event& event) = delete;

    /// Compares two events for equality.
    ///
    /// Events from different sessions should not be mixed.
    virtual bool operator==(const Event& event) const = 0;

    /// Compares two events for inequality.
    ///
    /// Events from different sessions should not be mixed.
    virtual bool operator!=(const Event& event) const = 0;

    /// Returns the hash value of this event.
    virtual size_t hash_code() const = 0;

    /// Pretty prints this event.
    virtual std::string to_string() const = 0;
};

}  // end Evaluator
}  // end FDR

namespace std
{
template <>
struct hash<FDR::Evaluator::Event>
{
    size_t operator()(const FDR::Evaluator::Event& event) const
    {
        return event.hash_code();
    }
};

template <>
struct hash<std::shared_ptr<FDR::Evaluator::Event>>
{
    size_t operator()(const std::shared_ptr<FDR::Evaluator::Event>& event) const
    {
        return event ? event->hash_code() : 0;
    }
};

inline bool operator==(const std::shared_ptr<FDR::Evaluator::Event>& first,
                       const std::shared_ptr<FDR::Evaluator::Event>& second)
{
    return first.get() == second.get() || *first == *second;
}

inline bool operator!=(const std::shared_ptr<FDR::Evaluator::Event>& first,
                       const std::shared_ptr<FDR::Evaluator::Event>& second)
{
    return first.get() != second.get() && *first != *second;
}

}  // end std
