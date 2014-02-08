//
//  ClangCursor.h
//  ObjClang
//
//  Created by R. Tony Goold on 2014-01-27.
//  Copyright (c) 2014 R. Tony Goold. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ClangTypes.h"

// This enumeration is copied straight from the Clang C API's Index.h file.
// The only difference is that the "ClangCursor" prefix has been changed to
// "ClangCursor".
typedef enum
{
    /* Declarations */
    /**
     * \brief A declaration whose specific kind is not exposed via this
     * interface.
     *
     * Unexposed declarations have the same operations as any other kind
     * of declaration; one can extract their location information,
     * spelling, find their definitions, etc. However, the specific kind
     * of the declaration is not reported.
     */
    ClangCursorUnexposedDecl                 = 1,
    /** \brief A C or C++ struct. */
    ClangCursorStructDecl                    = 2,
    /** \brief A C or C++ union. */
    ClangCursorUnionDecl                     = 3,
    /** \brief A C++ class. */
    ClangCursorClassDecl                     = 4,
    /** \brief An enumeration. */
    ClangCursorEnumDecl                      = 5,
    /**
     * \brief A field (in C) or non-static data member (in C++) in a
     * struct, union, or C++ class.
     */
    ClangCursorFieldDecl                     = 6,
    /** \brief An enumerator constant. */
    ClangCursorEnumConstantDecl              = 7,
    /** \brief A function. */
    ClangCursorFunctionDecl                  = 8,
    /** \brief A variable. */
    ClangCursorVarDecl                       = 9,
    /** \brief A function or method parameter. */
    ClangCursorParmDecl                      = 10,
    /** \brief An Objective-C \@interface. */
    ClangCursorObjCInterfaceDecl             = 11,
    /** \brief An Objective-C \@interface for a category. */
    ClangCursorObjCCategoryDecl              = 12,
    /** \brief An Objective-C \@protocol declaration. */
    ClangCursorObjCProtocolDecl              = 13,
    /** \brief An Objective-C \@property declaration. */
    ClangCursorObjCPropertyDecl              = 14,
    /** \brief An Objective-C instance variable. */
    ClangCursorObjCIvarDecl                  = 15,
    /** \brief An Objective-C instance method. */
    ClangCursorObjCInstanceMethodDecl        = 16,
    /** \brief An Objective-C class method. */
    ClangCursorObjCClassMethodDecl           = 17,
    /** \brief An Objective-C \@implementation. */
    ClangCursorObjCImplementationDecl        = 18,
    /** \brief An Objective-C \@implementation for a category. */
    ClangCursorObjCCategoryImplDecl          = 19,
    /** \brief A typedef */
    ClangCursorTypedefDecl                   = 20,
    /** \brief A C++ class method. */
    ClangCursorCXXMethod                     = 21,
    /** \brief A C++ namespace. */
    ClangCursorNamespace                     = 22,
    /** \brief A linkage specification, e.g. 'extern "C"'. */
    ClangCursorLinkageSpec                   = 23,
    /** \brief A C++ constructor. */
    ClangCursorConstructor                   = 24,
    /** \brief A C++ destructor. */
    ClangCursorDestructor                    = 25,
    /** \brief A C++ conversion function. */
    ClangCursorConversionFunction            = 26,
    /** \brief A C++ template type parameter. */
    ClangCursorTemplateTypeParameter         = 27,
    /** \brief A C++ non-type template parameter. */
    ClangCursorNonTypeTemplateParameter      = 28,
    /** \brief A C++ template template parameter. */
    ClangCursorTemplateTemplateParameter     = 29,
    /** \brief A C++ function template. */
    ClangCursorFunctionTemplate              = 30,
    /** \brief A C++ class template. */
    ClangCursorClassTemplate                 = 31,
    /** \brief A C++ class template partial specialization. */
    ClangCursorClassTemplatePartialSpecialization = 32,
    /** \brief A C++ namespace alias declaration. */
    ClangCursorNamespaceAlias                = 33,
    /** \brief A C++ using directive. */
    ClangCursorUsingDirective                = 34,
    /** \brief A C++ using declaration. */
    ClangCursorUsingDeclaration              = 35,
    /** \brief A C++ alias declaration */
    ClangCursorTypeAliasDecl                 = 36,
    /** \brief An Objective-C \@synthesize definition. */
    ClangCursorObjCSynthesizeDecl            = 37,
    /** \brief An Objective-C \@dynamic definition. */
    ClangCursorObjCDynamicDecl               = 38,
    /** \brief An access specifier. */
    ClangCursorCXXAccessSpecifier            = 39,
    
    ClangCursorFirstDecl                     = ClangCursorUnexposedDecl,
    ClangCursorLastDecl                      = ClangCursorCXXAccessSpecifier,
    
    /* References */
    ClangCursorFirstRef                      = 40, /* Decl references */
    ClangCursorObjCSuperClassRef             = 40,
    ClangCursorObjCProtocolRef               = 41,
    ClangCursorObjCClassRef                  = 42,
    /**
     * \brief A reference to a type declaration.
     *
     * A type reference occurs anywhere where a type is named but not
     * declared. For example, given:
     *
     * \code
     * typedef unsigned size_type;
     * size_type size;
     * \endcode
     *
     * The typedef is a declaration of size_type (ClangCursorTypedefDecl),
     * while the type of the variable "size" is referenced. The cursor
     * referenced by the type of size is the typedef for size_type.
     */
    ClangCursorTypeRef                       = 43,
    ClangCursorCXXBaseSpecifier              = 44,
    /**
     * \brief A reference to a class template, function template, template
     * template parameter, or class template partial specialization.
     */
    ClangCursorTemplateRef                   = 45,
    /**
     * \brief A reference to a namespace or namespace alias.
     */
    ClangCursorNamespaceRef                  = 46,
    /**
     * \brief A reference to a member of a struct, union, or class that occurs in
     * some non-expression context, e.g., a designated initializer.
     */
    ClangCursorMemberRef                     = 47,
    /**
     * \brief A reference to a labeled statement.
     *
     * This cursor kind is used to describe the jump to "start_over" in the
     * goto statement in the following example:
     *
     * \code
     *   start_over:
     *     ++counter;
     *
     *     goto start_over;
     * \endcode
     *
     * A label reference cursor refers to a label statement.
     */
    ClangCursorLabelRef                      = 48,
    
    /**
     * \brief A reference to a set of overloaded functions or function templates
     * that has not yet been resolved to a specific function or function template.
     *
     * An overloaded declaration reference cursor occurs in C++ templates where
     * a dependent name refers to a function. For example:
     *
     * \code
     * template<typename T> void swap(T&, T&);
     *
     * struct X { ... };
     * void swap(X&, X&);
     *
     * template<typename T>
     * void reverse(T* first, T* last) {
     *   while (first < last - 1) {
     *     swap(*first, *--last);
     *     ++first;
     *   }
     * }
     *
     * struct Y { };
     * void swap(Y&, Y&);
     * \endcode
     *
     * Here, the identifier "swap" is associated with an overloaded declaration
     * reference. In the template definition, "swap" refers to either of the two
     * "swap" functions declared above, so both results will be available. At
     * instantiation time, "swap" may also refer to other functions found via
     * argument-dependent lookup (e.g., the "swap" function at the end of the
     * example).
     *
     * The functions \c clang_getNumOverloadedDecls() and
     * \c clang_getOverloadedDecl() can be used to retrieve the definitions
     * referenced by this cursor.
     */
    ClangCursorOverloadedDeclRef             = 49,
    
    /**
     * \brief A reference to a variable that occurs in some non-expression
     * context, e.g., a C++ lambda capture list.
     */
    ClangCursorVariableRef                   = 50,
    
    ClangCursorLastRef                       = ClangCursorVariableRef,
    
    /* Error conditions */
    ClangCursorFirstInvalid                  = 70,
    ClangCursorInvalidFile                   = 70,
    ClangCursorNoDeclFound                   = 71,
    ClangCursorNotImplemented                = 72,
    ClangCursorInvalidCode                   = 73,
    ClangCursorLastInvalid                   = ClangCursorInvalidCode,
    
    /* Expressions */
    ClangCursorFirstExpr                     = 100,
    
    /**
     * \brief An expression whose specific kind is not exposed via this
     * interface.
     *
     * Unexposed expressions have the same operations as any other kind
     * of expression; one can extract their location information,
     * spelling, children, etc. However, the specific kind of the
     * expression is not reported.
     */
    ClangCursorUnexposedExpr                 = 100,
    
    /**
     * \brief An expression that refers to some value declaration, such
     * as a function, varible, or enumerator.
     */
    ClangCursorDeclRefExpr                   = 101,
    
    /**
     * \brief An expression that refers to a member of a struct, union,
     * class, Objective-C class, etc.
     */
    ClangCursorMemberRefExpr                 = 102,
    
    /** \brief An expression that calls a function. */
    ClangCursorCallExpr                      = 103,
    
    /** \brief An expression that sends a message to an Objective-C
     object or class. */
    ClangCursorObjCMessageExpr               = 104,
    
    /** \brief An expression that represents a block literal. */
    ClangCursorBlockExpr                     = 105,
    
    /** \brief An integer literal.
     */
    ClangCursorIntegerLiteral                = 106,
    
    /** \brief A floating point number literal.
     */
    ClangCursorFloatingLiteral               = 107,
    
    /** \brief An imaginary number literal.
     */
    ClangCursorImaginaryLiteral              = 108,
    
    /** \brief A string literal.
     */
    ClangCursorStringLiteral                 = 109,
    
    /** \brief A character literal.
     */
    ClangCursorCharacterLiteral              = 110,
    
    /** \brief A parenthesized expression, e.g. "(1)".
     *
     * This AST node is only formed if full location information is requested.
     */
    ClangCursorParenExpr                     = 111,
    
    /** \brief This represents the unary-expression's (except sizeof and
     * alignof).
     */
    ClangCursorUnaryOperator                 = 112,
    
    /** \brief [C99 6.5.2.1] Array Subscripting.
     */
    ClangCursorArraySubscriptExpr            = 113,
    
    /** \brief A builtin binary operation expression such as "x + y" or
     * "x <= y".
     */
    ClangCursorBinaryOperator                = 114,
    
    /** \brief Compound assignment such as "+=".
     */
    ClangCursorCompoundAssignOperator        = 115,
    
    /** \brief The ?: ternary operator.
     */
    ClangCursorConditionalOperator           = 116,
    
    /** \brief An explicit cast in C (C99 6.5.4) or a C-style cast in C++
     * (C++ [expr.cast]), which uses the syntax (Type)expr.
     *
     * For example: (int)f.
     */
    ClangCursorCStyleCastExpr                = 117,
    
    /** \brief [C99 6.5.2.5]
     */
    ClangCursorCompoundLiteralExpr           = 118,
    
    /** \brief Describes an C or C++ initializer list.
     */
    ClangCursorInitListExpr                  = 119,
    
    /** \brief The GNU address of label extension, representing &&label.
     */
    ClangCursorAddrLabelExpr                 = 120,
    
    /** \brief This is the GNU Statement Expression extension: ({int X=4; X;})
     */
    ClangCursorStmtExpr                      = 121,
    
    /** \brief Represents a C11 generic selection.
     */
    ClangCursorGenericSelectionExpr          = 122,
    
    /** \brief Implements the GNU __null extension, which is a name for a null
     * pointer constant that has integral type (e.g., int or long) and is the same
     * size and alignment as a pointer.
     *
     * The __null extension is typically only used by system headers, which define
     * NULL as __null in C++ rather than using 0 (which is an integer that may not
     * match the size of a pointer).
     */
    ClangCursorGNUNullExpr                   = 123,
    
    /** \brief C++'s static_cast<> expression.
     */
    ClangCursorCXXStaticCastExpr             = 124,
    
    /** \brief C++'s dynamic_cast<> expression.
     */
    ClangCursorCXXDynamicCastExpr            = 125,
    
    /** \brief C++'s reinterpret_cast<> expression.
     */
    ClangCursorCXXReinterpretCastExpr        = 126,
    
    /** \brief C++'s const_cast<> expression.
     */
    ClangCursorCXXConstCastExpr              = 127,
    
    /** \brief Represents an explicit C++ type conversion that uses "functional"
     * notion (C++ [expr.type.conv]).
     *
     * Example:
     * \code
     *   x = int(0.5);
     * \endcode
     */
    ClangCursorCXXFunctionalCastExpr         = 128,
    
    /** \brief A C++ typeid expression (C++ [expr.typeid]).
     */
    ClangCursorCXXTypeidExpr                 = 129,
    
    /** \brief [C++ 2.13.5] C++ Boolean Literal.
     */
    ClangCursorCXXBoolLiteralExpr            = 130,
    
    /** \brief [C++0x 2.14.7] C++ Pointer Literal.
     */
    ClangCursorCXXNullPtrLiteralExpr         = 131,
    
    /** \brief Represents the "this" expression in C++
     */
    ClangCursorCXXThisExpr                   = 132,
    
    /** \brief [C++ 15] C++ Throw Expression.
     *
     * This handles 'throw' and 'throw' assignment-expression. When
     * assignment-expression isn't present, Op will be null.
     */
    ClangCursorCXXThrowExpr                  = 133,
    
    /** \brief A new expression for memory allocation and constructor calls, e.g:
     * "new CXXNewExpr(foo)".
     */
    ClangCursorCXXNewExpr                    = 134,
    
    /** \brief A delete expression for memory deallocation and destructor calls,
     * e.g. "delete[] pArray".
     */
    ClangCursorCXXDeleteExpr                 = 135,
    
    /** \brief A unary expression.
     */
    ClangCursorUnaryExpr                     = 136,
    
    /** \brief An Objective-C string literal i.e. @"foo".
     */
    ClangCursorObjCStringLiteral             = 137,
    
    /** \brief An Objective-C \@encode expression.
     */
    ClangCursorObjCEncodeExpr                = 138,
    
    /** \brief An Objective-C \@selector expression.
     */
    ClangCursorObjCSelectorExpr              = 139,
    
    /** \brief An Objective-C \@protocol expression.
     */
    ClangCursorObjCProtocolExpr              = 140,
    
    /** \brief An Objective-C "bridged" cast expression, which casts between
     * Objective-C pointers and C pointers, transferring ownership in the process.
     *
     * \code
     *   NSString *str = (__bridge_transfer NSString *)CFCreateString();
     * \endcode
     */
    ClangCursorObjCBridgedCastExpr           = 141,
    
    /** \brief Represents a C++0x pack expansion that produces a sequence of
     * expressions.
     *
     * A pack expansion expression contains a pattern (which itself is an
     * expression) followed by an ellipsis. For example:
     *
     * \code
     * template<typename F, typename ...Types>
     * void forward(F f, Types &&...args) {
     *  f(static_cast<Types&&>(args)...);
     * }
     * \endcode
     */
    ClangCursorPackExpansionExpr             = 142,
    
    /** \brief Represents an expression that computes the length of a parameter
     * pack.
     *
     * \code
     * template<typename ...Types>
     * struct count {
     *   static const unsigned value = sizeof...(Types);
     * };
     * \endcode
     */
    ClangCursorSizeOfPackExpr                = 143,
    
    /* \brief Represents a C++ lambda expression that produces a local function
     * object.
     *
     * \code
     * void abssort(float *x, unsigned N) {
     *   std::sort(x, x + N,
     *             [](float a, float b) {
     *               return std::abs(a) < std::abs(b);
     *             });
     * }
     * \endcode
     */
    ClangCursorLambdaExpr                    = 144,
    
    /** \brief Objective-c Boolean Literal.
     */
    ClangCursorObjCBoolLiteralExpr           = 145,
    
    /** \brief Represents the "self" expression in a ObjC method.
     */
    ClangCursorObjCSelfExpr                  = 146,
    
    ClangCursorLastExpr                      = ClangCursorObjCSelfExpr,
    
    /* Statements */
    ClangCursorFirstStmt                     = 200,
    /**
     * \brief A statement whose specific kind is not exposed via this
     * interface.
     *
     * Unexposed statements have the same operations as any other kind of
     * statement; one can extract their location information, spelling,
     * children, etc. However, the specific kind of the statement is not
     * reported.
     */
    ClangCursorUnexposedStmt                 = 200,
    
    /** \brief A labelled statement in a function.
     *
     * This cursor kind is used to describe the "start_over:" label statement in
     * the following example:
     *
     * \code
     *   start_over:
     *     ++counter;
     * \endcode
     *
     */
    ClangCursorLabelStmt                     = 201,
    
    /** \brief A group of statements like { stmt stmt }.
     *
     * This cursor kind is used to describe compound statements, e.g. function
     * bodies.
     */
    ClangCursorCompoundStmt                  = 202,
    
    /** \brief A case statement.
     */
    ClangCursorCaseStmt                      = 203,
    
    /** \brief A default statement.
     */
    ClangCursorDefaultStmt                   = 204,
    
    /** \brief An if statement
     */
    ClangCursorIfStmt                        = 205,
    
    /** \brief A switch statement.
     */
    ClangCursorSwitchStmt                    = 206,
    
    /** \brief A while statement.
     */
    ClangCursorWhileStmt                     = 207,
    
    /** \brief A do statement.
     */
    ClangCursorDoStmt                        = 208,
    
    /** \brief A for statement.
     */
    ClangCursorForStmt                       = 209,
    
    /** \brief A goto statement.
     */
    ClangCursorGotoStmt                      = 210,
    
    /** \brief An indirect goto statement.
     */
    ClangCursorIndirectGotoStmt              = 211,
    
    /** \brief A continue statement.
     */
    ClangCursorContinueStmt                  = 212,
    
    /** \brief A break statement.
     */
    ClangCursorBreakStmt                     = 213,
    
    /** \brief A return statement.
     */
    ClangCursorReturnStmt                    = 214,
    
    /** \brief A GCC inline assembly statement extension.
     */
    ClangCursorGCCAsmStmt                    = 215,
    ClangCursorAsmStmt                       = ClangCursorGCCAsmStmt,
    
    /** \brief Objective-C's overall \@try-\@catch-\@finally statement.
     */
    ClangCursorObjCAtTryStmt                 = 216,
    
    /** \brief Objective-C's \@catch statement.
     */
    ClangCursorObjCAtCatchStmt               = 217,
    
    /** \brief Objective-C's \@finally statement.
     */
    ClangCursorObjCAtFinallyStmt             = 218,
    
    /** \brief Objective-C's \@throw statement.
     */
    ClangCursorObjCAtThrowStmt               = 219,
    
    /** \brief Objective-C's \@synchronized statement.
     */
    ClangCursorObjCAtSynchronizedStmt        = 220,
    
    /** \brief Objective-C's autorelease pool statement.
     */
    ClangCursorObjCAutoreleasePoolStmt       = 221,
    
    /** \brief Objective-C's collection statement.
     */
    ClangCursorObjCForCollectionStmt         = 222,
    
    /** \brief C++'s catch statement.
     */
    ClangCursorCXXCatchStmt                  = 223,
    
    /** \brief C++'s try statement.
     */
    ClangCursorCXXTryStmt                    = 224,
    
    /** \brief C++'s for (* : *) statement.
     */
    ClangCursorCXXForRangeStmt               = 225,
    
    /** \brief Windows Structured Exception Handling's try statement.
     */
    ClangCursorSEHTryStmt                    = 226,
    
    /** \brief Windows Structured Exception Handling's except statement.
     */
    ClangCursorSEHExceptStmt                 = 227,
    
    /** \brief Windows Structured Exception Handling's finally statement.
     */
    ClangCursorSEHFinallyStmt                = 228,
    
    /** \brief A MS inline assembly statement extension.
     */
    ClangCursorMSAsmStmt                     = 229,
    
    /** \brief The null satement ";": C99 6.8.3p3.
     *
     * This cursor kind is used to describe the null statement.
     */
    ClangCursorNullStmt                      = 230,
    
    /** \brief Adaptor class for mixing declarations with statements and
     * expressions.
     */
    ClangCursorDeclStmt                      = 231,
    
    /** \brief OpenMP parallel directive.
     */
    ClangCursorOMPParallelDirective          = 232,
    
    ClangCursorLastStmt                      = ClangCursorOMPParallelDirective,
    
    /**
     * \brief Cursor that represents the translation unit itself.
     *
     * The translation unit cursor exists primarily to act as the root
     * cursor for traversing the contents of a translation unit.
     */
    ClangCursorTranslationUnit               = 300,
    
    /* Attributes */
    ClangCursorFirstAttr                     = 400,
    /**
     * \brief An attribute whose specific kind is not exposed via this
     * interface.
     */
    ClangCursorUnexposedAttr                 = 400,
    
    ClangCursorIBActionAttr                  = 401,
    ClangCursorIBOutletAttr                  = 402,
    ClangCursorIBOutletCollectionAttr        = 403,
    ClangCursorCXXFinalAttr                  = 404,
    ClangCursorCXXOverrideAttr               = 405,
    ClangCursorAnnotateAttr                  = 406,
    ClangCursorAsmLabelAttr                  = 407,
    ClangCursorPackedAttr                    = 408,
    ClangCursorLastAttr                      = ClangCursorPackedAttr,
    
    /* Preprocessing */
    ClangCursorPreprocessingDirective        = 500,
    ClangCursorMacroDefinition               = 501,
    ClangCursorMacroExpansion                = 502,
    ClangCursorMacroInstantiation            = ClangCursorMacroExpansion,
    ClangCursorInclusionDirective            = 503,
    ClangCursorFirstPreprocessing            = ClangCursorPreprocessingDirective,
    ClangCursorLastPreprocessing             = ClangCursorInclusionDirective,
    
    /* Extra Declarations */
    /**
     * \brief A module import declaration.
     */
    ClangCursorModuleImportDecl              = 600,
    ClangCursorFirstExtraDecl                = ClangCursorModuleImportDecl,
    ClangCursorLastExtraDecl                 = ClangCursorModuleImportDecl
} ClangCursorKind;

typedef enum {
    /**
     * \brief Reprents an invalid type (e.g., where no type is available).
     */
    ClangCursorTypeInvalid = 0,
    
    /**
     * \brief A type whose specific kind is not exposed via this
     * interface.
     */
    ClangCursorTypeUnexposed = 1,
    
    /* Builtin types */
    ClangCursorTypeVoid = 2,
    ClangCursorTypeBool = 3,
    ClangCursorTypeChar_U = 4,
    ClangCursorTypeUChar = 5,
    ClangCursorTypeChar16 = 6,
    ClangCursorTypeChar32 = 7,
    ClangCursorTypeUShort = 8,
    ClangCursorTypeUInt = 9,
    ClangCursorTypeULong = 10,
    ClangCursorTypeULongLong = 11,
    ClangCursorTypeUInt128 = 12,
    ClangCursorTypeChar_S = 13,
    ClangCursorTypeSChar = 14,
    ClangCursorTypeWChar = 15,
    ClangCursorTypeShort = 16,
    ClangCursorTypeInt = 17,
    ClangCursorTypeLong = 18,
    ClangCursorTypeLongLong = 19,
    ClangCursorTypeInt128 = 20,
    ClangCursorTypeFloat = 21,
    ClangCursorTypeDouble = 22,
    ClangCursorTypeLongDouble = 23,
    ClangCursorTypeNullPtr = 24,
    ClangCursorTypeOverload = 25,
    ClangCursorTypeDependent = 26,
    ClangCursorTypeObjCId = 27,
    ClangCursorTypeObjCClass = 28,
    ClangCursorTypeObjCSel = 29,
    ClangCursorTypeFirstBuiltin = ClangCursorTypeVoid,
    ClangCursorTypeLastBuiltin  = ClangCursorTypeObjCSel,
    
    ClangCursorTypeComplex = 100,
    ClangCursorTypePointer = 101,
    ClangCursorTypeBlockPointer = 102,
    ClangCursorTypeLValueReference = 103,
    ClangCursorTypeRValueReference = 104,
    ClangCursorTypeRecord = 105,
    ClangCursorTypeEnum = 106,
    ClangCursorTypeTypedef = 107,
    ClangCursorTypeObjCInterface = 108,
    ClangCursorTypeObjCObjectPointer = 109,
    ClangCursorTypeFunctionNoProto = 110,
    ClangCursorTypeFunctionProto = 111,
    ClangCursorTypeConstantArray = 112,
    ClangCursorTypeVector = 113,
    ClangCursorTypeIncompleteArray = 114,
    ClangCursorTypeVariableArray = 115,
    ClangCursorTypeDependentSizedArray = 116,
    ClangCursorTypeMemberPointer = 117
} ClangCursorTypeKind;

@interface ClangCursor : NSObject

@property (nonatomic, readonly) ClangCursorKind kind;
@property (nonatomic, readonly) ClangCursorTypeKind typeKind;
@property (nonatomic, readonly) NSString *textContent;
@property (nonatomic, readonly) NSString *kindName;
@property (nonatomic, readonly) NSString *typeKindName;
@property (nonatomic, readonly) ClangCursor *semanticParent;
@property (nonatomic, readonly) ClangCursor *lexicalParent;

- (void)visitChildren:(ClangChildVisitResult (^)(ClangCursor *cursor, ClangCursor *parent))block;

@end
