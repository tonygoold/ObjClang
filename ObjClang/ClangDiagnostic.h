//
//  ClangDiagnostic.h
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-28.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ClangLocation;

@interface ClangDiagnostic : NSObject

@property (nonatomic, readonly) ClangLocation *location;
@property (nonatomic, readonly) NSString *textContent;

@end
