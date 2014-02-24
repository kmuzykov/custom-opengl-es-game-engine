//
//  P3DFileUtils.m
//  Bowling
//
//  Created by Kirill Muzykov on 16/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#import "KMFileUtilsIOS.h"
#import "KMMacros.h"
#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>

const char* KMFileUtilsIOS::loadFile(const char* fileName)
{
    NSString* fileNameIOS = [NSString stringWithUTF8String:fileName];
    NSString* fullPathIOS = [[NSBundle mainBundle] pathForResource:fileNameIOS ofType:nil];
    
    NSError* error = nil;
    NSString* fileContents = [NSString stringWithContentsOfFile:fullPathIOS encoding:NSUTF8StringEncoding error:&error];
    
    if (error != nil)
    {
        KMLOG("Error loading file contents: %s with error %s", fileName, [error.description cStringUsingEncoding:NSUTF8StringEncoding]);
        exit(1);
    }
    
    return [fileContents UTF8String];
};

const char* KMFileUtilsIOS::getFilePath(const char* fileName)
{
    return [[[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:fileName] ofType:nil] UTF8String];
}

GLuint KMFileUtilsIOS::loadTexture(const char* imgName)
{
    NSString* imageFilePath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:imgName] ofType:nil];
    NSError* theError;
    NSDictionary* options = @{GLKTextureLoaderGenerateMipmaps: @YES};
    
    GLKTextureInfo *spriteTexture = [GLKTextureLoader textureWithContentsOfFile:imageFilePath options:options error:&theError];
    if (theError)
    {
        KMLOG("Error loading image %s ERROR: %s", imgName, [[theError description] UTF8String]);
        return 0;
    }
    
    return spriteTexture.name;
}