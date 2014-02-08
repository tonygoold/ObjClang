//
//  ClangIndex.h
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-27.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "ClangTranslationUnit.h"

typedef enum
{
    ClangIndexOptionsExcludePCH         = 1 << 0,
    ClangIndexOptionsDisplayDiagnostics = 1 << 1
} ClangIndexOptions;

@interface ClangIndex : NSObject

+ (instancetype)index;
+ (instancetype)indexWithOptions:(ClangIndexOptions)options;

- (id)init;
- (id)initWithOptions:(ClangIndexOptions)options;

- (ClangTranslationUnit *)parseTranslationUnit:(NSString *)filename
                                          args:(NSArray *)args
                                  unsavedFiles:(NSArray *)unsavedFiles
                                       options:(ClangTranslationUnitOptions)options;

@end
