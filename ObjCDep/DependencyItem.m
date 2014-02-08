//
//  DependencyItem.m
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-28.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import "DependencyItem.h"

@implementation DependencyItem

- (id)initWithName:(NSString *)name parent:(NSString *)parent
{
    self = [super init];
    if (self)
    {
        _name = [name copy];
        _parent = [parent copy];
    }
    return self;
}

@end
