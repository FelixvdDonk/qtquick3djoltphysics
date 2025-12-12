set(PHYSICS_REPO_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/)

include(Jolt/Jolt.cmake)

qt_internal_add_3rdparty_library(BundledJoltPhysics
    STATIC
    SKIP_AUTOMOC
    EXCEPTIONS
    INSTALL
    SOURCES ${JOLT_PHYSICS_SRC_FILES}
    INCLUDE_DIRECTORIES
        ./
)

# Silence warnings
qt_disable_warnings(BundledJoltPhysics)
qt_set_symbol_visibility_hidden(BundledJoltPhysics)
