//
//  P3DGLView.m
//  Pixel3D
//
//  Created by Kirill Muzykov on 16/01/14.
//  Copyright (c) 2014 PixelOxygen. All rights reserved.
//

#import "KMGLView.h"
#include "KMDirector.h"

@implementation KMGLView
{
    EAGLContext*    _glContext;
    CADisplayLink*  _displayLink;
    CFTimeInterval  _timestamp;
}

- (id)initWithFrame:(CGRect)frame
{
    if (self = [super initWithFrame:frame])
    {
        self.contentScaleFactor = [[UIScreen mainScreen] scale];
        
        _glContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        if (!_glContext || ![EAGLContext setCurrentContext:_glContext])
        {
            NSLog(@"Error initializing _glContext");
            return nil;
        }
        
        KMDirector& director = KMDirector::getSharedDirector();
        director.initialize(self.frame.size.width, self.frame.size.height, self.contentScaleFactor);
        
        CAEAGLLayer* eaglLayer = (CAEAGLLayer*)super.layer;
        eaglLayer.opaque = YES;
        //eaglLayer.contentsScale = self.contentScaleFactor;
//        eaglLayer.drawableProperties = @{kEAGLDrawablePropertyColorFormat: kEAGLColorFormatRGBA8,
//                                         kEAGLDrawablePropertyRetainedBacking : @NO};
        //eaglLayer.contentsScale = self.contentScaleFactor;
        
        [_glContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];
        
        director.validateInit();
        
        _displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update:)];
        [_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    }
    return self;
}

- (void)update: (CADisplayLink*) dl
{
    float elapsed = 0.00001f;
    if (_timestamp > 0)
    {
        elapsed = dl.timestamp - _timestamp;
    }
    
    _timestamp = dl.timestamp;
    
    KMDirector::getSharedDirector().update(elapsed);
    
    [_glContext presentRenderbuffer:GL_RENDERBUFFER];
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch* touch = [touches anyObject];
    CGPoint location = [touch locationInView: self];
}

- (void) touchesEnded: (NSSet*) touches withEvent: (UIEvent*) event
{
    UITouch* touch = [touches anyObject];
    CGPoint location = [touch locationInView: self];
}

- (void) touchesMoved: (NSSet*) touches withEvent: (UIEvent*) event
{
    UITouch* touch = [touches anyObject];
    CGPoint location = [touch locationInView: self];
}

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

@end
