//
//  Document.h
//  ObjCDep
//
//  Created by R. Tony Goold on 2014-01-28.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class DependencyGraph;

@interface DependencyDocument : NSDocument <NSBrowserDelegate>

@property (nonatomic, copy) NSString *projectPath;
@property (nonatomic, copy) NSArray *excludedNames;
@property (nonatomic, copy) NSArray *filesToAnalyze;
@property (nonatomic, readonly) DependencyGraph *dependencies;
@property (nonatomic, weak) IBOutlet NSPathControl *pathControl;
@property (nonatomic, weak) IBOutlet NSBrowser *dependencyBrowser;
@property (nonatomic, weak) IBOutlet NSTextField *currentFileName;
@property (nonatomic, weak) IBOutlet NSProgressIndicator *fileProgress;

- (IBAction)chooseFolder:(id)sender;
- (IBAction)analyzeDependencies:(id)sender;

@end
