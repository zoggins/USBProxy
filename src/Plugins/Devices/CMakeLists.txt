#
# This file is part of USBProxy.
#

project(usbproxy_devices C)
set(PACKAGE usbproxy_devices)

set(CMAKE_C_FLAGS "$ENV{CFLAGS} -pthread -Wall")
set(CMAKE_CPP_FLAGS "${CMAKE_CPP_FLAGS} $ENV{CPPFLAGS} -std=gnu++11 -pthread -pedantic -Wall -felide-constructors -fno-exceptions -O3")

include_directories(${libusbproxy_SOURCE_DIR})
LIST(APPEND PLUGINS_LINK_LIBS USBProxy)

LIST(APPEND PLUGINS DeviceProxy_Loopback DeviceProxy_TCP DeviceProxy_Callback)

find_package(USB1)

if( ${LIBUSB_FOUND} )
	include_directories(${LIBUSB_INCLUDE_DIR})
	LIST(APPEND PLUGINS_LINK_LIBS ${LIBUSB_LIBRARIES})

	add_library(DeviceProxy_LibUSB SHARED DeviceProxy_LibUSB.cpp LibUSB_static.cpp)
	set_source_files_properties(DeviceProxy_LibUSB.cpp PROPERTIES COMPILE_FLAGS  "${CMAKE_CPP_FLAGS}")
	set_target_properties(DeviceProxy_LibUSB PROPERTIES PREFIX "")
	target_link_libraries(DeviceProxy_LibUSB ${PLUGINS_LINK_LIBS})
	install(TARGETS DeviceProxy_LibUSB
        LIBRARY DESTINATION lib/USBProxy${LIB_SUFFIX}
        COMPONENT sharedlibs
        )

	add_library(DeviceProxy_Xbox SHARED DeviceProxy_Xbox.cpp DeviceProxy_LibUSB.cpp)
	set_source_files_properties(DeviceProxy_Xbox.cpp PROPERTIES COMPILE_FLAGS  "${CMAKE_CPP_FLAGS}")
	set_target_properties(DeviceProxy_Xbox PROPERTIES PREFIX "")
	target_link_libraries(DeviceProxy_Xbox ${PLUGINS_LINK_LIBS})
	install(TARGETS DeviceProxy_Xbox
        LIBRARY DESTINATION lib/USBProxy${LIB_SUFFIX}
        COMPONENT sharedlibs
        )

	add_library(DeviceProxy_Xbox360 SHARED DeviceProxy_Xbox360.cpp DeviceProxy_LibUSB.cpp)
	set_source_files_properties(DeviceProxy_Xbox360.cpp PROPERTIES COMPILE_FLAGS  "${CMAKE_CPP_FLAGS}")
	set_target_properties(DeviceProxy_Xbox360 PROPERTIES PREFIX "")
	target_link_libraries(DeviceProxy_Xbox360 ${PLUGINS_LINK_LIBS})
	install(TARGETS DeviceProxy_Xbox360
        LIBRARY DESTINATION lib/USBProxy${LIB_SUFFIX}
        COMPONENT sharedlibs
        )

	add_library(DeviceProxy_NeoGeo SHARED DeviceProxy_NeoGeo.cpp DeviceProxy_LibUSB.cpp)
	set_source_files_properties(DeviceProxy_NeoGeo.cpp PROPERTIES COMPILE_FLAGS  "${CMAKE_CPP_FLAGS}")
	set_target_properties(DeviceProxy_NeoGeo PROPERTIES PREFIX "")
	target_link_libraries(DeviceProxy_NeoGeo ${PLUGINS_LINK_LIBS})
	install(TARGETS DeviceProxy_NeoGeo
        LIBRARY DESTINATION lib/USBProxy${LIB_SUFFIX}
        COMPONENT sharedlibs
        )

	add_library(DeviceProxy_PS3 SHARED DeviceProxy_PS3.cpp DeviceProxy_LibUSB.cpp)
	set_source_files_properties(DeviceProxy_PS3.cpp PROPERTIES COMPILE_FLAGS  "${CMAKE_CPP_FLAGS}")
	set_target_properties(DeviceProxy_PS3 PROPERTIES PREFIX "")
	target_link_libraries(DeviceProxy_PS3 ${PLUGINS_LINK_LIBS})
	install(TARGETS DeviceProxy_PS3
        LIBRARY DESTINATION lib/USBProxy${LIB_SUFFIX}
        COMPONENT sharedlibs
        )

	add_library(DeviceProxy_EVS SHARED DeviceProxy_EVS.cpp DeviceProxy_LibUSB.cpp)
	set_source_files_properties(DeviceProxy_EVS.cpp PROPERTIES COMPILE_FLAGS  "${CMAKE_CPP_FLAGS}")
	set_target_properties(DeviceProxy_EVS PROPERTIES PREFIX "")
	target_link_libraries(DeviceProxy_EVS ${PLUGINS_LINK_LIBS})
	install(TARGETS DeviceProxy_EVS
        LIBRARY DESTINATION lib/USBProxy${LIB_SUFFIX}
        COMPONENT sharedlibs
        )
else( ${LIBUSB_FOUND} )
	if( USE_LIBUSB1 AND NOT ${LIBUSB_FOUND} )
		message( FATAL_ERROR
			"Cannot find libUSB-1.0, which is required for USE_LIBUSB1")
	endif()
endif( ${LIBUSB_FOUND} )

find_package(lorcon)

if( ${LORCON_FOUND} )
	LIST(APPEND PLUGINS DeviceProxy_dot11)
	include_directories(${LORCON_INCLUDE_DIR})
	LIST(APPEND PLUGINS_LINK_LIBS ${LORCON_LIBRARIES})
else( ${LORCON_FOUND} )
	if( USE_LORCON AND NOT ${LORCON_FOUND} )
		message( FATAL_ERROR
			"Cannot find lorcon, which is required for USE_LORCON")
	endif()
endif( ${LORCON_FOUND} )

foreach(plugin ${PLUGINS})
	add_library(${plugin} SHARED ${plugin}.cpp)
	set_source_files_properties(${plugin}.cpp PROPERTIES COMPILE_FLAGS  "${CMAKE_CPP_FLAGS}")
	set_target_properties(${plugin} PROPERTIES PREFIX "")
	target_link_libraries(${plugin} ${PLUGINS_LINK_LIBS})
	install(TARGETS ${plugin}
        LIBRARY DESTINATION lib/USBProxy${LIB_SUFFIX}
        COMPONENT sharedlibs
        )
endforeach(plugin)
