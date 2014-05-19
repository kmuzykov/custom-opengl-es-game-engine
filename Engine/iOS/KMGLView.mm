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
        //Retina support
        self.contentScaleFactor = [[UIScreen mainScreen] scale];
        
        //Creating OpenGL ES 2.0 context
        _glContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        if (!_glContext || ![EAGLContext setCurrentContext:_glContext])
        {
            NSLog(@"Error initializing _glContext");
            return nil;
        }
        
        //Setting up director using fullscreen.
        KMDirector& director = KMDirector::getSharedDirector();
        director.initialize(self.frame.size.width, self.frame.size.height, self.contentScaleFactor);
        
        //Setting up underlying CoreAnimation layer.
        CAEAGLLayer* eaglLayer = (CAEAGLLayer*)super.layer;
        eaglLayer.opaque = YES;

        //eaglLayer.drawableProperties = @{kEAGLDrawablePropertyColorFormat: kEAGLColorFormatRGBA8,
        //                                 kEAGLDrawablePropertyRetainedBacking : @NO};
        
        //Allocating space for RENDERBUFFER
        [_glContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];
        
        //Checking glCheckFramebufferStatus
        director.validateInit();
        
        //Setting up update: function
        _displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update:)];
        [_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    }
    return self;
}

- (void)update: (CADisplayLink*) dl
{
    //Calculating delta from last update
    float elapsed = 0.00001f;
    if (_timestamp > 0)
    {
        elapsed = dl.timestamp - _timestamp;
    }
    _timestamp = dl.timestamp;
    
    //Calling director update: which will update: and render: all contents.
    KMDirector::getSharedDirector().update(elapsed);
    
    //Presenting renderbuffer on screen.
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
