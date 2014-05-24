//
//  CollidableSurface.cpp
//  Arkanoid
//
//  Created by Kirill Muzykov on 24/05/14.
//  Copyright (c) 2014 Kirill Muzykov. All rights reserved.
//

#include "CollidableSurface.h"
#include "ArkanoidGameObject.h"

static bool checkLineAndLineIntersection(const vec2& p1, const vec2& p2, const vec2& p3, const vec2& p4, float& s, float &t, vec2& pointOfIntersection);
static float distanceFromPointToSegment(const vec2& point, const vec2& p1, const vec2& p2);

CollidableSurface::CollidableSurface(const vec2& origin, const vec2& normal, const vec2& p1, const vec2& p2, ArkanoidGameObject* owner)
: _origin(origin),
  _normal(normal),
  _p1(p1),
  _p2(p2),
  _owner(owner)
{
        
}

bool CollidableSurface::ballIntersectsWhileMoving(const vec2& ballPos, const vec2& ballDesiredPos, const vec2& ballMovementVec, const float ballRadius, vec2& intersectionPoint)
{
    vec2 globalP1 = (_origin + _p1) + _normal * ballRadius;
    vec2 globalP2 = (_origin + _p2) + _normal * ballRadius;
   
    float s, t;
    bool linesIntersect = checkLineAndLineIntersection(globalP1, globalP2, ballPos, ballDesiredPos, s, t, intersectionPoint);

    if(linesIntersect && (t >=0.0f && t <= 1.0f))
    {
        float distanceFromSurfaceToMovementVector = distanceFromPointToSegment(intersectionPoint, globalP1, globalP2);
        return distanceFromSurfaceToMovementVector <= 2.0f * ballRadius; //TODO: Maybe add some EPS
    }
    
    return false;
};

static bool checkLineAndLineIntersection(const vec2& p1, const vec2& p2, const vec2& p3, const vec2& p4, float& s, float &t, vec2& pointOfIntersection)
{
    // FAIL: Line undefined
    if ( (p1.x==p2.x && p1.y==p2.y) || (p3.x==p4.x && p3.y==p4.y) ) return false;
    
    const float BAx = p2.x - p1.x;
    const float BAy = p2.y - p1.y;
    const float DCx = p4.x - p3.x;
    const float DCy = p4.y - p3.y;
    const float ACx = p1.x - p3.x;
    const float ACy = p1.y - p3.y;
    
    const float denom = DCy*BAx - DCx*BAy;
    
    s = DCx*ACy - DCy*ACx;
    t = BAx*ACy - BAy*ACx;
    
    if (denom == 0) {
        if (s == 0 || t == 0) {
            // Lines incident
            return true;
        }
        // Lines parallel and not incident
        return false;
    }
    
    s = s / denom;
    t = t / denom;
    
    // Point of intersection
    pointOfIntersection.x = p1.x + s * (p2.x - p1.x);
    pointOfIntersection.y = p1.y + s * (p2.y - p1.y);
    
    return true;
}

static float distanceFromPointToSegment(const vec2& point, const vec2& p1, const vec2& p2)
{
    const float l2 = (p2 - p1).LengthSquared();
    
    if (l2 < 0.01f)
        return (point - p1).Length(); //p1 == p2, so this is distance to any point.
    
    // Consider the line extending the segment, parameterized as p1 + t (p2 - p1).
    // We find projection of point onto the line.
    const float t = (point - p1).Dot(p2 - p1) / l2;
    
    if (t < 0.0f)       return (point - p1).Length(); //Projection falls beyond p1 end of segment
    else if (t > 1.0f)  return (point - p2).Length(); //Projection falls beyond p2 end of segment
    
    //Looks like projetion falls on our segment
    vec2 projection = p1 + ((p2 - p1) * t);
    return (point - projection).Length();
}