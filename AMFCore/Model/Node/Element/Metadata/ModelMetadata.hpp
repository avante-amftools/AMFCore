//
//  ModelMetadata.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 4/13/23.
//

#ifndef ModelMetadata_hpp
#define ModelMetadata_hpp

#include "ModelElement.hpp"

#include "ModelMetadataPtr.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    class ModelMetadata : public ModelElement
    {
    private:
        typedef ModelElement super;
                
        static ModelElementPtr _newModelMetadata();
        
    public:
        static NodeIdentifier Identifier;

        static void initialize();
        
        ModelMetadata() : super(Identifier)
        { }
        
        virtual const std::string& type() const;
        
        void setType(const std::string& type);
        
        virtual void debugShow(std::string indent = "");

    protected:
    };
}

#endif /* ModelMetadata_hpp */
