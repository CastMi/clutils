/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 *
 *   antlr -k 1 -CC ../../src/ConfigurationParser.gg
 *
 */

#define ANTLR_VERSION	13333
#include "pcctscfg.h"
#include "pccts_stdio.h"
#include "tokens.h"

#include "ConfigurationScope.h"
#include "ConfigurationValue.h"
#include "ConfigurationChoice.h"
#include <vector>
#include <stdio.h>
#include "Debug.h"
#include "AParser.h"
#include "ConfigurationParserHandle.h"
#include "DLexerBase.h"
#include "ATokPtr.h"

/* MR23 In order to remove calls to PURIFY use the antlr -nopurify option */

#ifndef PCCTS_PURIFY
#define PCCTS_PURIFY(r,s) memset((char *) &(r),'\0',(s));
#endif


// Base info for DLG-generated scanner
#include "DLexerBase.h"

// The scanner generated by DLG from this file
#include "ConfigurationLexer.h"

// Base token definitions for ANTLR
#include "AToken.h"

// Define your token type (ANTLRToken) as just ANTLRCommonToken
// (basically just token type and text
typedef ANTLRCommonToken ANTLRToken;

const ConfigurationScope *
ConfigurationParserHandle::parseFile( string fileName ){
  const ConfigurationScope *outerScope = 0;
  
  // define input file; standard input for this one
  const char *filename = fileName.c_str();
  FILE *inputFile = fopen( filename, "r" );
  
  if( inputFile != 0 ){
    DLGFileInput in( inputFile );
    
    // define an instance of your scanner
    ConfigurationLexer scanner(&in);
    
    // define token buffer between scanner and parser
    ANTLRTokenBuffer pipe(&scanner);
    
    // create a token to use as a model
    ANTLRToken tok;
    
    // tell the scanner what type the token is
    scanner.setToken(&tok);
    
    // create an instance of your parser
    ConfigurationParserHandle myParser(&pipe);
    
    // initialize your parser
    myParser.init();
    
    // start first rule
    outerScope = myParser.configurationFile();
    if( outerScope != 0 &&
    outerScope->findChoice("DEBUG") != 0 &&
    stringCaseCompare( outerScope->getStringValue("DEBUG"), "TRUE" )){
      clutils::enableDebug();
    }
  }
  else{
    string error = "Error reading configuration file \"" + fileName + "\"";
    perror( error.c_str() );
  }
  
  return outerScope; 
}

const ConfigurationScope *
ConfigurationParserHandle::configurationFile(void)
{
  const ConfigurationScope *   _retv;
  zzRULE;
  PCCTS_PURIFY(_retv,sizeof(const ConfigurationScope *  ))
  
  ConfigurationScope *retval = new ConfigurationScope( "" );
  nested_configuration(  retval  );
  zzmatch(END);
  if ( !guessing ) {
  
  _retv = retval;
  }
 consume();
  return _retv;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x1);
  return _retv;
}

void
ConfigurationParserHandle::nested_configuration(ConfigurationScope * outerScope)
{
  zzRULE;
  {
    zzGUESS_BLOCK
    for (;;) {
      if ( !((LA(1)==IDENTIFIER))) break;
      zzGUESS
      if ( !zzrv && (LA(1)==IDENTIFIER) ) {
        {
          zzmatch(IDENTIFIER); consume();
          zzmatch(COLON); consume();
        }
        zzGUESS_DONE
        config_value( outerScope );
      }
      else {
        if ( !zzrv ) zzGUESS_DONE;
        if ( (LA(1)==IDENTIFIER) ) {
          configuration_scope( outerScope );
        }
        else break; /* MR6 code for exiting loop "for sure" */
      }
    }
  }
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x2);
}

void
ConfigurationParserHandle::configuration_scope(ConfigurationScope * outerScope)
{
  zzRULE;
  ANTLRTokenPtr id=NULL;
  
  ConfigurationScope *newScope = 0;
  zzmatch(IDENTIFIER);
  if ( !guessing ) {
    id = (ANTLRTokenPtr)LT(1);
  }
  
  if ( !guessing ) {
  
  newScope = new ConfigurationScope( id->getText() );
  outerScope->addScope( newScope );
  }
 consume();
  zzmatch(LBRACE); consume();
  nested_configuration(  newScope  );
  zzmatch(RBRACE); consume();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x4);
}

void
ConfigurationParserHandle::config_value(ConfigurationScope * outerScope)
{
  zzRULE;
  ANTLRTokenPtr id=NULL;
  
  ConfigurationValue *firstValue = 0;
  ConfigurationValue *nextValue = 0;
  ConfigurationChoice *newChoice = 0;
  vector<const ConfigurationValue *> *myVector = 0;
  zzmatch(IDENTIFIER);
  if ( !guessing ) {
    id = (ANTLRTokenPtr)LT(1);
  }
   consume();
  zzmatch(COLON);
  if ( !guessing ) {
  
  newChoice = new ConfigurationChoice( id->getText() );
  }
 consume();
  if ( !guessing ) {
      firstValue   = value();

  } else {
    value();
  }
  {
    if ( (setwd1[LA(1)]&0x8) ) {
      {
        while ( (LA(1)==COMMA) ) {
          zzmatch(COMMA); consume();
          if ( !guessing ) {
              nextValue   = value();

          } else {
            value();
          }
          if ( !guessing ) {
          
          if( myVector == 0 ){
            myVector = new vector<const ConfigurationValue *>;
            myVector->push_back( firstValue );
          }
          myVector->push_back( nextValue );
          }
        }
      }
    }
    else {
      if ( (setwd1[LA(1)]&0x10) ) {
      }
      else {FAIL(1,err1,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
  if ( !guessing ) {
  
  if( myVector == 0 ){
    newChoice->setConfigurationValue( firstValue );
  }
  else{
    newChoice->setConfigurationValue( new VectorConfigurationValue( myVector ) );
  }
  outerScope->addChoice( newChoice );
  }
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x20);
}

ConfigurationValue *
ConfigurationParserHandle::value(void)
{
  ConfigurationValue *   _retv;
  zzRULE;
  ANTLRTokenPtr id=NULL, inttok=NULL, floattok=NULL;
  PCCTS_PURIFY(_retv,sizeof(ConfigurationValue *  ))
  
  _retv = 0;
  {
    if ( (LA(1)==IDENTIFIER) ) {
      zzmatch(IDENTIFIER);
      if ( !guessing ) {
            id = (ANTLRTokenPtr)LT(1);
      }
      
      if ( !guessing ) {
      
      _retv = new StringConfigurationValue( id->getText() );
      }
 consume();
    }
    else {
      if ( (LA(1)==INTEGERVAL) ) {
        zzmatch(INTEGERVAL);
        if ( !guessing ) {
                inttok = (ANTLRTokenPtr)LT(1);
        }
        
        if ( !guessing ) {
        
        _retv = new IntConfigurationValue( inttok->getText() );
        }
 consume();
      }
      else {
        if ( (LA(1)==FLOATVAL) ) {
          zzmatch(FLOATVAL);
          if ( !guessing ) {
                    floattok = (ANTLRTokenPtr)LT(1);
          }
          
          if ( !guessing ) {
          
          _retv = new DoubleConfigurationValue( floattok->getText() );
          }
 consume();
        }
        else {FAIL(1,err2,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
  }
  return _retv;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x40);
  return _retv;
}