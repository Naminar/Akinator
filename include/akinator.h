
#ifndef AKINATOR_

#define AKINATOR_

#include <iostream>
#include <string>
#include <windows.h>
#include "config.h"
#include "tree.h"

//===============================================

void akinator           (void);
void interectiv         (Node* root);
void fix_mistake        (Node* wrong_node);
void get_object_inform  (Node* node);

#endif // AKINATOR_
