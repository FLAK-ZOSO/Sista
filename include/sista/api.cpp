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

using namespace sista;

extern "C" {
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

    void sista_printField(SwappableFieldHandler_t field, char border) {
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
}
