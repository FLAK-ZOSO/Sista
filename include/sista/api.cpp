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
    FieldHandler_t sista_createField(size_t width, size_t height) {
        try {
            return reinterpret_cast<FieldHandler_t>(
                new Field(static_cast<int>(width), static_cast<int>(height))
            );
        } catch (const std::bad_alloc&) {
            return NULL;
        }
    }
    void sista_destroyField(FieldHandler_t field) {
        delete reinterpret_cast<Field*>(field);
    }
    SwappableFieldHandler_t sista_createSwappableField(size_t width, size_t height) {
        try {
            return reinterpret_cast<SwappableFieldHandler_t>(
                new SwappableField(static_cast<int>(width), static_cast<int>(height))
            );
        } catch (const std::bad_alloc&) {
            return NULL;
        }
    }
    void sista_destroySwappableField(SwappableFieldHandler_t field) {
        delete reinterpret_cast<SwappableField*>(field);
    }

    void sista_printField(FieldHandler_t field, char border) {
        if (field == nullptr) return;
        reinterpret_cast<Field*>(field)->print(border);
    }
    void sista_printSwappableField(SwappableFieldHandler_t field, char border) {
        if (field == nullptr) return;
        reinterpret_cast<SwappableField*>(field)->print(border);
    }

    void sista_resetAnsi() {
        sista::resetAnsi();
    }
    void sista_setForegroundColor(enum sista_ForegroundColor color) {
        sista::setForegroundColor(static_cast<sista::ForegroundColor>(color));
    }
    void sista_setBackgroundColor(enum sista_BackgroundColor color) {
        sista::setBackgroundColor(static_cast<sista::BackgroundColor>(color));
    }
    void sista_setAttribute(enum sista_Attribute attribute) {
        sista::setAttribute(static_cast<sista::Attribute>(attribute));
    }
    void sista_resetAttribute(enum sista_Attribute attribute) {
        sista::resetAttribute(static_cast<sista::Attribute>(attribute));
    }
    void sista_setForegroundColorRGB(const struct sista_RGBColor* color) {
        if (color == nullptr) return;
        sista::setForegroundColor(
            color->red,
            color->green,
            color->blue
        );
    }
    void sista_setBackgroundColorRGB(const struct sista_RGBColor* color) {
        if (color == nullptr) return;
        sista::setBackgroundColor(
            color->red,
            color->green,
            color->blue
        );
    }

    ANSISettingsHandler_t sista_createANSISettings(
        enum sista_ForegroundColor fgColor,
        enum sista_BackgroundColor bgColor,
        enum sista_Attribute attribute
    ) {
        try {
            return reinterpret_cast<ANSISettingsHandler_t>(
                new sista::ANSISettings(
                    static_cast<sista::ForegroundColor>(fgColor),
                    static_cast<sista::BackgroundColor>(bgColor),
                    static_cast<sista::Attribute>(attribute)
                )
            );
        } catch (const std::bad_alloc&) {
            return NULL;
        }
    }
    ANSISettingsHandler_t sista_createANSISettingsRGB(
        struct sista_RGBColor fgColor,
        struct sista_RGBColor bgColor,
        sista_Attribute attribute
    ) {
        try {
            return reinterpret_cast<ANSISettingsHandler_t>(
                new sista::ANSISettings(
                    sista::RGBColor(fgColor.red, fgColor.green, fgColor.blue),
                    sista::RGBColor(bgColor.red, bgColor.green, bgColor.blue),
                    static_cast<sista::Attribute>(attribute)
                )
            );
        } catch (const std::bad_alloc&) {
            return NULL;
        }
    }
    void sista_destroyANSISettings(ANSISettingsHandler_t settings) {
        delete reinterpret_cast<sista::ANSISettings*>(settings);
    }

    void sista_applyANSISettings(ANSISettingsHandler_t settings) {
        if (settings == nullptr) return;
        reinterpret_cast<sista::ANSISettings*>(settings)->apply();
    }

    BorderHandler_t sista_createBorder(char symbol, ANSISettingsHandler_t settings) {
        try {
            return reinterpret_cast<BorderHandler_t>(
                new sista::Border(symbol, *reinterpret_cast<sista::ANSISettings*>(settings))
            );
        } catch (const std::bad_alloc&) {
            return NULL;
        }
    }
    void sista_destroyBorder(BorderHandler_t border) {
        delete reinterpret_cast<sista::Border*>(border);
    }

    void sista_printFieldWithBorder(FieldHandler_t field, BorderHandler_t border) {
        if (field == nullptr || border == nullptr) return;
        reinterpret_cast<Field*>(field)->print(*reinterpret_cast<sista::Border*>(border));
    }
    void sista_printSwappableFieldWithBorder(SwappableFieldHandler_t field, BorderHandler_t border) {
        if (field == nullptr || border == nullptr) return;
        reinterpret_cast<SwappableField*>(field)->print(*reinterpret_cast<sista::Border*>(border));
    }

    PawnHandler_t sista_createPawnInSwappableField(
        SwappableFieldHandler_t field,
        char symbol, ANSISettingsHandler_t settings,
        struct sista_Coordinates position
    ) {
        if (field == nullptr || settings == nullptr) return NULL;
        sista::Coordinates pos(position.x, position.y);
        sista::SwappableField* f = reinterpret_cast<sista::SwappableField*>(field);
        try {
            std::shared_ptr<sista::Pawn> p = std::make_shared<sista::Pawn>(
                symbol, pos,
                *reinterpret_cast<sista::ANSISettings*>(settings)
            );
            f->addPawn(p);
            return reinterpret_cast<PawnHandler_t>(f->getPawn(pos));
        } catch (const std::bad_alloc&) {
            return NULL;
        }
    }
    PawnHandler_t sista_createPawnInField(
        FieldHandler_t field,
        char symbol, ANSISettingsHandler_t settings,
        struct sista_Coordinates position
    ) {
        if (field == nullptr || settings == nullptr) return NULL;
        sista::Coordinates pos(position.x, position.y);
        sista::Field* f = reinterpret_cast<sista::Field*>(field);
        try {
            std::shared_ptr<sista::Pawn> p = std::make_shared<sista::Pawn>(
                symbol, pos,
                *reinterpret_cast<sista::ANSISettings*>(settings)
            );
            f->addPawn(p);
            return reinterpret_cast<PawnHandler_t>(f->getPawn(pos));
        } catch (const std::bad_alloc&) {
            return NULL;
        }
    }
    int sista_movePawn(FieldHandler_t field, PawnHandler_t pawn, struct sista_Coordinates destination) {
        if (field == nullptr) return 4;
        if (pawn == nullptr) return 5;
        sista::Coordinates newPos(destination.x, destination.y);
        sista::Field* f = reinterpret_cast<sista::Field*>(field);
        try {
            f->validateCoordinates(newPos);
        } catch (const std::out_of_range&) {
            return 2;
        } catch (const std::invalid_argument&) {
            return 3;
        }
        try {
            f->movePawn(
                reinterpret_cast<sista::Pawn*>(pawn), newPos
            );
        } catch (const std::exception&) {
            return 1;
        }
        return 0;
    }
    int sista_addPawnToSwap(
        SwappableFieldHandler_t field,
        PawnHandler_t pawn,
        struct sista_Coordinates destination
    ) {
        if (field == nullptr) return 4;
        if (pawn == nullptr) return 5;
        sista::Coordinates newPos(destination.x, destination.y);
        sista::SwappableField* f = reinterpret_cast<sista::SwappableField*>(field);
        try {
            f->addPawnToSwap(
                reinterpret_cast<sista::Pawn*>(pawn), newPos
            );
        } catch (const std::out_of_range&) {
            return 2;
        } catch (const std::invalid_argument&) {
            return 3;
        } catch (const std::exception&) {
            return 1;
        }
        return 0;
    }
    int sista_applySwaps(SwappableFieldHandler_t field) {
        if (field == nullptr) return 1;
        try {
            reinterpret_cast<sista::SwappableField*>(field)->applySwaps();
        } catch (const std::exception&) {
            return 1;
        }
        return 0;
    }
    CursorHandler_t sista_createCursor() {
        try {
            return reinterpret_cast<CursorHandler_t>(new sista::Cursor());
        } catch (const std::bad_alloc&) {
            return NULL;
        }
    }
    void sista_destroyCursor(CursorHandler_t cursor) {
        delete reinterpret_cast<sista::Cursor*>(cursor);
    }
    void sista_moveCursor(CursorHandler_t cursor, enum sista_MoveCursor direction, unsigned short amount) {
        if (cursor == nullptr) return;
        reinterpret_cast<sista::Cursor*>(cursor)->move(
            static_cast<sista::MoveCursor>(direction), amount
        );
    }
    void sista_cursorGoTo(CursorHandler_t cursor, unsigned short y, unsigned short x) {
        if (cursor == nullptr) return;
        reinterpret_cast<sista::Cursor*>(cursor)->goTo(y, x);
    }
    void sista_cursorGoToCoordinates(CursorHandler_t cursor, struct sista_Coordinates coords) {
        if (cursor == nullptr) return;
        reinterpret_cast<sista::Cursor*>(cursor)->goTo(coords.y, coords.x);
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
}
