#ifndef VIEW_H
#define VIEW_H

#include "types.h"

//structure
typedef struct _viewmp3file
{
    FILE *fptr_mp3;

    char tag[4];
    int size;

} Viewmp3file;


//function declarations
//checking operation type
OperationType check_operation_type(char *argv[]);

//checking all CLA
Status check_view(char *argv[],Viewmp3file *view);

//starts view
Status do_view(Viewmp3file *view);

//swap little to big endian
int swap(int x);
#endif
