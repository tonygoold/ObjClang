//
//  DependencyItem.h
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-28.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DependencyItem : NSObject

@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSString *parent;

- (id)initWithName:(NSString *)name parent:(NSString *)parent;

@end
