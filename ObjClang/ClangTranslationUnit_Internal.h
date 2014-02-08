//
//  ClangTranslationUnit_Internal.h
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-27.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import "ClangTranslationUnit.h"

#include <clang-c/Index.h>

@interface ClangTranslationUnit ()

- (id)initWithIndex:(CXIndex)index
           filename:(NSString *)filename
               args:(NSArray *)args
       unsavedFiles:(NSArray *)unsavedFiles
            options:(ClangTranslationUnitOptions)options;

@end
