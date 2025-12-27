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

PyDoc_STRVAR(py_sista_set_foreground_color_doc,
"Set the terminal foreground color using one of the `F_*` constants.\n\n"
"### Parameters\n\n"
"- `color` (int): One of the `F_*` constants (e.g. `F_RED`).\n"
);

PyDoc_STRVAR(py_sista_set_background_color_doc,
"Set the terminal background color using one of the `B_*` constants.\n\n"
"### Parameters\n\n"
"- `color` (int): One of the `B_*` constants (e.g. `B_BLUE`).\n"
);

PyDoc_STRVAR(py_sista_set_attribute_doc,
"Enable a terminal text attribute using one of the `A_*` constants.\n\n"
"### Parameters\n\n"
"- `attribute` (int): One of the `A_*` constants (e.g. `A_UNDERLINE`).\n"
);

PyDoc_STRVAR(py_sista_reset_attribute_doc,
"Disable/reset a terminal text attribute using one of the `A_*` constants.\n\n"
"### Parameters\n\n"
"- `attribute` (int): One of the `A_*` constants (e.g. `A_RESET`).\n"
);

PyDoc_STRVAR(py_sista_reset_ansi_doc,
"Reset all ANSI text attributes and colors to the terminal defaults.\n"
);

PyDoc_STRVAR(py_sista_print_doc,
"Print a message to the terminal using Sista's configured output stream.\n\n"
"### Parameters\n\n"
"- `message` (str): Message to print (a single text line).\n"
);

PyDoc_STRVAR(py_sista_create_ansi_settings_doc,
"Create an ANSI settings object and return it as a capsule.\n\n"
"```py\n"
"create_ansi_settings(fgcolor=F_WHITE, bgcolor=B_BLACK, attribute=A_RESET) -> Capsule\n"
"```\n\n"
"### Parameters\n\n"
"- `fgcolor` (int): Foreground color (one of the `F_*` constants).\n"
"- `bgcolor` (int): Background color (one of the `B_*` constants).\n"
"- `attribute` (int): Text attribute (one of the `A_*` constants).\n\n"
"### Returns\n\n"
"- Capsule wrapping the ANSISettings handler.\n"
);

PyDoc_STRVAR(py_sista_create_border_doc,
"Create a Border object that uses a single-character symbol and ANSI settings.\n\n"
"### Parameters\n\n"
"- `symbol` (str): Single character string used to draw border bricks.\n"
"- `ansi_settings` (Capsule): Capsule returned by `create_ansi_settings`.\n\n"
"### Returns\n\n"
"- Capsule wrapping the Border handler.\n"
);

PyDoc_STRVAR(py_sista_create_coordinates_doc,
"Create a Coordinates object and return it as a capsule.\n\n"
"### Parameters\n\n"
"- `y` (int): Row index.\n"
"- `x` (int): Column index.\n\n"
"### Returns\n\n"
"- Capsule wrapping a Coordinates struct.\n"
);

PyDoc_STRVAR(py_doc_Field,
"Class representing a terminal Field for pawns and borders.\n\n"
"Create with `Field(width: int, height: int)`.\n\n"
"Provides: `create_pawn`, `move_pawn`, `print_with_border`.\n"
);

PyDoc_STRVAR(py_doc_SwappableField,
"Class representing a terminal SwappableField for pawns and borders.\n\n"
"Create with `SwappableField(width: int, height: int)`.\n\n"
"Provides: `create_pawn`, `print_with_border`, `add_pawn_to_swap`, `apply_swaps`.\n"
);

PyDoc_STRVAR(py_doc_Cursor,
"Class representing a terminal cursor for movement operations.\n\n"
"Create with `Cursor()`.\n\n"
"Provides: `move`, `go_to`, `go_to_coordinates`.\n"
);

PyDoc_STRVAR(py_Field_create_pawn_doc,
"Create a Pawn inside this Field and return a Pawn capsule.\n\n"
"### Parameters\n\n"
"- `symbol` (str): Single character string representing the pawn.\n"
"- `ansi_settings` (Capsule): Capsule returned by `create_ansi_settings`.\n"
"- `coords` (Capsule): Capsule returned by `create_coordinates`.\n\n"
"### Returns\n\n"
"- Capsule wrapping the Pawn handler.\n"
);

PyDoc_STRVAR(py_Field_move_pawn_doc,
"Move a pawn inside this Field and return a status code.\n\n"
"### Parameters\n\n"
"- `pawn` (Capsule): Capsule for the Pawn to move.\n"
"- `y` (int): Y coordinate of the destination.\n"
"- `x` (int): X coordinate of the destination.\n\n"
"### Returns\n\n"
"- `int`: status code (0 == success).\n"
);

PyDoc_STRVAR(py_Field_print_with_border_doc,
"Render this Field to the terminal using the given Border object.\n\n"
"### Parameters\n\n"
"- `border` (Capsule): Capsule for the Border to draw around the field.\n"
);

PyDoc_STRVAR(py_SwappableField_create_pawn_doc,
"create_pawn(self, symbol: str, ansi_settings: Capsule, coords: Capsule) -> Capsule\n\n"
"Create a Pawn inside this SwappableField and return a Pawn capsule.\n\n"
"### Parameters\n\n"
"- `symbol` (str): Single character string used to represent the pawn.\n"
"- `ansi_settings` (Capsule): Capsule returned by create_ansi_settings().\n"
"- `coords` (Capsule): Capsule returned by create_coordinates().\n\n"
"### Returns\n\n"
"- `Capsule` wrapping the Pawn handler.\n"
);

PyDoc_STRVAR(py_SwappableField_add_pawn_to_swap_doc,
"add_pawn_to_swap(self, pawn: Capsule, coords: Capsule) -> int\n\n"
"Schedule a pawn to be swapped to the given coordinates in the next swap operation.\n\n"
"### Parameters\n\n"
"- `pawn` (Capsule): Capsule for the Pawn to schedule for swapping.\n"
"- `coords` (Capsule): Capsule for the target Coordinates.\n\n"
"### Returns\n\n"
"- `int`: status code (0 == success).\n"
);

PyDoc_STRVAR(py_SwappableField_apply_swaps_doc,
"apply_swaps(self) -> int\n\n"
"Execute all scheduled pawn swaps in this SwappableField.\n\n"
"### Returns\n\n"
"- `int`: status code (0 == success).\n"
);

PyDoc_STRVAR(py_SwappableField_print_with_border_doc,
"print_with_border(self, border: Capsule) -> None\n\n"
"Render this SwappableField to the terminal using the given Border object.\n\n"
"### Parameters\n\n"
"- `border` (Capsule): Capsule for the Border to draw around the field.\n"
);

PyDoc_STRVAR(py_Cursor_go_to_doc,
"Move the cursor to the absolute `(y, x)` position.\n\n"
"### Parameters\n\n"
"- `y` (int): Row index to move to.\n"
"- `x` (int): Column index to move to.\n"
);

PyDoc_STRVAR(py_Cursor_move_doc,
"Move the cursor in the specified direction by the given amount.\n\n"
"### Parameters\n\n"
"- `direction` (int): One of the `DIRECTION_*` constants.\n"
"- `amount` (int): Number of positions to move the cursor.\n"
);

PyDoc_STRVAR(py_Cursor_go_to_coordinates_doc,
"Move the cursor to the position described by a Coordinates capsule.\n\n"
"### Parameters\n\n"
"- `coords` (Capsule): Capsule returned by `create_coordinates`.\n"
);

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

/** \brief Prints a message
 *
 *  Prints a message using Sista's ANSI settings,
 *  using the same stream as printf.
 *
 *  \param message The message to print.
 */
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

/** \brief Resets ANSI settings to default.
 */
static PyObject*
py_sista_reset_ansi(PyObject* self, PyObject* Py_UNUSED(ignored)) {
    sista_resetAnsi();
    Py_RETURN_NONE;
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

/* New Python type that wraps CursorHandler_t */
typedef struct {
    PyObject_HEAD
    CursorHandler_t cursor;
} CursorObject;

static PyTypeObject CursorType;

/* dealloc */
static void
Cursor_dealloc(PyObject *self)
{
    CursorObject *obj = (CursorObject*)self;
    if (obj->cursor) {
        sista_destroyCursor(obj->cursor);
        obj->cursor = NULL;
    }
    Py_TYPE(self)->tp_free(self);
}

/** \brief Cursor.go_to(self, y, x)
 *
 *  Moves the cursor to the specified (y, x) coordinates.
 *
 *  \param y The y coordinate.
 *  \param x The x coordinate.
*/
static PyObject*
Cursor_go_to(PyObject *self, PyObject *args)
{
    Py_ssize_t y, x;
    if (!PyArg_ParseTuple(args, "nn", &y, &x)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, "Expected (y: int, x: int)");
        }
        return NULL;
    }
    CursorHandler_t cursor = ((CursorObject*)self)->cursor;
    if (cursor == NULL) {
        PyErr_SetString(PyExc_ValueError, "Cursor object already destroyed");
        return NULL;
    }
    sista_cursorGoTo(cursor, (unsigned short)y, (unsigned short)x);
    Py_RETURN_NONE;
}

/** \brief Cursor.go_to_coordinates(self, coords_capsule)
 *
 *  Moves the cursor to the specified coordinates.
 *
 *  \param coords_capsule Capsule containing Coordinates.
*/
static PyObject*
Cursor_go_to_coordinates(PyObject *self, PyObject *args)
{
    PyObject *coords_capsule;
    if (!PyArg_ParseTuple(args, "O", &coords_capsule)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, "Expected (coords_capsule)");
        }
        return NULL;
    }
    CursorHandler_t cursor = ((CursorObject*)self)->cursor;
    if (cursor == NULL) {
        PyErr_SetString(PyExc_ValueError, "Cursor object already destroyed");
        return NULL;
    }
    struct sista_Coordinates* coords = (struct sista_Coordinates*)PyCapsule_GetPointer(
        coords_capsule, "sista_Coordinates"
    );
    if (coords == NULL) {
        PyErr_SetString(PyExc_ValueError, "Invalid Coordinates capsule");
        return NULL;
    }
    sista_cursorGoToCoordinates(cursor, *coords);
    Py_RETURN_NONE;
}

/** \brief Cursor.move(self, direction, amount)
 *
 *  Moves the cursor in the specified direction by the given amount.
 *
 *  \param direction The direction to move the cursor.
 *  \param amount The amount to move the cursor.
*/
static PyObject*
Cursor_move(PyObject *self, PyObject *args)
{
    Py_ssize_t direction, amount;
    if (!PyArg_ParseTuple(args, "nn", &direction, &amount)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, "Expected (direction: int, amount: int)");
        }
        return NULL;
    }
    CursorHandler_t cursor = ((CursorObject*)self)->cursor;
    if (cursor == NULL) {
        PyErr_SetString(PyExc_ValueError, "Cursor object already destroyed");
        return NULL;
    }
    sista_moveCursor(cursor, (enum sista_MoveCursor)direction, (unsigned short)amount);
    Py_RETURN_NONE;
}

/* methods table */
static PyMethodDef Cursor_methods[] = {
    {"go_to", (PyCFunction)Cursor_go_to, METH_VARARGS, py_Cursor_go_to_doc},
    {"go_to_coordinates", (PyCFunction)Cursor_go_to_coordinates, METH_VARARGS, py_Cursor_go_to_coordinates_doc},
    {"move", (PyCFunction)Cursor_move, METH_VARARGS, py_Cursor_move_doc},
    {NULL, NULL, 0, NULL}
};

static int
Cursor_init(PyObject* self, PyObject* args, PyObject* kwds) {
    CursorHandler_t cursor = sista_createCursor();
    if (cursor == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_MemoryError, "Failed to create Cursor");
        }
        return -1;
    }

    CursorObject *obj = (CursorObject*)self;  /* object already allocated by tp_new */
    obj->cursor = cursor;
    return 0;
}

/* type object */
static PyTypeObject CursorType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "sista.Cursor",
    .tp_basicsize = sizeof(CursorObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = py_doc_Cursor,
    .tp_methods = Cursor_methods,
    .tp_dealloc = (destructor)Cursor_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = Cursor_init,
};

/* New Python type that wraps SwappableFieldHandler_t */
typedef struct {
    PyObject_HEAD
    SwappableFieldHandler_t field;
} SwappableFieldObject;

static PyTypeObject SwappableFieldType;

/* dealloc */
static void
SwappableField_dealloc(PyObject *self)
{
    SwappableFieldObject *obj = (SwappableFieldObject*)self;
    if (obj->field) {
        sista_destroySwappableField(obj->field);
        obj->field = NULL;
    }
    Py_TYPE(self)->tp_free(self);
}

/* SwappableField.create_pawn(self, symbol, ansi_capsule, coords_capsule) */
static PyObject*
SwappableField_create_pawn(PyObject *self, PyObject *args)
{
    const char *symbol_str;
    Py_ssize_t symbol_len;
    PyObject *ansi_capsule;
    PyObject *coords_capsule;

    if (!PyArg_ParseTuple(args, "s#OO", &symbol_str, &symbol_len, &ansi_capsule, &coords_capsule)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, "Expected (symbol: str of length 1, ansi_settings_capsule, coords_capsule)");
        }
        return NULL;
    }
    if (symbol_len != 1) {
        PyErr_SetString(PyExc_ValueError, "symbol must be a single character");
        return NULL;
    }
    char symbol = symbol_str[0];

    ANSISettingsHandler_t settings = (ANSISettingsHandler_t)PyCapsule_GetPointer(ansi_capsule, "ANSISettingsHandler_t");
    if (settings == NULL) {
        PyErr_SetString(PyExc_ValueError, "Invalid ANSISettingsHandler_t capsule");
        return NULL;
    }

    struct sista_Coordinates *coords = (struct sista_Coordinates*)PyCapsule_GetPointer(coords_capsule, "sista_Coordinates");
    if (coords == NULL) {
        PyErr_SetString(PyExc_ValueError, "Invalid Coordinates capsule");
        return NULL;
    }

    SwappableFieldHandler_t field = ((SwappableFieldObject*)self)->field;
    if (field == NULL) {
        PyErr_SetString(PyExc_ValueError, "SwappableField object already destroyed");
        return NULL;
    }

    PawnHandler_t pawn = sista_createPawnInSwappableField(field, symbol, settings, *coords);
    if (pawn == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_MemoryError, "Failed to create Pawn in SwappableField");
        }
        return NULL;
    }
    return PyCapsule_New((void*)pawn, "PawnHandler_t", NULL);
}

/* SwappableField.add_pawn_to_swap(self, pawn_capsule, coords_capsule) */
static PyObject*
SwappableField_add_pawn_to_swap(PyObject *self, PyObject *args)
{
    PyObject *pawn_capsule;
    PyObject *coords_capsule;
    if (!PyArg_ParseTuple(args, "OO", &pawn_capsule, &coords_capsule)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, "Expected (pawn_capsule, coords_capsule)");
        }
        return NULL;
    }
    PawnHandler_t pawn = (PawnHandler_t)PyCapsule_GetPointer(pawn_capsule, "PawnHandler_t");
    if (pawn == NULL) {
        PyErr_SetString(PyExc_ValueError, "Invalid PawnHandler_t capsule");
        return NULL;
    }

    struct sista_Coordinates *coords = (struct sista_Coordinates*)PyCapsule_GetPointer(coords_capsule, "sista_Coordinates");
    if (coords == NULL) {
        PyErr_SetString(PyExc_ValueError, "Invalid Coordinates capsule");
        return NULL;
    }

    SwappableFieldHandler_t field = ((SwappableFieldObject*)self)->field;
    if (field == NULL) {
        PyErr_SetString(PyExc_ValueError, "SwappableField object already destroyed");
        return NULL;
    }

    int result = sista_addPawnToSwap(field, pawn, *coords);
    return PyLong_FromLong((long)result);
}

/* SwappableField.apply_swaps(self) */
static PyObject*
SwappableField_apply_swaps(PyObject *self, PyObject *Py_UNUSED(ignored))
{
    SwappableFieldHandler_t field = ((SwappableFieldObject*)self)->field;
    if (field == NULL) {
        PyErr_SetString(PyExc_ValueError, "SwappableField object already destroyed");
        return NULL;
    }
    int result = sista_applySwaps(field);
    if (result != 0) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to apply swaps in SwappableField");
        return NULL;
    }
    Py_RETURN_NONE;
}

/* SwappableField.print_with_border(self, border_capsule) */
static PyObject*
SwappableField_print_with_border(PyObject *self, PyObject *args)
{
    PyObject *border_capsule;
    if (!PyArg_ParseTuple(args, "O", &border_capsule)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, "Expected (border_capsule)");
        }
        return NULL;
    }
    BorderHandler_t border = (BorderHandler_t)PyCapsule_GetPointer(border_capsule, "BorderHandler_t");
    if (border == NULL) {
        PyErr_SetString(PyExc_ValueError, "Invalid BorderHandler_t capsule");
        return NULL;
    }

    SwappableFieldHandler_t field = ((SwappableFieldObject*)self)->field;
    if (field == NULL) {
        PyErr_SetString(PyExc_ValueError, "SwappableField object already destroyed");
        return NULL;
    }

    sista_printSwappableFieldWithBorder(field, border);
    Py_RETURN_NONE;
}

/* methods table */
static PyMethodDef SwappableField_methods[] = {
    {"create_pawn", (PyCFunction)SwappableField_create_pawn, METH_VARARGS, py_SwappableField_create_pawn_doc},
    {"add_pawn_to_swap", (PyCFunction)SwappableField_add_pawn_to_swap, METH_VARARGS, py_SwappableField_add_pawn_to_swap_doc},
    {"apply_swaps", (PyCFunction)SwappableField_apply_swaps, METH_NOARGS, py_SwappableField_apply_swaps_doc},
    {"print_with_border", (PyCFunction)SwappableField_print_with_border, METH_VARARGS, py_SwappableField_print_with_border_doc},
    {NULL, NULL, 0, NULL}
};

static int
SwappableField_init(PyObject* self, PyObject* args, PyObject* kwds) {
    Py_ssize_t w, h;
    static char *kwlist[] = {"width", "height", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "nn", kwlist, &w, &h)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError,
                            "SwappableField(width:int, height:int) expected");
        }
        return -1;
    }
    if (w < 0 || h < 0) {
        PyErr_SetString(PyExc_ValueError, "width and height must be non-negative");
        return -1;
    }
    size_t width = (size_t)w;
    size_t height = (size_t)h;

    SwappableFieldHandler_t field = sista_createSwappableField(width, height);
    if (field == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_MemoryError, "Failed to create SwappableField");
        }
        return -1;
    }

    // object already allocated by tp_new
    SwappableFieldObject *obj = (SwappableFieldObject*)self;
    obj->field = field;
    return 0;
}

/* type object */
static PyTypeObject SwappableFieldType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "sista.SwappableField",
    .tp_basicsize = sizeof(SwappableFieldObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = py_doc_SwappableField,
    .tp_methods = SwappableField_methods,
    .tp_dealloc = (destructor)SwappableField_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = SwappableField_init,
};

/* New Python type that wraps FieldHandler_t */
typedef struct {
    PyObject_HEAD
    FieldHandler_t field;
} FieldObject;

static PyTypeObject FieldType;

/* dealloc */
static void
Field_dealloc(PyObject *self)
{
    FieldObject *obj = (FieldObject*)self;
    if (obj->field) {
        sista_destroyField(obj->field);
        obj->field = NULL;
    }
    Py_TYPE(self)->tp_free(self);
}

/* Field.create_pawn(self, symbol, ansi_capsule, coords_capsule) */
static PyObject*
Field_create_pawn(PyObject *self, PyObject *args)
{
    const char *symbol_str;
    Py_ssize_t symbol_len;
    PyObject *ansi_capsule;
    PyObject *coords_capsule;

    if (!PyArg_ParseTuple(args, "s#OO", &symbol_str, &symbol_len, &ansi_capsule, &coords_capsule)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, "Expected (symbol: str of length 1, ansi_settings_capsule, coords_capsule)");
        }
        return NULL;
    }
    if (symbol_len != 1) {
        PyErr_SetString(PyExc_ValueError, "symbol must be a single character");
        return NULL;
    }
    char symbol = symbol_str[0];

    ANSISettingsHandler_t settings = (ANSISettingsHandler_t)PyCapsule_GetPointer(ansi_capsule, "ANSISettingsHandler_t");
    if (settings == NULL) {
        PyErr_SetString(PyExc_ValueError, "Invalid ANSISettingsHandler_t capsule");
        return NULL;
    }

    struct sista_Coordinates *coords = (struct sista_Coordinates*)PyCapsule_GetPointer(coords_capsule, "sista_Coordinates");
    if (coords == NULL) {
        PyErr_SetString(PyExc_ValueError, "Invalid Coordinates capsule");
        return NULL;
    }

    FieldHandler_t field = ((FieldObject*)self)->field;
    if (field == NULL) {
        PyErr_SetString(PyExc_ValueError, "Field object already destroyed");
        return NULL;
    }

    PawnHandler_t pawn = sista_createPawnInField(field, symbol, settings, *coords);
    if (pawn == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_MemoryError, "Failed to create Pawn in Field");
        }
        return NULL;
    }
    return PyCapsule_New((void*)pawn, "PawnHandler_t", NULL);
}

/* Field.move_pawn(self, pawn_capsule, y, x) */
static PyObject*
Field_move_pawn(PyObject *self, PyObject *args)
{
    PyObject *pawn_capsule;
    Py_ssize_t y, x;
    if (!PyArg_ParseTuple(args, "Onn", &pawn_capsule, &y, &x)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, "Expected (pawn_capsule, y: int, x: int)");
        }
        return NULL;
    }
    PawnHandler_t pawn = (PawnHandler_t)PyCapsule_GetPointer(pawn_capsule, "PawnHandler_t");
    if (pawn == NULL) {
        PyErr_SetString(PyExc_ValueError, "Invalid PawnHandler_t capsule");
        return NULL;
    }

    FieldHandler_t field = ((FieldObject*)self)->field;
    if (field == NULL) {
        PyErr_SetString(PyExc_ValueError, "Field object already destroyed");
        return NULL;
    }

    struct sista_Coordinates destination = {
        .y = (unsigned short)y,
        .x = (unsigned short)x
    };
    int result = sista_movePawn(field, pawn, destination);
    return PyLong_FromLong((long)result);
}

/* Field.print_with_border(self, border_capsule) */
static PyObject*
Field_print_with_border(PyObject *self, PyObject *args)
{
    PyObject *border_capsule;
    if (!PyArg_ParseTuple(args, "O", &border_capsule)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, "Expected (border_capsule)");
        }
        return NULL;
    }
    BorderHandler_t border = (BorderHandler_t)PyCapsule_GetPointer(border_capsule, "BorderHandler_t");
    if (border == NULL) {
        PyErr_SetString(PyExc_ValueError, "Invalid BorderHandler_t capsule");
        return NULL;
    }

    FieldHandler_t field = ((FieldObject*)self)->field;
    if (field == NULL) {
        PyErr_SetString(PyExc_ValueError, "Field object already destroyed");
        return NULL;
    }

    sista_printFieldWithBorder(field, border);
    Py_RETURN_NONE;
}

/* methods table */
static PyMethodDef Field_methods[] = {
    {"create_pawn", (PyCFunction)Field_create_pawn, METH_VARARGS, py_Field_create_pawn_doc},
    {"move_pawn", (PyCFunction)Field_move_pawn, METH_VARARGS, py_Field_move_pawn_doc},
    {"print_with_border", (PyCFunction)Field_print_with_border, METH_VARARGS, py_Field_print_with_border_doc},
    {NULL, NULL, 0, NULL}
};

/** \brief Initializes a Field object.
 *  \param w The width of the field.
 *  \param h The height of the field.
 *  \return 0 on success, -1 on failure.
 *
 *  This function is called during the creation of a Field object.
*/
static int
Field_init(PyObject* self, PyObject* args, PyObject *kwds) {
    Py_ssize_t w, h;
    static char *kwlist[] = {"width", "height", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "nn", kwlist, &w, &h)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, "Field(width:int, height:int) expected");
        }
        return -1;
    }
    if (w < 0 || h < 0) {
        PyErr_SetString(PyExc_ValueError, "width and height must be non-negative");
        return -1;
    }

    FieldHandler_t field = sista_createField((size_t)w, (size_t)h);
    if (field == NULL) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_MemoryError, "Failed to create Field");
        }
        return -1;
    }

    FieldObject *obj = (FieldObject*)self;  /* object already allocated by tp_new */
    obj->field = field;
    return 0;
}

/* type object */
static PyTypeObject FieldType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "sista.Field",
    .tp_basicsize = sizeof(FieldObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = py_doc_Field,
    .tp_methods = Field_methods,
    .tp_dealloc = (destructor)Field_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = Field_init,
};

/* In sista_module_exec(...) add registration of the SwappableField and Field types */
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

    PyModule_AddIntConstant(module, "DIRECTION_UP", UP);
    PyModule_AddIntConstant(module, "DIRECTION_DOWN", DOWN);
    PyModule_AddIntConstant(module, "DIRECTION_RIGHT", RIGHT);
    PyModule_AddIntConstant(module, "DIRECTION_LEFT", LEFT);
    PyModule_AddIntConstant(module, "BEGINNING_OF_NEXT_LINE", BEGINNING_OF_NEXT_LINE);
    PyModule_AddIntConstant(module, "BEGINNING_OF_PREVIOUS_LINE", BEGINNING_OF_PREVIOUS_LINE);

    if (PyType_Ready(&CursorType) < 0) return -1;
    Py_INCREF(&CursorType);
    if (PyModule_AddObject(module, "Cursor", (PyObject*)&CursorType) < 0) {
        Py_DECREF(&CursorType);
        return -1;
    }

    if (PyType_Ready(&SwappableFieldType) < 0) return -1;
    Py_INCREF(&SwappableFieldType);
    if (PyModule_AddObject(module, "SwappableField", (PyObject*)&SwappableFieldType) < 0) {
        Py_DECREF(&SwappableFieldType);
        return -1;
    }

    if (PyType_Ready(&FieldType) < 0) return -1;
    Py_INCREF(&FieldType);
    if (PyModule_AddObject(module, "Field", (PyObject*)&FieldType) < 0) {
        Py_DECREF(&FieldType);
        return -1;
    }

    return 0;
}

/* Module methods definition. */
static PyMethodDef sista_module_methods[] = {
    {"reset_ansi", (PyCFunction)py_sista_reset_ansi,
     METH_NOARGS,
     py_sista_reset_ansi_doc},

    {"set_foreground_color", (PyCFunction)py_sista_set_foreground_color,
     METH_O,
     py_sista_set_foreground_color_doc},
    {"set_background_color", (PyCFunction)py_sista_set_background_color,
     METH_O,
     py_sista_set_background_color_doc},
    {"set_attribute", (PyCFunction)py_sista_set_attribute,
     METH_O,
     py_sista_set_attribute_doc},
    {"reset_attribute", (PyCFunction)py_sista_reset_attribute,
     METH_O,
     py_sista_reset_attribute_doc},

    {"create_border", (PyCFunction)py_sista_create_border, METH_VARARGS,
     py_sista_create_border_doc},
    {"create_ansi_settings", (PyCFunction)py_sista_create_ansi_settings,
     METH_VARARGS | METH_KEYWORDS,
     py_sista_create_ansi_settings_doc},
    {"print", (PyCFunction)py_sista_print,
     METH_VARARGS,
     py_sista_print_doc},

    {"create_coordinates", (PyCFunction)py_sista_create_coordinates, METH_VARARGS,
     py_sista_create_coordinates_doc},

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
