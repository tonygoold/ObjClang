//
//  DependencyGraph.h
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-28.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DependencyGraph : NSObject
{
    NSMutableDictionary *_map;
    NSMutableArray *_sortedClasses;
}

- (void)addDependencyFrom:(NSString *)from to:(NSString *)to;
- (void)removeDependencyFrom:(NSString *)from to:(NSString *)to;
- (void)removeAllDependencies;

- (NSArray *)dependenciesForClass:(NSString *)name;
- (NSArray *)knownClasses;

@end
