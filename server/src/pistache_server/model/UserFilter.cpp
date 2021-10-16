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


#include "UserFilter.h"

namespace io {
namespace swagger {
namespace server {
namespace model {

UserFilter::UserFilter()
{
    m_FilterName = "";
    m_FilterNameIsSet = false;
    m_FilterValuesIsSet = false;
    
}

UserFilter::~UserFilter()
{
}

void UserFilter::validate()
{
    // TODO: implement validation
}

nlohmann::json UserFilter::toJson() const
{
    nlohmann::json val = nlohmann::json::object();

    if(m_FilterNameIsSet)
    {
        val["filterName"] = ModelBase::toJson(m_FilterName);
    }
    {
        nlohmann::json jsonArray;
        for( auto& item : m_FilterValues )
        {
            jsonArray.push_back(ModelBase::toJson(item));
        }
        
        if(jsonArray.size() > 0)
        {
            val["filterValues"] = jsonArray;
        }
    }
    

    return val;
}

void UserFilter::fromJson(nlohmann::json& val)
{
    if(val.find("filterName") != val.end())
    {
        setFilterName(val.at("filterName"));
        
    }
    {
        m_FilterValues.clear();
        nlohmann::json jsonArray;
        if(val.find("filterValues") != val.end())
        {
        for( auto& item : val["filterValues"] )
        {
            m_FilterValues.push_back(item);
            
        }
        }
    }
    
}


std::string UserFilter::getFilterName() const
{
    return m_FilterName;
}
void UserFilter::setFilterName(std::string value)
{
    m_FilterName = value;
    m_FilterNameIsSet = true;
}
bool UserFilter::filterNameIsSet() const
{
    return m_FilterNameIsSet;
}
void UserFilter::unsetFilterName()
{
    m_FilterNameIsSet = false;
}
std::vector<std::string>& UserFilter::getFilterValues()
{
    return m_FilterValues;
}
bool UserFilter::filterValuesIsSet() const
{
    return m_FilterValuesIsSet;
}
void UserFilter::unsetFilterValues()
{
    m_FilterValuesIsSet = false;
}

}
}
}
}

