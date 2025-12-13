idf_component_register(SRC_DIRS "Source"
                    INCLUDE_DIRS "Source/include")

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
        OSInterface
        GIT_REPOSITORY  git@github.com:vacmg/OSInterface.git
        GIT_TAG         v0.0.1
)
FetchContent_MakeAvailable(OSInterface)

target_link_libraries(${COMPONENT_LIB} PUBLIC OSInterface)
