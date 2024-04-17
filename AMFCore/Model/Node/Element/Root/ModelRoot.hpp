//
//  ModelRoot.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/28/23.
//

#ifndef ModelRoot_hpp
#define ModelRoot_hpp

#include "ModelElement.hpp"

#include "ModelRootPtr.hpp"
#include "ModelUnitPtr.hpp"
#include "ModelColorPtr.hpp"
#include "ModelObjectPtr.hpp"
#include "ModelVolumePtr.hpp"
#include "ModelTrianglePtr.hpp"

#include "Vector3D.hpp"
#include "Color.hpp"

#include <assert.h>

namespace tinyxml2
{
    class XMLDocument;
};

namespace AMFCore
{
    using namespace tinyxml2;
    
    class ModelRoot : public ModelElement
    {
    private:
        typedef ModelElement super;
                
        static ModelElementPtr _newModelRoot();
        
    public:
        static NodeIdentifier Identifier;

        static void initialize();
        
        // Create a ModelRoot object.
        
        static ModelRootPtr newModelRoot()
        {
            auto result = std::dynamic_pointer_cast<ModelRoot>(ModelElement::newModelElement(ModelRoot::Identifier));
            assert(result != nullptr);
            return result;
        }

        ModelRoot() : super(Identifier),
        _compressed(true)
        { }
        
        bool compressed() const
        { return _compressed; }
        
        void setCompressed(bool compressed)
        { _compressed = compressed; }
        
        std::unique_ptr<XMLDocument> toXMLDocument() const;

        ModelObjectPtr newModelObject();

        ModelUnitPtr modelUnit();
        
        ConstModelUnitPtr modelUnit() const;
                
        ModelColorPtr modelColor();
        
        ConstModelColorPtr modelColor() const;
        
        ModelObjectPtr defaultModelObject();
        
        ModelVolumePtr defaultModelVolume();
                
        std::vector<ModelObjectPtr> modelObjects();
        
        const std::vector<ConstModelObjectPtr> modelObjects() const;

        std::vector<ModelElementPtr> modelMaterials();
        
        const std::vector<ConstModelElementPtr> modelMaterials() const;

        std::vector<ModelElementPtr> modelConstellations();
        
        const std::vector<ConstModelElementPtr> modelConstellations() const;
        
    protected:
        bool _compressed;
    };
}

#endif /* ModelRoot_hpp */
