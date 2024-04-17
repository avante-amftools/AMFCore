//
//  ModelUnit.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 8/15/23.
//

#ifndef ModelUnit_hpp
#define ModelUnit_hpp

#include "ModelAttribute.hpp"

#include "ModelUnitPtr.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    class ModelUnit : public ModelAttribute
    {
    private:
        typedef ModelAttribute super;
                        
        static ModelAttributePtr _newModelUnit();
        
    public:
        enum UnitType
        {
            unitMetre,
            unitMillimetre,
            unitMicrometre,
            unitInch,
            unitFoot
        };

        static NodeIdentifier Identifier;

        static void initialize();
        
        ModelUnit() : super(Identifier)
        { }
              
        UnitType value() const
        {
            auto i = __unitTypes.find(this->valueAsString());
            
            if (i == __unitTypes.end())
            {
                const_cast<ModelUnit*>(this)->setValue(unitMillimetre);
                return unitMillimetre;
            }
            
            return i->second;
        }

        void setValue(UnitType value)
        { this->setValueAsString(__unitNames[value]); }
        
        
        static const std::vector<std::string>& unitTitles()
        { return __unitTitles; }

    protected:
        static const std::vector<std::string> __unitNames;
        static const std::map<std::string, UnitType> __unitTypes;
        static const std::vector<std::string> __unitTitles;
    };
}

#endif /* ModelUnit_hpp */
