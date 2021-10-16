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


#include "ProjectInfo.h"

namespace io {
namespace swagger {
namespace server {
namespace model {

ProjectInfo::ProjectInfo()
{
    m_Id = 0L;
    m_IdIsSet = false;
    m_Name = "";
    m_NameIsSet = false;
    m_Description = "";
    m_DescriptionIsSet = false;
    
}

ProjectInfo::~ProjectInfo()
{
}

void ProjectInfo::validate()
{
    // TODO: implement validation
}

nlohmann::json ProjectInfo::toJson() const
{
    nlohmann::json val = nlohmann::json::object();

    if(m_IdIsSet)
    {
        val["id"] = m_Id;
    }
    if(m_NameIsSet)
    {
        val["name"] = ModelBase::toJson(m_Name);
    }
    if(m_DescriptionIsSet)
    {
        val["description"] = ModelBase::toJson(m_Description);
    }
    

    return val;
}

void ProjectInfo::fromJson(nlohmann::json& val)
{
    if(val.find("id") != val.end())
    {
        setId(val.at("id"));
    }
    if(val.find("name") != val.end())
    {
        setName(val.at("name"));
        
    }
    if(val.find("description") != val.end())
    {
        setDescription(val.at("description"));
        
    }
    
}


int64_t ProjectInfo::getId() const
{
    return m_Id;
}
void ProjectInfo::setId(int64_t value)
{
    m_Id = value;
    m_IdIsSet = true;
}
bool ProjectInfo::idIsSet() const
{
    return m_IdIsSet;
}
void ProjectInfo::unsetId()
{
    m_IdIsSet = false;
}
std::string ProjectInfo::getName() const
{
    return m_Name;
}
void ProjectInfo::setName(std::string value)
{
    m_Name = value;
    m_NameIsSet = true;
}
bool ProjectInfo::nameIsSet() const
{
    return m_NameIsSet;
}
void ProjectInfo::unsetName()
{
    m_NameIsSet = false;
}
std::string ProjectInfo::getDescription() const
{
    return m_Description;
}
void ProjectInfo::setDescription(std::string value)
{
    m_Description = value;
    m_DescriptionIsSet = true;
}
bool ProjectInfo::descriptionIsSet() const
{
    return m_DescriptionIsSet;
}
void ProjectInfo::unsetDescription()
{
    m_DescriptionIsSet = false;
}

}
}
}
}
