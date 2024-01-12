//==============================================================================
//
// Title:       main.c
// Purpose:     A short description of the implementation.
//
// Created on:  10-Jan-24 at 09:42:46 by .
// Copyright:   . All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "main.h"
#include "toolbox.h"
#include <ansi_c.h>

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
AssemblyDLL MyDLL;
ClassDLL MyClass;
MethodDLL MyMethod;

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int main(int argc, char **argv)
{
    char *pathToJSONConf = "configuration.json";
    int status = LoadAssemblyDLL(pathToJSONConf, &MyDLL);
    if (status < 0)
    {
        return -1;
    }

    char *className = "MyClass";
    status = CreateClassDLL(className, &MyDLL, &MyClass);
    if (status < 0)
    {
        return -2;
    }

    char *methodName = "MyMethod";
    status = LoadMethodDLL(pathToJSONConf, methodName, &MyClass, &MyMethod);
    if (status < 0)
    {
        return -3;
    }

    int returnValue = 0;
    char *filePath = "commonLogs.txt";
    char *message = "Hello World!";
    void *parameterValues[2] = {(void *)&filePath, (void *)&message};

    status = InvokeMethodDLL(&MyMethod, &returnValue, parameterValues);
    if (status < 0)
    {
        return -4;
    }

    printf("InvokeMethodDLL: %d\n", returnValue);

    int result = exampleKnownMethod(&filePath, &message, &MyClass);

    printf("exampleKnownMethod: %d\n", result);

    getchar();

    return 0;
}
