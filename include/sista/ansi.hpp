/**
 * \file ansi.hpp
 * \brief ANSI escape code utilities and types for terminal formatting.
 *
 * This header provides macros, enums, structs, and functions for working with
 * ANSI escape codes, including color, attribute, and screen mode settings.
 * It is part of the Sista library and is intended for use in terminal-based
 * applications requiring advanced text formatting and control.
 *
 * \author FLAK-ZOSO
 * \date 2022-2025
 * \version 3.0.0
 * \note Many niche features are not implemented, see references for more details.
 * \note Not all terminals support all ANSI features.
 * \see https://en.wikipedia.org/wiki/ANSI_escape_code
 * \see https://gist.github.com/ConnerWill/d4b6c776b509add763e17f9f113fd25b
 * \copyright GNU General Public License v3.0
 */
#pragma once

#include <variant>


/** \def ESC
 *  \brief Escape character for ANSI escape codes.
 *
 *  This macro defines the escape character used in ANSI escape codes.
 *  It is represented as a string literal containing the escape character.
 *
 *  \see CSI
 *  \see CLS
 *  \see SSB
 *  \see HIDE_CURSOR
 *  \see SHOW_CURSOR
 *  \see TL
*/
#define ESC "\x1b"
/** \def CSI
 *  \brief Control Sequence Introducer for ANSI escape codes.
 *
 *  This macro defines the Control Sequence Introducer (CSI) used in ANSI escape codes.
 *  It is represented as a string literal containing the escape character followed by
 *  the '[' character.
 *
 *  \see ESC
 *  \see CLS
 *  \see SSB
 *  \see TL
*/
#define CSI "\x1b["
/** \def CLS
 *  \brief Clear Screen ANSI escape code.
 *
 *  This macro defines the ANSI escape code for clearing the screen.
 *  It is represented as a string literal containing the appropriate escape sequence.
 *
 *  \see ESC
 *  \see CSI
 *  \see SSB
 *  \see TL
*/
#define CLS "\x1b[2J"
/** \def SSB
 *  \brief Erase Scrollback Buffer ANSI escape code.
 * 
 *  This macro defines the ANSI escape code for erasing the scrollback buffer.
 *  It is represented as a string literal containing the appropriate escape sequence.
 * 
 * \see ESC
 * \see CSI
 * \see CLS
 * \see TL
*/
#define SSB "\x1b[3J"
/** \def HIDE_CURSOR
 *  \brief Hide Cursor ANSI escape code.
 *
 *  This macro defines the ANSI escape code for hiding the cursor.
 *  It is represented as a string literal containing the appropriate escape sequence.
 *
 *  \see ESC
 *  \see CSI
 *  \see SHOW_CURSOR
*/
#define HIDE_CURSOR "\x1b[?25l"
/** \def SHOW_CURSOR
 *  \brief Show Cursor ANSI escape code.
 *
 *  This macro defines the ANSI escape code for showing the cursor.
 *  It is represented as a string literal containing the appropriate escape sequence.
 *
 *  \see ESC
 *  \see CSI
 *  \see HIDE_CURSOR
*/
#define SHOW_CURSOR "\x1b[?25h"
/** \def TL
 *  \brief Top Left ANSI escape code.
 *
 *  This macro defines the ANSI escape code for moving the cursor to the top-left corner of the screen.
 *  It is represented as a string literal containing the appropriate escape sequence.
 *
 *  \see ESC
 *  \see CSI
 *  \see CLS
 *  \see SSB
*/
#define TL "\x1b[H"


namespace sista {
    /** \enum ForegroundColor
     *  \brief Enumeration of foreground colors for ANSI escape codes.
     *
     *  This enum class defines various foreground colors that can be used in ANSI escape codes.
     *  Each color is associated with its corresponding ANSI code value, ranging from 30 to 37.
     *
     *  \see setForegroundColor(ForegroundColor)
    */
    enum class ForegroundColor: int {
        BLACK = 30,
        RED = 31,
        GREEN = 32,
        YELLOW = 33,
        BLUE = 34,
        MAGENTA = 35,
        CYAN = 36,
        WHITE = 37
    };
    /** \enum BackgroundColor
     *  \brief Enumeration of background colors for ANSI escape codes.
     *
     *  This enum class defines various background colors that can be used in ANSI escape codes.
     *  Each color is associated with its corresponding ANSI code value, ranging from 40 to 47.
     *
     *  \see setBackgroundColor(BackgroundColor)
    */
    enum class BackgroundColor: int {
        BLACK = 40,
        RED = 41,
        GREEN = 42,
        YELLOW = 43,
        BLUE = 44,
        MAGENTA = 45,
        CYAN = 46,
        WHITE = 47
    };
    /** \enum Attribute
     *  \brief Enumeration of text attributes for ANSI escape codes.
     *
     *  This enum class defines various text attributes that can be used in ANSI escape codes.
     *  Each attribute is associated with its corresponding ANSI code value, ranging from 0 to 9.
     *
     *  \see setAttribute(Attribute)
     *  \see resetAttribute(Attribute)
    */
    enum class Attribute: int {
        RESET = 0,
        BRIGHT = 1,
        FAINT = 2,
        ITALIC = 3,
        UNDERSCORE = 4,
        BLINK = 5,
        RAPID_BLINK = 6,
        REVERSE = 7,
        HIDDEN = 8,
        STRIKETHROUGH = 9
    };
    /** \struct RGBColor
     *  \brief Represents an RGB color with red, green, and blue components in True Color (24-bit).
     *
     *  This struct holds three numbers in (0-255) representing the red, green,
     *  and blue components of a color. It provides constructors for default and
     *  parameterized initialization. Default values are set to 0.
    */
    struct RGBColor {
        unsigned char red; /** Red component (0-255) */
        unsigned char green; /** Green component (0-255) */
        unsigned char blue; /** Blue component (0-255) */

        /** \brief Default constructor initializing color to black (0,0,0). */
        RGBColor();
        /** \brief Parameterized constructor.
         *  \param red The red component (0-255).
         *  \param green The green component (0-255).
         *  \param blue The blue component (0-255).
        */
        RGBColor(unsigned char, unsigned char, unsigned char);
    };

    /** \brief Sets the foreground color using a predefined ForegroundColor enum.
     *  \param color The ForegroundColor to set.
     *
     *  This function sets the terminal's foreground color based on the provided
     *  ForegroundColor enum value. It outputs the corresponding ANSI escape code
     *  to standard output.
     *
     *  \see ForegroundColor
    */
    void setForegroundColor(ForegroundColor);
    /** \brief Sets the background color using a predefined BackgroundColor enum.
     *  \param color The BackgroundColor to set.
     *
     *  This function sets the terminal's background color based on the provided
     *  BackgroundColor enum value. It outputs the corresponding ANSI escape code
     *  to standard output.
     *
     *  \see BackgroundColor
    */
    void setBackgroundColor(BackgroundColor);
    /** \brief Sets a text attribute using a predefined Attribute enum.
     *  \param attribute The Attribute to set.
     *
     *  This function sets the terminal's text attribute based on the provided
     *  Attribute enum value. It outputs the corresponding ANSI escape code
     *  to standard output.
     *
     *  \see Attribute
    */
    void setAttribute(Attribute);
    /** \brief Resets a text attribute using a predefined Attribute enum.
     *  \param attribute The Attribute to reset.
     *
     *  This function resets the terminal's text attribute based on the provided
     *  Attribute enum value. It outputs the corresponding ANSI escape code
     *  to standard output.
     *
     *  \see Attribute
    */
    void resetAttribute(Attribute);

    /** \brief Resets all ANSI settings to default values.
     *
     *  This function resets the terminal's text attributes, foreground color,
     *  and background color to their default values. It outputs the corresponding
     *  ANSI escape codes to standard output.
     *
     *  Default settings are:
     *  - Attribute: RESET
     *  - Foreground Color: WHITE
     *  - Background Color: BLACK
     *
     *  \see Attribute
     *  \see ForegroundColor
     *  \see BackgroundColor
    */
    void resetAnsi();

    /** \brief Sets the foreground color using an RGBColor struct.
     *  \param rgbcolor The RGBColor to set.
     *
     *  This function sets the terminal's foreground color based on the
     *  provided RGBColor struct. It extracts the red, green, and blue components
     *  and calls the appropriate function to set the color using RGB values.
     *
     *  \see RGBColor
    */
    void setForegroundColor(const RGBColor&);
    /** \brief Sets the background color using an RGBColor struct.
     *  \param rgbcolor The RGBColor to set.
     *
     *  This function sets the terminal's background color based on the
     *  provided RGBColor struct. It extracts the red, green, and blue components
     *  and calls the appropriate function to set the color using RGB values.
     *
     *  \see RGBColor
    */
    void setBackgroundColor(const RGBColor&);
    /** \brief Sets the foreground color using RGB values.
     *  \param red The red component (0-255).
     *  \param green The green component (0-255).
     *  \param blue The blue component (0-255).
     *
     *  This function sets the terminal's foreground color based on the provided
     *  RGB values. It outputs the corresponding ANSI escape code to standard output.
     *
     *  \see RGBColor
    */
    void setForegroundColor(unsigned char, unsigned char, unsigned char);
    /** \brief Sets the background color using RGB values.
     *  \param red The red component (0-255).
     *  \param green The green component (0-255).
     *  \param blue The blue component (0-255).
     *
     *  This function sets the terminal's background color based on the provided
     *  RGB values. It outputs the corresponding ANSI escape code to standard output.
     *
     *  \see RGBColor
    */
    void setBackgroundColor(unsigned char, unsigned char, unsigned char);
    /** \brief Sets the foreground color using a 256-color palette index.
     *  \param color The color index (0-255).
     *
     *  This function sets the terminal's foreground color based on the provided
     *  256-color palette index. It outputs the corresponding ANSI escape code
     *  to standard output.
     *
     *  \see 256-color palette
    */
    void setForegroundColor(unsigned char);
    /** \brief Sets the background color using a 256-color palette index.
     *  \param color The color index (0-255).
     *
     *  This function sets the terminal's background color based on the provided
     *  256-color palette index. It outputs the corresponding ANSI escape code
     *  to standard output.
     *
     *  \see 256-color palette
    */
    void setBackgroundColor(unsigned char);

    /** \enum ScreenMode
     *  \brief Represents various ANSI screen modes.
     *
     *  This enum defines [different screen modes](https://gist.github.com/ConnerWill/d4b6c776b509add763e17f9f113fd25b#set-mode)
     *  that can be set or unset using ANSI escape codes.
     *  Each mode corresponds to a specific configuration
     *  of text and graphics display.
    */
    enum class ScreenMode: int {
        MONOCROME_TEXT_40_25 = 0,
        COLOR_TEXT_40_25 = 1,
        MONOCROME_TEXT_80_25 = 2,
        COLOR_TEXT_80_25 = 3,
        FOUR_COLORS_GRAPHICS_320_200 = 4,
        MONOCROME_GRAPHICS_320_200 = 5,
        MONOCROME_GRAPHICS_640_200 = 6,
        LINE_WRAPPING = 7,
        COLOR_GRAPHICS_320_200 = 13,
        COLOR_16_COLORS_GRAPHICS_640_200 = 14,
        MONOCROME_2_COLORS_GRAPHICS_640_350 = 15,
        COLOR_16_COLORS_GRAPHICS_640_350 = 16,
        MONOCROME_2_COLORS_GRAPHICS_640_480 = 17,
        COLOR_16_COLORS_GRAPHICS_640_480 = 18,
        COLOR_256_COLORS_GRAPHICS_320_200 = 19
    };

    /** \brief Sets a specific screen mode.
     *  \param mode The ScreenMode to set.
     *
     *  This function sets the terminal's screen mode based on the provided
     *  ScreenMode enum value. It outputs the corresponding ANSI escape code
     *  to standard output.
     *
     *  \see ScreenMode
    */
    void setScreenMode(ScreenMode);
    /** \brief Unsets a specific screen mode.
     *  \param mode The ScreenMode to unset.
     *
     *  This function unsets the terminal's screen mode based on the provided
     *  ScreenMode enum value. It outputs the corresponding ANSI escape code
     *  to standard output.
     *
     *  \see ScreenMode
    */
    void unsetScreenMode(ScreenMode);

    /** \struct ANSISettings
     *  \brief Represents a set of ANSI settings including colors and attributes.
     *
     *  This struct holds the foreground color, background color, and text attribute
     *  settings for ANSI escape codes. It provides constructors for various combinations
     *  of color types (predefined enums and RGB colors) and a method to apply these
     *  settings to the terminal.
    */
    struct ANSISettings {
        /** 
         * \brief Foreground color, can be ForegroundColor or RGBColor.
         *
         *  This variant holds either a predefined ForegroundColor enum value
         *  or an RGBColor struct for custom colors.
         *
         *  \see ForegroundColor
         *  \see RGBColor
        */
        std::variant<ForegroundColor, RGBColor> foregroundColor;
        /** 
         * \brief Background color, can be BackgroundColor or RGBColor.
         *
         *  This variant holds either a predefined BackgroundColor enum value
         *  or an RGBColor struct for custom colors.
         *
         *  \see BackgroundColor
         *  \see RGBColor
        */
        std::variant<BackgroundColor, RGBColor> backgroundColor;
        /** \brief Text attribute setting. */
        Attribute attribute;

        /** Default constructor initializing to white foreground, black background, and reset attribute. */
        ANSISettings();
        /** \brief Parameterized constructor with RGBColor for both foreground and background.
         *  \param foregroundColor_ The RGBColor for the foreground.
         *  \param backgroundColor_ The RGBColor for the background.
         *  \param attribute_ The text Attribute.
        */
        ANSISettings(const RGBColor&, const RGBColor&, const Attribute&);
        /** \brief Parameterized constructor with ForegroundColor and BackgroundColor enums.
         *  \param foregroundColor_ The ForegroundColor for the foreground.
         *  \param backgroundColor_ The BackgroundColor for the background.
         *  \param attribute_ The text Attribute.
        */
        ANSISettings(const ForegroundColor&, const BackgroundColor&, const Attribute&);
        /** \brief Parameterized constructor with ForegroundColor enum and RGBColor for background.
         *  \param foregroundColor_ The ForegroundColor for the foreground.
         *  \param backgroundColor_ The RGBColor for the background.
         *  \param attribute_ The text Attribute.
        */
        ANSISettings(const RGBColor&, const BackgroundColor&, const Attribute&);
        /** \brief Parameterized constructor with RGBColor for foreground and BackgroundColor enum.
         *  \param foregroundColor_ The RGBColor for the foreground.
         *  \param backgroundColor_ The BackgroundColor for the background.
         *  \param attribute_ The text Attribute.
        */
        ANSISettings(const ForegroundColor&, const RGBColor&, const Attribute&);

        /** \brief Applies the ANSI settings to the terminal.
         *
         *  This method applies the stored foreground color, background color,
         *  and text attribute settings to the terminal by calling the appropriate
         *  functions to set each property.
         * 
         *  The settings will be visible on characters printed after this call.
         *
         *  \see setForegroundColor
         *  \see setBackgroundColor
         *  \see setAttribute
        */
        void apply() const;
    };
};
