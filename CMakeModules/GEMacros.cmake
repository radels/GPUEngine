macro(_ge_check_file_exists file target)
   if(NOT EXISTS "${file}")
      message(FATAL_ERROR "The imported target ${target} references file ${file} which doesn't seem to exist. Reported by ${CMAKE_CURRENT_LIST_FILE}")
   endif()
endmacro()

macro(_ge_check_file_exists_weak file target)
   if(NOT EXISTS "${file}")
      message("The imported target ${target} references file ${file} which doesn't seem to exist. Reported by ${CMAKE_CURRENT_LIST_FILE}")
   endif()
endmacro()

macro(_ge_check_and_import target prop path)
   #message("${${ARGV3}}")
   set(status)
   if(${${ARGV3}})
      set(status FATAL_ERROR)
      #message("required")
   endif()
   if(EXISTS "${path}")
      set_property(TARGET ${target} APPEND PROPERTY ${prop} ${path})
   else()
      if(NOT (${${ARGV4}}) )
         message(${status} "The imported target ${target} references file ${path} which doesn't seem to exist. Reported by ${CMAKE_CURRENT_LIST_FILE}")
      endif()
   endif()
endmacro()

macro(_ge_populate_imported_target target install_prefix name)
   set_property(TARGET ${target} APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
   set_property(TARGET ${target} APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
   _ge_check_and_import(${target} INTERFACE_INCLUDE_DIRECTORIES "${${install_prefix}}/include" ${ARGV3} ${ARGV4})
   if(WIN32)
      _ge_check_and_import(${target} IMPORTED_LOCATION_RELEASE "${${install_prefix}}/bin/${name}.dll" ${ARGV3} ${ARGV4})
      _ge_check_and_import(${target} IMPORTED_LOCATION_DEBUG "${${install_prefix}}/bin/${name}d.dll" FALSE ${ARGV4})
      _ge_check_and_import(${target} IMPORTED_IMPLIB_RELEASE "${${install_prefix}}/lib/${name}.lib" ${ARGV3} ${ARGV4})
      _ge_check_and_import(${target} IMPORTED_IMPLIB_DEBUG "${${install_prefix}}/lib/${name}d.lib" FALSE ${ARGV4})
   ELSE()
      _ge_check_and_import(${target} IMPORTED_LOCATION_RELEASE "${${install_prefix}}/bin/${name}.so" ${ARGV3} ${ARGV4})
   ENDIF()
endmacro()

macro(ge_use_modules target)
   set(_modules ${ARGN})
   foreach(_module ${_modules})
      message("${_module}")
   endforeach()
endmacro()

macro(ge_report_find_status found_where)
   if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
      if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
         get_property(ALREADY_REPORTED GLOBAL PROPERTY ${CMAKE_FIND_PACKAGE_NAME}_FOUND_REPORTED)
         if(NOT ALREADY_REPORTED)
            message(STATUS "Find package ${CMAKE_FIND_PACKAGE_NAME}: ${found_where}")
            set_property(GLOBAL PROPERTY ${CMAKE_FIND_PACKAGE_NAME}_FOUND_REPORTED True)
         endif()
      endif()
   else()
      if(${CMAKE_FIND_PACKAGE_NAME}_FIND_REQUIRED)
         get_property(ALREADY_REPORTED GLOBAL PROPERTY ${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_ERROR_REPORTED)
         if(NOT ALREADY_REPORTED)
            message(SEND_ERROR "Find package ${CMAKE_FIND_PACKAGE_NAME}: not found")
            set_property(GLOBAL PROPERTY ${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_ERROR_REPORTED True)
         endif()
      else()
         if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
            get_property(ALREADY_REPORTED GLOBAL PROPERTY ${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_INFO_REPORTED)
            if(NOT ALREADY_REPORTED)
               message(STATUS "Find package ${CMAKE_FIND_PACKAGE_NAME}: not found")
               set_property(GLOBAL PROPERTY ${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_INFO_REPORTED True)
            endif()
         endif()
      endif()
   endif()
endmacro()

macro(ge_report_find_status)
   if(TARGET ${CMAKE_FIND_PACKAGE_NAME})
      if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
         get_property(ALREADY_REPORTED GLOBAL PROPERTY ${CMAKE_FIND_PACKAGE_NAME}_FOUND_REPORTED)
         if(NOT ALREADY_REPORTED)

            # try path from the linked library
            get_target_property(found_where ${CMAKE_FIND_PACKAGE_NAME} INTERFACE_LINK_LIBRARIES)

            # try path from include directory
            if("${found_where}" STREQUAL "found_where-NOTFOUND")
               get_target_property(found_where ${CMAKE_FIND_PACKAGE_NAME} INTERFACE_INCLUDE_DIRECTORIES)
            endif()

            # try config path
            if("${found_where}" STREQUAL "found_where-NOTFOUND")
               set(found_where "${${CMAKE_FIND_PACKAGE_NAME}_DIR}")
            endif()

            # use target name
            if("${found_where}" STREQUAL "found_where-NOTFOUND")
               set(found_where "${CMAKE_FIND_PACKAGE_NAME}")
            endif()

            # print message
            message(STATUS "Find package ${CMAKE_FIND_PACKAGE_NAME}: ${found_where}")
            set_property(GLOBAL PROPERTY ${CMAKE_FIND_PACKAGE_NAME}_FOUND_REPORTED True)

         endif()
      endif()
   else()
      if(${CMAKE_FIND_PACKAGE_NAME}_FIND_REQUIRED)
         get_property(ALREADY_REPORTED GLOBAL PROPERTY ${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_ERROR_REPORTED)
         if(NOT ALREADY_REPORTED)
            message(SEND_ERROR "Find package ${CMAKE_FIND_PACKAGE_NAME}: not found")
            set_property(GLOBAL PROPERTY ${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_ERROR_REPORTED True)
         endif()
      else()
         if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
            get_property(ALREADY_REPORTED GLOBAL PROPERTY ${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_INFO_REPORTED)
            if(NOT ALREADY_REPORTED)
               message(STATUS "Find package ${CMAKE_FIND_PACKAGE_NAME}: not found")
               set_property(GLOBAL PROPERTY ${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_INFO_REPORTED True)
            endif()
         endif()
      endif()
   endif()
endmacro()
