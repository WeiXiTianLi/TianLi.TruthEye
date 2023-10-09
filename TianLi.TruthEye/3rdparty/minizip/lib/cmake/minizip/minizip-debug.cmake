#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MINIZIP::minizip" for configuration "Debug"
set_property(TARGET MINIZIP::minizip APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MINIZIP::minizip PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libminizip.lib"
  )

list(APPEND _cmake_import_check_targets MINIZIP::minizip )
list(APPEND _cmake_import_check_files_for_MINIZIP::minizip "${_IMPORT_PREFIX}/lib/libminizip.lib" )

# Import target "MINIZIP::zlibstatic" for configuration "Debug"
set_property(TARGET MINIZIP::zlibstatic APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MINIZIP::zlibstatic PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/zlibstaticd.lib"
  )

list(APPEND _cmake_import_check_targets MINIZIP::zlibstatic )
list(APPEND _cmake_import_check_files_for_MINIZIP::zlibstatic "${_IMPORT_PREFIX}/lib/zlibstaticd.lib" )

# Import target "MINIZIP::bzip2" for configuration "Debug"
set_property(TARGET MINIZIP::bzip2 APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MINIZIP::bzip2 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/bzip2.lib"
  )

list(APPEND _cmake_import_check_targets MINIZIP::bzip2 )
list(APPEND _cmake_import_check_files_for_MINIZIP::bzip2 "${_IMPORT_PREFIX}/lib/bzip2.lib" )

# Import target "MINIZIP::liblzma" for configuration "Debug"
set_property(TARGET MINIZIP::liblzma APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MINIZIP::liblzma PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/liblzma.lib"
  )

list(APPEND _cmake_import_check_targets MINIZIP::liblzma )
list(APPEND _cmake_import_check_files_for_MINIZIP::liblzma "${_IMPORT_PREFIX}/lib/liblzma.lib" )

# Import target "MINIZIP::libzstd_static" for configuration "Debug"
set_property(TARGET MINIZIP::libzstd_static APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MINIZIP::libzstd_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/zstd_static.lib"
  )

list(APPEND _cmake_import_check_targets MINIZIP::libzstd_static )
list(APPEND _cmake_import_check_files_for_MINIZIP::libzstd_static "${_IMPORT_PREFIX}/lib/zstd_static.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
