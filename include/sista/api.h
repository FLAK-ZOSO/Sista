/** \file api.h
 *  \brief C API for Sista library
 *
 *  This header defines the C API for the Sista library, allowing interaction
 *  with core functionalities such as creating and managing SwappableFields
 *  and Pawns. The API is designed to be used in C programs, providing a
 *  bridge to the underlying C++ implementations and allowing for FFI usage
 *  with other programming languages thanks to ABI compatibility.
 *
 *  \author FLAK-ZOSO
 *  \date 2025
 *  \version 3.0.0
 *  \copyright GNU General Public License v3.0
 */
#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct sista_SwappableField;
typedef struct sista_SwappableField* SwappableFieldHandler_t;

/** \brief Creates a SwappableField with the specified width and height.
 *  \param width The width of the SwappableField.
 *  \param height The height of the SwappableField.
 *  \return A handler to the created SwappableField.
 *
 *  This function allocates and initializes a new SwappableField object
 *  with the given dimensions. It returns a pointer that can be used to
 *  reference the SwappableField in subsequent API calls.
 *
 *  \retval NULL If memory allocation fails.
 *
 *  \note The caller is responsible for managing the lifetime of the
 *        returned SwappableField object, including deallocation if necessary.
 *
 *  \see SwappableField
*/
SwappableFieldHandler_t sista_createSwappableField(size_t, size_t);
/** \brief Prints the specified Field with a given border
 *  \param field The SwappableField.
 *  \param border The border character to use.
 *
 *  This function prints the entire field to the terminal, using the specified
 *  character as the border around the field.
 *
 *  \see Field
 *  \see Border
*/
void sista_printField(SwappableFieldHandler_t, char);
/** \brief Deallocates the SwappableField from memory
 *  \param field The SwappableField to delete
 *
 *  This function deallocates the SwappableField from memory through the opaque
 *  handler pointing to it.
 *
 *  \see SwappableField
 */
void sista_destroySwappableField(SwappableFieldHandler_t);

/** \brief Resets ANSI settings to default.
 *
 *  This function resets the terminal's ANSI settings, including colors
 *  and attributes, to their default values.
 *
 *  \see sista::resetAnsi
*/
void sista_resetAnsi();

/** \enum sista_ForegroundColor
 *  \brief Predefined foreground colors for terminal text.
 *
 *  This enumeration defines a set of standard foreground colors that can be
 *  used to change the color of text in terminal applications using ANSI
 *  escape codes.
 *
 *  \see sista_setForegroundColor
 *  \see sista::ForegroundColor
*/
enum sista_ForegroundColor : int {
    F_BLACK = 30,
    F_RED = 31,
    F_GREEN = 32,
    F_YELLOW = 33,
    F_BLUE = 34,
    F_MAGENTA = 35,
    F_CYAN = 36,
    F_WHITE = 37
};
/** \enum sista_BackgroundColor
 *  \brief Predefined background colors for terminal text.
 *
 *  This enumeration defines a set of standard background colors that can be
 *  used to change the background color of text in terminal applications using
 *  ANSI escape codes.
 *
 *  \see sista_setBackgroundColor
 *  \see sista::BackgroundColor
*/
enum sista_BackgroundColor: int {
    B_BLACK = 40,
    B_RED = 41,
    B_GREEN = 42,
    B_YELLOW = 43,
    B_BLUE = 44,
    B_MAGENTA = 45,
    B_CYAN = 46,
    B_WHITE = 47
};
/** \enum sista_Attribute
 *  \brief Text attributes for terminal text.
 *
 *  This enumeration defines a set of text attributes that can be used to
 *  modify the appearance of text in terminal applications using ANSI escape
 *  codes. Attributes include styles such as bold, italic, underline, and more.
 *
 *  \see sista_setAttribute
 *  \see sista_resetAttribute
 *  \see sista::Attribute
*/
enum sista_Attribute: int {
    A_RESET = 0,
    A_BRIGHT = 1,
    A_FAINT = 2,
    A_ITALIC = 3,
    A_UNDERLINE = 4,
    A_BLINK_SLOW = 5,
    A_BLINK_FAST = 6,
    A_REVERSE = 7,
    A_CONCEAL = 8,
    A_CROSSED_OUT = 9
};
/** \struct sista_RGBColor
 *  \brief Represents an RGB color with red, green, and blue components.
 *
 *  This struct is used to define colors in terms of their red, green, and
 *  blue components, each ranging from 0 to 255. It can be used to set
 *  custom colors for terminal text and backgrounds using ANSI escape codes.
 *
 *  \see sista_setForegroundColor
 *  \see sista_setBackgroundColor
 *  \see sista::RGBColor
*/
struct sista_RGBColor {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

/** \brief Sets the foreground color using a predefined color.
 *  \param color The predefined foreground color to set.
 *
 *  This function sets the terminal's foreground color to one of the
 *  predefined colors specified in the sista_ForegroundColor enumeration.
 *  It outputs the corresponding ANSI escape code to standard output.
 *
 *  \see sista_ForegroundColor
 *  \see sista::setForegroundColor
*/
void sista_setForegroundColor(enum sista_ForegroundColor);
/** \brief Sets the background color using a predefined color.
 *  \param color The predefined background color to set.
 *
 *  This function sets the terminal's background color to one of the
 *  predefined colors specified in the sista_BackgroundColor enumeration.
 *  It outputs the corresponding ANSI escape code to standard output.
 *
 *  \see sista_BackgroundColor
 *  \see sista::setBackgroundColor
*/
void sista_setBackgroundColor(enum sista_BackgroundColor);
/** \brief Sets a text attribute.
 *  \param attribute The text attribute to set.
 *
 *  This function sets a text attribute, such as bold or underline,
 *  specified in the sista_Attribute enumeration. It outputs the
 *  corresponding ANSI escape code to standard output.
 *
 *  \see sista_Attribute
 *  \see sista::setAttribute
*/
void sista_setAttribute(enum sista_Attribute);
/** \brief Resets a text attribute.
 *  \param attribute The text attribute to reset.
 *
 *  This function resets a text attribute, such as bold or underline,
 *  specified in the sista_Attribute enumeration. It outputs the
 *  corresponding ANSI escape code to standard output.
 *
 *  \see sista_Attribute
 *  \see sista::resetAttribute
*/
void sista_resetAttribute(enum sista_Attribute);
/** \brief Sets the foreground color using an RGB color.
 *  \param color A pointer to a sista_RGBColor struct defining the color.
 *
 *  This function sets the terminal's foreground color using the RGB
 *  components specified in the provided sista_RGBColor struct. It outputs
 *  the corresponding ANSI escape code to standard output.
 *
 *  \note The function takes no effect if the pointer is nullptr.
 *
 *  \see sista_RGBColor
 *  \see sista::setForegroundColor
*/
void sista_setForegroundColorRGB(const struct sista_RGBColor*);
/** \brief Sets the background color using an RGB color.
 *  \param color A pointer to a sista_RGBColor struct defining the color.
 *
 *  This function sets the terminal's background color using the RGB
 *  components specified in the provided sista_RGBColor struct. It outputs
 *  the corresponding ANSI escape code to standard output.
 *
 *  \note The function takes no effect if the pointer is nullptr.
 *
 *  \see sista_RGBColor
 *  \see sista::setBackgroundColor
*/
void sista_setBackgroundColorRGB(const struct sista_RGBColor*);

#ifdef __cplusplus
}
#endif
