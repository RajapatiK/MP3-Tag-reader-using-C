#include <stdio.h>
#include "view.h"
#include "types.h"
#include <string.h>
#include <stdlib.h>
//function definitions
Status check_view(char *argv[],Viewmp3file *view)
{
    if(argv[2]!=NULL)
    {
	//checking .mp3 extention
	if(strstr(argv[2],".mp3") != NULL)
	{
	    //open the mp3file in read mode
	    view->fptr_mp3=fopen(argv[2],"r");
	    if(view->fptr_mp3 == NULL)
	    {
		printf("File not exist\n");
		return e_failure;
	    }
	    //chceking the ID3
	    char ID3[3];
	    fread(ID3,3,1,view->fptr_mp3);
	    ID3[3]='\0';
	    if(strcmp(ID3,"ID3")==0)
	    {
		//checking version
		char version[2];
		fread(version,2,1,view->fptr_mp3);
		version[2]='\0';
		if(version[0]==3 && version[1]==0)
		{
		    if(do_view(view) == e_success)
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

Status do_view(Viewmp3file *view)
{
    printf("———————--———-——SELECTED VIEW DETAILS———---—————————\n\n");
    printf("————————MP3 TAG READER AND EDITOR FOR ID3v2————————\n\n");
    rewind(view->fptr_mp3);
    fseek(view->fptr_mp3,10,SEEK_SET);
    //reading title TIT2
    fread(view->tag,4,1,view->fptr_mp3);
    view->tag[4]='\0';
    if(strcmp(view->tag,"TIT2")==0)
    {
	int x;
	fread(&x,4,1,view->fptr_mp3);
	view->size=swap(x);
	fseek(view->fptr_mp3,3,SEEK_CUR);
	char content[view->size];
	fread(content,(view->size-1),1,view->fptr_mp3);
	content[view->size-1]='\0';
	printf("TITLE            :           %s\n", content);
    }
    //reading artist name TPE1
    fread(view->tag,4,1,view->fptr_mp3);
    view->tag[4]='\0';
    if(strcmp(view->tag,"TPE1")==0)
    {
	int x;
	fread(&x,4,1,view->fptr_mp3);
	view->size=swap(x);
	fseek(view->fptr_mp3,3,SEEK_CUR);
	char content[view->size];
	fread(content,(view->size-1),1,view->fptr_mp3);
	content[view->size-1]='\0';
	printf("ARTIST           :           %s\n", content);
    }
    //reading album name TALB
    fread(view->tag,4,1,view->fptr_mp3);
    view->tag[4]='\0';
    if(strcmp(view->tag,"TALB")==0)
    {
	int x;
	fread(&x,4,1,view->fptr_mp3);
	view->size=swap(x);
	fseek(view->fptr_mp3,3,SEEK_CUR);
	char content[view->size];
	fread(content,(view->size-1),1,view->fptr_mp3);
	content[view->size-1]='\0';
	printf("ALBUM            :           %s\n", content);
    }

    //reading year TYER
    fread(view->tag,4,1,view->fptr_mp3);
    view->tag[4]='\0';
    if(strcmp(view->tag,"TYER")==0)
    {
	int x;
	fread(&x,4,1,view->fptr_mp3);
	view->size=swap(x);
	fseek(view->fptr_mp3,3,SEEK_CUR);
	char content[view->size];
	fread(content,(view->size-1),1,view->fptr_mp3);
	content[view->size-1]='\0';
	printf("YEAR             :           %s\n", content);
    }

    //reading content type TCON
    fread(view->tag,4,1,view->fptr_mp3);
    view->tag[4]='\0';
    if(strcmp(view->tag,"TCON")==0)
    {
	int x;
	fread(&x,4,1,view->fptr_mp3);
	view->size=swap(x);
	fseek(view->fptr_mp3,3,SEEK_CUR);
	char content[view->size];
	fread(content,(view->size-1),1,view->fptr_mp3);
	content[view->size-1]='\0';
	printf("MUSIC            :           %s\n", content);
    }
    //reading composer TCOM
    fread(view->tag,4,1,view->fptr_mp3);
    view->tag[4]='\0';
    if(strcmp(view->tag,"COMM")==0)
    {
	int x;
	fread(&x,4,1,view->fptr_mp3);
	view->size=swap(x);
	fseek(view->fptr_mp3,3,SEEK_CUR);
	char content[view->size];
	fread(content,(view->size-1),1,view->fptr_mp3);
	content[view->size-1]='\0';
	printf("COMMENT          :           %s\n", content);

    }
    return e_success;
}

int swap(int x)
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
