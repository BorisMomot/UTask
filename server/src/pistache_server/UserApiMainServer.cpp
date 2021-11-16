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

#include "pistache/endpoint.h"
#include "pistache/http.h"
#include "pistache/router.h"
#include "UserApiImpl.h"

#include "user.h"
#include "task.h"
#include "role.h"
#include "project.h"
#include "filter.h"

using namespace io::swagger::server::api;

int main() {
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(8085));

    UserApiImpl server(addr);
    server.init(2);
    server.start();

    server.shutdown();
}

