
if (CMAKE_VERSION VERSION_LESS 2.8.3)
    message(FATAL_ERROR "Qt 5 requires at least CMake version 2.8.3")
endif()

set(_qt5Ftp_install_prefix "/usr")

set(Qt5Ftp_VERSION_MAJOR 5)
set(Qt5Ftp_VERSION_MINOR 0)
set(Qt5Ftp_VERSION_PATCH 0)
set(Qt5Ftp_VERSION_STRING 5.0.0)

set(Qt5Ftp_LIBRARIES Qt5::Ftp)

macro(_populate_Ftp_target_properties Configuration LIB_LOCATION IMPLIB_LOCATION)
    set_property(TARGET Qt5::Ftp APPEND PROPERTY IMPORTED_CONFIGURATIONS ${Configuration})

    set_target_properties(Qt5::Ftp PROPERTIES
        "IMPORTED_LINK_INTERFACE_LIBRARIES_${Configuration}" "${_Qt5Ftp_LIB_DEPENDENCIES}"
        "IMPORTED_LOCATION_${Configuration}" "/usr/lib/x86_64-linux-gnu/${LIB_LOCATION}"
        "IMPORTED_SONAME_${Configuration}" "libQt5Ftp.so.5"
    )
endmacro()

if (NOT TARGET Qt5::Ftp)

    set(Qt5Ftp_INCLUDE_DIRS "/usr/include/qt5/QtFtp")
    set(Qt5Ftp_PRIVATE_INCLUDE_DIRS
        "/usr/include/qt5/QtFtp/${Qt5Ftp_VERSION_STRING}"
        "/usr/include/qt5/QtFtp/${Qt5Ftp_VERSION_STRING}/QtFtp"
    )

    set(Qt5Ftp_DEFINITIONS -DQT_FTP_LIB)
    set(Qt5Ftp_COMPILE_DEFINITIONS QT_FTP_LIB)

    set(_Qt5Ftp_MODULE_DEPENDENCIES "Network;Core")

    set(_Qt5Ftp_FIND_DEPENDENCIES_REQUIRED)
    if (Qt5Ftp_FIND_REQUIRED)
        set(_Qt5Ftp_FIND_DEPENDENCIES_REQUIRED REQUIRED)
    endif()
    set(_Qt5Ftp_FIND_DEPENDENCIES_QUIET)
    if (Qt5Ftp_FIND_QUIETLY)
        set(_Qt5Ftp_DEPENDENCIES_FIND_QUIET QUIET)
    endif()

    foreach(_module_dep ${_Qt5Ftp_MODULE_DEPENDENCIES})
        if (NOT Qt5${_module_dep}_FOUND)
            find_package(Qt5${_module_dep}
                ${_Qt5Ftp_DEPENDENCIES_FIND_QUIET}
                ${_Qt5Ftp_FIND_DEPENDENCIES_REQUIRED}
                PATHS "${_qt5Ftp_install_prefix}" NO_DEFAULT_PATH
            )
        endif()

        if (NOT Qt5${_module_dep}_FOUND)
            set(Qt5Ftp_FOUND False)
            return()
        endif()

        list(APPEND Qt5Ftp_INCLUDE_DIRS "${Qt5${_module_dep}_INCLUDE_DIRS}")
        list(APPEND Qt5Ftp_PRIVATE_INCLUDE_DIRS "${Qt5${_module_dep}_PRIVATE_INCLUDE_DIRS}")
        list(APPEND Qt5Ftp_DEFINITIONS ${Qt5${_module_dep}_DEFINITIONS})
        list(APPEND Qt5Ftp_COMPILE_DEFINITIONS ${Qt5${_module_dep}_COMPILE_DEFINITIONS})
        list(APPEND Qt5Ftp_EXECUTABLE_COMPILE_FLAGS ${Qt5${_module_dep}_EXECUTABLE_COMPILE_FLAGS})
    endforeach()
    list(REMOVE_DUPLICATES Qt5Ftp_INCLUDE_DIRS)
    list(REMOVE_DUPLICATES Qt5Ftp_PRIVATE_INCLUDE_DIRS)
    list(REMOVE_DUPLICATES Qt5Ftp_DEFINITIONS)
    list(REMOVE_DUPLICATES Qt5Ftp_COMPILE_DEFINITIONS)
    if (Qt5Ftp_EXECUTABLE_COMPILE_FLAGS)
      list(REMOVE_DUPLICATES Qt5Ftp_EXECUTABLE_COMPILE_FLAGS)
    endif()

    set(_Qt5Ftp_LIB_DEPENDENCIES "Qt5::Network;Qt5::Core")

    add_library(Qt5::Ftp SHARED IMPORTED)

    _populate_Ftp_target_properties(RELEASE "libQt5Ftp.so.5.0.0" "" )






endif()
