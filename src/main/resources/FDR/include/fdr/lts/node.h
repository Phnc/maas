#pragma once

#include <cstddef>
#include <functional>
#include <memory>

namespace FDR
{
namespace LTS
{
/// A node (also known as state) in a GLTS.
///
/// This MUST not be subclassed.
class Node
{
public:
    Node(){};
    virtual ~Node(){};

    /// Compares two nodes for equality.
    ///
    /// Note, the nodes MUST be nodes of the same machine. Comparing two
    /// nodes of different machines is NOT supported under any circumstance.
    virtual bool operator==(const Node& node) const = 0;

    /// Compares two nodes for inequality.
    ///
    /// Note, the nodes MUST be nodes of the same machine. Comparing two
    /// nodes of different machines is NOT supported under any circumstance.
    virtual bool operator!=(const Node& node) const = 0;

    /// Returns the hash value of this event.
    virtual size_t hash_code() const = 0;
};

}  // end LTS
}  // end FDR

namespace std
{
template <>
struct hash<FDR::LTS::Node>
{
    size_t operator()(const FDR::LTS::Node& node) const
    {
        return node.hash_code();
    }
};

template <>
struct hash<std::shared_ptr<FDR::LTS::Node>>
{
    size_t operator()(const std::shared_ptr<FDR::LTS::Node>& node) const
    {
        return node ? node->hash_code() : 0;
    }
};

inline bool operator==(const std::shared_ptr<FDR::LTS::Node>& first, const std::shared_ptr<FDR::LTS::Node>& second)
{
    return first.get() == second.get() || *first == *second;
}

inline bool operator!=(const std::shared_ptr<FDR::LTS::Node>& first, const std::shared_ptr<FDR::LTS::Node>& second)
{
    return first.get() != second.get() && *first != *second;
}

}  // end std
