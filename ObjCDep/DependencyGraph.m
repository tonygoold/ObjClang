//
//  DependencyGraph.m
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-28.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import "DependencyGraph.h"

static void SortedArrayInsert (NSMutableArray *array, id value, NSComparator comparator)
{
    if ([array containsObject:value])
        return;

    __block NSUInteger index = NSNotFound;
    [array enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        if (comparator(obj, value) == NSOrderedDescending)
        {
            index = idx;
            *stop = YES;
        }
    }];
    if (index == NSNotFound)
        [array addObject:value];
    else
        [array insertObject:value atIndex:index];
}

@implementation DependencyGraph

- (id)init
{
    self = [super init];
    if (self)
    {
        _map = [[NSMutableDictionary alloc] init];
        _sortedClasses = [[NSMutableArray alloc] init];
    }
    return self;
}

- (void)addDependencyFrom:(NSString *)from to:(NSString *)to
{
    NSComparator stringComparator = ^NSComparisonResult(NSString *str1, NSString *str2) {
        return [str1 localizedCompare:str2];
    };
    NSMutableArray *values = _map[from];
    if (values)
    {
        SortedArrayInsert(values, to, stringComparator);
    }
    else
    {
        values = [[NSMutableArray alloc] initWithObjects:to, nil];
        _map[from] = values;
    }
    if (![_sortedClasses containsObject:from])
        SortedArrayInsert(_sortedClasses, from, stringComparator);
    if (![_sortedClasses containsObject:to])
        SortedArrayInsert(_sortedClasses, to, stringComparator);
}

- (void)removeDependencyFrom:(NSString *)from to:(NSString *)to
{
    [_map[from] removeObject:to];
}

- (void)removeAllDependencies
{
    [_map removeAllObjects];
    [_sortedClasses removeAllObjects];
}

- (NSArray *)dependenciesForClass:(NSString *)name
{
    NSMutableArray *values = _map[name];
    return values ? [values copy] : @[];
}

- (NSArray *)knownClasses
{
    return [_sortedClasses copy];
}

@end
