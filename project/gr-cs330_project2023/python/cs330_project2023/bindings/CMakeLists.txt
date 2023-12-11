# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT cs330_project2023_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT cs330_project2023_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND cs330_project2023_python_files
    framer_python.cc
    frame_sync_python.cc
    fec_encoder_python.cc
    fec_decoder_python.cc
    interleaver_python.cc
    deinterleaver_python.cc python_bindings.cc)

GR_PYBIND_MAKE_OOT(cs330_project2023
   ../../..
   gr::cs330_project2023
   "${cs330_project2023_python_files}")

# copy in bindings .so file for use in QA test module
add_custom_target(
  copy_bindings_for_tests ALL
  COMMAND
    ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/*.so"
    ${CMAKE_BINARY_DIR}/test_modules/gnuradio/cs330_project2023/
  DEPENDS cs330_project2023_python)

install(TARGETS cs330_project2023_python DESTINATION ${GR_PYTHON_DIR}/gnuradio/cs330_project2023 COMPONENT pythonapi)
