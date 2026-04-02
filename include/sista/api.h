/** \file api.h
 *  \brief C API for Sista library
 *
 *  This header defines the C API for the Sista library, allowing interaction
 *  with core functionalities such as creating and managing SwappableFields
 *  and Pawns. The API is designed to be used in C programs, providing a
 *  bridge to the underlying C++ implementations and allowing for FFI usage
 *  with other programming languages thanks to ABI compatibility.
 *
 *  \note This API is compatible with the C89 standard for maximum ABI stability.
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

/** \struct sista_Field
 *  \brief Opaque struct representing a Field object.
 *
 *  This struct is used as an opaque handle for managing Field objects
 *  in terminal applications. It encapsulates the internal state and
 *  configuration related to field representation and behavior.
 *
 *  \see sista::Field
*/
struct sista_Field;
typedef struct sista_Field* FieldHandler_t;

/** \brief Creates a Field with the specified width and height.
 *  \param width The width of the Field.
 *  \param height The height of the Field.
 *  \return A handler to the created Field.
 *
 *  This function allocates and initializes a new Field object
 *  with the given dimensions. It returns a pointer that can be used to
 *  reference the Field in subsequent API calls.
 *
 *  \retval NULL If memory allocation fails.
 *
 *  \warning The caller is responsible for managing the lifetime of the
 *        returned Field object, including deallocation if necessary.
 *
 *  \see Field
*/
FieldHandler_t sista_createField(size_t, size_t);
/** \brief Prints the specified Field with a given border
 *  \param field The Field.
 *  \param border The border character to use.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function prints the entire field to the terminal, using the specified
 *  character as the border around the field.
 *
 *  \see Field
 *  \see Border
 *  \retval SISTA_OK On success.
 *  \retval SISTA_ERR_NULL_FIELD If `field` is `NULL`.
*/
int sista_printField(FieldHandler_t, char);
/** \brief Deallocates the Field from memory
 *  \param field The Field to delete
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function deallocates the Field from memory through the opaque
 *  handler pointing to it.
 *
 *  \see Field
 *  \retval SISTA_OK On success.
 *  \retval SISTA_ERR_NULL_FIELD If `field` is `NULL`.
 */
int sista_destroyField(FieldHandler_t);

/** \struct sista_SwappableField
 *  \brief Opaque struct representing a SwappableField object.
 *
 *  This struct is used as an opaque handle for managing SwappableField
 *  objects in terminal applications. It encapsulates the internal state
 *  and configuration related to swappable fields.
 *
 *  \see sista::SwappableField
*/
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
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function prints the entire field to the terminal, using the specified
 *  character as the border around the field.
 *
 *  \see Field
 *  \see Border
 *  \retval SISTA_OK On success.
 *  \retval SISTA_ERR_NULL_FIELD If `field` is `NULL`.
*/
int sista_printSwappableField(SwappableFieldHandler_t, char);
/** \brief Deallocates the SwappableField from memory
 *  \param field The SwappableField to delete
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function deallocates the SwappableField from memory through the opaque
 *  handler pointing to it.
 *
 *  \see SwappableField
 *  \retval SISTA_OK On success.
 *  \retval SISTA_ERR_NULL_FIELD If `field` is `NULL`.
 */
int sista_destroySwappableField(SwappableFieldHandler_t);

/** \brief Resets ANSI settings to default.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function resets the terminal's ANSI settings, including colors
 *  and attributes, to their default values.
 *
 *  \see sista::resetAnsi
 *  \retval SISTA_OK On success.
*/
int sista_resetAnsi();

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
enum sista_ForegroundColor {
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
enum sista_BackgroundColor {
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
enum sista_Attribute {
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
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function sets the terminal's foreground color to one of the
 *  predefined colors specified in the sista_ForegroundColor enumeration.
 *  It outputs the corresponding ANSI escape code to standard output.
 *
 *  \see sista_ForegroundColor
 *  \see sista::setForegroundColor
 *  \retval SISTA_OK On success.
*/
int sista_setForegroundColor(enum sista_ForegroundColor);
/** \brief Sets the background color using a predefined color.
 *  \param color The predefined background color to set.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function sets the terminal's background color to one of the
 *  predefined colors specified in the sista_BackgroundColor enumeration.
 *  It outputs the corresponding ANSI escape code to standard output.
 *
 *  \see sista_BackgroundColor
 *  \see sista::setBackgroundColor
 *  \retval SISTA_OK On success.
*/
int sista_setBackgroundColor(enum sista_BackgroundColor);
/** \brief Sets a text attribute.
 *  \param attribute The text attribute to set.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function sets a text attribute, such as bold or underline,
 *  specified in the sista_Attribute enumeration. It outputs the
 *  corresponding ANSI escape code to standard output.
 *
 *  \see sista_Attribute
 *  \see sista::setAttribute
 *  \retval SISTA_OK On success.
*/
int sista_setAttribute(enum sista_Attribute);
/** \brief Resets a text attribute.
 *  \param attribute The text attribute to reset.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function resets a text attribute, such as bold or underline,
 *  specified in the sista_Attribute enumeration. It outputs the
 *  corresponding ANSI escape code to standard output.
 *
 *  \see sista_Attribute
 *  \see sista::resetAttribute
 *  \retval SISTA_OK On success.
*/
int sista_resetAttribute(enum sista_Attribute);
/** \brief Sets the foreground color using an RGB color.
 *  \param color A pointer to a sista_RGBColor struct defining the color.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function sets the terminal's foreground color using the RGB
 *  components specified in the provided sista_RGBColor struct. It outputs
 *  the corresponding ANSI escape code to standard output.
 *
 *  \retval SISTA_OK On success.
 *  \retval SISTA_ERR_NULL_COLOR If `color` is `NULL`.
 *
 *  \see sista_RGBColor
 *  \see sista::setForegroundColor
*/
int sista_setForegroundColorRGB(const struct sista_RGBColor*);
/** \brief Sets the background color using an RGB color.
 *  \param color A pointer to a sista_RGBColor struct defining the color.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function sets the terminal's background color using the RGB
 *  components specified in the provided sista_RGBColor struct. It outputs
 *  the corresponding ANSI escape code to standard output.
 *
 *  \retval SISTA_OK On success.
 *  \retval SISTA_ERR_NULL_COLOR If `color` is `NULL`.
 *
 *  \see sista_RGBColor
 *  \see sista::setBackgroundColor
*/
int sista_setBackgroundColorRGB(const struct sista_RGBColor*);

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
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function applies the specified ANSI settings to the terminal by
 *  outputting the corresponding ANSI escape codes to standard output.
 *
 *  \see sista::ANSISettings::apply
 *  \retval SISTA_OK On success.
 *  \retval SISTA_ERR_NULL_SETTINGS If `settings` is `NULL`.
*/
int sista_applyANSISettings(ANSISettingsHandler_t);
/** \brief Deallocates the ANSISettings from memory.
 *  \param settings The ANSISettings to delete.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function deallocates the ANSISettings from memory through the opaque
 *  handler pointing to it.
 *
 *  \see sista::ANSISettings
 *  \see sista_createANSISettings
 *  \retval SISTA_OK On success.
 *  \retval SISTA_ERR_NULL_SETTINGS If `settings` is `NULL`.
*/
int sista_destroyANSISettings(ANSISettingsHandler_t);

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
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function deallocates the Border from memory through the opaque
 *  handler pointing to it.
 *
 *  \see sista::Border
 *  \see sista_createBorder
 *  \retval SISTA_OK On success.
 *  \retval SISTA_ERR_NULL_BORDER If `border` is `NULL`.
*/
int sista_destroyBorder(BorderHandler_t);

/** \brief Prints the field with the specified border.
 *  \param field The Field to print.
 *  \param border The Border to print.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function prints the entire field to the terminal, using the specified
 *  Border object to draw the border around the field.
 *
 *  \see sista::Border::print
 *  \see sista::Field::print
 *  \retval SISTA_OK On success.
 *  \retval SISTA_ERR_NULL_FIELD If `field` is `NULL`.
 *  \retval SISTA_ERR_NULL_BORDER If `border` is `NULL`.
*/
int sista_printFieldWithBorder(FieldHandler_t, BorderHandler_t);
/** \brief Prints the field with the specified border.
 *  \param field The SwappableField to print.
 *  \param border The Border to print.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function prints the entire field to the terminal, using the specified
 *  Border object to draw the border around the field.
 *
 *  \see sista::Border::print
 *  \see sista::Field::print
 *  \retval SISTA_OK On success.
 *  \retval SISTA_ERR_NULL_FIELD If `field` is `NULL`.
 *  \retval SISTA_ERR_NULL_BORDER If `border` is `NULL`.
*/
int sista_printSwappableFieldWithBorder(SwappableFieldHandler_t, BorderHandler_t);

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

/** \struct sista_Pawn
 *  \brief Opaque struct representing a Pawn object.
 *
 *  This struct is used as an opaque handle for managing Pawn objects
 *  in terminal applications. It encapsulates the internal state and
 *  configuration related to pawn representation and behavior.
 *
 *  \see sista::Pawn
*/
struct sista_Pawn;
typedef struct sista_Pawn* PawnHandler_t;

/** \enum sista_ErrorCode
 *  \brief Error codes exposed by the C API for detailed diagnostics.
 *
 *  Functions that return opaque handlers may fail with `NULL`. In those cases,
 *  callers can use `sista_getLastErrorCode()` and `sista_getLastErrorMessage()`
 *  to retrieve the specific reason for the most recent failure on the current thread.
 */
enum sista_ErrorCode {
    SISTA_OK = 0,
    SISTA_ERR_NULL_FIELD = 1001,
    SISTA_ERR_NULL_SETTINGS = 1002,
    SISTA_ERR_OUT_OF_BOUNDS = 1003,
    SISTA_ERR_OCCUPIED = 1004,
    SISTA_ERR_BAD_ALLOC = 1005,
    SISTA_ERR_NULL_PAWN = 1006,
    SISTA_ERR_NULL_BORDER = 1007,
    SISTA_ERR_NULL_CURSOR = 1008,
    SISTA_ERR_NULL_COLOR = 1009,
    SISTA_ERR_UNKNOWN = 1099
};

/** \brief Creates a Pawn object in a given field.
 *  \param field The SwappableField to add the pawn to.
 *  \param symbol The character symbol for the pawn.
 *  \param settings The ANSISettings to apply to the pawn.
 *  \param position The initial position of the pawn.
 *  \return A handler to the created Pawn object.
 *
 *  This function allocates and initializes a new Pawn object with the
 *  specified symbol, ANSI settings, and initial position. It returns a
 *  pointer that can be used to reference the Pawn in subsequent API calls.
 *
 *  \retval NULL If creation fails for any reason.
 *
 *  \warning Unlike with other objects, the caller is NOT responsible for
 *           managing the lifetime of the returned Pawn object. Pawns are
 *           managed by the SwappableField they are added to, and will be
 *           deallocated when the SwappableField is destroyed.
 *
 *  \note On failure, call `sista_getLastErrorCode()` and
 *        `sista_getLastErrorMessage()` for details.
 *
 *  \see sista::Pawn
 *  \see sista_destroyPawn
*/
PawnHandler_t sista_createPawnInSwappableField(SwappableFieldHandler_t,
                                               char, ANSISettingsHandler_t,
                                               struct sista_Coordinates);
/** \brief Creates a Pawn object in a given field.
 *  \param field The Field to add the pawn to.
 *  \param symbol The character symbol for the pawn.
 *  \param settings The ANSISettings to apply to the pawn.
 *  \param position The initial position of the pawn.
 *  \return A handler to the created Pawn object.
 *
 *  This function allocates and initializes a new Pawn object with the
 *  specified symbol, ANSI settings, and initial position. It returns a
 *  pointer that can be used to reference the Pawn in subsequent API calls.
 *
 *  \retval NULL If creation fails for any reason.
 *
 *  \warning Unlike with other objects, the caller is NOT responsible for
 *           managing the lifetime of the returned Pawn object. Pawns are
 *           managed by the Field they are added to, and will be deallocated
 *           when the Field is destroyed.
 *
 *  \note On failure, call `sista_getLastErrorCode()` and
 *        `sista_getLastErrorMessage()` for details.
 *
 *  \see sista::Pawn
 *  \see sista_destroyPawn
*/
PawnHandler_t sista_createPawnInField(FieldHandler_t, char,
                                      ANSISettingsHandler_t,
                                      struct sista_Coordinates);

/** \brief Returns the last API error code for the current thread.
 *
 *  This value is updated by API functions that expose failure diagnostics,
 *  including functions that return `NULL` and functions that return a
 *  status code from `enum sista_ErrorCode`.
 *
 *  Successful calls participating in this model reset the value to `SISTA_OK`.
 *
 *  \return One value from `enum sista_ErrorCode`.
 */
int sista_getLastErrorCode();

/** \brief Returns the last API error message for the current thread.
 *
 *  The returned pointer remains valid until the next API call on the same thread
 *  that updates the last-error state.
 *
 *  Successful calls participating in this model reset the message to `"ok"`.
 *  Call this function immediately after a failing API call to read diagnostics.
 *
 *  \return A static, null-terminated message string.
 */
const char* sista_getLastErrorMessage();

/** \brief Moves the pawn to a new position.
 *  \param field The Field containing the Pawn.
 *  \param pawn The Pawn to move.
 *  \param destination The destination coordinates.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  On failure, this function also updates the per-thread last-error state
 *  accessible with `sista_getLastErrorCode()` and `sista_getLastErrorMessage()`.
 *
 *  \retval SISTA_OK If the move was successful.
 *  \retval SISTA_ERR_NULL_FIELD If `field` is `NULL`.
 *  \retval SISTA_ERR_NULL_PAWN If `pawn` is `NULL`.
 *  \retval SISTA_ERR_OUT_OF_BOUNDS If the destination is out of bounds.
 *  \retval SISTA_ERR_OCCUPIED If the destination is occupied or invalid.
 *  \retval SISTA_ERR_UNKNOWN If the move failed for another reason.
 *
 *  \see sista::Field::movePawn
*/
int sista_movePawn(FieldHandler_t, PawnHandler_t, struct sista_Coordinates);

/** \brief Adds the Pawn to a list of pawns to be moved ("swapped") later.
 *  \param field The SwappableField containing the Pawn.
 *  \param pawn The Pawn to add to the swap list.
 *  \param destination The destination coordinates.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function adds the specified Pawn to a list of pawns that will be
 *  moved (swapped) when sista_executeSwaps is called. The pawn will be moved
 *  to the specified destination coordinates.
 *
 *  On failure, this function also updates the per-thread last-error state
 *  accessible with `sista_getLastErrorCode()` and `sista_getLastErrorMessage()`.
 *
 *  \retval SISTA_OK If the pawn was successfully added to the swap list.
 *  \retval SISTA_ERR_NULL_FIELD If `field` is `NULL`.
 *  \retval SISTA_ERR_NULL_PAWN If `pawn` is `NULL`.
 *  \retval SISTA_ERR_OUT_OF_BOUNDS If the destination is out of bounds.
 *  \retval SISTA_ERR_OCCUPIED If the destination is occupied or invalid.
 *  \retval SISTA_ERR_UNKNOWN If adding the pawn to the swap list failed for another reason.
 *
 *  \see sista::SwappableField::addPawnToSwap
*/
int sista_addPawnToSwap(SwappableFieldHandler_t, PawnHandler_t, struct sista_Coordinates);
/** \brief Executes all pending pawn swaps.
 *  \param field The SwappableField containing the pawns to swap.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function executes all pending pawn swaps that have been added
 *  using sista_addPawnToSwap. It attempts to move each pawn to its
 *  specified destination, handling any conflicts or errors that arise.
 *
 *  \note The swaps that cannot be applied (due to more than one pawn
 *        trying to move to the same destination, generally) are skipped.
 * 
 *  \todo In future versions, the function may return a list of the
 *        swaps that could not be applied.
 *
 *  On failure, this function also updates the per-thread last-error state
 *  accessible with `sista_getLastErrorCode()` and `sista_getLastErrorMessage()`.
 *
 *  \retval SISTA_OK If all possible (read note) swaps were successful.
 *  \retval SISTA_ERR_NULL_FIELD If `field` is `NULL`.
 *  \retval SISTA_ERR_UNKNOWN If executing swaps failed for another reason.
 *
 *  \see sista::SwappableField::applySwaps
*/
int sista_applySwaps(SwappableFieldHandler_t);

/** \brief Clears the terminal screen and repositions the cursor.
 *  \param spaces Non-zero to clear visible content and scrollback buffer;
 *                zero to only move the cursor to the top-left corner.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This is the C API counterpart of `sista::clearScreen(bool)`.
 *
 *  \see sista::clearScreen
 *  \retval SISTA_OK On success.
*/
int sista_clearScreen(int spaces);

/** \enum sista_MoveCursor
 *  \brief Enumeration for cursor movement directions in ANSI escape codes.
 *
 *  This enum class defines various directions for moving the terminal cursor using ANSI escape codes.
 *  Each direction corresponds to a specific command character used in the escape sequences.
 *
 *  \see sista::MoveCursor
*/
enum sista_MoveCursor {
    UP = 'A',
    DOWN = 'B',
    RIGHT = 'C',
    LEFT = 'D',
    BEGINNING_OF_NEXT_LINE = 'E',
    BEGINNING_OF_PREVIOUS_LINE = 'F',
    HORIZONTAL_ABSOLUTE = 'G' /** Move to an absolute horizontal position (column). */
};

struct sista_Cursor;
typedef struct sista_Cursor* CursorHandler_t;

/** \brief Creates a cursor handler.
 *  \return A handler to the created Cursor object.
 *
 *  This function allocates and initializes a new Cursor object.
 *  It returns a pointer that can be used to reference the Cursor
 *  in subsequent API calls.
 *
 *  \retval NULL If memory allocation fails.
 *
 *  \warning The caller is responsible for managing the lifetime of the
 *           returned Cursor object, including deallocation if necessary.
 *
 *  \see sista::Cursor
*/
CursorHandler_t sista_createCursor();
/** \brief Moves the cursor in the specified direction by a given amount.
 *  \param cursor The Cursor handler.
 *  \param direction The direction to move the cursor.
 *  \param amount The number of positions to move the cursor.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function moves the terminal cursor in the specified direction
 *  by the given amount using ANSI escape codes.
 *
 *  \see sista::Cursor::move
 *  \retval SISTA_OK On success.
 *  \retval SISTA_ERR_NULL_CURSOR If `cursor` is `NULL`.
*/
int sista_moveCursor(CursorHandler_t, enum sista_MoveCursor, unsigned short);
/** \brief Moves the cursor to the specified coordinates.
 *  \param cursor The Cursor handler.
 *  \param y The y coordinate (row).
 *  \param x The x coordinate (column).
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function moves the terminal cursor to the specified (y, x)
 *  coordinates using ANSI escape codes.
 *
 *  \see sista::Cursor::goTo
 *  \retval SISTA_OK On success.
 *  \retval SISTA_ERR_NULL_CURSOR If `cursor` is `NULL`.
*/
int sista_cursorGoTo(CursorHandler_t, unsigned short, unsigned short);
/** \brief Moves the cursor to the specified coordinates.
 *  \param cursor The Cursor handler.
 *  \param coords The coordinates struct containing y and x.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function moves the terminal cursor to the specified (y, x)
 *  coordinates using ANSI escape codes.
 *
 *  \see sista::Cursor::goTo
 *  \retval SISTA_OK On success.
 *  \retval SISTA_ERR_NULL_CURSOR If `cursor` is `NULL`.
*/
int sista_cursorGoToCoordinates(CursorHandler_t, struct sista_Coordinates);
/** \brief Deallocates the Cursor from memory.
 *  \param cursor The Cursor to delete.
 *  \return Status code from `enum sista_ErrorCode`.
 *
 *  This function deallocates the Cursor from memory through the opaque
 *  handler pointing to it.
 *
 *  \see sista::Cursor
 *  \see sista_createCursor
 *  \retval SISTA_OK On success.
 *  \retval SISTA_ERR_NULL_CURSOR If `cursor` is `NULL`.
*/
int sista_destroyCursor(CursorHandler_t);

const char* sista_getVersion();
int sista_getVersionMajor();
int sista_getVersionMinor();
int sista_getVersionPatch();

#ifdef __cplusplus
}
#endif
