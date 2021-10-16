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
 * ProjectFilter.h
 *
 * 
 */

#ifndef ProjectFilter_H_
#define ProjectFilter_H_


#include "ModelBase.h"

#include <string>
#include <vector>

namespace io {
namespace swagger {
namespace server {
namespace model {

/// <summary>
/// 
/// </summary>
class  ProjectFilter
    : public ModelBase
{
public:
    ProjectFilter();
    virtual ~ProjectFilter();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    nlohmann::json toJson() const override;
    void fromJson(nlohmann::json& json) override;

    /////////////////////////////////////////////
    /// ProjectFilter members

    /// <summary>
    /// 
    /// </summary>
    std::string getFilterName() const;
    void setFilterName(std::string value);
    bool filterNameIsSet() const;
    void unsetFilterName();
    /// <summary>
    /// 
    /// </summary>
    std::vector<std::string>& getFilterValues();
    bool filterValuesIsSet() const;
    void unsetFilterValues();

protected:
    std::string m_FilterName;
    bool m_FilterNameIsSet;
    std::vector<std::string> m_FilterValues;
    bool m_FilterValuesIsSet;
};

}
}
}
}

#endif /* ProjectFilter_H_ */
