#pragma once

#ifdef WIN32
#  define EXPORT_DYNAMIC_LIBRARY __declspec(dllexport)
#  define IMPORT_DYNAMIC_LIBRARY __declspec(dllimport)
#else // WIN32
#  define EXPORT_DYNAMIC_LIBRARY
#  define IMPORT_DYNAMIC_LIBRARY
#endif // WIN32

#ifdef BUILDING_ODIL
#  define ODIL_API EXPORT_DYNAMIC_LIBRARY
#else // BUILDING_ODIL
#  define ODIL_API IMPORT_DYNAMIC_LIBRARY
#endif // BUILDING_ODIL