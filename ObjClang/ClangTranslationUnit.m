//
//  ClangTranslationUnit.m
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-27.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import "ClangTranslationUnit_Internal.h"
#import "ClangCursor_Internal.h"
#import "ClangDiagnostic_Internal.h"

@interface ClangTranslationUnit ()
{
    CXTranslationUnit _unit;
}
@end

@implementation ClangTranslationUnit

- (void)dealloc
{
    if (_unit)
        clang_disposeTranslationUnit(_unit);
}

- (id)initWithIndex:(CXIndex)index
           filename:(NSString *)filename
               args:(NSArray *)args
       unsavedFiles:(NSArray *)unsavedFiles
            options:(ClangTranslationUnitOptions)options
{
    self = [super init];
    if (!self)
        return nil;

    const char *cFilename = [filename UTF8String];
    const char **cArgs = NULL;
    int numArgs = (int)[args count];
    if (numArgs > 0)
    {
        cArgs = calloc((size_t)numArgs, sizeof(char*));
        if (cArgs)
        {
            [args enumerateObjectsUsingBlock:^(NSString *arg, NSUInteger index, BOOL *stop) {
                cArgs[index] = [arg UTF8String];
            }];
        }
        else
        {
            numArgs = 0;
        }
    }
    struct CXUnsavedFile *cUnsavedFiles = NULL;
    unsigned numUnsavedFiles = (unsigned)[unsavedFiles count];
    if (numUnsavedFiles > 0)
    {
#if 0
        cUnsavedFiles = calloc((size_t)numUnsavedFiles, sizeof(struct CXUnsavedFile));
        if (cUnsavedFiles)
        {
            [unsavedFiles enumerateObjectsUsingBlock:^(NSString *unsavedFile, NSUInteger index, BOOL *stop) {
                // TODO: Define a class to encapsulate unsaved files
                cUnsavedFiles[index] = NULL;
            }];
        }
        else
        {
            numUnsavedFiles = 0;
        }
#else
        numUnsavedFiles = 0;
#endif
    }
    unsigned cOptions = 0;
    _unit = clang_parseTranslationUnit(index, cFilename, cArgs, numArgs, cUnsavedFiles, numUnsavedFiles, cOptions);
    return self;
}

- (NSArray *)diagnostics
{
    const unsigned count = clang_getNumDiagnostics(_unit);
    NSMutableArray *diagnostics = [[NSMutableArray alloc] initWithCapacity:(NSUInteger)count];
    for (unsigned i = 0; i < count; ++i)
    {
        [diagnostics addObject:[[ClangDiagnostic alloc] initWithCXDiagnostic:clang_getDiagnostic(_unit, i)]];
    }
    return diagnostics;
}

- (void)visitChildren:(ClangChildVisitResult (^)(ClangCursor *cursor, ClangCursor *parent))block
{
    if (!block)
        return;

    ClangCursor *cursor = [ClangCursor cursorWithCXCursor:clang_getTranslationUnitCursor(_unit)];
    [cursor visitChildren:block];
}

@end
