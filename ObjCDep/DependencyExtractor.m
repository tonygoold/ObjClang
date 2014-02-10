//
//  DependencyExtractor.m
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-28.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import "DependencyExtractor.h"
#import "ObjClang.h"

static inline BOOL IsClassScopeCursor(ClangCursor *cursor)
{
    return cursor.kind == ClangCursorObjCInterfaceDecl || cursor.kind == ClangCursorObjCImplementationDecl;
}

@implementation DependencyExtractor

- (id)initWithTranslationUnit:(ClangTranslationUnit *)unit
{
    self = [super init];
    if (self)
    {
        _unit = unit;
        _graph = [[DependencyGraph alloc] init];
    }
    return self;
}

- (void)extractDependencies
{
    [_unit visitChildren:^ClangChildVisitResult(ClangCursor *cursor, ClangCursor *parent) {
        if (IsClassScopeCursor(cursor) && [self shouldAddDependenciesForClassCursor:cursor])
            [self extractClassDependencies:cursor];
        return ClangChildVisitContinue;
    }];
}

- (void)extractClassDependencies:(ClangCursor *)classCursor
{
    _className = [classCursor.textContent copy];
    [classCursor visitChildren:^ClangChildVisitResult(ClangCursor *cursor, ClangCursor *parent) {
        if ([self shouldAddDependencyForCursor:cursor])
        {
            [_graph addDependencyFrom:_className to:cursor.textContent];
            return ClangChildVisitContinue;
        }
        else
        {
            return ClangChildVisitRecurse;
        }
    }];
}

- (BOOL)shouldAddDependenciesForClassCursor:(ClangCursor *)cursor
{
    // TODO: Add proper checking for classes imported from outside the project
    NSString *className = cursor.textContent;
    if ([className hasPrefix:@"NS"] || [className hasPrefix:@"UI"])
        return NO;
    return YES;
}

- (BOOL)shouldAddDependencyForCursor:(ClangCursor *)cursor
{
    if (cursor.kind == ClangCursorObjCClassRef)
    {
        NSString *refName = cursor.textContent;
        return ![refName hasPrefix:@"NS"] && ![refName isEqualToString:_className];
    }
    else
    {
        return NO;
    }
}

@end
