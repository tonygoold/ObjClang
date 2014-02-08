//
//  ClangTranslationUnit.h
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-27.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ClangTypes.h"

typedef enum
{
    ClangTranslationUnitOptionsFoo
} ClangTranslationUnitOptions;

@class ClangCursor;
@class ClangIndex;

@interface ClangTranslationUnit : NSObject

@property (nonatomic, readonly) NSArray *diagnostics;

- (void)visitChildren:(ClangChildVisitResult (^)(ClangCursor *cursor, ClangCursor *parent))block;

@end
