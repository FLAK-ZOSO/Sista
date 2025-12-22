/** \file sistamodule.c
 *  \brief Python C extension module for Sista C API
 *
 *  This file defines a Python C extension module that wraps the Sista C API,
 *  allowing Python programs to interact with the Sista library functionalities.
 *
 *  \author FLAK-ZOSO
 *  \date 2025
 *  \version 3.0.0
 *  \copyright GNU General Public License v3.0
 *
 *  \see https://peps.python.org/pep-0007/
 */
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <sista/api.h>


/** \brief Sets the foreground color.
 *  \param color The foreground color to set.
 */
static PyObject*
py_sista_set_foreground_color(PyObject* self, PyObject* arg) {
    long val = PyLong_AsLong(arg);
    if (PyErr_Occurred()) return NULL;
    sista_setForegroundColor((enum sista_ForegroundColor)val);
    Py_RETURN_NONE;
}
PyDoc_STRVAR(py_sista_set_foreground_color_doc,
"Sets the foreground color.\n"
"\n"
"Parameters:\n"
"  color (int): The foreground color to set.\n"
);

/** \brief Sets the background color.
 *  \param color The background color to set.
 */
static PyObject*
py_sista_set_background_color(PyObject* self, PyObject* arg) {
    long val = PyLong_AsLong(arg);
    if (PyErr_Occurred()) return NULL;
    sista_setBackgroundColor((enum sista_BackgroundColor)val);
    Py_RETURN_NONE;
}

/** \brief Sets the text attribute.
 *  \param attribute The text attribute to set.
 */
static PyObject*
py_sista_set_attribute(PyObject* self, PyObject* arg) {
    long val = PyLong_AsLong(arg);
    if (PyErr_Occurred()) return NULL;
    sista_setAttribute((enum sista_Attribute)val);
    Py_RETURN_NONE;
}

/** \brief Resets the text attribute.
 *  \param attribute The text attribute to reset.
 */
static PyObject*
py_sista_reset_attribute(PyObject* self, PyObject* arg) {
    long val = PyLong_AsLong(arg);
    if (PyErr_Occurred()) return NULL;
    sista_resetAttribute((enum sista_Attribute)val);
    Py_RETURN_NONE;
}

// Just a function printing a string using the same stream settings as sista
static PyObject*
py_sista_print(PyObject* self, PyObject* args) {
    const char* message;
    if (!PyArg_ParseTuple(args, "s", &message)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError,
                            "Invalid arguments: expected a string");
        }
        return NULL;
    }
    printf("%s\n", message);
    Py_RETURN_NONE;
}

static PyObject*
py_sista_reset_ansi(PyObject* self, PyObject* Py_UNUSED(ignored)) {
    sista_resetAnsi();
    Py_RETURN_NONE;
}

static void py_sista_destroy_swappable_field_capsule_destructor(PyObject*);

/** \brief Creates a SwappableField with the specified width and height.
 *  \param width The width of the SwappableField.
 *  \param height The height of the SwappableField.
 *  \return A handler to the created SwappableField.
 *
 *  This function allocates and initializes a new SwappableField object
 *  with the given dimensions. It returns a pointer that can be used to
 *  reference the SwappableField in subsequent API calls.
 *  \retval NULL If memory allocation fails.
 *  \warning The caller is responsible for managing the lifetime of the
 *        returned SwappableField object, including deallocation if necessary.
 *  \see SwappableField
*/
static PyObject*
py_sista_createSwappableField(PyObject* self,
                              PyObject* args) {
    Py_ssize_t w, h;
    if (!PyArg_ParseTuple(args, "nn", &w, &h)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError,
                            "Invalid arguments: expected two integers (width, height)");
        }
        return NULL;
    }
    if (w < 0 || h < 0) {
        PyErr_SetString(PyExc_ValueError, "width and height must be non-negative");
        return NULL;
    }
    size_t width = (size_t)w;
    size_t height = (size_t)h;

    SwappableFieldHandler_t field = sista_createSwappableField(width, height);
    if (field == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_MemoryError,
                            "Failed to create SwappableField");
        }
        return NULL;
    }

    return PyCapsule_New((void*)field, "SwappableFieldHandler_t", 
                         (PyCapsule_Destructor)py_sista_destroy_swappable_field_capsule_destructor);
}

/** \brief Destructor for SwappableFieldHandler_t capsule.
 *  \param capsule The capsule object.
 *
 *  This function is called when the SwappableFieldHandler_t capsule is
 *  deallocated. It retrieves the SwappableFieldHandler_t pointer from
 *  the capsule and calls the appropriate destructor to free the memory.
*/
static void
py_sista_destroy_swappable_field_capsule_destructor(PyObject* capsule) {
    SwappableFieldHandler_t field = (SwappableFieldHandler_t)PyCapsule_GetPointer(
        capsule, "SwappableFieldHandler_t"
    );
    if (field != NULL) {
        sista_destroySwappableField(field);
    }
}

static void
py_sista_destroy_ansi_settings_capsule_destructor(PyObject*);

static PyObject*
py_sista_create_ansi_settings(PyObject* self, PyObject* args, PyObject* kwargs) {
    int fg = F_WHITE;
    int bg = B_BLACK;
    int attr = A_RESET;
    static char *kwlist[] = {"fgcolor", "bgcolor", "attribute", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|iii", kwlist, &fg, &bg, &attr)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError,
                            "Invalid arguments: expected optional keyword ints (fgcolor, bgcolor, attribute)");
        }
        return NULL;
    }

    ANSISettingsHandler_t settings = sista_createANSISettings(
        (enum sista_ForegroundColor)fg,
        (enum sista_BackgroundColor)bg,
        (enum sista_Attribute)attr
    );

    if (settings == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_MemoryError,
                            "Failed to create ANSISettings");
        }
        return NULL;
    }

    return PyCapsule_New((void*)settings, "ANSISettingsHandler_t",
                         (PyCapsule_Destructor)py_sista_destroy_ansi_settings_capsule_destructor);
}

static void
py_sista_destroy_ansi_settings_capsule_destructor(PyObject* capsule) {
    ANSISettingsHandler_t settings = (ANSISettingsHandler_t)PyCapsule_GetPointer(
        capsule, "ANSISettingsHandler_t"
    );
    if (settings != NULL) {
        sista_destroyANSISettings(settings);
    }
}

static void
py_sista_destroy_border_capsule_destructor(PyObject*);

/** \brief Creates a Border object.
 *  \param border The BorderHandler_t to wrap.
 *  \return A capsule containing the BorderHandler_t.
*/
static PyObject*
py_sista_create_border(PyObject* self, PyObject* args) {
    const char* symbol_str;
    Py_ssize_t symbol_len;
    PyObject* ansi_capsule;

    if (!PyArg_ParseTuple(args, "s#O", &symbol_str, &symbol_len, &ansi_capsule)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError,
                            "Invalid arguments: expected (symbol: str of length 1, ansi_settings_capsule)");
        }
        return NULL;
    }

    if (symbol_len != 1) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Symbol must be a single character");
        }
        return NULL;
    }
    char symbol = symbol_str[0];

    ANSISettingsHandler_t settings = (ANSISettingsHandler_t)PyCapsule_GetPointer(
        ansi_capsule, "ANSISettingsHandler_t"
    );
    if (settings == NULL) {
        PyErr_SetString(PyExc_ValueError,
                        "Invalid ANSISettingsHandler_t capsule");
        return NULL;
    }

    BorderHandler_t border = sista_createBorder(symbol, settings);
    if (border == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_MemoryError,
                            "Failed to create Border");
        }
        return NULL;
    }

    return PyCapsule_New((void*)border, "BorderHandler_t",
                         (PyCapsule_Destructor)py_sista_destroy_border_capsule_destructor);
}

/** \brief Destructor for BorderHandler_t capsule.
 *  \param capsule The capsule object.
 *
 *  This function is called when the BorderHandler_t capsule is
 *  deallocated. It retrieves the BorderHandler_t pointer from
 *  the capsule and calls the appropriate destructor to free the memory.
*/
static void
py_sista_destroy_border_capsule_destructor(PyObject* capsule) {
    BorderHandler_t border = (BorderHandler_t)PyCapsule_GetPointer(
        capsule, "BorderHandler_t"
    );
    if (border != NULL) {
        sista_destroyBorder(border);
    }
}

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
static PyObject*
py_sista_print_swappable_field_with_border(PyObject* self, PyObject* args)
{
    PyObject* field_capsule;
    PyObject* border_capsule;
    if (!PyArg_ParseTuple(args, "OO", &field_capsule, &border_capsule)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError,
                            "Invalid arguments: expected two capsules (SwappableFieldHandler_t, BorderHandler_t)");
        }
        return NULL;
    }

    SwappableFieldHandler_t field = (SwappableFieldHandler_t)PyCapsule_GetPointer(
        field_capsule, "SwappableFieldHandler_t"
    );
    if (field == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Invalid SwappableFieldHandler_t capsule");
        }
        return NULL;
    }

    BorderHandler_t border = (BorderHandler_t)PyCapsule_GetPointer(
        border_capsule, "BorderHandler_t"
    );
    if (border == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Invalid BorderHandler_t capsule");
        }
        return NULL;
    }

    sista_printSwappableFieldWithBorder(field, border);
    Py_RETURN_NONE;
}

/** \brief Prints the field with the specified border.
 *  \param field The Field to print.
 *  \param border The Border to print.
 *
 *  This function prints the entire field to the terminal, using the specified
 *  Border object to draw the border around the field.
 *
 *  \see sista::Border::print
 *  \see sista::Field::print
*/
static PyObject*
py_sista_print_field_with_border(PyObject* self, PyObject* args)
{
    PyObject* field_capsule;
    PyObject* border_capsule;
    if (!PyArg_ParseTuple(args, "OO", &field_capsule, &border_capsule)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError,
                            "Invalid arguments: expected two capsules (FieldHandler_t, BorderHandler_t)");
        }
        return NULL;
    }

    FieldHandler_t field = (FieldHandler_t)PyCapsule_GetPointer(
        field_capsule, "FieldHandler_t"
    );
    if (field == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Invalid FieldHandler_t capsule");
        }
        return NULL;
    }

    BorderHandler_t border = (BorderHandler_t)PyCapsule_GetPointer(
        border_capsule, "BorderHandler_t"
    );
    if (border == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Invalid BorderHandler_t capsule");
        }
        return NULL;
    }

    sista_printFieldWithBorder(field, border);
    Py_RETURN_NONE;
}

/** \brief Creates a Pawn in the specified SwappableField at given coordinates with ANSI settings.
 *  \param field_capsule Capsule containing SwappableFieldHandler_t.
 *  \param symbol Character symbol for the Pawn.
 *  \param ansi_capsule Capsule containing ANSISettingsHandler_t.
 *  \param coords_capsule Capsule containing Coordinates.
 *  \return Capsule containing PawnHandler_t.
 *
 *  This function creates a Pawn in the specified SwappableField at the given coordinates,
 *  using the provided ANSI settings for its appearance.
 *  \retval NULL If any error occurs during the creation process.
*/
static PyObject*
py_sista_create_pawn_in_swappable_field(PyObject* self, PyObject* args) {
    PyObject* field_capsule;
    const char* symbol_str;
    Py_ssize_t symbol_len;
    PyObject* ansi_capsule;
    PyObject* coords_capsule;
    /* accept str or bytes; s# returns UTF-8 bytes + length */
    if (!PyArg_ParseTuple(args, "Os#OO", &field_capsule, &symbol_str, &symbol_len, &ansi_capsule, &coords_capsule)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError,
                            "Invalid arguments: expected (SwappableFieldHandler_t capsule, symbol (1-char), ANSISettingsHandler_t capsule, Coordinates capsule)");
        }
        return NULL;
    }
    if (symbol_len != 1) {
        PyErr_SetString(PyExc_ValueError, "symbol must be a single character (length 1)");
        return NULL;
    }
    char symbol = symbol_str[0];

    SwappableFieldHandler_t field = (SwappableFieldHandler_t)PyCapsule_GetPointer(
        field_capsule, "SwappableFieldHandler_t"
    );
    if (field == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Invalid SwappableFieldHandler_t capsule");
        }
        return NULL;
    }

    ANSISettingsHandler_t settings = (ANSISettingsHandler_t)PyCapsule_GetPointer(
        ansi_capsule, "ANSISettingsHandler_t"
    );
    if (settings == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Invalid ANSISettingsHandler_t capsule");
        }
        return NULL;
    }

    struct sista_Coordinates* coords = (struct sista_Coordinates*)PyCapsule_GetPointer(
        coords_capsule, "sista_Coordinates"
    );
    if (coords == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Invalid Coordinates capsule");
        }
        return NULL;
    }

    PawnHandler_t pawn = sista_createPawnInSwappableField(
        field, symbol, settings, *coords
    );
    if (pawn == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_MemoryError,
                            "Failed to create Pawn in SwappableField");
        }
        return NULL;
    }

    return PyCapsule_New((void*)pawn, "PawnHandler_t",
                         NULL);
}

static void
py_sista_destroy_coordinates_capsule_destructor(PyObject*);

/** \brief Creates a Coordinates object.
 *  \param y The y coordinate.
 *  \param x The x coordinate.
 *  \return A capsule containing the Coordinates object.
*/
static PyObject*
py_sista_create_coordinates(PyObject* self, PyObject* args) {
    unsigned short y, x;
    if (!PyArg_ParseTuple(args, "HH", &y, &x)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError,
                            "Invalid arguments: expected two unsigned shorts (y, x)");
        }
        return NULL;
    }

    struct sista_Coordinates* coords = (struct sista_Coordinates*)malloc(sizeof(struct sista_Coordinates));
    if (coords == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_MemoryError,
                            "Failed to allocate Coordinates");
        }
        return NULL;
    }

    coords->y = y;
    coords->x = x;

    return PyCapsule_New((void*)coords, "sista_Coordinates",
                         (PyCapsule_Destructor)py_sista_destroy_coordinates_capsule_destructor);
}

static void
py_sista_destroy_coordinates_capsule_destructor(PyObject* capsule) {
    struct sista_Coordinates* coords = (struct sista_Coordinates*)PyCapsule_GetPointer(
        capsule, "sista_Coordinates"
    );
    if (coords != NULL) {
        free(coords);
    }
}

/** \brief Creates a Pawn in the specified Field at given coordinates with ANSI settings.
 *  \param field_capsule Capsule containing FieldHandler_t.
 *  \param symbol Character symbol for the Pawn.
 *  \param ansi_capsule Capsule containing ANSISettingsHandler_t.
 *  \param coords_capsule Capsule containing Coordinates.
 *  \return Capsule containing PawnHandler_t.
 *
 *  This function creates a Pawn in the specified Field at the given coordinates,
 *  using the provided ANSI settings for its appearance.
 *  \retval NULL If any error occurs during the creation process.
*/
static PyObject*
py_sista_create_pawn_in_field(PyObject* self, PyObject* args) {
    PyObject* field_capsule;
    const char* symbol_str;
    Py_ssize_t symbol_len;
    PyObject* ansi_capsule;
    PyObject* coords_capsule;
    if (!PyArg_ParseTuple(args, "Os#OO", &field_capsule, &symbol_str, &symbol_len, &ansi_capsule, &coords_capsule)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError,
                            "Invalid arguments: expected (FieldHandler_t capsule, symbol (1-char), ANSISettingsHandler_t capsule, Coordinates capsule)");
        }
        return NULL;
    }
    if (symbol_len != 1) {
        PyErr_SetString(PyExc_ValueError, "symbol must be a single character (length 1)");
        return NULL;
    }
    char symbol = symbol_str[0];

    FieldHandler_t field = (FieldHandler_t)PyCapsule_GetPointer(
        field_capsule, "FieldHandler_t"
    );
    if (field == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Invalid FieldHandler_t capsule");
        }
        return NULL;
    }
    struct sista_Coordinates* coords = (struct sista_Coordinates*)PyCapsule_GetPointer(
        coords_capsule, "sista_Coordinates"
    );
    if (coords == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Invalid Coordinates capsule");
        }
        return NULL;
    }
    ANSISettingsHandler_t settings = (ANSISettingsHandler_t)PyCapsule_GetPointer(
        ansi_capsule, "ANSISettingsHandler_t"
    );
    if (settings == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Invalid ANSISettingsHandler_t capsule");
        }
        return NULL;
    }
    PawnHandler_t pawn = sista_createPawnInField(
        field, symbol, settings, *coords
    );
    if (pawn == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_MemoryError,
                            "Failed to create Pawn in Field");
        }
        return NULL;
    }
    return PyCapsule_New((void*)pawn, "PawnHandler_t",
                         NULL);
}

/** \brief Moves the Pawn by the specified deltas.
 *  \param pawn_capsule Capsule containing PawnHandler_t.
 *  \param dx The delta x to move.
 *  \param dy The delta y to move.
 *  \return The result of the move operation.
 *
 *  This function moves the specified Pawn by the given deltas in the x and y directions.
 *  It returns an integer indicating the result of the move operation.
*/
static PyObject*
py_sista_move_pawn(PyObject* self, PyObject* args) {
    PyObject* field_capsule;
    PyObject* pawn_capsule;
    Py_ssize_t dx, dy;
    if (!PyArg_ParseTuple(args, "OOnn", &field_capsule, &pawn_capsule, &dx, &dy)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError,
                            "Invalid arguments: expected (FieldHandler_t capsule, PawnHandler_t capsule, dx: int, dy: int)");
        }
        return NULL;
    }

    FieldHandler_t field = (FieldHandler_t)PyCapsule_GetPointer(
        field_capsule, "FieldHandler_t"
    );
    if (field == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Invalid FieldHandler_t capsule");
        }
        return NULL;
    }

    PawnHandler_t pawn = (PawnHandler_t)PyCapsule_GetPointer(
        pawn_capsule, "PawnHandler_t"
    );
    if (pawn == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Invalid PawnHandler_t capsule");
        }
        return NULL;
    }
    struct sista_Coordinates delta = {
        .y = (unsigned short)dy,
        .x = (unsigned short)dx
    };
    int result = sista_movePawn(field, pawn, delta);
    return PyLong_FromLong((long)result);
}

/** \brief Adds a Pawn to the SwappableField's swap list at given coordinates.
 *  \param field_capsule Capsule containing SwappableFieldHandler_t.
 *  \param pawn_capsule Capsule containing PawnHandler_t.
 *  \param coords_capsule Capsule containing Coordinates.
 *  \return The result of the add operation.
 *
 *  This function adds the specified Pawn to the SwappableField's swap list
 *  at the given coordinates. It returns an integer indicating the result
 *  of the add operation.
*/
static PyObject*
py_sista_add_pawn_to_swap(PyObject* self, PyObject* args) {
    PyObject* field_capsule;
    PyObject* pawn_capsule;
    PyObject* coords_capsule;
    if (!PyArg_ParseTuple(args, "OOO", &field_capsule, &pawn_capsule, &coords_capsule)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError,
                            "Invalid arguments: expected (SwappableFieldHandler_t capsule, PawnHandler_t capsule, Coordinates capsule)");
        }
        return NULL;
    }

    SwappableFieldHandler_t field = (SwappableFieldHandler_t)PyCapsule_GetPointer(
        field_capsule, "SwappableFieldHandler_t"
    );
    if (field == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Invalid SwappableFieldHandler_t capsule");
        }
        return NULL;
    }

    PawnHandler_t pawn = (PawnHandler_t)PyCapsule_GetPointer(
        pawn_capsule, "PawnHandler_t"
    );
    if (pawn == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Invalid PawnHandler_t capsule");
        }
        return NULL;
    }

    struct sista_Coordinates* coords = (struct sista_Coordinates*)PyCapsule_GetPointer(
        coords_capsule, "sista_Coordinates"
    );
    if (coords == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Invalid Coordinates capsule");
        }
        return NULL;
    }

    int result = sista_addPawnToSwap(field, pawn, *coords);
    return PyLong_FromLong((long)result);
}

/** \brief Module execution function.
 *  \param module The module object.
 *  \return 0 on success, -1 on failure.
 *
 *  This function is called when the module is initialized. It can be used
 *  to perform any necessary setup or initialization tasks.
*/
static int
sista_module_exec(PyObject* module)
{
    const char* version = sista_getVersion();
    if (version == NULL) {
        PyErr_SetString(PyExc_RuntimeError,
                        "Failed to retrieve Sista version");
        return -1;
    }

    /* Export enums as integer constants so callers can use `sista.F_WHITE` directly. */
    PyModule_AddIntConstant(module, "F_BLACK", F_BLACK);
    PyModule_AddIntConstant(module, "F_RED", F_RED);
    PyModule_AddIntConstant(module, "F_GREEN", F_GREEN);
    PyModule_AddIntConstant(module, "F_YELLOW", F_YELLOW);
    PyModule_AddIntConstant(module, "F_BLUE", F_BLUE);
    PyModule_AddIntConstant(module, "F_MAGENTA", F_MAGENTA);
    PyModule_AddIntConstant(module, "F_CYAN", F_CYAN);
    PyModule_AddIntConstant(module, "F_WHITE", F_WHITE);

    PyModule_AddIntConstant(module, "B_BLACK", B_BLACK);
    PyModule_AddIntConstant(module, "B_RED", B_RED);
    PyModule_AddIntConstant(module, "B_GREEN", B_GREEN);
    PyModule_AddIntConstant(module, "B_YELLOW", B_YELLOW);
    PyModule_AddIntConstant(module, "B_BLUE", B_BLUE);
    PyModule_AddIntConstant(module, "B_MAGENTA", B_MAGENTA);
    PyModule_AddIntConstant(module, "B_CYAN", B_CYAN);
    PyModule_AddIntConstant(module, "B_WHITE", B_WHITE);

    PyModule_AddIntConstant(module, "A_RESET", A_RESET);
    PyModule_AddIntConstant(module, "A_BRIGHT", A_BRIGHT);
    PyModule_AddIntConstant(module, "A_FAINT", A_FAINT);
    PyModule_AddIntConstant(module, "A_ITALIC", A_ITALIC);
    PyModule_AddIntConstant(module, "A_UNDERLINE", A_UNDERLINE);
    PyModule_AddIntConstant(module, "A_BLINK", A_BLINK);
    PyModule_AddIntConstant(module, "A_BLINK_FAST", A_BLINK_FAST);
    PyModule_AddIntConstant(module, "A_REVERSE", A_REVERSE);
    PyModule_AddIntConstant(module, "A_HIDDEN", A_HIDDEN);
    PyModule_AddIntConstant(module, "A_STRIKETHROUGH", A_STRIKETHROUGH);

    // PyModule_AddStringConstant(module, "__version__", version);
    // printf("Sista C API Module - Version: %s\n", version);
    return 0;
}

/** \brief Module methods definition.
*/
static PyMethodDef sista_module_methods[] = {
    {"create_swappable_field", py_sista_createSwappableField, METH_VARARGS,
     "Creates a SwappableField with the specified width and height."},
    
    {"reset_ansi", (PyCFunction)py_sista_reset_ansi,
     METH_NOARGS,
     "Resets ANSI settings to default."},

    {"set_foreground_color", (PyCFunction)py_sista_set_foreground_color,
     METH_O,
     py_sista_set_foreground_color_doc},
    {"set_background_color", (PyCFunction)py_sista_set_background_color,
     METH_O,
     "Sets the background color."},
    {"set_attribute", (PyCFunction)py_sista_set_attribute,
     METH_O,
     "Sets the text attribute."},
    {"reset_attribute", (PyCFunction)py_sista_reset_attribute,
     METH_O,
     "Resets the text attribute."},

    {"create_border", py_sista_create_border, METH_VARARGS,
     "Creates a Border object."},
    {"print_swappable_field_with_border",
     py_sista_print_swappable_field_with_border,
     METH_VARARGS,
     "Prints the SwappableField with the specified Border."},
    {"print_field_with_border",
     py_sista_print_field_with_border,
     METH_VARARGS,
     "Prints the Field with the specified Border."},
    {"create_ansi_settings", (PyCFunction)py_sista_create_ansi_settings,
     METH_VARARGS | METH_KEYWORDS,
     "create_ansi_settings(fgcolor=F_WHITE, bgcolor=B_BLACK, attribute=A_RESET) -> ANSISettingsHandler_t capsule"},
    {"print", (PyCFunction)py_sista_print,
     METH_VARARGS,
     "Prints a message using Sista's ANSI settings."},

    {"create_pawn_in_swappable_field", py_sista_create_pawn_in_swappable_field, METH_VARARGS,
     "Creates a Pawn in the specified SwappableField at given coordinates with ANSI settings."},
    {"create_coordinates", py_sista_create_coordinates, METH_VARARGS,
     "Creates a Coordinates object."},
    {"move_pawn", py_sista_move_pawn, METH_VARARGS,
     "Moves the Pawn by the specified deltas."},
    {"add_pawn_to_swap", py_sista_add_pawn_to_swap, METH_VARARGS,
     "Adds a Pawn to the SwappableField's swap list at given coordinates."},
    {"create_pawn_in_field", py_sista_create_pawn_in_field, METH_VARARGS,
     "Creates a Pawn in the specified Field at given coordinates with ANSI settings."},

    {NULL, NULL, 0, NULL}  // Sentinel
};

/* Add module slots and use Py_mod_exec properly */
static PyModuleDef_Slot sista_module_slots[] = {
    {Py_mod_exec, (void*)sista_module_exec},
    {0, NULL}
};

/** \brief Module definition.
*/
static struct PyModuleDef sista_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "sista._sista",
    .m_size = 0,  // non-negative
    .m_methods = sista_module_methods,
    .m_slots = sista_module_slots,
};

/** \brief Module initialization function.
 *  \return The initialized module object.
 *
 *  This function is called when the module is imported in Python. It
 *  initializes the module and returns the module object.
*/
PyMODINIT_FUNC
PyInit__sista(void)
{
    /* create module; the exec slot (sista_module_exec) will be run by the import machinery */
    return PyModuleDef_Init(&sista_module);
}
