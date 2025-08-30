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
 *  \warning The caller is responsible for managing the lifetime of the
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
    A_BLINK = 5,
    A_BLINK_FAST = 6,
    A_REVERSE = 7,
    A_HIDDEN = 8,
    A_STRIKETHROUGH = 9
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
    unsigned char red; /** Red component (0-255) */
    unsigned char green; /** Green component (0-255) */
    unsigned char blue; /** Blue component (0-255) */
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

/** \struct sista_ANSISettings
 *  \brief Opaque struct representing ANSI settings.
 *
 *  This struct is used as an opaque handle for managing ANSI settings
 *  in terminal applications. It encapsulates the internal state and
 *  configuration related to ANSI escape codes.
 *
 *  \see sista::ANSISettings
*/
struct sista_ANSISettings;
typedef struct sista_ANSISettings* ANSISettingsHandler_t;

/** \brief Creates an ANSISettings object.
 *  \param fgColor The foreground color (predefined).
 *  \param bgColor The background color (predefined).
 *  \param attribute The text attribute to apply.
 *  \return A handler to the created ANSISettings object.
 *
 *  This function allocates and initializes a new ANSISettings object.
 *  It returns a pointer that can be used to reference the ANSISettings
 *  in subsequent API calls.
 *
 *  \retval NULL If memory allocation fails.
 *
 *  \warning The caller is responsible for managing the lifetime of the
 *        returned ANSISettings object, including deallocation if necessary.
 *
 *  \see sista::ANSISettings
 *  \see sista_destroyANSISettings
*/
ANSISettingsHandler_t sista_createANSISettings(enum sista_ForegroundColor,
                                               enum sista_BackgroundColor,
                                               enum sista_Attribute);
/** \brief Creates an ANSISettings object.
 *  \param fgColor The foreground color (RGB).
 *  \param bgColor The background color (RGB).
 *  \param attribute The text attribute to apply.
 *  \return A handler to the created ANSISettings object.
 *
 *  This function allocates and initializes a new ANSISettings object.
 *  It returns a pointer that can be used to reference the ANSISettings
 *  in subsequent API calls. Unlike sista_createANSISettings, it takes
 *  RGB colors for foreground and background.
 *
 *  \retval NULL If memory allocation fails.
 *
 *  \warning The caller is responsible for managing the lifetime of the
 *        returned ANSISettings object, including deallocation if necessary.
 *
 *  \note While the API only accepts either predefined colors or RGB colors,
 *        the underlying implementation supports mixing both types. This
 *        would require two more functions to be exposed in the API.
 *
 *  \see sista::ANSISettings
 *  \see sista_destroyANSISettings
*/
ANSISettingsHandler_t sista_createANSISettingsRGB(struct sista_RGBColor,
                                                  struct sista_RGBColor,
                                                  enum sista_Attribute);
/** \brief Applies the ANSI settings to the terminal.
 *  \param settings The ANSISettings to apply.
 *
 *  This function applies the specified ANSI settings to the terminal by
 *  outputting the corresponding ANSI escape codes to standard output.
 *
 *  \see sista::ANSISettings::apply
*/
void sista_applyANSISettings(ANSISettingsHandler_t);
/** \brief Deallocates the ANSISettings from memory.
 *  \param settings The ANSISettings to delete.
 *
 *  This function deallocates the ANSISettings from memory through the opaque
 *  handler pointing to it.
 *
 *  \see sista::ANSISettings
 *  \see sista_createANSISettings
*/
void sista_destroyANSISettings(ANSISettingsHandler_t);

/** \struct sista_Border
 *  \brief Opaque struct representing a Border object.
 *
 *  This struct is used as an opaque handle for managing Border objects
 *  in terminal applications. It encapsulates the internal state and
 *  configuration related to border representation.
 *
 *  \see sista::Border
*/
struct sista_Border;
typedef struct sista_Border* BorderHandler_t;

/** \brief Creates a Border object.
 *  \param symbol The character symbol for the border brick.
 *  \param settings The ANSISettings to apply to the border brick.
 *  \return A handler to the created Border object.
 *
 *  This function allocates and initializes a new Border object with the
 *  specified symbol and ANSI settings. It returns a pointer that can be
 *  used to reference the Border in subsequent API calls.
 *
 *  \retval NULL If memory allocation fails.
 *
 *  \warning The caller is responsible for managing the lifetime of the
 *        returned Border object, including deallocation if necessary.
 *
 *  \see sista::Border
 *  \see sista_destroyBorder
*/
BorderHandler_t sista_createBorder(char, ANSISettingsHandler_t);
/** \brief Deallocates the Border from memory.
 *  \param border The Border to delete.
 *
 *  This function deallocates the Border from memory through the opaque
 *  handler pointing to it.
 *
 *  \see sista::Border
 *  \see sista_createBorder
*/
void sista_destroyBorder(BorderHandler_t);

/** \brief Prints the field with the specified border.
 *  \param field The SwappableField to print.
 *  \param border The Border to print.
 *
 *  This function prints the entire field to the terminal, using the specified
 *  Border object to draw the border around the field.
 *
 *  \see sista::Border::print
 *  \see sista::Field::print
*/
void sista_printFieldWithBorder(SwappableFieldHandler_t, BorderHandler_t);

/** \struct sista_Coordinates
 *  \brief Represents a pair of coordinates (y, x).
 *
 *  This struct is used to define a pair of coordinates in a 2D space,
 *  typically representing a position in a grid or matrix. The y coordinate
 *  corresponds to the row, and the x coordinate corresponds to the column.
 *
 *  \see sista::Coordinates
*/
struct sista_Coordinates {
    unsigned short y; /** y coordinate */
    unsigned short x; /** x coordinate */
};

#ifdef __cplusplus
}
#endif
