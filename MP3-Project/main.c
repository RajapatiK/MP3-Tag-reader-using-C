#include <stdio.h>
#include "view.h"
#include "edit.h"
#include "types.h"
#include <string.h>

int main(int argc,char *argv[])
{
    if(argv[1]==NULL)
    {
        printf("ERROR: ./a.out: INVALID ARGUMENTS\nUSAGE:\nTo view please pass like: ./a.out -v mp3filename\nTo edit please pass like : ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\nTo get help pass like : ./a.out --help\n");
    }
    else
    {

        //checking it is encoding '-e'
        if(check_operation_type(argv)==v_view)
        {

            //allocate memeory of structure
            Viewmp3file view;
            //check ID3
            if(check_view(argv,&view) == e_success)
            {
                 printf("\n———————————DETAILS DISPLAYED SUCCESSFULLY—————————-\n");
            }
            else
                printf("Check unsuccessfull\n");
        }
        else if(check_operation_type(argv)==e_edit)
        {

                 printf("\n———————---————SELECTED EDIT DETAILS————--——————-\n");

            //allocate memeory of structure
            Editmp3file edit;
            //check ID3
            if(check_edit(argv,&edit) == e_success)
            {
                 printf("\n————————-----———EDIT SUCCESSFULL———-----———————-\n");
            }
            else
                printf("Check unsuccessfull\n");
        }
        else if(check_operation_type(argv)==help)
        {
            printf("\n———————————----------HELP MENU-----------——————————-\n");
            printf("\n");
            printf("1. -v -> to view mp3 file contents\n2. e -> to edit mp3 file contents\n\t2.1. t -> to edit song title\n\t2.2. -a -> to edit artist name\n\t2.3. -A -> to edit album name\n\t2.4. -y -> to edit year\n\t2.5. -m -> to edit content\n\t2.1. c to edit comment\n");
            printf("\n");
            printf("\n----------------------------------------------------\n");

        }
        else
            printf("Enter -v or -e\n");

    }
    return 0;
}

OperationType check_operation_type(char *argv[])
{
 if(strcmp(argv[1],"-v")==0)
        return v_view;
    else if(strcmp(argv[1],"-e")==0)
        return e_edit;
    else if(strcmp(argv[1],"--help")==0)
        return help;
    else
        return e_unsupported;
}





