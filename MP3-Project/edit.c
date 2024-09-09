#include <stdio.h>
#include "edit.h"
#include "types.h"
#include <string.h>
#include <stdlib.h>
//function definitions
Status check_edit(char *argv[],Editmp3file *edit)
{
    if(argv[2]!=NULL)
    {
	//checking .mp3 extention
	if(strstr(argv[4],".mp3") != NULL)
	{
	    //open the mp3file in read mode
	    edit->fptr_mp3=fopen(argv[4],"r+");
	    if(edit->fptr_mp3 == NULL)
	    {
		printf("File not exist\n");
		return e_failure;
	    }
	    //chceking the ID3
	    char ID3[3];
	    fread(ID3,3,1,edit->fptr_mp3);
	    ID3[3]='\0';
	    if(strcmp(ID3,"ID3")==0)
	    {
		//checking version
		char version[2];
		fread(version,2,1,edit->fptr_mp3);
		version[2]='\0';
		if(version[0]==3 && version[1]==0)
		{
		    printf("\n—————-———-——-—SELECTED EDIT OPTION—-—-——————-——-\n");
		    if(do_edit(argv,edit)==e_success)
		    {

			return e_success;
		    }
		    else
		    {
			printf("View error\n");
			return e_failure;
		    }
		}
		else
		{
		    printf("Version error\n");
		    return e_failure;
		}
	    }
	    else
	    {
		printf("Invalid extention\n");
		return e_failure;
	    }
	}
	else
	{
	    printf("Mp3file not found\n");
	    return e_failure;
	}
    }
    else
    {
	printf("Mp3file not passed\n");
	return e_failure;
    }
}


Status do_edit(char *argv[],Editmp3file *edit)
{
    if(strcmp(argv[2],"-t")==0)
    {
	edit_title(argv,edit);
	return e_success;
    }
    else if(strcmp(argv[2],"-a")==0)
    {
	edit_artist(argv,edit);
	return e_success;
    }
    else if(strcmp(argv[2],"-A")==0)
    {
	edit_album(argv,edit);
	return e_success;
    }
    else if(strcmp(argv[2],"-y")==0)
    {
	edit_year(argv,edit);
	return e_success;
    }
    else if(strcmp(argv[2],"-m")==0)
    {
	edit_content(argv,edit);
	return e_success;
    }
    else if(strcmp(argv[2],"-c")==0)
    {
	edit_comment(argv,edit);
	return e_success;
    }
    else
    {
	printf("Enter a valid option\n");
	return e_failure;
    }
}

Status createfile_and_skipheader(char *argv[],Editmp3file *edit)
{
    //creating a temp file
    edit->fptr_temp=fopen("file_temp.mp3","w");
    if(edit->fptr_temp==NULL)
    {
	printf("File not exist\n");
	return e_failure;
    }
    rewind(edit->fptr_mp3);
    char buf[10];
    fread(buf,10,1,edit->fptr_mp3);
    fwrite(buf,10,1,edit->fptr_temp);
    return e_success;
}

Status skip_content(char *argv[],Editmp3file *edit)
{

    fread(edit->tag,4,1,edit->fptr_mp3);
    fwrite(edit->tag,4,1,edit->fptr_temp);

    int x;
    fread(&x,4,1,edit->fptr_mp3);
    edit->size=swap_edit(x);
    fwrite(&x,4,1,edit->fptr_temp);

    fread(edit->flag,3,1,edit->fptr_mp3);
    fwrite(edit->flag,3,1,edit->fptr_temp);

    char cont[edit->size];
    fread(cont,edit->size-1,1,edit->fptr_mp3);
    fwrite(cont,edit->size-1,1,edit->fptr_temp);
    return e_success;
}

Status editcontent(char *argv[],Editmp3file *edit)
{
    fwrite(edit->tag,4,1,edit->fptr_temp);
    //read size
    int x;
    fread(&x,4,1,edit->fptr_mp3);

    //write the new size
    edit->temp=argv[3];
    edit->size=strlen(edit->temp);
    int newsize=swap_edit(edit->size+1);
    fwrite(&newsize,4,1,edit->fptr_temp);

    //read and write flag
    fread(edit->flag,3,1,edit->fptr_mp3);
    fwrite(edit->flag,3,1,edit->fptr_temp);

    //write the new content
    fwrite(edit->temp,edit->size,1,edit->fptr_temp);

    //skip the old content
    edit->size=swap_edit(x);
    fseek(edit->fptr_mp3,(edit->size-1),SEEK_CUR);

    //read and write remaining content
    char ch;
    while(fread(&ch,1,1,edit->fptr_mp3))
    {
	fwrite(&ch,1,1,edit->fptr_temp);
    }

    //close both files
    fclose(edit->fptr_mp3);
    fclose(edit->fptr_temp);

    //remove old file and replace with new file
    remove(argv[4]);
    rename("file_temp.mp3", argv[4]);

    return e_success;

}

//TITLE
Status edit_title(char *argv[],Editmp3file *edit)
{
    printf("\n———————--—---———CHANGE THE TITLE————---———-———-\n");
    printf("\n");
    createfile_and_skipheader(argv,edit);

    //raeading and writing title TIT2
    fread(edit->tag,4,1,edit->fptr_mp3);
    fwrite(edit->tag,4,1,edit->fptr_temp);
    edit->tag[4]='\0';

    // check TIT2
    if(strcmp(edit->tag,"TIT2")==0)
    {
	//read size
	int x;
	fread(&x,4,1,edit->fptr_mp3);

	//write the new size
	edit->temp=argv[3];
	edit->size=strlen(edit->temp);
	int newsize=swap_edit(edit->size+1);
	fwrite(&newsize,4,1,edit->fptr_temp);

	//read and write flag
	fread(edit->flag,3,1,edit->fptr_mp3);
	fwrite(edit->flag,3,1,edit->fptr_temp);

	//write the new content
	fwrite(edit->temp,edit->size,1,edit->fptr_temp);

	//skip the old content
	edit->size=swap_edit(x);
	fseek(edit->fptr_mp3,(edit->size-1),SEEK_CUR);

	//read and write remaining content
	char ch;
	while(fread(&ch,1,1,edit->fptr_mp3))
	{
	    fwrite(&ch,1,1,edit->fptr_temp);
	}

	//close both files
	fclose(edit->fptr_mp3);
	fclose(edit->fptr_temp);

	//remove old file and replace with new file
	remove(argv[4]);
	rename("file_temp.mp3", argv[4]);

	printf("TITLE         :  %s\n",argv[3]);

	printf("\n———————————TITLE CHANGED SUCCESSFULLY—————————-\n");
	return e_success;

    }
    else
	return e_failure;
}

Status edit_artist(char *argv[],Editmp3file *edit)
{
    printf("\n———————--—---———CHANGE THE ARTIST————----——————-\n");
    printf("\n");
    createfile_and_skipheader(argv,edit);

    skip_content(argv,edit);

    fread(edit->tag,4,1,edit->fptr_mp3);
    // check TIT2
    if(strcmp(edit->tag,"TPE1")==0)
    {

	editcontent(argv,edit);
	printf("ARTIST         :  %s\n",argv[3]);
	printf("\n———————————ARTIST CHANGED SUCCESSFULLY—————————-\n");
	return e_success;

    }
    else
	return e_failure;
}


Status edit_album(char *argv[],Editmp3file *edit)
{
    printf("\n———————--—---———CHANGE THE ALBUM————----———-——-\n");
    printf("\n");
    createfile_and_skipheader(argv,edit);
    skip_content(argv,edit);
    skip_content(argv,edit);

    fread(edit->tag,4,1,edit->fptr_mp3);
    // check TALB
    if(strcmp(edit->tag,"TALB")==0)
    {

	editcontent(argv,edit);
	printf("ALBUM         :  %s\n",argv[3]);
	printf("\n———————————ALBUM CHANGED SUCCESSFULLY—————————-\n");
	return e_success;

    }
    else
	return e_failure;

}

Status edit_year(char *argv[],Editmp3file *edit)
{
    printf("\n———————--—---———CHANGE THE YEAR————----——-———-\n");
    printf("\n");
    createfile_and_skipheader(argv,edit);
    skip_content(argv,edit);
    skip_content(argv,edit);
    skip_content(argv,edit);

    fread(edit->tag,4,1,edit->fptr_mp3);
    // check TALB
    if(strcmp(edit->tag,"TYER")==0)
    {

	editcontent(argv,edit);
	printf("YEAR         :  %s\n",argv[3]);
	printf("\n———————————YEAR CHANGED SUCCESSFULLY—————————-\n");
	return e_success;

    }
    else
	return e_failure;

}

Status edit_content(char *argv[],Editmp3file *edit)
{
    printf("\n———————--—---———CHANGE THE CONTENT————----——-———-\n");
    printf("\n");
    createfile_and_skipheader(argv,edit);
    skip_content(argv,edit);
    skip_content(argv,edit);
    skip_content(argv,edit);
    skip_content(argv,edit);

    fread(edit->tag,4,1,edit->fptr_mp3);
    // check TALB
    if(strcmp(edit->tag,"TCON")==0)
    {

	editcontent(argv,edit);
	printf("CONTENT         :  %s\n",argv[3]);
	printf("\n———————————CONTENT CHANGED SUCCESSFULLY—————————-\n");
	return e_success;

    }
    return e_success;
}

Status edit_comment(char *argv[],Editmp3file *edit)
{
    printf("\n———————--—---———CHANGE THE COMMENT————----——————-\n");
    printf("\n");
    createfile_and_skipheader(argv,edit);
    skip_content(argv,edit);
    skip_content(argv,edit);
    skip_content(argv,edit);
    skip_content(argv,edit);
    skip_content(argv,edit);

    fread(edit->tag,4,1,edit->fptr_mp3);
    // check TALB
    if(strcmp(edit->tag,"COMM")==0)
    {

	editcontent(argv,edit);
	printf("COMMENT         :  %s\n",argv[3]);
	printf("\n———————————COMMENT CHANGED SUCCESSFULLY—————————-\n");
	return e_success;

    }
    return e_success;
}

int swap_edit(int x)
{
    void *ptr=&x;
    for(int i=0;i<4/2;i++)
    {
	char temp=*((char*)ptr+i);
	*((char*)ptr+i)=*((char*)ptr+4-i-1);
	*((char*)ptr+4-i-1)=temp;
    }
    return x;
}
