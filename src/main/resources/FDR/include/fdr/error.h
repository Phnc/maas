#pragma once

#include <stdexcept>

namespace FDR
{
/// An error thrown by libfdr.
///
/// All errors that libfdr throws will be a subclasses of this.
class Error : public std::runtime_error
{
public:
    /// Creates a new error with the specified error message.
    Error(const std::string& description);
};

}  // end FDR
