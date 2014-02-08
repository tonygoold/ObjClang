//
//  ClangDiagnostic_Internal.h
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-28.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import "ClangDiagnostic.h"

#include <clang-c/Index.h>

@interface ClangDiagnostic ()
{
    CXDiagnostic _diagnostic;
}

- (id)initWithCXDiagnostic:(CXDiagnostic)diagnostic;

@end
