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

#include <ostream>
#include "UserApiImpl.h"

namespace io {
namespace swagger {
namespace server {
namespace api {

using namespace io::swagger::server::model;

UserApiImpl::UserApiImpl(Pistache::Address addr)
    : UserApi(addr)
    { }

void UserApiImpl::create_role(const Role &body, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::create_task(const Task &body, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::create_user(const User &body, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::delete_role(const int64_t &roleId, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::delete_task(const int64_t &taskId, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::delete_user(const int64_t &userId, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::get_project(const std::optional<std::string> &filterfield, const std::optional<std::string> &filtervalue, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::get_projects_filters(Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::get_role_by_id(const int64_t &roleId, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::get_roles(Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::get_task_by_id(const int64_t &taskId, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::get_task_by_name(const std::string &taskName, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::get_task_filters(Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::get_tasks(const std::optional<std::string> &filterField, const std::optional<std::string> &filterValue, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::get_user_by_id(const int64_t &userId, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::get_user_by_name(const std::string &username, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::get_users(const std::optional<std::string> &filterField, const std::optional<std::string> &filterValue, Pistache::Http::ResponseWriter &response) {
    UserInfo user;
    user.setId(1);
    user.setUsername("setUsername");
    user.setFirstName("setFirstName");
    user.setLastName("setLastName");
    user.setEmail("setEmail");
    user.setPhone("setPhone");
    user.setUserStatus(1);

    auto json = user.toJson();
    response.send(Pistache::Http::Code::Ok, json.dump());
}

void UserApiImpl::get_users_filters(Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::update_task(const int64_t &taskId, const std::optional<std::string> &taskfiled, const std::optional<std::string> &taskvalue, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void UserApiImpl::update_user(const int64_t &userId, const std::optional<std::string> &userfiled, const std::optional<std::string> &uservalue, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}

}
}
}
}
