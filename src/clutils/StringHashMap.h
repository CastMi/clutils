#ifndef STRING_HASH_MAP_H
#define STRING_HASH_MAP_H

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

#include "ClutilsConfig.h"

/*#ifdef HAVE_HASH_MAP
#include <hash_map>
using std::hash_map;
using std::hash;
#else
#ifdef HAVE_EXT_HASH_MAP
#include <ext/hash_map>
using __gnu_cxx::hash_map;
using __gnu_cxx::hash;
#else
#error "Couldn't find #include<hash_map> or #include<ext/hash_map>"
#endif
#endif*/
#include "StringUtilities.h"

#include <tr1/unordered_map>
#include <string>
#include <vector>

using std::tr1::unordered_map;
using std::string;
using std::vector;
/*
template <bool caseSensitive> class HashString {
public:
  inline size_t operator()( const string &s ) const {
    hash<const char *> H;
    string toHash;
    if( caseSensitive ){
      toHash = s;
    }
    else{
      toHash = upperCase(s);
    }
    return H( toHash.c_str() );
  }

}; 

template <bool caseSensitive> class HashEqual {
public:
  inline bool operator()( const string &s1, const string &s2 ) const {
    if( caseSensitive ){
      return s1 == s2;
    }
    else{
      return stringCaseCompare(s1, s2);
    }
  }
};
*/
/**
   A hash map that uses STL strings as a key and a template parameter as
   the stored value.
*/
template <class toHash, bool caseSensitive=false> class StringHashMap {

public:
  //typedef unordered_map<string, toHash, HashString<caseSensitive>, HashEqual<caseSensitive> > HashMap;
  typedef unordered_map<string, toHash> HashMap;

  StringHashMap(){}
  ~StringHashMap(){}

  unsigned int count( const string &key ){
    return myHashMap.count( key );
  }

  /**
     Find the entry or return null.
  */
  toHash find( const string &key ) const {
    toHash retval = 0;

    typename HashMap::const_iterator found =
      myHashMap.find( key );
  
    if( found != myHashMap.end() ){
      retval = (*found).second;
    }
  
    return retval;
  }

  /**
     Insert ( key, value ) pair.
  */
  void insert( const string &key, toHash value ){
    myHashMap[ key ] = value;
  }

  /**
     Returns true if it's empty, false otherwise.
  */
  bool empty() const {
    return myHashMap.empty();
  }


  /**
     Returns a vector full of the elements of this StringHashMap.
     Note that it is allocated and return - caller must delete.
  */
  vector<toHash> *getElementVector() const {
    vector<toHash> *retval = new vector<toHash>();
    for( typename HashMap::const_iterator i = myHashMap.begin();
	 i != myHashMap.end();
	 i++ ){
      retval->push_back( (*i).second );
    }
    return retval;
  }

  /**
     Returns a vector full of the elements of this StringHashMap.
     Note that it is allocated and return - caller must delete.
  */
  vector<string> *getKeyVector() const {
    vector<string> *retval = new vector<string>;
    for( typename HashMap::const_iterator i = myHashMap.begin();
	 i != myHashMap.end();
	 i++ ){
      retval->push_back( (*i).first );
    }
    return retval;
  }

  /**
     Removes the element from the hash map, returns the removed element.
     If the object is not in the map it returns 0.
  */
  toHash remove( const string &key ) {
    toHash retval = 0;
    typename HashMap::iterator found = myHashMap.find( key );
    if( found != myHashMap.end() ){
      retval = found->second;      
      myHashMap.erase( found );
    }
    return retval;    
  }

  /**
     Deletes all objects then clears the now NULL pointers
  */
  void erase()
  {
	  for (typename HashMap::iterator iter = myHashMap.begin(); iter != myHashMap.end(); iter++)
	  {
		  delete iter->second;
	  }
	  myHashMap.clear();
  }

private:
  HashMap myHashMap;

};
#endif

