//
//  ClangCursor.m
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-27.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import "ClangCursor_Internal.h"

@implementation ClangCursor

+ (instancetype)cursorWithCXCursor:(CXCursor)cursor
{
    return [[ClangCursor alloc] initWithCXCursor:cursor];
}

- (id)initWithCXCursor:(CXCursor)cursor
{
    self = [super init];
    if (self)
    {
        _cursor = cursor;
    }
    return self;
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"%@ (%@)", [self kindName], [self textContent]];
}

- (ClangCursorKind)kind
{
    return (ClangCursorKind) clang_getCursorKind(_cursor);
}

- (ClangCursorTypeKind)typeKind
{
    return (ClangCursorTypeKind) clang_getCursorType(_cursor).kind;
}

- (NSString *)textContent
{
    CXString content = clang_getCursorSpelling(_cursor);
    NSString *result = [NSString stringWithUTF8String:clang_getCString(content)];
    clang_disposeString(content);
    return result;
}

- (NSString *)kindName
{
    CXString name = clang_getCursorKindSpelling(clang_getCursorKind(_cursor));
    NSString *result = [NSString stringWithUTF8String:clang_getCString(name)];
    clang_disposeString(name);
    return result;
}

- (NSString *)typeKindName
{
    CXString name = clang_getTypeKindSpelling(clang_getCursorType(_cursor).kind);
    NSString *result = [NSString stringWithUTF8String:clang_getCString((name))];
    clang_disposeString(name);
    return result;
}

- (ClangCursor *)semanticParent
{
    return [ClangCursor cursorWithCXCursor:clang_getCursorSemanticParent(_cursor)];
}

- (ClangCursor *)lexicalParent
{
    return [ClangCursor cursorWithCXCursor:clang_getCursorLexicalParent(_cursor)];
}

- (void)visitChildren:(ClangChildVisitResult (^)(ClangCursor *cursor, ClangCursor *parent))block
{
    if (!block)
        return;

    clang_visitChildrenWithBlock(_cursor, ^enum CXChildVisitResult(CXCursor cursor, CXCursor parent) {
        return (enum CXChildVisitResult) block([ClangCursor cursorWithCXCursor:cursor], [ClangCursor cursorWithCXCursor:parent]);
    });
}

@end
