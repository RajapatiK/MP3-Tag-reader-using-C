#ifndef EDIT_H
#define EDIT_H

#include "types.h"

//structure
typedef struct _editmp3file
{
    FILE *fptr_mp3;
    FILE *fptr_temp;

    char tag[4];
    char charsize[4];
    char flag[3];
    int size;
    char *temp;

}Editmp3file;


//function declarations
//checking operation type
OperationType check_operation_type(char *argv[]);

//checking all CLA
Status check_edit(char *argv[],Editmp3file *edit);

//starts view
Status do_edit(char *argv[],Editmp3file *edit);

//swap little to big endian
int swap_edit(int x);

Status createfile_and_skipheader(char *argv[],Editmp3file *edit);

Status skip_content(char *argv[],Editmp3file *edit);

Status editcontent(char *argv[],Editmp3file *edit);

Status edit_title(char *arv[],Editmp3file *edit);

Status edit_artist(char *argv[],Editmp3file *edit);

Status edit_album(char *argv[],Editmp3file *edit);

Status edit_year(char *argv[],Editmp3file *edit);

Status edit_content(char *argv[],Editmp3file *edit);

Status edit_comment(char *argv[], Editmp3file *edit);

#endif
