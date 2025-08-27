/** \file version.hpp
 *  \brief Sista version information.
 *  \author FLAK-ZOSO
 *  \date 2022-2025
 *  \version 3.0.0
 */
#define SISTA_VERSION "3.0.0"
#define SISTA_VERSION_MAJOR 3
#define SISTA_VERSION_MINOR 0
#define SISTA_VERSION_PATCH 0

namespace sista {
    /** \brief Returns the Sista library version as a string.
     *  \return A string representing the Sista library version.
     *
     *  This function returns the version of the Sista library in the format "MAJOR.MINOR.PATCH".
     *  It is useful for logging, debugging, or displaying version information in applications
     *  that utilize the Sista library.
     *
     *  \see SISTA_VERSION
    */
    inline const char* getVersion() {
        return SISTA_VERSION;
    }
    /** \brief Returns the major version number of the Sista library.
     *  \return An integer representing the major version number.
     *
     *  This function returns the major version number of the Sista library.
     *  The major version typically indicates significant changes or milestones
     *  in the library's development.
     *
     *  \see SISTA_VERSION_MAJOR
    */
    inline int getVersionMajor() {
        return SISTA_VERSION_MAJOR;
    }
    /** \brief Returns the minor version number of the Sista library.
     *  \return An integer representing the minor version number.
     *
     *  This function returns the minor version number of the Sista library.
     *  The minor version typically indicates the addition of new features or
     *  improvements that are backward-compatible.
     *
     *  \see SISTA_VERSION_MINOR
    */
    inline int getVersionMinor() {
        return SISTA_VERSION_MINOR;
    }
    /** \brief Returns the patch version number of the Sista library.
     *  \return An integer representing the patch version number.
     *
     *  This function returns the patch version number of the Sista library.
     *  The patch version typically indicates bug fixes or minor changes that
     *  do not affect the overall functionality or compatibility of the library.
     *
     *  \see SISTA_VERSION_PATCH
    */
    inline int getVersionPatch() {
        return SISTA_VERSION_PATCH;
    }
};
