cmake_minimum_required(VERSION 3.16)

qt_internal_add_test(tst_hermitepath
    SOURCES
        tst_hermitepath.cpp
    INCLUDE_DIRECTORIES
        ${CMAKE_SOURCE_DIR}/src/3rdparty/JoltPhysics
    LIBRARIES
        Qt::Test
        Qt::Quick3DPrivate
        Qt::Quick3DJoltPhysicsPrivate
)
