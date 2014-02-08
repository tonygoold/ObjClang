//
//  DependencyExtractor.h
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-28.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DependencyGraph.h"

@class ClangTranslationUnit;

@interface DependencyExtractor : NSObject
{
    ClangTranslationUnit *_unit;
    NSString *_className;
}
@property (nonatomic, strong) DependencyGraph *graph;

- (id)initWithTranslationUnit:(ClangTranslationUnit *)unit;

- (void)extractDependencies;

@end
