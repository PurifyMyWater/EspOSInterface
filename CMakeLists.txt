idf_component_register(SRC_DIRS "Source"
                    INCLUDE_DIRS "Source/include")

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
        OSInterface
        GIT_REPOSITORY  git@github.com:vacmg/OSInterface.git
        GIT_TAG         Add_OSInterface_MessageQueue_V2 # TODO: merge & release OSInterface before using a stable tag
)
FetchContent_MakeAvailable(OSInterface)

target_link_libraries(${COMPONENT_LIB} PUBLIC OSInterface)
