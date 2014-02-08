//
//  ClangIndex.m
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-27.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import "ClangIndex.h"
#import "ClangTranslationUnit_Internal.h"
#include <clang-c/Index.h>

@interface ClangIndex ()
{
    CXIndex _index;
}
@end

@implementation ClangIndex

+ (instancetype)index
{
    return [[ClangIndex alloc] initWithOptions:0];
}

+ (instancetype)indexWithOptions:(ClangIndexOptions)options
{
    return [[ClangIndex alloc] initWithOptions:options];
}

- (id)init
{
    return [self initWithOptions:0];
}

- (id)initWithOptions:(ClangIndexOptions)options
{
    self = [super init];
    if (self)
    {
        _index = clang_createIndex(options & ClangIndexOptionsExcludePCH, options & ClangIndexOptionsDisplayDiagnostics);
        if (!_index)
            return nil;
    }
    return self;
}

- (void)dealloc
{
    if (_index)
        clang_disposeIndex(_index);
}

- (ClangTranslationUnit *)parseTranslationUnit:(NSString *)filename
                                          args:(NSArray *)args
                                  unsavedFiles:(NSArray *)unsavedFiles
                                       options:(ClangTranslationUnitOptions)options
{
    return [[ClangTranslationUnit alloc] initWithIndex:_index
                                              filename:filename
                                                  args:args
                                          unsavedFiles:unsavedFiles
                                               options:options];
}

@end
