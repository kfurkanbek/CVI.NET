//==============================================================================
//
// Title:       toolbox.h
// Purpose:     A short description of the interface.
//
// Created on:  10-Jan-24 at 09:30:28 by .
// Copyright:   . All Rights Reserved.
//
//==============================================================================

#ifndef __toolbox_H__
#define __toolbox_H__

#ifdef __cplusplus
extern "C"
{
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "cvidotnet.h"

//==============================================================================
// Constants

#define MAX_JSON_SIZE 4096
#define MAX_CONTROL_LOOP 1000

//==============================================================================
// Types

typedef struct __Object *NET_Class;

typedef struct
{
    char name[100];
    char extension[100];
    char version[100];
    char culture[100];
    char publicKeyToken[100];
    char path[1024];
    char fullName[550]; // "%s, Version=%s, Culture=%s, PublicKeyToken=%s", name, version, culture, publicKeyToken
    CDotNetAssemblyHandle handle;
} AssemblyDLL;

typedef struct
{
    char fullName[220]; // "%s.%s", assemblyDLL.name, className
    CDotNetAssemblyHandle assemblyHandle;
    NET_Class handle;
} ClassDLL;

typedef struct
{
    char name[100];
    int returnType;
    int numberOfParameters;
    int parameterTypes[16];
    ClassDLL classDLL;
} MethodDLL;

//==============================================================================
// External variables

//==============================================================================
// Global functions

//==============================================================================
// JSON reading functions

char *readJSONFile(const char *filename);
char *parseJSONTable(const char *jsonContent, const char *key);
char *parseJSONKey(const char *jsonContent, const char *key);
int charArrayToInt(const char *charArray);
int charArrayToEnum(const char *charArray);

//==============================================================================
// .NET functions calls
int LoadAssemblyDLL(const char *pathToJSONConf, AssemblyDLL *assemblyDLL);
int CreateClassDLL(const char *className, const AssemblyDLL *assemblyDLL, ClassDLL *classDLL);
int LoadMethodDLL(const char *pathToJSONConf, const char *methodName, const ClassDLL *classDLL, MethodDLL *methodDLL);
int InvokeMethodDLL(const MethodDLL *methodDLL, void *returnValue, void **parameterValues);

//==============================================================================
// DLL Functions Library
// one can also predefine already known methods,
// this will look cleaner, but it needs to be compiled within the CVI everytime.
int exampleKnownMethod(char *parameter1, char *parameter2, const ClassDLL *classDLL);

#ifdef __cplusplus
}
#endif

#endif /* ndef __toolbox_H__ */
