// Copyright (c) 2000-2003 Clifton Labs, Inc.  
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

#include <clutils/ArgumentParser.h>
#include <clutils/Debug.h>
#include <clutils/StringUtilities.h>
#include "ArgumentParserTest.h"

ArgumentParserTest *
ArgumentParserTest::instance(){
  static ArgumentParserTest *myArgumentParserTest = new ArgumentParserTest();
  
  return myArgumentParserTest;
}

ArgumentParser *
ArgumentParserTest::getDefaultArgumentParser(){
  static ArgumentParser::ArgRecord argList[] = {
    { "-boolArg", "help for boolean argument", &boolArg, ArgumentParser::BOOLEAN, true }, 
    { "-intArg", "help for integer argument", &intArg, ArgumentParser::INTEGER, true }, 
    { "-stringArg", "help for string argument", &stringArg, ArgumentParser::STRING, false },
    { "", "", 0 }
  };

  static ArgumentParser *defaultParser = new ArgumentParser( argList );
  return defaultParser;
}

int 
ArgumentParserTest::testConstruction(){
  int retval = 0;
  
  ArgumentParser *toTest = getDefaultArgumentParser();
  if( toTest == 0 ){
    retval = 1;
    goto end;
  }

 end:
  return retval;
}

int 
ArgumentParserTest::testNoneMatch(){
  int retval = 0;

  char *argv[4] = {
    "the",
    "quick",
    "brown",
    "fox"
  };

  ArgumentParser *toTest = getDefaultArgumentParser();
  vector<string> argVec = ArgumentParser::vectorifyArguments( 4, argv, false );
  if( argVec[0] != "the" ||
      argVec[1] != "quick" ||
      argVec[2] != "brown" ||
      argVec[3] != "fox" ){
    retval = 1;
    goto end;
  }
  toTest->checkArgs( argVec );
  
  if( boolArg != false || intArg != 0 || stringArg != ""  ){
    retval = 1;
    goto end;
  }
  
  if( argVec.size() != 4 ){
    retval = 1;
    goto end;
  }

 end:
  return retval;
}

int 
ArgumentParserTest::testBoolMatch(){
  int retval = 0;

  char *argv[1] = {
    "-boolArg",
  };

  ArgumentParser *toTest = getDefaultArgumentParser();
  vector<string> argVec = ArgumentParser::vectorifyArguments( 1, argv, false );
  if( argVec[0] != "-boolArg" ){
    retval = 1;
    goto end;
  }
  toTest->checkArgs( argVec );
  if( boolArg != true ){
    retval = 1;
    goto end;
  }
  if( argVec.size() > 0 ){
    retval = 1;
    goto end;
  }

 end:
  return retval;
}

int 
ArgumentParserTest::testIntMatch(){
  int retval = 0;

  char *argv[2] = {
    "-intArg",
    "77",
  };

  ArgumentParser *toTest = getDefaultArgumentParser();
  vector<string> argVec = ArgumentParser::vectorifyArguments( 2, argv, false );
  if( argVec[0] != "-intArg" || argVec[1] != "77" ){
    retval = 1;
    goto end;
  }
  toTest->checkArgs( argVec );
  if( intArg != 77 ){
    retval = 1;
    goto end;
  }
  if( argVec.size() > 0 ){
    retval = 1;
    goto end;
  }

 end:
  return retval;
}

int 
ArgumentParserTest::testStringMatch(){
  int retval = 0;

  char *argv[2] = {
    "-stringArg",
    "someString",
  };

  ArgumentParser *toTest = getDefaultArgumentParser();
  vector<string> argVec = ArgumentParser::vectorifyArguments( 2, argv, false );
  if( argVec[0] != "-stringArg" || argVec[1] != "someString" ){
    retval = 1;
    goto end;
  }
  toTest->checkArgs( argVec );
  if( stringArg != "someString" ){
    retval = 1;
    goto end;
  }
  if( argVec.size() > 0 ){
    retval = 1;
    goto end;
  }

 end:
  return retval;
}

int 
ArgumentParserTest::testMultiple(){
int retval = 0;
  char *argv[5] = {
    "-stringArg",
    "someString2",
    "-intArg",
    "12",
    "shouldnotmatch",
  };

  ArgumentParser *toTest = getDefaultArgumentParser();
  vector<string> argVec = ArgumentParser::vectorifyArguments( 5, argv, false );
  if( argVec[0] != "-stringArg" || argVec[1] != "someString2" ||
      argVec[2] != "-intArg" || argVec[3] != "12" || 
      argVec[4] != "shouldnotmatch"  ){
    retval = 1;
    goto end;
  }
  toTest->checkArgs( argVec );
  if( argVec.size() != 1 || argVec[0] != "shouldnotmatch" ){
    retval = 1;
    goto end;
  }
  if( stringArg != "someString2" || intArg != 12 ){
    retval = 1;
    goto end;
  }

 end:
  return retval;
}

int 
ArgumentParserTest::regressionTest(){
  int retval = 0;

  clutils::enableDebug();

  retval = testConstruction();
  if( retval != 0 ){
    goto end;
  }
  retval = testNoneMatch();
  if( retval != 0 ){
    goto end;
  }
  retval = testBoolMatch();
  if( retval != 0 ){
    goto end;
  }
  retval = testIntMatch();
  if( retval != 0 ){
    goto end;
  }
  retval = testStringMatch();
  if( retval != 0 ){
    goto end;
  }
  retval = testMultiple();
  if( retval != 0 ){
    goto end;
  }

 end:
  return retval;
}
