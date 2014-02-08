//
//  DependencyExtractor.m
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-28.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import "DependencyExtractor.h"
#import "ObjClang.h"

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

- (void)extractClassDependencies:(ClangCursor *)classCursor
{
    _className = [classCursor.textContent copy];
    if ([_className hasPrefix:@"NS"])
        return;
    [classCursor visitChildren:^ClangChildVisitResult(ClangCursor *cursor, ClangCursor *parent) {
        if (cursor.kind == ClangCursorObjCClassRef)
        {
            NSString *refName = cursor.textContent;
            if (![refName hasPrefix:@"NS"] && ![refName isEqualToString:_className])
            {
                [_graph addDependencyFrom:_className to:refName];
            }
        }
        return ClangChildVisitRecurse;
    }];
}

- (void)extractDependencies
{
    [_unit visitChildren:^ClangChildVisitResult(ClangCursor *cursor, ClangCursor *parent) {
        if (cursor.kind == ClangCursorObjCInterfaceDecl || cursor.kind == ClangCursorObjCImplementationDecl)
            [self extractClassDependencies:cursor];
        return ClangChildVisitContinue;
    }];
}

@end
