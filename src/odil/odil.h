/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b9c5b481_c291_4d87_b721_1e19d577d5e4
#define _b9c5b481_c291_4d87_b721_1e19d577d5e4

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

#endif // _b9c5b481_c291_4d87_b721_1e19d577d5e4
