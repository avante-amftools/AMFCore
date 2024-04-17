//
//  ModelObject.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/28/23.
//

#ifndef ModelObject_hpp
#define ModelObject_hpp

#include "ModelElement.hpp"

#include "ModelObjectPtr.hpp"
#include "ModelRootPtr.hpp"
#include "ModelMeshPtr.hpp"
#include "ModelVolumePtr.hpp"
#include "ModelTrianglePtr.hpp"
#include "ModelMetadataPtr.hpp"

#include "Vector3D.hpp"
#include "Color.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    class ModelObject : public ModelElement
    {
        //  <object id={integer}>
        //      <metadata>          Plural
        //      <colour>            Singular
        //      <mesh>              Singular

    private:
        typedef ModelElement super;
                
        static ModelElementPtr _newModelObject();
        
    public:
        static NodeIdentifier Identifier;

        static void initialize();
                
        ModelObject() : super(Identifier)
        { }
        
        ModelObjectPtr sharedModelObjectPtr()
        { return std::static_pointer_cast<ModelObject>(shared_from_this()); }
        
        const std::string& name() const;
        
        ModelMeshPtr defaultModelMesh();
        
        ModelVolumePtr defaultModelVolume();
        
        ModelMeshPtr newModelMesh();

        ModelMeshPtr modelMesh();
        
        ConstModelMeshPtr modelMesh() const;
        
        ModelMetadataPtr modelName();
        
        ConstModelMetadataPtr modelName() const;
        
    protected:
    };
}

#endif /* ModelObject_hpp */
