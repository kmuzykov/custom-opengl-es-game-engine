//
//  KMVertex.cpp
//  Bowling
//
//  Created by Kirill Muzykov on 20/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#include "KMVertex.h"
#include "KMFileUtils.h"
#include "KMMacros.h"

#include <fstream>
#include <vector>

using namespace std;

std::vector<KMVertex> KMVertex::loadFromObj(const char* objFileName, bool includeTexCoords)
{
    vector<vec3> positions;
    vector<vec2> textureCoords;
    vector<vec3> normals;
    vector<ivec3> faces;
    
    const char* objFilePath = KMFileUtils::getSharedFileUtils().getFilePath(objFileName);
    ifstream objFile(objFilePath);
    
    while (objFile)
    {
        string line;
        getline(objFile, line);
        
        string type = line.substr(0,2);
        
        if (type.compare("v ") == 0)
        {
            vec3 pos;
            sscanf(line.c_str(), "v %f %f %f", &pos.x, &pos.y, &pos.z);
            positions.push_back(pos);
        }
        else if (type.compare("vt") == 0)
        {
            vec2 tex;
            sscanf(line.c_str(), "vt %f %f", &tex.x, &tex.y);
            textureCoords.push_back(tex);
        }
        else if (type.compare("vn") == 0)
        {
            vec3 norm;
            sscanf(line.c_str(), "vn %f %f %f", &norm.x, &norm.y, &norm.z);
            normals.push_back(norm);
        }
        else if (type.compare("f ") == 0)
        {
            ivec3 f1;
            ivec3 f2;
            ivec3 f3;
            sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &f1.x, &f1.y, &f1.z, &f2.x, &f2.y, &f2.z, &f3.x, &f3.y, &f3.z);
            
            //This is required since faces in obj start from 1 and we need 0 (for arrays)
            f1 -= ivec3(1,1,1);
            f2 -= ivec3(1,1,1);
            f3 -= ivec3(1,1,1);
            
            faces.push_back(f1);
            faces.push_back(f2);
            faces.push_back(f3);
        }
    }
    
    vector<KMVertex> vertices;
    for (ivec3& face : faces)
    {
        KMVertex vertex;
        vertex.position = positions[face.x];
        vertex.texCoords = includeTexCoords? textureCoords[face.y] : vec2(0,0);
        vertex.normal = normals[face.z];
        
        vertices.push_back(vertex);
    }
    
    KMLOG("Loaded OBJ: Positions %ld, Normals %ld, Texture %ld, Faces %ld", positions.size(), normals.size(), textureCoords.size(), faces.size());
    
    return vertices;
}


void KMVertex::cuboid(float width, float height, float depth, std::vector<KMVertex>& vertices, std::vector<GLushort>& indices)
{
    const vec3 normals[6] =
    {
        {0, 0, 1},
        {0, 0, -1},
        {1, 0, 0},
        {-1, 0, 0},
        {0, 1, 0},
        {0, -1, 0},
    };
    
    //Just to be safe
    vertices.clear();
    indices.clear();
    
    //Creating a cube with side 1
    float size = 1;
    
    // Create each face in turn.
    for (int i=0 ; i < 6; i++)
    {
        vec3 normal = normals[i];
        
        // Get two vectors perpendicular to the face normal and to each other.
        vec3 side1 = vec3(normal.y, normal.z, normal.x);
        vec3 side2 = normal.Cross(side1);
        
        // Six indices (two triangles) per face.
        indices.push_back(vertices.size() + 0);
        indices.push_back(vertices.size() + 1);
        indices.push_back(vertices.size() + 2);
        
        indices.push_back(vertices.size() + 0);
        indices.push_back(vertices.size() + 2);
        indices.push_back(vertices.size() + 3);
        
        // Four vertices per face.
        vertices.push_back( {(normal - side1 - side2) * size / 2, normal} );
        vertices.push_back( {(normal - side1 + side2) * size / 2, normal} );
        vertices.push_back( {(normal + side1 + side2) * size / 2, normal} );
        vertices.push_back( {(normal + side1 - side2) * size / 2, normal} );
    }
    
    //Transforming cube into cuboid
    for(KMVertex& v : vertices)
    {
        v.position.x = v.position.x * width + width * 0.5f;
        v.position.y = v.position.y * height + height * 0.5f;
        v.position.z = v.position.z * depth - depth * 0.5f;
    }
}

void KMVertex::sphere(float radius, unsigned short verticalSegments, unsigned short horizontalSegments,
                      std::vector<KMVertex>& vertices, std::vector<GLushort>& indices)
{
    vertices.clear();
    indices.clear();
    
    
    float TwoPi = M_PI * 2.0f;
    vec3 sphereCenter = vec3(0,0,0);
    
    float dy = M_PI/(verticalSegments-1);
    float dxAngle = TwoPi/(horizontalSegments-1);
    
    float dxTex = 1.0f/(horizontalSegments-1);
    float dyTex = 1.0f/(verticalSegments-1);
    
    for (int i=0; i < verticalSegments; i++)
    {
        float y = cosf(dy * i - M_PI);
        
        for (int j = 0; j < horizontalSegments; j++)
        {
            float r = sinf(dy * i);
            float x = r * cosf(dxAngle * j);
            float z = r * cosf(dxAngle * j + M_PI_2); //this can be sinf, but then we'll go CW
            
            vec3 pos = vec3(x,y,z);
            vec3 normal = (pos - sphereCenter).Normalized();
            pos = sphereCenter + normal * radius;
            vec2 tex = vec2(dxTex * j, dyTex * i);
            
            vertices.push_back({pos, normal, tex});
        }
    }
    
    for (int i=0; i < verticalSegments -1 ; i ++)
    {
        for (int j = 0; j < horizontalSegments - 1; j++)
        {
            int bl = i * horizontalSegments + j;            //Bottom Left
            int br = i * horizontalSegments + (j + 1);      //Bottom Right
            int tl = (i + 1) * horizontalSegments + j;      //Top Left
            int tr = (i + 1) * horizontalSegments + (j + 1);//Top Right
            
            indices.push_back(bl);
            indices.push_back(br);
            indices.push_back(tl);
            
            indices.push_back(tr);
            indices.push_back(tl);
            indices.push_back(br);
        }
    }
}