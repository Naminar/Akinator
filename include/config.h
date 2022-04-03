
#ifndef AKIN_CONFIG_

#define AKIN_CONFIG_

#include <stdlib.h>
#include <stdio.h>

#define speach_setting "espeak -v mb-en1 \""

//===============================================

const size_t INDENT_STEP    =  4,
             WORLD_LENGTH   = 20;

const char *const CONSOLE       = "stdout",
           *const SECRET_MODE   = "secret";

//===============================================

void scanf_string       (FILE* in_file, char** string);
void voice_assistant    (const char *const ex_phrase, const char *const add_phrase = nullptr);
void questions_assistant(const char *const ex_phrase, const char *const add_phrase);

#endif // AKIN_CONFIG_
