#include "HW4-2.h"

int main()
{
    FILES* command = new FILES("./LPS_command.txt");

    for (int i = 0; i < command->num; i++) {
        BLOCK* block = new BLOCK(string("./") + command->filelist[i][0]);

        block->get_all_LPS();
        block->write(string("./")+command->filelist[i][1]);

        delete block;
    }

    delete command;

    return 0;
}

