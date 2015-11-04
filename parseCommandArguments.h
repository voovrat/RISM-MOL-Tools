#ifndef parseCommandArguments_h
#define parseCommandArguments_h

class Parameters;

void parseCommandArguments(
int argc,  // in
char *argv[],   //in
Parameters *params, //in/out
char *paramFile, //out
char *additionalParams, //out
char *Error, // aux
char *prefix //out
);

#endif
