//
//  KMTouchDispatcher.cpp
//  Arkanoid
//
//  Created by Kirill Muzykov on 25/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#include "KMTouchDispatcher.h"
#include "KMMacros.h"

KMTouchDispatcher& KMTouchDispatcher::getSharedInstance()
{
    static KMTouchDispatcher _Instance;
    return _Instance;
}

void KMTouchDispatcher::notifyTouchBegan(const vec2& location)
{
    bool needCleanup = false;
    
    for (SubscriberAdapter& adapter: _subscribers)
    {
        if (adapter.subscriber != nullptr)
            adapter.subscriber->touchBegan(location);
        else
            needCleanup = true;
    }
    
    if (needCleanup)
        removeMarkedSubscribers();
}

void KMTouchDispatcher::notifyTouchMove(const vec2& location)
{
    bool needCleanup = false;
    
    for (SubscriberAdapter& adapter: _subscribers)
    {
        if (adapter.subscriber != nullptr)
            adapter.subscriber->touchMoved(location);
        else
            needCleanup = true;
    }
    
    if (needCleanup)
        removeMarkedSubscribers();

}

void KMTouchDispatcher::notifyTouchEnded(const vec2& location)
{
    bool needCleanup = false;
    
    for (SubscriberAdapter& adapter: _subscribers)
    {
        if (adapter.subscriber != nullptr)
            adapter.subscriber->touchEnded(location);
        else
            needCleanup = true;
    }
    
    if (needCleanup)
        removeMarkedSubscribers();
}

void KMTouchDispatcher::subscribe(ITouchSubscriber* const subscriber)
{
    auto iter = std::find_if(_subscribers.begin(), _subscribers.end(), [subscriber](SubscriberAdapter& adapter) { return adapter.subscriber == subscriber; });
    if (iter != _subscribers.end())
    {
        KMLOG("Subscribing multile times");
    }
    else
    {
        SubscriberAdapter adapter(subscriber);
        _subscribers.push_back(adapter);
    }
}

void KMTouchDispatcher::unsubscribe(ITouchSubscriber* subscriber)
{
    auto iter = std::find_if(_subscribers.begin(), _subscribers.end(), [subscriber](SubscriberAdapter& adapter) { return adapter.subscriber == subscriber; });
    if (iter != _subscribers.end())
    {
        (*iter).subscriber = nullptr;
    }
    else
    {
        KMLOG("Can't find subscriber to unsubscribe");
    }
}

void KMTouchDispatcher::removeMarkedSubscribers()
{
    _subscribers.remove_if([](const SubscriberAdapter& adapter){ return adapter.subscriber == nullptr; });
}
