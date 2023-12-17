find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_LAB1_MODULE gnuradio-lab1_module)

FIND_PATH(
    GR_LAB1_MODULE_INCLUDE_DIRS
    NAMES gnuradio/lab1_module/api.h
    HINTS $ENV{LAB1_MODULE_DIR}/include
        ${PC_LAB1_MODULE_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_LAB1_MODULE_LIBRARIES
    NAMES gnuradio-lab1_module
    HINTS $ENV{LAB1_MODULE_DIR}/lib
        ${PC_LAB1_MODULE_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-lab1_moduleTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_LAB1_MODULE DEFAULT_MSG GR_LAB1_MODULE_LIBRARIES GR_LAB1_MODULE_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_LAB1_MODULE_LIBRARIES GR_LAB1_MODULE_INCLUDE_DIRS)
