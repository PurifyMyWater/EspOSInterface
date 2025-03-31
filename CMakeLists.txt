idf_component_register(SRCS "EspOSInterface.cpp"
                    INCLUDE_DIRS "include")

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
if(DEFINED ENV{GITHUB_ACTION})
    set(GIT_REPO https://vacmg:$ENV{GH_PAT}@github.com/vacmg/OSInterface.git)
else()
    set(GIT_REPO git@github.com:vacmg/OSInterface.git)
endif()
message(STATUS "GIT_REPO: ${GIT_REPO}")
FetchContent_Declare(
        OSInterface
        GIT_REPOSITORY  ${GIT_REPO}
        GIT_TAG         73fdfbf1000ea1d8a0c3e7eaa391fb7b51fec06a # TODO: use main branch
#        GIT_TAG         main
)
FetchContent_MakeAvailable(OSInterface)
target_link_libraries(${COMPONENT_LIB} PUBLIC OSInterface)
