//==============================================================================
//
// Title:       toolbox.c
// Purpose:     A short description of the implementation.
//
// Created on:  10-Jan-24 at 09:30:28 by .
// Copyright:   . All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toolbox.h"
#include "cvidotnet.h"

//==============================================================================
// Constants

#define MAX_JSON_SIZE 4096
#define MAX_CONTROL_LOOP 1000

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// \brief Reads the content of a JSON file.
/// \param filename The name of the JSON file to read.
/// \return The content of the JSON file as a dynamically allocated string, or NULL if the file cannot be opened or memory allocation fails.
char *readJSONFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open the JSON file.\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *fileContent = (char *)malloc(fileSize + 1);
    if (fileContent == NULL)
    {
        printf("Failed to allocate memory.\n");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(fileContent, 1, fileSize, file);
    fclose(file);
    fileContent[bytesRead] = '\0';

    printf("File: %s\n", fileContent);
    return fileContent;
}

/// \brief Parses a JSON table and extracts the content associated with a given key.
/// \param jsonContent The JSON content to parse.
/// \param key The key to search for in the JSON content.
/// \return The content associated with the key as a dynamically allocated string, or NULL if the key is not found or memory allocation fails.
char *parseJSONTable(const char *jsonContent, const char *key)
{
    char *tableContent = NULL;

    char *start = strstr(jsonContent, key);
    if (start == NULL)
    {
        return NULL;
    }
    start += strlen(key) + 2;

    start = strchr(start, '{');
    if (start == NULL)
    {
        return NULL;
    }
    start += 1; // Skip the {

    char *end = strchr(start, '}');
    if (end == NULL)
    {
        return NULL;
    }

    char *bracketIn;
    char *bracketOut;
    char *searchPos = start;
    int controlLoop = MAX_CONTROL_LOOP;
    while (controlLoop-- > 0)
    {
        bracketOut = strchr(searchPos, '}');
        if (bracketOut == NULL)
        {
            break;
        }

        bracketIn = strchr(searchPos, '{');
        if (bracketIn == NULL)
        {
            end = bracketOut;
            break;
        }
        bracketIn += 1;

        if (strlen(bracketOut) > strlen(bracketIn))
        {
            end = bracketOut;
            break;
        }

        searchPos = bracketOut + 1;
    }

    int length = end - start;
    tableContent = (char *)malloc(length + 1);
    if (tableContent != NULL)
    {
        strncpy(tableContent, start, length);
        tableContent[length] = '\0';
        printf("Table: %s\n", tableContent);
    }
    return tableContent;
}

/// \brief Parses a JSON key and extracts the content associated with it.
/// \param jsonContent The JSON content to parse.
/// \param key The key to search for in the JSON content.
/// \return The content associated with the key as a dynamically allocated string, or NULL if the key is not found or memory allocation fails.
char *parseJSONKey(const char *jsonContent, const char *key)
{
    char *keyContent = NULL;

    char *start = strstr(jsonContent, key);
    if (start == NULL)
    {
        return NULL;
    }
    start += strlen(key) + 2;

    start = strchr(start, '\"');
    if (start == NULL)
    {
        return NULL;
    }
    start += 1; // Skip the "

    char *end = strchr(start, '\"');
    if (end == NULL)
    {
        return NULL;
    }

    int length = end - start;
    keyContent = (char *)malloc(length + 1);
    if (keyContent != NULL)
    {
        strncpy(keyContent, start, length);
        keyContent[length] = '\0';
        printf("Key: %s\n", keyContent);
    }
    return keyContent;
}

/// \brief Converts a character array to an integer.
/// \param charArray The character array to convert.
/// \return The converted integer value.
int charArrayToInt(const char *charArray)
{
    int number = 0;

    int i = 0;
    while (charArray[i] != '\0')
    {
        number = number * 10 + (charArray[i++] - '0');
    }

    return number;
}

/// \brief Converts a character array to an enumeration value.
/// \param charArray The character array to convert.
/// \return The converted enumeration value, or -1 if the conversion fails.
int charArrayToEnum(const char *charArray)
{
    if (strcmp(charArray, "CDOTNET_VOID") == 0)
    {
        return CDOTNET_VOID;
    }
    else if (strcmp(charArray, "CDOTNET_STRING") == 0)
    {
        return CDOTNET_STRING;
    }
    else if (strcmp(charArray, "CDOTNET_BOOLEAN") == 0)
    {
        return CDOTNET_BOOLEAN;
    }
    else if (strcmp(charArray, "CDOTNET_BYTE") == 0)
    {
        return CDOTNET_BYTE;
    }
    else if (strcmp(charArray, "CDOTNET_SBYTE") == 0)
    {
        return CDOTNET_SBYTE;
    }
    else if (strcmp(charArray, "CDOTNET_INT16") == 0)
    {
        return CDOTNET_INT16;
    }
    else if (strcmp(charArray, "CDOTNET_INT32") == 0)
    {
        return CDOTNET_INT32;
    }
    else if (strcmp(charArray, "CDOTNET_INT64") == 0)
    {
        return CDOTNET_INT64;
    }
    else if (strcmp(charArray, "CDOTNET_UINT16") == 0)
    {
        return CDOTNET_UINT16;
    }
    else if (strcmp(charArray, "CDOTNET_UINT32") == 0)
    {
        return CDOTNET_UINT32;
    }
    else if (strcmp(charArray, "CDOTNET_UINT64") == 0)
    {
        return CDOTNET_UINT64;
    }
    else if (strcmp(charArray, "CDOTNET_SINGLE") == 0)
    {
        return CDOTNET_SINGLE;
    }
    else if (strcmp(charArray, "CDOTNET_DOUBLE") == 0)
    {
        return CDOTNET_DOUBLE;
    }
    else if (strcmp(charArray, "CDOTNET_DECIMAL") == 0)
    {
        return CDOTNET_DECIMAL;
    }
    else if (strcmp(charArray, "CDOTNET_CHAR") == 0)
    {
        return CDOTNET_CHAR;
    }
    else if (strcmp(charArray, "CDOTNET_INTPTR") == 0)
    {
        return CDOTNET_INTPTR;
    }
    else if (strcmp(charArray, "CDOTNET_ENUM") == 0)
    {
        return CDOTNET_ENUM;
    }
    else if (strcmp(charArray, "CDOTNET_OBJECT") == 0)
    {
        return CDOTNET_OBJECT;
    }
    else if (strcmp(charArray, "CDOTNET_STRUCT") == 0)
    {
        return CDOTNET_STRUCT;
    }
    else if (strcmp(charArray, "CDOTNET_GENERIC") == 0)
    {
        return CDOTNET_GENERIC;
    }
    else if (strcmp(charArray, "CDOTNET_BASIC_TYPE_MASK") == 0)
    {
        return CDOTNET_BASIC_TYPE_MASK;
    }
    else if (strcmp(charArray, "CDOTNET_MODIFIER_MASK") == 0)
    {
        return CDOTNET_MODIFIER_MASK;
    }
    else if (strcmp(charArray, "CDOTNET_OUT") == 0)
    {
        return CDOTNET_OUT;
    }
    else if (strcmp(charArray, "CDOTNET_REF") == 0)
    {
        return CDOTNET_REF;
    }
    else if (strcmp(charArray, "CDOTNET_ARRAY") == 0)
    {
        return CDOTNET_ARRAY;
    }
    else if (strcmp(charArray, "CDOTNET_TYPEID_4BYTES") == 0)
    {
        return CDOTNET_TYPEID_4BYTES;
    }
    else
    {
        return -1;
    }
}

//==============================================================================
// .NET functions calls

/// \brief Loads an assembly DLL based on the provided JSON configuration file.
/// \param pathToJSONConf The path to the JSON configuration file.
/// \param assemblyDLL Pointer to the AssemblyDLL structure to store the loaded assembly information.
/// \return 0 if the assembly is loaded successfully, a negative value otherwise.
int LoadAssemblyDLL(const char *pathToJSONConf, AssemblyDLL *assemblyDLL)
{
    char *fileContent = readJSONFile(pathToJSONConf);
    if (fileContent == NULL)
    {
        return -1;
    }

    char *tableContent = parseJSONTable(fileContent, "Configuration");
    if (tableContent == NULL)
    {
        return -2;
    }

    char *name = parseJSONKey(tableContent, "Name");
    char *extension = parseJSONKey(tableContent, "Extension");
    char *version = parseJSONKey(tableContent, "Version");
    char *culture = parseJSONKey(tableContent, "Culture");
    char *publicKeyToken = parseJSONKey(tableContent, "PublicKeyToken");
    char *path = parseJSONKey(tableContent, "Path");

    if (name != NULL &&
        extension != NULL &&
        version != NULL &&
        culture != NULL &&
        publicKeyToken != NULL &&
        path != NULL)
    {
        strncpy(assemblyDLL->name, name, strlen(name));
        strncpy(assemblyDLL->extension, extension, strlen(extension));
        strncpy(assemblyDLL->version, version, strlen(version));
        strncpy(assemblyDLL->culture, culture, strlen(culture));
        strncpy(assemblyDLL->publicKeyToken, publicKeyToken, strlen(publicKeyToken));

        sprintf(assemblyDLL->path,
                "%s\\%s.%s",
                path, name, extension);
    }
    else
    {
        printf("Invalid JSON format.\n");
        return -3;
    }

    sprintf(assemblyDLL->fullName,
            "%s, Version=%s, Culture=%s, PublicKeyToken=%s",
            name, version, culture, publicKeyToken);

    int status = CDotNetRegisterAssemblyPath(assemblyDLL->fullName, assemblyDLL->path);
    if (status != 0)
    {
        return -4;
    }

    status = CDotNetLoadAssembly(assemblyDLL->fullName,
                                 &assemblyDLL->handle);
    if (status != 0)
    {
        return -4;
    }

    return 0;
}

/// \brief Creates an instance of a class DLL based on the provided class name and assembly information.
/// \param className The name of the class to create an instance of.
/// \param assemblyDLL Pointer to the AssemblyDLL structure containing the assembly information.
/// \param classDLL Pointer to the ClassDLL structure to store the created class instance.
/// \return 0 if the class instance is created successfully, a negative value otherwise.
int CreateClassDLL(const char *className, const AssemblyDLL *assemblyDLL, ClassDLL *classDLL)
{
    classDLL->assemblyHandle = assemblyDLL->handle;
    sprintf(classDLL->fullName, "%s.%s", assemblyDLL->name, className);

    int status = CDotNetCreateGenericInstance(classDLL->assemblyHandle,
                                              classDLL->fullName,
                                              0,
                                              0,
                                              &classDLL->handle,
                                              0,
                                              0,
                                              0,
                                              0,
                                              NULL);
    if (status != 0)
    {
        return -1;
    }

    return 0;
}

/// \brief Loads a method DLL based on the provided JSON configuration file and method name.
/// \param pathToJSONConf The path to the JSON configuration file.
/// \param methodName The name of the method to load.
/// \param classDLL Pointer to the ClassDLL structure containing the class information.
/// \param methodDLL Pointer to the MethodDLL structure to store the loaded method information.
/// \return 0 if the method is loaded successfully, a negative value otherwise.
int LoadMethodDLL(const char *pathToJSONConf, const char *methodName, const ClassDLL *classDLL, MethodDLL *methodDLL)
{
    strncpy(methodDLL->classDLL.fullName, classDLL->fullName, strlen(classDLL->fullName));
    methodDLL->classDLL.assemblyHandle = classDLL->assemblyHandle;
    methodDLL->classDLL.handle = classDLL->handle;

    char *fileContent = readJSONFile(pathToJSONConf);
    if (fileContent == NULL)
    {
        return -1;
    }

    char *tableContent = parseJSONTable(fileContent, "MethodLibrary");
    if (tableContent == NULL)
    {
        return -2;
    }

    char *methodContent = parseJSONTable(tableContent, methodName);
    if (tableContent == NULL)
    {
        return -3;
    }

    strncpy(methodDLL->name, methodName, strlen(methodName));

    char *returnType = parseJSONKey(methodContent, "ReturnType");
    char *numberOfParameters = parseJSONKey(methodContent, "NumberOfParameters");

    if (returnType == NULL || numberOfParameters == NULL)
    {
        printf("Invalid JSON format.\n");
        return -4;
    }

    methodDLL->returnType = charArrayToEnum(returnType);
    methodDLL->numberOfParameters = charArrayToInt(numberOfParameters);

    int i = 0;
    for (i = 0; i < 16; i++)
    {
        methodDLL->parameterTypes[i] = CDOTNET_VOID;
    }

    if (methodDLL->numberOfParameters == 0)
    {
        return 0;
    }

    for (i = 1; i <= methodDLL->numberOfParameters; i++)
    {
        char parameterTypeKey[20];
        sprintf(parameterTypeKey, "%s_%d", "ParameterType", i);

        char *parameterType = parseJSONKey(methodContent, parameterTypeKey);
        if (parameterType == NULL)
        {
            printf("Invalid JSON format.\n");
            return -5;
        }

        methodDLL->parameterTypes[i - 1] = charArrayToEnum(parameterType);
        printf("%s: %d {%s}\n", parameterTypeKey, methodDLL->parameterTypes[i - 1], parameterType);
    }

    return 0;
}

/// \brief Invokes a method DLL based on the provided method information and parameter values.
/// \param methodDLL Pointer to the MethodDLL structure containing the method information.
/// \param returnValue Pointer to store the return value of the method.
/// \param parameterValues Array of pointers to the parameter values.
/// \return 0 if the method is invoked successfully, a negative value otherwise.
int InvokeMethodDLL(const MethodDLL *methodDLL, void *returnValue, void **parameterValues)
{
    int status = CDotNetInvokeMember(methodDLL->classDLL.assemblyHandle,
                                     methodDLL->classDLL.fullName,
                                     methodDLL->classDLL.handle,
                                     CDOTNET_CALL_METHOD,
                                     methodDLL->name,
                                     methodDLL->numberOfParameters,
                                     methodDLL->parameterTypes,
                                     parameterValues,
                                     methodDLL->returnType,
                                     returnValue,
                                     NULL);

    if (status != 0)
    {
        return -1;
    }

    return 0;
}

//==============================================================================
// DLL Functions Library
// one can also predefine already known methods,
// this will look cleaner, but it needs to be compiled within the CVI everytime.
int exampleKnownMethod(char *parameter1, char *parameter2, const ClassDLL *classDLL)
{
    const char *methodName = "exampleKnownMethod";
    int returnType = CDOTNET_INT32;

    int numberOfParameters = 2;
    unsigned parameterTypes[2] = {CDOTNET_STRING, CDOTNET_STRING};
    void *parameterValues[2] = {(void *)parameter1, (void *)parameter1};

    int returnValue;

    CDotNetInvokeMember(classDLL->assemblyHandle,
                        classDLL->fullName,
                        classDLL->handle,
                        CDOTNET_CALL_METHOD,
                        methodName,
                        numberOfParameters,
                        parameterTypes,
                        parameterValues,
                        returnType,
                        &returnValue,
                        NULL);

    return returnValue;
}
