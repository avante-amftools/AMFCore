//
//  ModelMetadataType.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 10/24/23.
//

#ifndef ModelMetadataType_hpp
#define ModelMetadataType_hpp

#include "ModelAttribute.hpp"

#include "ModelMetadataTypePtr.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    class ModelMetadataType : public ModelAttribute
    {
    private:
        typedef ModelAttribute super;
                
        static ModelAttributePtr newModelMetadataType();
        
    public:
        static NodeIdentifier Identifier;

        static const std::string MetadataTypeName;                // Alphanumeric label of the entity.
        static const std::string MetadataTypeDescription;        // Description of the entity.
        static const std::string MetadataTypeURL;                // External URL relating to the entity.
        static const std::string MetadataTypeAuthor;            // Name(s) of the author(s) of the entity.
        static const std::string MetadataTypeCompany;            // Company generating the entity.
        static const std::string MetadataTypeProducer;            // Name and version of the software which produced the entity.
        static const std::string MetadataTypeRevision;            // Revision of the entity.
        static const std::string MetadataTypeTolerance;            // Desired manufacturing tolerance of the entity, in entity's units.
        static const std::string MetadataTypeVolume;            // Total volume of the entity, in the entity's units (object and volume elements only)
        static const std::string MetadataTypeElasticModulus;    // Elastic modulus of the material, in SI units (<material> only).
        static const std::string MetadataTypePoissonRatio;        // Poisson ratio of the material, in SI units (<material> only).
        static const std::string MetadataTypeColorProfile;        // ICC color space used to interpret colors (<amf> only).

        static void initialize();
        
        ModelMetadataType() : super(Identifier)
        {
        }
    };
}

#endif /* ModelMetadataType_hpp */
