#pragma once

#include <string>
#include <vector>

namespace FDR
{
/// Initialises libfdr.
///
/// This must be called prior to any other function being called. Further, it
/// must be called from the main thread of the program.
void library_init();

/// Initialises libfdr.
///
/// This must be called prior to any other function being called. Further, it
/// must be called from the main thread of the program.
///
/// This version allows extra command line arguments to be set that will be
/// passed to Haskell and MPI.
///
/// @param argc Arguments as passed to the main function.
/// @param argv Arguments as passed to the main function.
void library_init(int* argc, char*** argv);

/// Actives an embedded copy of FDR, if applicable.
void activate_embedded_license(const std::string& payload, const std::string& signature);

/// Checks if a valid license exists for libfdr.
///
/// If this returns true then the API may be called without problem. However, if this returns false then the API may
/// not be used. You should prompt the user to either run refines or fdr4 to obtain a valid license. 
///
/// This should be called after library_init(), but before any other call.
bool has_valid_license();

/// Clears any storage used by libfdr.
///
/// This should be called before program exit. If it is called it must be called
/// from the main thread and no further calls to any libfdr functions (even to
/// library_exit or library_init again) may be made afterwards.
void library_exit();

/// Returns a representation the running version of FDR.
std::string version();

}  // end FDR
