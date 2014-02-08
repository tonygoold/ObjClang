//
//  ClangTypes.h
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-28.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum
{
    /**
     * \brief Terminates the cursor traversal.
     */
    ClangChildVisitBreak,
    /**
     * \brief Continues the cursor traversal with the next sibling of
     * the cursor just visited, without visiting its children.
     */
    ClangChildVisitContinue,
    /**
     * \brief Recursively traverse the children of this cursor, using
     * the same visitor and client data.
     */
    ClangChildVisitRecurse
} ClangChildVisitResult;
