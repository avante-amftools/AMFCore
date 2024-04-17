//
//  SceneVertex.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/23/23.
//

#ifndef SceneVertex_hpp
#define SceneVertex_hpp

#include "Vector3D.hpp"
#include "Color.hpp"

#include <assert.h>

namespace AMFCore
{
    struct SceneVertex
    {
        DoubleVector3D coordinates;
        DoubleVector3D normal;
        SingleColor color;
        // Texture mapping...
        
        // operators
        
        const bool operator == (const SceneVertex& rhs) const
        {
            return (coordinates == rhs.coordinates &&
                    normal == rhs.normal &&
                    color == rhs.color);
        }

        const bool operator < (const SceneVertex& rhs) const
        {
            return (coordinates < rhs.coordinates ? true :
                    coordinates > rhs.coordinates ? false :
                    normal < rhs.normal ? true :
                    normal > rhs.normal ? false :
                    color < rhs.color ? true :
                    color > rhs.color);
        }

        void debugShow(uint32_t index) const
        {
            /*
            printf("%d [%f %f %f] [%f %f %f] [%f %f %f %f]\n",
                   index,
                   coordinates.x(), coordinates.y(), coordinates.z(),
                   normal.x(), normal.y(), normal.z(),
                   color.r(), color.g(), color.b(), color.a());
             */
        }
    };
    
    class SceneVertices : public std::vector<SceneVertex>
    {
    private:
        typedef std::vector<SceneVertex> super;
        
    public:
        SceneVertices() : super() { }
        
        SceneVertices(const SceneVertices& other) : super(other)
        {
            assert(!"SceneVertices copy constructor should not be called. Avoid using auto when declaring SceneVertices& (reference) variables.");
        }
    };

}

#endif /* SceneVertex_hpp */
