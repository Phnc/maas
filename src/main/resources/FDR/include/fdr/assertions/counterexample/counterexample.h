#pragma once

#include <memory>

namespace FDR
{
namespace Assertions
{
class Assertion;

/// A reason why an Assertion fails.
///
/// There are many different subclasses of this. The recommended method of
/// differentiating between them is to use dynamic_cast.
class Counterexample
{
public:
    virtual ~Counterexample();

    Counterexample(const Counterexample&) = delete;
    Counterexample& operator=(const Counterexample&) = delete;

protected:
    Counterexample();

private:
    struct Data;
    std::unique_ptr<Data> data;
    friend class DebugContext;
    friend struct CounterexampleFactory;
};

}  // end Assertions
}  // end FDR
