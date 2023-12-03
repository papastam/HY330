find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_CHRIS_MODULE gnuradio-chris_module)

FIND_PATH(
    GR_CHRIS_MODULE_INCLUDE_DIRS
    NAMES gnuradio/chris_module/api.h
    HINTS $ENV{CHRIS_MODULE_DIR}/include
        ${PC_CHRIS_MODULE_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_CHRIS_MODULE_LIBRARIES
    NAMES gnuradio-chris_module
    HINTS $ENV{CHRIS_MODULE_DIR}/lib
        ${PC_CHRIS_MODULE_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-chris_moduleTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_CHRIS_MODULE DEFAULT_MSG GR_CHRIS_MODULE_LIBRARIES GR_CHRIS_MODULE_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_CHRIS_MODULE_LIBRARIES GR_CHRIS_MODULE_INCLUDE_DIRS)
