#pragma once

#ifdef WIN32
#  define EXPORT_DYNAMIC_LIBRARY __declspec(dllexport)
#  define IMPORT_DYNAMIC_LIBRARY __declspec(dllimport)
// disable warning: 'identifier': class 'type' needs to have dll-interface to be
//   used by clients of class 'type2'
// disable warning: non - DLL-interface classkey 'identifier' used as base for
//   DLL-interface classkey 'identifier'
#pragma warning( disable : 4251 4275 )
#else // WIN32
#  define EXPORT_DYNAMIC_LIBRARY
#  define IMPORT_DYNAMIC_LIBRARY
#endif // WIN32

#ifdef BUILDING_ODIL
#  define ODIL_API EXPORT_DYNAMIC_LIBRARY
#else // BUILDING_ODIL
#  define ODIL_API IMPORT_DYNAMIC_LIBRARY
#endif // BUILDING_ODIL
