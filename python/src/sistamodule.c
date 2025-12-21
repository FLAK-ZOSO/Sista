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

// Just a function printing a string using the same stream settings as sista
static PyObject* py_sista_print(PyObject* self, PyObject* args) {
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
    size_t width;
    size_t height;
    if (!PyArg_ParseTuple(args, "nn", &width, &height)) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError,
                            "Invalid arguments: expected two size_t values (width, height)");
        }
        return NULL;
    }

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
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "Invalid ANSISettingsHandler_t capsule");
        }
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
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_RuntimeError,
                            "Failed to retrieve Sista version");
        }
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

    {"set_foreground_color", (PyCFunction)py_sista_set_foreground_color,
     METH_O,
     "Sets the foreground color."},
    {"set_background_color", (PyCFunction)py_sista_set_background_color,
     METH_O,
     "Sets the background color."},
    {"set_attribute", (PyCFunction)py_sista_set_attribute,
     METH_O,
     "Sets the text attribute."},

    {"create_border", py_sista_create_border, METH_VARARGS,
     "Creates a Border object."},
    {"print_swappable_field_with_border",
     py_sista_print_swappable_field_with_border,
     METH_VARARGS,
     "Prints the SwappableField with the specified Border."},
    {"create_ansi_settings", (PyCFunction)py_sista_create_ansi_settings,
     METH_VARARGS | METH_KEYWORDS,
     "create_ansi_settings(fgcolor=F_WHITE, bgcolor=B_BLACK, attribute=A_RESET) -> ANSISettingsHandler_t capsule"},
    {"print", (PyCFunction)py_sista_print,
     METH_VARARGS,
     "Prints a message using Sista's ANSI settings."},
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
    .m_size = -1, // -1 means the module keeps state in global variables, https://realpython.com/python312-subinterpreters/
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
