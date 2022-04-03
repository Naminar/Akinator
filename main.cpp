
#define  TX_USE_SPEAK

#include "include/TXLib.h"

#include "include/config.h"
#include "include/akinator.h"
#include "include/dump.h"
#include "include/database.h"
#include "Stack/stack.h"
#include "include/tree.h"

#include "source/akinatorCPP.h"
#include "source/dumpCPP.h"
#include "source/databaseCPP.h"
#include "Stack/stackCPP.h"
#include "source/treeCPP.h"


int main()
{
    txPlaySound("sound/tech.wav", SND_LOOP);

    akinator();

    txPlaySound(NULL);

    return 0;
}
