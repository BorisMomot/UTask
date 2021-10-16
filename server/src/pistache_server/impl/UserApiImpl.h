/**
* Pet project for tasks managment
* Declare Api between chat bot and server part
*
* OpenAPI spec version: 0.0.1
* Contact: bolik-u13@mail.ru
*
* NOTE: This class is auto generated by the swagger code generator program.
* https://github.com/swagger-api/swagger-codegen.git
* Do not edit the class manually.
*/

/*
* UserApiImpl.h
*
* 
*/

#ifndef USER_API_IMPL_H_
#define USER_API_IMPL_H_


#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <memory>

#include <UserApi.h>

#include "ProjectFilter.h"
#include "ProjectInfo.h"
#include "Role.h"
#include "RoleInfo.h"
#include "Task.h"
#include "TaskFilter.h"
#include "TaskInfo.h"
#include "User.h"
#include "UserFilter.h"
#include "UserInfo.h"
#include <string>

namespace io {
namespace swagger {
namespace server {
namespace api {

using namespace io::swagger::server::model;

class UserApiImpl : public io::swagger::server::api::UserApi {
public:
    UserApiImpl(Pistache::Address addr);
    ~UserApiImpl() { };

    void create_role(const Role &body, Pistache::Http::ResponseWriter &response);
    void create_task(const Task &body, Pistache::Http::ResponseWriter &response);
    void create_user(const User &body, Pistache::Http::ResponseWriter &response);
    void delete_role(const int64_t &roleId, Pistache::Http::ResponseWriter &response);
    void delete_task(const int64_t &taskId, Pistache::Http::ResponseWriter &response);
    void delete_user(const int64_t &userId, Pistache::Http::ResponseWriter &response);
    void get_project(const std::optional<std::string> &filterfield, const std::optional<std::string> &filtervalue, Pistache::Http::ResponseWriter &response);
    void get_projects_filters(Pistache::Http::ResponseWriter &response);
    void get_role_by_id(const int64_t &roleId, Pistache::Http::ResponseWriter &response);
    void get_roles(Pistache::Http::ResponseWriter &response);
    void get_task_by_id(const int64_t &taskId, Pistache::Http::ResponseWriter &response);
    void get_task_by_name(const std::string &taskName, Pistache::Http::ResponseWriter &response);
    void get_task_filters(Pistache::Http::ResponseWriter &response);
    void get_tasks(const std::optional<std::string> &filterField, const std::optional<std::string> &filterValue, Pistache::Http::ResponseWriter &response);
    void get_user_by_id(const int64_t &userId, Pistache::Http::ResponseWriter &response);
    void get_user_by_name(const std::string &username, Pistache::Http::ResponseWriter &response);
    void get_users(const std::optional<std::string> &filterField, const std::optional<std::string> &filterValue, Pistache::Http::ResponseWriter &response);
    void get_users_filters(Pistache::Http::ResponseWriter &response);
    void update_task(const int64_t &taskId, const std::optional<std::string> &taskfiled, const std::optional<std::string> &taskvalue, Pistache::Http::ResponseWriter &response);
    void update_user(const int64_t &userId, const std::optional<std::string> &userfiled, const std::optional<std::string> &uservalue, Pistache::Http::ResponseWriter &response);

};

}
}
}
}



#endif