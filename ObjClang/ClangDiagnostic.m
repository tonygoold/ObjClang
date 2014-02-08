//
//  ClangDiagnostic.m
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-28.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import "ClangDiagnostic_Internal.h"

@implementation ClangDiagnostic

- (id)initWithCXDiagnostic:(CXDiagnostic)diagnostic
{
    self = [super init];
    if (self)
    {
        _diagnostic = diagnostic;
    }
    return self;
}

- (void)dealloc
{
    if (_diagnostic)
        clang_disposeDiagnostic(_diagnostic);
}

- (ClangLocation *)location
{
    return nil;
}

- (NSString *)textContent
{
    CXString text = clang_getDiagnosticSpelling(_diagnostic);
    NSString *result = [NSString stringWithUTF8String:clang_getCString(text)];
    clang_disposeString(text);
    return result;
}

@end
