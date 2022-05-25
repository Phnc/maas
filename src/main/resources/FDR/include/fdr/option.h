#pragma once

#include <memory>
#include <string>
#include <vector>

#include <fdr/error.h>

namespace FDR
{
/// Thrown when an option is set to a disallowed value.
class DisallowedOptionValueError : public Error
{
public:
    DisallowedOptionValueError(const std::string& key, const std::string& value);
};

/// Thrown when an option is not known (i.e. the key is invalid).
class UnknownOptionError : public Error
{
public:
    UnknownOptionError(const std::string& key);
};

/// A setting for FDR.
///
/// See https://www.cs.ox.ac.uk/projects/fdr/manual/gui/options.html for a
/// description of the standard options that are accepted.
class Option
{
public:
    virtual ~Option()
    {
    }

    /// The values that the option is allowed to take.
    ///
    /// Note that this list may be empty in the case of options for which
    /// there is no finite set of allowed values.
    virtual std::vector<std::string> allowed_values() const = 0;

    /// The default value of this option.
    virtual std::string default_value() const = 0;

    /// The current value of this option.
    virtual std::string get() const = 0;

    /// A human-readable description of the option.
    virtual std::string description() const = 0;

    /// The current value of the option.
    virtual std::string name() const = 0;

    /// Sets the value of the option.
    ///
    /// @param new_value The value to set it to.
    ///
    /// @throws DisallowedOptionValueError if the option value is not
    ///     allowed.
    virtual void set(const std::string& new_value) = 0;

    /// Returns a list of all the options available.
    static const std::vector<std::shared_ptr<Option>>& options();

    /// Returns the Option with the specified name.
    ///
    /// @throws UnknownOptionError if the option is unknown.
    static const std::shared_ptr<Option>& get_option(const std::string& option_name);
};

}  // end FDR
