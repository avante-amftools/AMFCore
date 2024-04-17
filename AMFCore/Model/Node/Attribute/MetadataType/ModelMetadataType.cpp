//
//  ModelMetadataType.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 10/24/23.
//

#include "ModelMetadataType.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    NodeIdentifier ModelMetadataType::Identifier("type");
    
    const std::string ModelMetadataType::MetadataTypeName("name");
    const std::string ModelMetadataType::MetadataTypeDescription("description");
    const std::string ModelMetadataType::MetadataTypeURL("url");
    const std::string ModelMetadataType::MetadataTypeAuthor("author");
    const std::string ModelMetadataType::MetadataTypeCompany("company");
    const std::string ModelMetadataType::MetadataTypeProducer("producer");
    const std::string ModelMetadataType::MetadataTypeRevision("revision");
    const std::string ModelMetadataType::MetadataTypeTolerance("tolerance");
    const std::string ModelMetadataType::MetadataTypeVolume("volume");
    const std::string ModelMetadataType::MetadataTypeElasticModulus("elasticmodulus");
    const std::string ModelMetadataType::MetadataTypePoissonRatio("poissonratio");
    const std::string ModelMetadataType::MetadataTypeColorProfile("colourprofile");

    ModelAttributePtr ModelMetadataType::newModelMetadataType()
    {
        return std::make_shared<ModelMetadataType>();
    }
    
    void ModelMetadataType::initialize()
    {
        static bool initialized = false;
        
        if (!initialized)
        {
            newModelAttributeFunctions().emplace(Identifier, newModelMetadataType);

            initialized = true;
        }
    }        
}
