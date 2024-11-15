# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_h6x_packet_handler_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED h6x_packet_handler_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(h6x_packet_handler_FOUND FALSE)
  elseif(NOT h6x_packet_handler_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(h6x_packet_handler_FOUND FALSE)
  endif()
  return()
endif()
set(_h6x_packet_handler_CONFIG_INCLUDED TRUE)

# output package information
if(NOT h6x_packet_handler_FIND_QUIETLY)
  message(STATUS "Found h6x_packet_handler: 1.6.0 (${h6x_packet_handler_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'h6x_packet_handler' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${h6x_packet_handler_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(h6x_packet_handler_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_include_directories-extras.cmake;ament_cmake_export_libraries-extras.cmake")
foreach(_extra ${_extras})
  include("${h6x_packet_handler_DIR}/${_extra}")
endforeach()
