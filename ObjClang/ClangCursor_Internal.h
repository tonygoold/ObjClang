//
//  ClangCursor_Internal.h
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-28.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import "ClangCursor.h"

#include <clang-c/Index.h>

@interface ClangCursor ()
{
    CXCursor _cursor;
}

+ (instancetype)cursorWithCXCursor:(CXCursor)cursor;

- (id)initWithCXCursor:(CXCursor)cursor;

@end
