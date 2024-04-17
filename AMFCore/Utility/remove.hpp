//
//  remove.hpp
//
//  Created by Ron Aldrich on 9/22/20.
//  Copyright © 2020 Ron Aldrich. All rights reserved.
//

#ifndef remove_hpp
#define remove_hpp

#include <vector>
#include <set>

namespace AMFCore
{
    template <class ForwardIterator, class ToRemove>
    ForwardIterator remove_(ForwardIterator first, ForwardIterator last, ToRemove toRemove)
    {
        ForwardIterator result = first;
        
        while (first!=last)
        {
            if (!toRemove.count(*first))
            {
                *result = *first;
                ++result;
            }
            ++first;
        }
        return result;
    };
    
    template<class T>
    void erase(std::vector<T>& from, const std::set<T>& toRemove)
    {
        from.erase(remove_(from.begin(), from.end(), toRemove), from.end());
    };
}

#endif /* remove_hpp */
