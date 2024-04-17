//
//  ModelVertices.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/5/23.
//

#ifndef ModelVertices_hpp
#define ModelVertices_hpp

#include "ModelElement.hpp"

#include "ModelVerticesPtr.hpp"
#include "ModelMeshPtr.hpp"

#include "ModelVertexPtr.hpp"

#include "Vector3D.hpp"
#include "Color.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    class ModelVertices : public ModelElement
    {
    private:
        typedef ModelElement super;
                
        static ModelElementPtr _newModelVertices();
        
        static ModelVerticesPtr newModelVertices();
        
    public:
        static NodeIdentifier Identifier;

        static void initialize();
                
        ModelVertices() : super(Identifier)
        { }
               
        virtual ModelElementPtr addElement(ModelElementPtr modelElement);

        virtual void removeElement(ModelElementPtr modelElement);
        
        ModelVertexPtr addVertex(const DoubleVector3D coordinate,
                                 const DoubleVector3D* normal,
                                 const DoubleColor* color);
        
        virtual void fromXML(const XMLElement* xmlElement);
        
        std::vector<ModelVertexPtr> modelVertexes();
        
        const std::vector<ConstModelVertexPtr> modelVertexes() const;
        
    protected:
        std::set<ModelVertexPtr> _modelVertexes;
    };
}

#endif /* ModelVertices_hpp */
