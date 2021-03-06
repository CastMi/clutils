// Copyright (c) 2000-2002 Clifton Labs, Inc.  
// All rights reserved.

// Clifton Labs MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  Clifton Labs SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
// DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.

// Authors: Dale E. Martin   dmartin@cliftonlabs.com

#include "StringHashMap.h"

using std::hash;

size_t
hashString::operator()( const std::string &s ) const {
  hash<const char *> H;
  const std::string upper = upperCase(s);
  return H( upper.c_str() );
}

bool 
hashEqual::operator()( const std::string &s1, const std::string &s2 ) const{
  return stringCaseCompare(s1, s2);
}
