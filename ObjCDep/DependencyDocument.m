//
//  Document.m
//  ObjCDep
//
//  Created by R. Tony Goold on 2014-01-28.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import "DependencyDocument.h"
#import "DependencyExtractor.h"
#import "DependencyGraph.h"
#import "DependencyItem.h"
#import "ObjClang.h"

@implementation DependencyDocument

- (id)init
{
    self = [super init];
    if (self)
    {
        _projectPath = @"";
        _excludedNames = @[];
        _dependencies = [[DependencyGraph alloc] init];
    }
    return self;
}

- (NSString *)windowNibName
{
    // Override returning the nib file name of the document
    // If you need to use a subclass of NSWindowController or if your document supports multiple NSWindowControllers, you should remove this method and override -makeWindowControllers instead.
    return @"DependencyDocument";
}

- (void)windowControllerDidLoadNib:(NSWindowController *)aController
{
    [super windowControllerDidLoadNib:aController];
    // Add any code here that needs to be executed once the windowController has loaded the document's window.
}

+ (BOOL)autosavesInPlace
{
    return YES;
}

- (NSData *)dataOfType:(NSString *)typeName error:(NSError **)outError
{
    NSDictionary *dict = @{ @"projectPath": self.projectPath, @"excludedNames": self.excludedNames };
    return [NSJSONSerialization dataWithJSONObject:dict options:NSJSONWritingPrettyPrinted error:outError];
}

- (BOOL)readFromData:(NSData *)data ofType:(NSString *)typeName error:(NSError **)outError
{
    NSDictionary *dict = [NSJSONSerialization JSONObjectWithData:data options:0 error:outError];
    if (!dict)
        return NO;
    if (![dict isKindOfClass:[NSDictionary class]])
    {
        if (outError)
            *outError = [NSError errorWithDomain:@"ObjCDepDomain" code:1 userInfo:nil];
        return NO;
    }
    NSString *path = dict[@"projectPath"];
    if ([path isKindOfClass:[NSString class]])
        self.projectPath = path;
    NSArray *names = dict[@"excludedNames"];
    if ([names isKindOfClass:[NSArray class]])
    {
        BOOL allStrings = YES;
        for (id value in names)
        {
            if (![value isKindOfClass:[NSString class]])
            {
                allStrings = NO;
                break;
            }
        }
        if (allStrings)
            self.excludedNames = names;
    }
    // Insert code here to read your document from the given data of the specified type. If outError != NULL, ensure that you create and set an appropriate error when returning NO.
    // You can also choose to override -readFromFileWrapper:ofType:error: or -readFromURL:ofType:error: instead.
    // If you override either of these, you should also override -isEntireFileLoaded to return NO if the contents are lazily loaded.
    if (self.projectPath)
    {
        self.pathControl.URL = [NSURL fileURLWithPath:self.projectPath];
    }
    return YES;
}

- (IBAction)chooseFolder:(id)sender
{
    NSOpenPanel *panel = [NSOpenPanel openPanel];
    panel.canChooseFiles = YES;
    panel.canChooseDirectories = YES;
    panel.allowsMultipleSelection = YES;
    panel.title = @"Select File/Folder";
    [panel beginWithCompletionHandler:^(NSInteger result) {
        if (result == NSFileHandlingPanelOKButton)
        {
            [self processURLs:panel.URLs];
            [self analyzeDependencies:sender];
        }
    }];
}

- (BOOL)hasSourceFileSuffix:(NSString *)filename
{
    NSArray *suffixes = @[ @".m", @".mm", @".c", @".cpp", @".cxx", @".cc", @".C" ];
    for (NSString *suffix in suffixes)
    {
        if ([filename hasSuffix:suffix])
            return YES;
    }
    return NO;
}

- (void)addFilesFromDirectory:(NSString *)path toFiles:(NSMutableArray *)files
{
    NSFileManager *fmgr = [NSFileManager defaultManager];
    BOOL isDirectory;
    for (NSString *file in [fmgr enumeratorAtPath:path])
    {
        NSString *filepath = [path stringByAppendingPathComponent:file];
        if ([fmgr fileExistsAtPath:filepath isDirectory:&isDirectory])
        {
            if (!isDirectory && [self hasSourceFileSuffix:file])
                [files addObject:filepath];
        }
    }
}

- (void)processURLs:(NSArray *)urls
{
    NSMutableArray *filesToAnalyze = [[NSMutableArray alloc] init];
    NSFileManager *fmgr = [NSFileManager defaultManager];
    [urls enumerateObjectsUsingBlock:^(NSURL *url, NSUInteger idx, BOOL *stop) {
        NSString *path = [url path];
        BOOL isDirectory;
        if (![fmgr fileExistsAtPath:path isDirectory:&isDirectory])
        {
            NSLog(@"FAIL: Got a file path that doesn't even exist: %@", path);
            return;
        }
        if (isDirectory)
        {
            [self addFilesFromDirectory:path toFiles:filesToAnalyze];
        }
        else if ([self hasSourceFileSuffix:[path lastPathComponent]])
        {
            [filesToAnalyze addObject:path];
        }
    }];
    self.filesToAnalyze = filesToAnalyze;
}

- (IBAction)analyzeDependencies:(id)sender
{
    [_dependencies removeAllDependencies];
    [self.dependencyBrowser reloadColumn:0];
    if ([self.filesToAnalyze count] == 0)
        return;

    NSMutableSet *directorySet = [[NSMutableSet alloc] init];
    [self.filesToAnalyze enumerateObjectsUsingBlock:^(NSString *path, NSUInteger idx, BOOL *stop) {
        [directorySet addObject:[path stringByDeletingLastPathComponent]];
    }];
    NSMutableArray *args = [[NSMutableArray alloc] initWithCapacity:[directorySet count]];
    [directorySet enumerateObjectsUsingBlock:^(NSString *dir, BOOL *stop) {
        [args addObject:[NSString stringWithFormat:@"-I\"%@\"", dir]];
    }];
    self.fileProgress.maxValue = (double) [self.filesToAnalyze count];
    self.fileProgress.doubleValue = 0.0;
    [self.fileProgress setHidden:NO];
    [self.currentFileName setHidden:NO];
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        ClangIndex *index = [ClangIndex indexWithOptions:ClangIndexOptionsDisplayDiagnostics];
        [self.filesToAnalyze enumerateObjectsUsingBlock:^(NSString *file, NSUInteger idx, BOOL *stop) {
            dispatch_sync(dispatch_get_main_queue(), ^{
                self.currentFileName.stringValue = [file lastPathComponent];
            });
            ClangTranslationUnit *unit = [index parseTranslationUnit:file args:args unsavedFiles:@[] options:0];
            if (!unit)
            {
                NSLog(@"Failed to parse file: %@", file);
                return;
            }
            NSArray *diagnostics = unit.diagnostics;
            for (ClangDiagnostic *diagnostic in diagnostics)
            {
                NSLog(@"Diagnostic: %@", diagnostic.textContent);
            }
            DependencyExtractor *extractor = [[DependencyExtractor alloc] initWithTranslationUnit:unit];
            extractor.graph = _dependencies;
            [extractor extractDependencies];
            dispatch_sync(dispatch_get_main_queue(), ^{
                [self.fileProgress incrementBy:1.0];
            });
        }];
        double delayInSeconds = 1.0;
        dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
        dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
            [self.fileProgress setHidden:YES];
            [self.currentFileName setHidden:YES];
            self.fileProgress.doubleValue = 0.0;
            [self.dependencyBrowser reloadColumn:0];
        });
    });
}

#pragma mark - NSBrowserDelegate methods

static DependencyItem *s_rootItem;

- (id)rootItemForBrowser:(NSBrowser *)browser
{
    if (!s_rootItem)
        s_rootItem = [[DependencyItem alloc] initWithName:@"_root" parent:nil];
    return s_rootItem;
}

- (NSInteger)browser:(NSBrowser *)browser numberOfChildrenOfItem:(id)item
{
    if (item == s_rootItem)
        return [_dependencies.knownClasses count];
    else
        return [[_dependencies dependenciesForClass:[item name]] count];
}

- (id)browser:(NSBrowser *)browser child:(NSInteger)index ofItem:(id)item
{
    NSString *value;
    if (item == s_rootItem)
        value = _dependencies.knownClasses[index];
    else
        value = [_dependencies dependenciesForClass:[item name]][index];
    return [[DependencyItem alloc] initWithName:value parent:[item name]];
}

- (BOOL)browser:(NSBrowser *)browser isLeafItem:(id)item
{
    return ![[item parent] isEqual:@"_root"];
}

- (id)browser:(NSBrowser *)browser objectValueForItem:(id)item
{
    return [item name];
}

@end
