#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "gnuradio::gnuradio-cs330_project2023" for configuration "Release"
set_property(TARGET gnuradio::gnuradio-cs330_project2023 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(gnuradio::gnuradio-cs330_project2023 PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/libgnuradio-cs330_project2023.so.1.0.0.0"
  IMPORTED_SONAME_RELEASE "libgnuradio-cs330_project2023.so.1.0.0"
  )

list(APPEND _cmake_import_check_targets gnuradio::gnuradio-cs330_project2023 )
list(APPEND _cmake_import_check_files_for_gnuradio::gnuradio-cs330_project2023 "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/libgnuradio-cs330_project2023.so.1.0.0.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
