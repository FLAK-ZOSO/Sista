/** \file api.cpp
 *  \brief Implementation of the C API for Sista
 *
 *  This file contains the implementation of the C API functions declared in
 *  api.h. It provides a C-compatible interface to interact with the Sista
 *  library, allowing for operations on SwappableField objects.
 *
 *  \author FLAK-ZOSO
 *  \date 2025
 *  \version 3.0.0
 *  \copyright GNU General Public License v3.0
 */
#include <sista/api.h>
#include <sista/sista.hpp>
#include <stdexcept>

using namespace sista;

extern "C" {
    static thread_local int sista_last_error_code = SISTA_OK;
    static thread_local const char* sista_last_error_message = "ok";

    static void sista_set_last_error(int code, const char* message) {
        sista_last_error_code = code;
        sista_last_error_message = message;
    }

    static void sista_clear_last_error() {
        sista_set_last_error(SISTA_OK, "ok");
    }

    FieldHandler_t sista_createField(size_t width, size_t height) {
        sista_clear_last_error();
        try {
            return reinterpret_cast<FieldHandler_t>(
                new Field(static_cast<int>(width), static_cast<int>(height))
            );
        } catch (const std::bad_alloc&) {
            sista_set_last_error(SISTA_ERR_BAD_ALLOC, "memory allocation failed while creating Field");
            return NULL;
        }
    }
    int sista_destroyField(FieldHandler_t field) {
        sista_clear_last_error();
        if (field == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_FIELD, "field is null");
            return SISTA_ERR_NULL_FIELD;
        }
        delete reinterpret_cast<Field*>(field);
        return SISTA_OK;
    }
    SwappableFieldHandler_t sista_createSwappableField(size_t width, size_t height) {
        sista_clear_last_error();
        try {
            return reinterpret_cast<SwappableFieldHandler_t>(
                new SwappableField(static_cast<int>(width), static_cast<int>(height))
            );
        } catch (const std::bad_alloc&) {
            sista_set_last_error(SISTA_ERR_BAD_ALLOC, "memory allocation failed while creating SwappableField");
            return NULL;
        }
    }
    int sista_destroySwappableField(SwappableFieldHandler_t field) {
        sista_clear_last_error();
        if (field == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_FIELD, "field is null");
            return SISTA_ERR_NULL_FIELD;
        }
        delete reinterpret_cast<SwappableField*>(field);
        return SISTA_OK;
    }

    int sista_printField(FieldHandler_t field, char border) {
        sista_clear_last_error();
        if (field == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_FIELD, "field is null");
            return SISTA_ERR_NULL_FIELD;
        }
        reinterpret_cast<Field*>(field)->print(border);
        return SISTA_OK;
    }
    int sista_printSwappableField(SwappableFieldHandler_t field, char border) {
        sista_clear_last_error();
        if (field == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_FIELD, "field is null");
            return SISTA_ERR_NULL_FIELD;
        }
        reinterpret_cast<SwappableField*>(field)->print(border);
        return SISTA_OK;
    }

    int sista_resetAnsi() {
        sista_clear_last_error();
        sista::resetAnsi();
        return SISTA_OK;
    }
    int sista_setForegroundColor(enum sista_ForegroundColor color) {
        sista_clear_last_error();
        sista::setForegroundColor(static_cast<sista::ForegroundColor>(color));
        return SISTA_OK;
    }
    int sista_setBackgroundColor(enum sista_BackgroundColor color) {
        sista_clear_last_error();
        sista::setBackgroundColor(static_cast<sista::BackgroundColor>(color));
        return SISTA_OK;
    }
    int sista_setAttribute(enum sista_Attribute attribute) {
        sista_clear_last_error();
        sista::setAttribute(static_cast<sista::Attribute>(attribute));
        return SISTA_OK;
    }
    int sista_resetAttribute(enum sista_Attribute attribute) {
        sista_clear_last_error();
        sista::resetAttribute(static_cast<sista::Attribute>(attribute));
        return SISTA_OK;
    }
    int sista_setForegroundColorRGB(const struct sista_RGBColor* color) {
        sista_clear_last_error();
        if (color == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_COLOR, "color is null");
            return SISTA_ERR_NULL_COLOR;
        }
        sista::setForegroundColor(
            color->red,
            color->green,
            color->blue
        );
        return SISTA_OK;
    }
    int sista_setBackgroundColorRGB(const struct sista_RGBColor* color) {
        sista_clear_last_error();
        if (color == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_COLOR, "color is null");
            return SISTA_ERR_NULL_COLOR;
        }
        sista::setBackgroundColor(
            color->red,
            color->green,
            color->blue
        );
        return SISTA_OK;
    }

    ANSISettingsHandler_t sista_createANSISettings(
        enum sista_ForegroundColor fgColor,
        enum sista_BackgroundColor bgColor,
        enum sista_Attribute attribute
    ) {
        sista_clear_last_error();
        try {
            return reinterpret_cast<ANSISettingsHandler_t>(
                new sista::ANSISettings(
                    static_cast<sista::ForegroundColor>(fgColor),
                    static_cast<sista::BackgroundColor>(bgColor),
                    static_cast<sista::Attribute>(attribute)
                )
            );
        } catch (const std::bad_alloc&) {
            sista_set_last_error(SISTA_ERR_BAD_ALLOC, "memory allocation failed while creating ANSISettings");
            return NULL;
        }
    }
    ANSISettingsHandler_t sista_createANSISettingsRGB(
        struct sista_RGBColor fgColor,
        struct sista_RGBColor bgColor,
        sista_Attribute attribute
    ) {
        sista_clear_last_error();
        try {
            return reinterpret_cast<ANSISettingsHandler_t>(
                new sista::ANSISettings(
                    sista::RGBColor(fgColor.red, fgColor.green, fgColor.blue),
                    sista::RGBColor(bgColor.red, bgColor.green, bgColor.blue),
                    static_cast<sista::Attribute>(attribute)
                )
            );
        } catch (const std::bad_alloc&) {
            sista_set_last_error(SISTA_ERR_BAD_ALLOC, "memory allocation failed while creating ANSISettings (RGB)");
            return NULL;
        }
    }
    int sista_destroyANSISettings(ANSISettingsHandler_t settings) {
        sista_clear_last_error();
        if (settings == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_SETTINGS, "settings is null");
            return SISTA_ERR_NULL_SETTINGS;
        }
        delete reinterpret_cast<sista::ANSISettings*>(settings);
        return SISTA_OK;
    }

    int sista_applyANSISettings(ANSISettingsHandler_t settings) {
        sista_clear_last_error();
        if (settings == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_SETTINGS, "settings is null");
            return SISTA_ERR_NULL_SETTINGS;
        }
        reinterpret_cast<sista::ANSISettings*>(settings)->apply();
        return SISTA_OK;
    }

    BorderHandler_t sista_createBorder(char symbol, ANSISettingsHandler_t settings) {
        sista_clear_last_error();
        if (settings == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_SETTINGS, "settings is null");
            return NULL;
        }
        try {
            return reinterpret_cast<BorderHandler_t>(
                new sista::Border(symbol, *reinterpret_cast<sista::ANSISettings*>(settings))
            );
        } catch (const std::bad_alloc&) {
            sista_set_last_error(SISTA_ERR_BAD_ALLOC, "memory allocation failed while creating Border");
            return NULL;
        }
    }
    int sista_destroyBorder(BorderHandler_t border) {
        sista_clear_last_error();
        if (border == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_BORDER, "border is null");
            return SISTA_ERR_NULL_BORDER;
        }
        delete reinterpret_cast<sista::Border*>(border);
        return SISTA_OK;
    }

    int sista_printFieldWithBorder(FieldHandler_t field, BorderHandler_t border) {
        sista_clear_last_error();
        if (field == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_FIELD, "field is null");
            return SISTA_ERR_NULL_FIELD;
        }
        if (border == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_BORDER, "border is null");
            return SISTA_ERR_NULL_BORDER;
        }
        reinterpret_cast<Field*>(field)->print(*reinterpret_cast<sista::Border*>(border));
        return SISTA_OK;
    }
    int sista_printSwappableFieldWithBorder(SwappableFieldHandler_t field, BorderHandler_t border) {
        sista_clear_last_error();
        if (field == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_FIELD, "field is null");
            return SISTA_ERR_NULL_FIELD;
        }
        if (border == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_BORDER, "border is null");
            return SISTA_ERR_NULL_BORDER;
        }
        reinterpret_cast<SwappableField*>(field)->print(*reinterpret_cast<sista::Border*>(border));
        return SISTA_OK;
    }

    PawnHandler_t sista_createPawnInSwappableField(
        SwappableFieldHandler_t field,
        char symbol, ANSISettingsHandler_t settings,
        struct sista_Coordinates position
    ) {
        sista_clear_last_error();
        if (field == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_FIELD, "field is null");
            return NULL;
        }
        if (settings == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_SETTINGS, "settings is null");
            return NULL;
        }
        sista::Coordinates pos(position.y, position.x);
        sista::SwappableField* f = reinterpret_cast<sista::SwappableField*>(field);
        try {
            std::shared_ptr<sista::Pawn> p = std::make_shared<sista::Pawn>(
                symbol, pos,
                *reinterpret_cast<sista::ANSISettings*>(settings)
            );
            f->addPawn(p);
            return reinterpret_cast<PawnHandler_t>(f->getPawn(pos));
        } catch (const std::bad_alloc&) {
            sista_set_last_error(SISTA_ERR_BAD_ALLOC, "memory allocation failed while creating Pawn");
            return NULL;
        } catch (const std::out_of_range&) {
            sista_set_last_error(SISTA_ERR_OUT_OF_BOUNDS, "pawn coordinates are out of bounds");
            return NULL;
        } catch (const std::invalid_argument&) {
            sista_set_last_error(SISTA_ERR_OCCUPIED, "pawn coordinates are occupied or invalid");
            return NULL;
        } catch (const std::exception&) {
            sista_set_last_error(SISTA_ERR_UNKNOWN, "unknown error while creating Pawn in SwappableField");
            return NULL;
        }
    }
    PawnHandler_t sista_createPawnInField(
        FieldHandler_t field,
        char symbol, ANSISettingsHandler_t settings,
        struct sista_Coordinates position
    ) {
        sista_clear_last_error();
        if (field == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_FIELD, "field is null");
            return NULL;
        }
        if (settings == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_SETTINGS, "settings is null");
            return NULL;
        }
        sista::Coordinates pos(position.y, position.x);
        sista::Field* f = reinterpret_cast<sista::Field*>(field);
        try {
            std::shared_ptr<sista::Pawn> p = std::make_shared<sista::Pawn>(
                symbol, pos,
                *reinterpret_cast<sista::ANSISettings*>(settings)
            );
            f->addPawn(p);
            return reinterpret_cast<PawnHandler_t>(f->getPawn(pos));
        } catch (const std::bad_alloc&) {
            sista_set_last_error(SISTA_ERR_BAD_ALLOC, "memory allocation failed while creating Pawn");
            return NULL;
        } catch (const std::out_of_range&) {
            sista_set_last_error(SISTA_ERR_OUT_OF_BOUNDS, "pawn coordinates are out of bounds");
            return NULL;
        } catch (const std::invalid_argument&) {
            sista_set_last_error(SISTA_ERR_OCCUPIED, "pawn coordinates are occupied or invalid");
            return NULL;
        } catch (const std::exception&) {
            sista_set_last_error(SISTA_ERR_UNKNOWN, "unknown error while creating Pawn in Field");
            return NULL;
        }
    }
    int sista_movePawn(FieldHandler_t field, PawnHandler_t pawn, struct sista_Coordinates destination) {
        sista_clear_last_error();
        if (field == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_FIELD, "field is null");
            return SISTA_ERR_NULL_FIELD;
        }
        if (pawn == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_PAWN, "pawn is null");
            return SISTA_ERR_NULL_PAWN;
        }
        sista::Coordinates newPos(destination.y, destination.x);
        sista::Field* f = reinterpret_cast<sista::Field*>(field);
        try {
            f->validateCoordinates(newPos);
        } catch (const std::out_of_range&) {
            sista_set_last_error(SISTA_ERR_OUT_OF_BOUNDS, "destination coordinates are out of bounds");
            return SISTA_ERR_OUT_OF_BOUNDS;
        } catch (const std::invalid_argument&) {
            sista_set_last_error(SISTA_ERR_OCCUPIED, "destination coordinates are occupied or invalid");
            return SISTA_ERR_OCCUPIED;
        }
        try {
            f->movePawn(
                reinterpret_cast<sista::Pawn*>(pawn), newPos
            );
        } catch (const std::out_of_range&) {
            sista_set_last_error(SISTA_ERR_OUT_OF_BOUNDS, "destination coordinates are out of bounds");
            return SISTA_ERR_OUT_OF_BOUNDS;
        } catch (const std::invalid_argument&) {
            sista_set_last_error(SISTA_ERR_OCCUPIED, "destination coordinates are occupied or invalid");
            return SISTA_ERR_OCCUPIED;
        } catch (const std::exception&) {
            sista_set_last_error(SISTA_ERR_UNKNOWN, "unknown error while moving Pawn in Field");
            return SISTA_ERR_UNKNOWN;
        }
        return SISTA_OK;
    }
    int sista_addPawnToSwap(
        SwappableFieldHandler_t field,
        PawnHandler_t pawn,
        struct sista_Coordinates destination
    ) {
        sista_clear_last_error();
        if (field == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_FIELD, "field is null");
            return SISTA_ERR_NULL_FIELD;
        }
        if (pawn == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_PAWN, "pawn is null");
            return SISTA_ERR_NULL_PAWN;
        }
        sista::Coordinates newPos(destination.y, destination.x);
        sista::SwappableField* f = reinterpret_cast<sista::SwappableField*>(field);
        try {
            f->addPawnToSwap(
                reinterpret_cast<sista::Pawn*>(pawn), newPos
            );
        } catch (const std::out_of_range&) {
            sista_set_last_error(SISTA_ERR_OUT_OF_BOUNDS, "destination coordinates are out of bounds");
            return SISTA_ERR_OUT_OF_BOUNDS;
        } catch (const std::invalid_argument&) {
            sista_set_last_error(SISTA_ERR_OCCUPIED, "destination coordinates are occupied or invalid");
            return SISTA_ERR_OCCUPIED;
        } catch (const std::exception&) {
            sista_set_last_error(SISTA_ERR_UNKNOWN, "unknown error while adding Pawn swap in SwappableField");
            return SISTA_ERR_UNKNOWN;
        }
        return SISTA_OK;
    }
    int sista_applySwaps(SwappableFieldHandler_t field) {
        sista_clear_last_error();
        if (field == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_FIELD, "field is null");
            return SISTA_ERR_NULL_FIELD;
        }
        try {
            reinterpret_cast<sista::SwappableField*>(field)->applySwaps();
        } catch (const std::exception&) {
            sista_set_last_error(SISTA_ERR_UNKNOWN, "unknown error while applying swaps in SwappableField");
            return SISTA_ERR_UNKNOWN;
        }
        return SISTA_OK;
    }
    int sista_clearScreen(int spaces) {
        sista_clear_last_error();
        sista::clearScreen(spaces != 0);
        return SISTA_OK;
    }
    CursorHandler_t sista_createCursor() {
        sista_clear_last_error();
        try {
            return reinterpret_cast<CursorHandler_t>(new sista::Cursor());
        } catch (const std::bad_alloc&) {
            sista_set_last_error(SISTA_ERR_BAD_ALLOC, "memory allocation failed while creating Cursor");
            return NULL;
        }
    }
    int sista_destroyCursor(CursorHandler_t cursor) {
        sista_clear_last_error();
        if (cursor == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_CURSOR, "cursor is null");
            return SISTA_ERR_NULL_CURSOR;
        }
        delete reinterpret_cast<sista::Cursor*>(cursor);
        return SISTA_OK;
    }
    int sista_moveCursor(CursorHandler_t cursor, enum sista_MoveCursor direction, unsigned short amount) {
        sista_clear_last_error();
        if (cursor == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_CURSOR, "cursor is null");
            return SISTA_ERR_NULL_CURSOR;
        }
        reinterpret_cast<sista::Cursor*>(cursor)->move(
            static_cast<sista::MoveCursor>(direction), amount
        );
        return SISTA_OK;
    }
    int sista_cursorGoTo(CursorHandler_t cursor, unsigned short y, unsigned short x) {
        sista_clear_last_error();
        if (cursor == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_CURSOR, "cursor is null");
            return SISTA_ERR_NULL_CURSOR;
        }
        reinterpret_cast<sista::Cursor*>(cursor)->goTo(y, x);
        return SISTA_OK;
    }
    int sista_cursorGoToCoordinates(CursorHandler_t cursor, struct sista_Coordinates coords) {
        sista_clear_last_error();
        if (cursor == nullptr) {
            sista_set_last_error(SISTA_ERR_NULL_CURSOR, "cursor is null");
            return SISTA_ERR_NULL_CURSOR;
        }
        reinterpret_cast<sista::Cursor*>(cursor)->goTo(coords.y, coords.x);
        return SISTA_OK;
    }
    const char* sista_getVersion() {
        return sista::getVersion();
    }
    int sista_getVersionMajor() {
        return sista::getVersionMajor();
    }
    int sista_getVersionMinor() {
        return sista::getVersionMinor();
    }
    int sista_getVersionPatch() {
        return sista::getVersionPatch();
    }
    int sista_getLastErrorCode() {
        return sista_last_error_code;
    }
    const char* sista_getLastErrorMessage() {
        return sista_last_error_message;
    }
}
