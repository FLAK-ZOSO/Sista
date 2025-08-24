/** \file cursor.hpp
 *  \brief Cursor manipulation header file.
 * 
 *  This file contains the declaration of the Cursor class and related enums for terminal cursor manipulation.
 * 
 *  \author FLAK-ZOSO
 *  \date 2022-2025
 *  \version 3.0.0
 *  \see Cursor
 *  \copyright GNU General Public License v3.0
 */
#pragma once

#include "ansi.hpp"
#include "coordinates.hpp"

/** \def CHA
 *  \brief Cursor Horizontal Absolute ANSI command character.
 * 
 *  This macro defines the command character used in ANSI escape codes to move the cursor horizontally to an absolute position.
 *  It is represented as a character literal 'H'.
 * 
 *  \see VPA
*/
#define CHA 'H'
/** \def VPA
 *  \brief Vertical Position Absolute ANSI command character.
 * 
 *  This macro defines the command character used in ANSI escape codes to move the cursor vertically to an absolute position.
 *  It is represented as a character literal 'd'.
 * 
 *  \see CHA
*/
#define VPA 'd'

namespace sista {
    /** \brief Clears the terminal screen and optionally the scrollback buffer.
     *  \param spaces If true, clears both the screen and the scrollback buffer; if false, only moves the cursor to the top-left corner.
     *
     *  This function outputs ANSI escape codes to clear the terminal screen. If the `spaces` parameter is set to true,
     *  it also clears the scrollback buffer. After clearing, it moves the cursor to the top-left corner of the terminal.
     * 
     *  \note Clearing the scrollback buffer may not be necessary in all applications and can be omitted by setting `spaces` to false.
     *  \see CLS
     *  \see SSB
     *  \see TL
    */
    void clearScreen(bool spaces=true);

    /** \enum EraseScreen
     *  \brief Enumeration for screen erasure options in ANSI escape codes.
     *
     *  This enum class defines various options for erasing parts of the terminal screen using ANSI escape codes.
     *  Each option corresponds to a specific ANSI code value.
     *
     *  \see Cursor::eraseScreen
    */
    enum class EraseScreen: int {
        FROM_CURSOR_TO_END = 0, /** Erase from the cursor position to the end of the screen. */
        FROM_CURSOR_TO_BEGINNING = 1, /** Erase from the cursor position to the beginning of the screen. */
        ENTIRE_SCREEN = 2, /** Erase the entire screen. */
        ERASE_SAVED_LINES = 3, /** Erase all lines saved in the scrollback buffer. */
    };
    /** \enum EraseLine
     *  \brief Enumeration for line erasure options in ANSI escape codes.
     *
     *  This enum class defines various options for erasing parts of the current line in the terminal using ANSI escape codes.
     *  Each option corresponds to a specific ANSI code value.
     *
     *  \see Cursor::eraseLine
    */
    enum class EraseLine: int {
        LINE_FROM_CURSOR_TO_END = 0, /** Erase from the cursor position to the end of the line. */
        LINE_FROM_CURSOR_TO_BEGINNING = 1, /** Erase from the cursor position to the beginning of the line. */
        ENTIRE_LINE = 2, /** Erase the entire line. */
    };
    /** \enum MoveCursor
     *  \brief Enumeration for cursor movement directions in ANSI escape codes.
     *
     *  This enum class defines various directions for moving the terminal cursor using ANSI escape codes.
     *  Each direction corresponds to a specific command character used in the escape sequences.
     *
     *  \see Cursor::move(MoveCursor, unsigned short int)
    */
    enum class MoveCursor: char {
        UP = 'A',
        DOWN = 'B',
        RIGHT = 'C',
        LEFT = 'D',
        BEGINNING_OF_NEXT_LINE = 'E',
        BEGINNING_OF_PREVIOUS_LINE = 'F',
        HORIZONTAL_ABSOLUTE = 'G' /** Move to an absolute horizontal position (column). */
    };
    /** \enum MoveCursorDEC
     *  \brief Enumeration for DEC-specific cursor movement commands in ANSI escape codes.
     *
     *  This enum class defines specific commands for saving and restoring the cursor position using DEC (Digital Equipment Corporation) ANSI escape codes.
     *  Each command corresponds to a specific ANSI code value.
     *
     *  \see Cursor::move(MoveCursorDEC)
    */
    enum class MoveCursorDEC: int {
        SAVE_CURSOR_POSITION = 7,
        RESTORE_CURSOR_POSITION = 8
    };
    /** \enum MoveCursorSCO
     *  \brief Enumeration for SCO-specific cursor movement commands in ANSI escape codes.
     *
     *  This enum class defines specific commands for saving and restoring the cursor position using SCO (Santa Cruz Operation) ANSI escape codes.
     *  Each command corresponds to a specific command character used in the escape sequences.
     *
     *  \see Cursor::move(MoveCursorSCO)
    */
    enum class MoveCursorSCO: char {
        SCO_SAVE_CURSOR_POSITION = 's',
        SCO_RESTORE_CURSOR_POSITION = 'u'
    };
    
    /** \struct Cursor
     *  \brief Manages terminal cursor operations.
     *
     *  The Cursor struct provides methods to manipulate the terminal cursor, including moving to specific coordinates,
     *  erasing parts of the screen or line, and moving the cursor in various directions. It also handles hiding and
     *  showing the cursor upon creation and destruction.
     *
     *  \see EraseScreen
     *  \see EraseLine
     *  \see MoveCursor
     *  \see MoveCursorDEC
     *  \see MoveCursorSCO
    */
    struct Cursor {
    private:
        const static unsigned short int offset_y;
        const static unsigned short int offset_x;

    public:
        /** \brief Constructor that hides the cursor and clears the screen. */
        Cursor();
        /** \brief Destructor that shows the cursor and resets ANSI settings. */
        ~Cursor();

        /** \brief Moves the cursor to the specified (y, x) coordinates.
         *  \param y_ The y coordinate (row).
         *  \param x_ The x coordinate (column).
         *  \note The coordinates are 0-based for this function and are absolute positions on the terminal.
        */
        void goTo(unsigned short int, unsigned short int) const;
        /** \brief Moves the cursor to the specified Coordinates.
         *  \param coordinates_ A Coordinates instance specifying the (y, x) position.
         *  \note The coordinates are adjusted by predefined offsets to account for terminal borders or margins.
         *  \see sista::Coordinates
        */
        void goTo(sista::Coordinates) const;

        /** \brief Erases parts of the screen based on the specified EraseScreen option.
         *  \param eraseScreen_ The EraseScreen option specifying which part of the screen to erase.
         *
         *  This method outputs the appropriate ANSI escape code to erase parts of the terminal screen
         *  according to the selected option from the EraseScreen enum.
         *
         *  \see EraseScreen
        */
        void eraseScreen(EraseScreen) const;
        /** \brief Erases parts of the current line based on the specified EraseLine option.
         *  \param eraseLine_ The EraseLine option specifying which part of the line to erase.
         *  \param moveCursor If true, moves the cursor to the beginning of the line after erasure.
         *
         *  This method outputs the appropriate ANSI escape code to erase parts of the current line
         *  according to the selected option from the EraseLine enum. If moveCursor is true,
         *  it also moves the cursor to the start of the line after performing the erasure.
         *
         *  \see EraseLine
        */
        void eraseLine(EraseLine, bool=true) const;

        /** \brief Moves the cursor in the specified direction by a given number of positions.
         *  \param moveCursor_ The MoveCursor direction to move the cursor.
         *  \param n The number of positions to move the cursor (default is 1).
         *
         *  This method outputs the appropriate ANSI escape code to move the terminal cursor
         *  in the specified direction by the given number of positions.
         *
         *  \see MoveCursor
        */
        void move(MoveCursor, unsigned short int) const;
        /** \brief Moves the cursor using DEC-specific commands.
         *  \param moveCursorDEC_ The MoveCursorDEC command to execute (save or restore cursor position).
         *
         *  This method outputs the appropriate ANSI escape code to save or restore the cursor position
         *  using DEC-specific commands.
         *
         *  \see MoveCursorDEC
        */
        void move(MoveCursorDEC) const;
        /** \brief Moves the cursor using SCO-specific commands.
         *  \param moveCursorSCO_ The MoveCursorSCO command to execute (save or restore cursor position).
         *
         *  This method outputs the appropriate ANSI escape code to save or restore the cursor position
         *  using SCO-specific commands.
         *
         *  \see MoveCursorSCO
        */
        void move(MoveCursorSCO) const;
    };
};
