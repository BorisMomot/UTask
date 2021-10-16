#cmake_minimum_required (VERSION 3.2)

#project(server)

#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)

#link_directories(/usr/local/lib/)

aux_source_directory(model MODEL_SOURCES)
file(GLOB USER_API_SOURCES
"api/UserApi.h"
"api/UserApi.cpp"
"impl/UserApiImpl.h"
"impl/UserApiImpl.cpp"
)

include_directories(model)
include_directories(api)
include_directories(impl)

set(USER_API_SERVER_SOURCES
UserApiMainServer.cpp
    ${MODEL_SOURCES}
    ${USER_API_SOURCES})

add_executable(user_api_server
${USER_API_SERVER_SOURCES})

target_link_libraries(user_api_server pistache pthread  nlohmann_json::nlohmann_json)
target_include_directories(user_api_server PUBLIC RapidJSON )

#------------------------------------------------------------------------------------------------
#
#aux_source_directory(model MODEL_SOURCES)
#file(GLOB PROJECT_API_SOURCES
#        "api/ProjectApi.h"
#        "api/ProjectApi.cpp"
#        "impl/ProjectApiImpl.h"
#        "impl/ProjectApiImpl.cpp"
#        )
#file(GLOB ROLE_API_SOURCES
#        "api/RoleApi.h"
#        "api/RoleApi.cpp"
#        "impl/RoleApiImpl.h"
#        "impl/RoleApiImpl.cpp"
#        )
#file(GLOB TASK_API_SOURCES
#        "api/TaskApi.h"
#        "api/TaskApi.cpp"
#        "impl/TaskApiImpl.h"
#        "impl/TaskApiImpl.cpp"
#        )
#file(GLOB USER_API_SOURCES
#        "api/UserApi.h"
#        "api/UserApi.cpp"
#        "impl/UserApiImpl.h"
#        "impl/UserApiImpl.cpp"
#        )
#
#include_directories(model)
#include_directories(api)
#include_directories(impl)
#
#set(PROJECT_API_SERVER_SOURCES
#        ProjectApiMainServer.cpp
#        ${MODEL_SOURCES}
#        ${PROJECT_API_SOURCES})
#set(ROLE_API_SERVER_SOURCES
#        RoleApiMainServer.cpp
#        ${MODEL_SOURCES}
#        ${ROLE_API_SOURCES})
#set(TASK_API_SERVER_SOURCES
#        TaskApiMainServer.cpp
#        ${MODEL_SOURCES}
#        ${TASK_API_SOURCES})
#set(USER_API_SERVER_SOURCES
#        UserApiMainServer.cpp
#        ${MODEL_SOURCES}
#        ${USER_API_SOURCES})
#
#add_executable(project_api_server
#        ${PROJECT_API_SERVER_SOURCES})
#add_executable(role_api_server
#        ${ROLE_API_SERVER_SOURCES})
#add_executable(task_api_server
#        ${TASK_API_SERVER_SOURCES})
#add_executable(user_api_server
#        ${USER_API_SERVER_SOURCES})

#target_link_libraries(project_api_server pistache pthread  nlohmann_json::nlohmann_json)
#target_link_libraries(role_api_server pistache pthread  nlohmann_json::nlohmann_json)
#target_link_libraries(task_api_server pistache pthread  nlohmann_json::nlohmann_json)
#target_link_libraries(user_api_server pistache pthread  nlohmann_json::nlohmann_json)
#
#target_include_directories(project_api_server PUBLIC RapidJSON )
#target_include_directories(role_api_server PUBLIC RapidJSON )
#target_include_directories(task_api_server PUBLIC RapidJSON )
#target_include_directories(user_api_server PUBLIC RapidJSON )









