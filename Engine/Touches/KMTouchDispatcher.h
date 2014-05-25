//
//  KMTouchDispatcher.h
//  Arkanoid
//
//  Created by Kirill Muzykov on 25/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#ifndef __Arkanoid__KMTouchDispatcher__
#define __Arkanoid__KMTouchDispatcher__

#include "ITouchSubscriber.h"
#include "Vector.hpp"
#include <list>

class KMTouchDispatcher
{
public:
    void notifyTouchBegan(const vec2& location);
    void notifyTouchMove(const vec2& location);
    void notifyTouchEnded(const vec2& location);
    
    void subscribe(ITouchSubscriber* subscriber);
    void unsubscribe(ITouchSubscriber* subscriber);
    
    static KMTouchDispatcher& getSharedInstance();
    
private:
    KMTouchDispatcher() {}
    KMTouchDispatcher(const KMTouchDispatcher& other) = delete;
    KMTouchDispatcher& operator=(const KMTouchDispatcher&) = delete;
    void removeMarkedSubscribers();
    
    struct SubscriberAdapter
    {
        ITouchSubscriber* subscriber;
        
        SubscriberAdapter(ITouchSubscriber* sub): subscriber(sub) {}
        
        bool operator < (const SubscriberAdapter& other)
        {
            return subscriber < other.subscriber;
        };
    };
    
    std::list<SubscriberAdapter> _subscribers;
};

#endif /* defined(__Arkanoid__KMTouchDispatcher__) */
