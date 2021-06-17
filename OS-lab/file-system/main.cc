#include "file_system.h"

Disk disk("./disk");

int main()
{
    DataManager dmanager(disk);
    IndexManager imanager(disk);
    UserManager umanager(disk);

    FileSystem fs(disk, dmanager, imanager, umanager);

    printf("\n\n\n");

    fs.Run();
    return 0;
}
/*
1     1      32       6        344       16000
0     1     2-33     34-39    40-383   384-16383
super usr   dmap     imap     inode      data

*/