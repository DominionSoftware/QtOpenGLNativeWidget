 cmake_minimum_required(VERSION 3.16)


set(QT_OPENGL_NATIVE_WIDGET_PROJECT_NAME
	QtOpenGLNativeWidget
)
project(${QT_OPENGL_NATIVE_WIDGET_PROJECT_NAME})

find_package(VTK 8.2 REQUIRED NO_MODULE)
include(${VTK_USE_FILE})

find_package(Qt5 COMPONENTS Core Gui OpenGL OpenGLExtensions Widgets REQUIRED)
find_package(OpenGL REQUIRED)

set(Qt5Includes
    ${Qt5Core_INCLUDES}
    ${Qt5Gui_INCLUDES}
    ${Qt5OpenGL_INCLUDES}
	${Qt5OpenGLExtensions_INCLUDES}
    ${Qt5Widgets_INCLUDES}
  
)

set(Qt5Libraries
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5OpenGL_LIBRARIES}
    ${Qt5OpenGLExtensions_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
)

set(SOURCE
	main.cpp
	mainwindow.cpp
	mainwindow.h
 	 
)


set(HEADERS_MOC_HPP
	 mainwindow.h
)

QT5_WRAP_CPP(MOCSrcs
	${HEADERS_MOC_HPP}
)

 include_directories(  )
add_executable(${QT_OPENGL_NATIVE_WIDGET_PROJECT_NAME} WIN32
	${SOURCE}
	${MOCSrcs}
)


target_link_libraries(${QT_OPENGL_NATIVE_WIDGET_PROJECT_NAME} 
	debug netapi32 optimized netapi32
	debug ws2_32 optimized ws2_32
	debug wsock32 optimized wsock32
	debug Shcore optimized Shcore
	${VTK_LIBRARIES}
	${Qt5Libraries}
	

)

 