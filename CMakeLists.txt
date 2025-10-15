file(GLOB sources "./*.cpp" "./*.c")
idf_component_register(SRCS ${sources}
                    INCLUDE_DIRS "include")

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
        OSInterface
        GIT_REPOSITORY  git@github.com:vacmg/OSInterface.git
        GIT_TAG         v1.1.1
)
FetchContent_MakeAvailable(OSInterface)

target_link_libraries(${COMPONENT_LIB} PUBLIC OSInterface)
