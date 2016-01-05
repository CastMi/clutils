#ifndef STRING_UTILITIES_H
#define STRING_UTILITIES_H

// Copyright (c) 2000-2002 Clifton Labs.
// All rights reserved.

// Clifton Labs MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  Clifton Labs SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.

// Author: Dale E. Martin          dmartin@cliftonlabs.com

#include <string>
#include <string.h>

using std::string;

/* This is here solely to make something we can check for from configure. */
extern "C" {int fake();}

/** Uppercase the passed-in input string */
const string upperCase( const string &inputString );

/** Cut out all white spaces in passed-in input string */
const string trimWhiteSpaces( const string &inputString );

/**
   Return the integer passed in as a string.
*/
const string intToString( int input );

/**
   Return the double passed in as a string.
*/
const string doubleToString( double input );

/**
   Take the string that represents an integer, and return an int.  The bool
   passed in will be set to true if the conversion is successful, else it
   will be false.
*/
long stringToLong( const string &input, int &endPos );

/**
   Take the string containing a floating point value, and return a float.
   The bool passed in will be set to true if the conversion is successful,
   else it will be false.
*/
double stringToDouble( const string &input, int &endPos );

/**
   Compares if two strings are equal if one ignores case differences.
*/
bool stringCaseCompare( const string &s1, const string &s2 );

/**
   This function does a strdup like the tradition library function, except
   it uses "new" to allocate the memory.  Memory returned needs to be
   deleted with "delete []".

   @param toDup String to duplicate.  Does not have to be null terminated
   if the second parameter is supplied.
   @param len (optional) The length of the string to duplicate.  If this
   parameter is not supplied, strlen will be called on "toDup".  (In that 
   case "toDup" should be NULL terminated!
*/
inline char *cppStrDup( const char *toDup, int len = -1 ){
  char *retval = 0;
  if( len == -1 ){
    len = strlen( toDup ) + 1;
    retval = new char[len];
    memcpy( retval, toDup, len );
    retval[ len - 1 ] = '\0';    
  }
  else{
    retval = new char[len];
    memcpy( retval, toDup, len );
  }
  return retval;
}

#endif
