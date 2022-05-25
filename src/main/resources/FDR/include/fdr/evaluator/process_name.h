#pragma once

#include <functional>
#include <memory>

namespace FDR
{
class Session;

namespace Evaluator
{
/// The name of a process in the input file.
///
/// This MUST not be subclassed.
class ProcessName
{
public:
    ProcessName(){};
    virtual ~ProcessName(){};

    ProcessName(const ProcessName& process_name) = delete;
    ProcessName& operator=(const ProcessName& event) = delete;

    /// Compares two process names for equality.
    ///
    /// ProcessNames from different sessions should not be mixed.
    virtual bool operator==(const ProcessName& event) const = 0;

    /// Compares two process names for inequality.
    ///
    /// ProcessNames from different sessions should not be mixed.
    virtual bool operator!=(const ProcessName& event) const = 0;

    /// Returns the hash value of this event.
    virtual size_t hash_code() const = 0;

    /// Pretty prints this process name.
    virtual std::string to_string() const = 0;
};

}  // end Evaluator
}  // end FDR

namespace std
{
template <>
struct hash<FDR::Evaluator::ProcessName>
{
    size_t operator()(const FDR::Evaluator::ProcessName& name) const
    {
        return name.hash_code();
    }
};

template <>
struct hash<std::shared_ptr<FDR::Evaluator::ProcessName>>
{
    size_t operator()(const std::shared_ptr<FDR::Evaluator::ProcessName>& name) const
    {
        return name ? name->hash_code() : 0;
    }
};

inline bool operator==(const std::shared_ptr<FDR::Evaluator::ProcessName>& first,
                       const std::shared_ptr<FDR::Evaluator::ProcessName>& second)
{
    return first.get() == second.get() || *first == *second;
}

inline bool operator!=(const std::shared_ptr<FDR::Evaluator::ProcessName>& first,
                       const std::shared_ptr<FDR::Evaluator::ProcessName>& second)
{
    return first.get() != second.get() && *first != *second;
}

}  // end std
