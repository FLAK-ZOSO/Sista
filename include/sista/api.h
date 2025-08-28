/** \file api.h
 *  \brief C API for Sista library
 *
 *  This header defines the C API for the Sista library, allowing interaction
 *  with core functionalities such as creating and managing SwappableFields
 *  and Pawns. The API is designed to be used in C programs, providing a
 *  bridge to the underlying C++ implementations and allowing for FFI usage
 *  with other programming languages thanks to ABI compatibility.
 *
 *  \author FLAK-ZOSO
 *  \date 2025
 *  \version 3.0.0
 *  \copyright GNU General Public License v3.0
 */
#ifdef __cplusplus
extern "C" {
#endif

struct sista_SwappableField;
typedef struct sista_SwappableField* SwappableFieldHandler_t;
struct sista_Pawn;
typedef struct sista_Pawn* PawnHandler_t;

/** \brief Creates a SwappableField with the specified width and height.
 *  \param width The width of the SwappableField.
 *  \param height The height of the SwappableField.
 *  \return A handler to the created SwappableField.
 *
 *  This function allocates and initializes a new SwappableField object
 *  with the given dimensions. It returns a pointer that can be used to
 *  reference the SwappableField in subsequent API calls.
 *
 *  \note The caller is responsible for managing the lifetime of the
 *        returned SwappableField object, including deallocation if necessary.
 *
 *  \see SwappableField
*/
SwappableFieldHandler_t sista_createSwappableField(int, int);
/** \brief Prints the specified Field with a given border
 *  \param field The SwappableField.
 *  \param border The border character to use.
 *
 *  This function prints the entire field to the terminal, using the specified
 *  character as the border around the field.
 *
 *  \see Field
 *  \see Border
*/
void sista_printField(SwappableFieldHandler_t, char);
/** \brief Deallocates the SwappableField from memory
 *  \param field The SwappableField to delete
 *
 *  This function deallocates the SwappableField from memory through the opaque
 *  handler pointing to it.
 *
 *  \see SwappableField
 */
void sista_destroySwappableField(SwappableFieldHandler_t);

#ifdef __cplusplus
}
#endif
