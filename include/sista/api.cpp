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
    SwappableFieldHandler_t sista_createSwappableField(int width, int height) {
        return reinterpret_cast<SwappableFieldHandler_t>(new SwappableField(width, height));
    }
    void sista_destroySwappableField(SwappableFieldHandler_t field) {
        delete reinterpret_cast<SwappableField*>(field);
    }

    void sista_printField(SwappableFieldHandler_t field, char border) {
        if (field == nullptr) return;
        reinterpret_cast<SwappableField*>(field)->print(border);
    }
}
