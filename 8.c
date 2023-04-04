#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h> 
#define ROW 900
#define Songlist_Max 1000
#define SWAP(x, y, t) {(t) = (x) ; (x) = (y) ; (y) = (t) ;}

typedef struct
{ 
	char Song[100];
	char Singer[100];
	int Time;
	char fav;	
	char srcData[256] ; 
} alldata;

void Search_song(alldata *s, int sum);//�̷Ӻq�W�j�M 
void Search_singersortbysong(alldata *s, int sum); //�̷Ӻq��j�M����Ӻq�W�Ƨ�
void Search_singersortbytime(alldata *s, int sum); //�̷Ӻq��j�M����Ӻq���ɶ��Ƨ�
void Search_timesortbysong(alldata *s, int sum); //�̷Ӯɶ��϶��j�M���Ӻq�W�Ƨ�
void Search_timesortbysinger(alldata *s, int sum); //�̷Ӯɶ��϶��j�M���Ӻq��Ƨ�

void quicksortsong(alldata *s, int left, int right); //�q�W�ֳt�Ƨ�(�H�q�W�Ĥ@�Ӧr���Ƨ�)
void quicksortsinger(alldata *s, int left, int right); //�q��ֳt�Ƨ�
void quicksorttime(alldata *s, int left, int right); //�q�����ױƧ�
void printlist (alldata *s, int sum); //�L�X�q��  

void Modify(alldata *AllData, int RowCount );
void Randomplay(alldata *s, int sum);
void AddFavorite(alldata *s, int sum);
void SearchFavorite();

int fooOperate(alldata *AllData, int RowCount );
int fooAdd(alldata* AllData , int  RowCount ); // �s�W
int fooDelete(alldata* AllData, int  RowCount); // ����  


char *getData( char *outName , char *inStr )
{
	char *retStr ;
	if( inStr[0] == '\"' )
	{
		retStr = strtok( inStr, "\"" );
		strcpy( outName , retStr );
		retStr += strlen( outName ) + 1 ;
	} else
	{
		retStr = strtok( inStr, "," );
		strcpy( outName , retStr );
		retStr += strlen( outName ) ;
	}

	return retStr + 1 ;

}

void getData3( char *A , char *B , char *C , const char *inStr )// AllData[RowCount].Song ,  AllData[RowCount].Singer , C , Row
{
	char ch[1024] ;
	char * str ;  
	strcpy( ch , inStr );  // ex: Pass Out,Tinie Tempah,237 
	str = ch ;
	str = getData( A , str );//Song,Row
	str = getData( B , str );//singer,row
	str = getData( C , str );//c,row
}

int main()
{

	alldata AllData[ROW]; // define ROW 900 //�q�����c  
	FILE *fp;	//�ɮ׫���  
	fp = fopen("songlist.csv", "r"); //�uŪ ����  
	if (fp == NULL) 
	{
		fprintf(stderr, "fopen() failed.\n");
		exit(EXIT_FAILURE);
	}

	char Row[80];
	char C[200] ;
	char *RowData;
	int RowCount=0,index=0;   

	while (fgets(Row, 80, fp) != NULL)
	{
		// �s���l��Ʀ�m(���Ϥ�)���̫�@��  
		strcpy(AllData[RowCount].srcData ,Row );
		// �h����Ÿ�   
		strtok( AllData[RowCount].srcData , "\n" );
		// ���� 
		getData3( AllData[RowCount].Song ,  AllData[RowCount].Singer , C , Row );
		AllData[RowCount].Time = atoi( C );//�ন�Ʀr  
		AllData[RowCount].fav='n'; 
		RowCount++;
		printf("\n");
	
	}  
	printlist(AllData,  RowCount);
    printf("Welcome to our music player system !!!\n ");
    int Function;
    do
	{
		printf("�Цb�U���ܱ��ϥΪ��\\��N�X :  \n 1.�\\��ާ@(�s�W�B�R���B�ק�)\n 2.�d��\n 3.�[�J�̷R�M��\n 4.�d�̷߳R�M��\n 5.�H������\n 6.���} : \n");
		scanf("%d",&Function);
		switch(Function)
		{
			case 1:
				RowCount=fooOperate(AllData, RowCount );
				break;
			case 2:
				Search_singersortbysong(AllData,RowCount);
				break;
			case 3:
				AddFavorite(AllData, RowCount);
				printlist(AllData,  RowCount);
				break;
			case 4:
				SearchFavorite(); 
				break;	
			case 5:
				Randomplay(AllData,RowCount);
				break;
			case 6:
				printf("���\\���}\n"); 
				break;
			default:
				printf("�Э��s��J,�õL���\\��\n");
		}	
	}while(Function != 6);
	return 0;	
}

int fooOperate(alldata *AllData, int RowCount )
{
	int Function ;
	while( 1 )
	{
		printf("�п�J�N�X (1.�s�W2.�R��3.�ק�4.���}): \n");
		scanf("%d",&Function);
		switch(Function)
		{
		case 1:
			printf("��J�n�s�W���q����T(�q�W�B�t�̡۪B�q������):\n");
			return fooAdd(AllData, RowCount ); //�I�s  
			break;
		case 2:
			printf("��J�n�R�����q�W�κt�۪�(�Ӻt�۪̩Ҧ��q���ҧR��):\n"); 
			return  fooDelete(AllData, RowCount); //�I�s  
			break;
		case 3:
			Modify(AllData , RowCount );  
			return RowCount ;  
			break;
		case 4 :
			return RowCount ;
		default :
			printf("��J���~\n" );
		}
		
	}

	return RowCount ;
 
}

int fooAdd(alldata* AllData, int  RowCount)
{
	alldata saveData ; //�o�ӬO�I�s���s���c �H�s����J����T  
	alldata* list = AllData ;//�쥻��Ƶ� list  
	FILE *fp ; //�ɮ׫���   
	char songinfo_name[100];	  //�n�ק��T���q�W 
	char songinfo_namecpy[100];
	char songinfo_new[100];		  //�ק鷺�e 
								  
	char song_time[1024] ;
	char song_modify[100];
	int mm , ss ;
	int i ;

	scanf("\n");
	gets(songinfo_new); //�}�l�ǤJ�ϥΪ̪����  
	song_time[0] = 0 ;  //����ɶ��w�]��0�A�]���D�حn�D�n��J�X���X��A�̫�A������A�������  
	sscanf( songinfo_new , "%s %s %s" , saveData.Song , saveData.Singer , song_time ); //�N��O�Nsonginfo_new�H%s %s %s���Φ��s�J�T���ܼƤ� 
	if( song_time[0] == 0 )
	{
		printf("��J���~\n" );
		return RowCount ; 
	}
	mm = ss = 0 ;
	sscanf( song_time , "%d:%d" , &mm , &ss );  //�Nsong_time�H%d:%d���Φ��s�J����ܼƤ�
	ss += mm * 60 ; //�p���`���  
	saveData.Time = ss ; //�s�_�ӡA��s 
	if(ss <= 0 ) //�p�G�ɶ�<0�A�N���X��  
	{
		printf("��J���~\n" );
		return RowCount ; //�^�ǭ쥻����ƶq�A���[1  
	}

	// �۰ʲ��� n
	saveData.fav = 'n' ;

	// �r��榡��  �N�᭱�T�ӭȨ̷ӳo�Ӯ榡�s�J�e�����ܼƤ�  ���榡�|�ŦXcsv�ɪ��n�D  �]����J���ɭԧڭ̬O��J�r�����A �o�ɭn�令csv�Q�n���榡  
	sprintf( saveData.srcData , "%s,%s,%d" , saveData.Song , saveData.Singer , saveData.Time );



	// �[�J  ��saveData�ҫ���NULL�������r�Ŧ�ƻs��AllData + RowCount�ҫ����Ʋդ�  
	memcpy( AllData + RowCount , &saveData , sizeof( saveData ));




	//��s�W���q���[��}�C�̫�@��  // ��saveData�ҫ��O����ϰ�ƻs sizeof( saveData )�Ӧr�`�� AllData + RowCount�ҫ��O����ϰ� 
	RowCount ++ ; //�T�O��ƶq�[1�C�A��ܺq���q�h�@��  

	// �s��  
	fp = fopen("songlist.csv", "w"); //�s�ɡA�g�J���  
	list = AllData ; // �w�����Y  
	//�s�ɶ��K�T�{ ���Y�ӹL   
	for( i = 0 ; i < RowCount ; ++i , ++list ) // �] RowCount ���A�C���������з| + 1
	{
		// �s��  
		sprintf( song_modify , "%s\n" , list->srcData ); //��᭱���r��[�@�Ӵ���Ÿ��ᵹsongmodify  
		//sprintf �r��榡��  
		fwrite( song_modify , strlen( song_modify ) , 1 , fp );  
	}

	printf("�s�W���\\n");
	fclose(fp);
	//
	return RowCount  ;
}
  
int fooDelete(alldata* AllData, int  RowCount)
{
	//alldata saveData ; //�o�ӬO�I�s���s���c �H�s����J����T 
	alldata* list = AllData ; //�쥻��Ƶ� list   
	FILE *fp ;
	char songinfo_name[100];	  //�n�ק��T���q�W 
	char songinfo_namecpy[100];
	char songinfo_new[100];		  //�ק鷺�e 

	char song_time[1024] ;
	char song_modify[100];
	int mm , ss ;
	int i ;
	int k ;
	int count ;

	scanf("\n"); // �D�حn�D�O"��J�n�R�����q�W�κt�۪�(�Ӻt�۪̩Ҧ��q���ҧR��):\n"
	gets(songinfo_name);

	// ��  
	count = 0 ;
	list = AllData + RowCount - 1 ; //�q�᭱�}�l��  
	for( i = RowCount - 1 ; i >= 0 ; i-- , list --  ){//strcmp �r�Ŧ���  strcmp(str1,str2)�A�Ystr1=str2�A�h��^�s�F�Ystr1<str2�A�h��^�t�ơF�Ystr1>str2�A�h��^����
		if(( strcmp( list->Song , songinfo_name ) == 0 )|| ( strcmp( list->Singer , songinfo_name ) == 0 )) //�Ystr1=str2 // || => �άO //�Ystr1=str2 
		{
			count ++ ; //�N�����ۦP  �A�̫�i�H�ݨ쩳�R�F�h�֭� 
			// ���e�h  
			RowCount -- ;  //���۵����� �A���ּƶq�N-1 
			for( k = i ; k < RowCount ; ++k )
			{
				memcpy( AllData + k , AllData + k + 1 , sizeof( alldata )); // ��AllData + k + 1�ҫ��O����ϰ�ƻs sizeof( alldata )�Ӧr�`�� AllData + k�ҫ��O����ϰ� 
			}  //�]�N�O����ۦP�B�R�� �ѤU�@���л\��  
		}
	}   
	
	//
	if( count == 0 )
	{
		printf( "�䤣��ۦP���q���A���t�Τ�����R���\\��\n" );
		return RowCount ; //�S���A���ּƶq�N����  
	}
	// �s��  
	fp = fopen("songlist.csv", "w");
	list = AllData ; 
	for( i = 0 ; i < RowCount ; ++i , ++list ) 
	{
		// �s�� �N�O���s��s  
		sprintf( song_modify , "%s\n" , list->srcData );
		fwrite( song_modify , strlen( song_modify ) , 1 , fp );
	}

	printf("���������A�@�����F%d��\n" , count );
	fclose(fp);

	return RowCount ;
}
 
void Modify(alldata* AllData , int  RowCount )
{
	alldata saveData ;
	alldata* list = AllData ;
	FILE *fp ;
	char songinfo_name[100];	    
	char songinfo_new[100];		   

	char song_time[1024] ;
	char song_modify[100];
	int mm , ss ;
	int i ;

	printf("��J�n�ק諸�q�W:\n");
	scanf("\n");
	gets(songinfo_name); //Ū���ϥΪ̪��q�W  
  
	for( i = 0 ; i < RowCount ; ++i , list++ )  
		if( strcmp( list->Song , songinfo_name ) == 0 )  
			break ;   
	if( ROW == i )  
	{
		printf("�䤣��o�q�W\n" );
		return ; 
	}

	printf("�ק鷺�e:\n");
	scanf("\n");
	gets(songinfo_new);   
	song_time[0] = 0 ;
	sscanf( songinfo_new , "%s %s %s" , saveData.Song , saveData.Singer , song_time ); //�Nsonginfo_new�H%s %s %s���Φ��s�J�T���ܼƤ� 
	if( song_time[0] == 0 )
	{
		printf("��J���~\n" );
		return ; 
	}
	mm = ss = 0 ;   
	sscanf( song_time , "%d:%d" , &mm , &ss ); //�j��q�r���ഫ���Ʀr��  
	ss += mm * 60 ;  
	saveData.Time = ss ;  
	if(ss <= 0 )
	{
		printf("��J���~\n" );
		return ;
	}

	// �}�l��Ʈ榡��
	sprintf( saveData.srcData , "%s,%s,%d" , saveData.Song , saveData.Singer , saveData.Time );
	memcpy( list , &saveData , sizeof(saveData));

	fp = fopen("songlist.csv", "w");
	list = AllData ;
	for( i = 0 ; i < RowCount ; ++i , ++list )
	{
		// �s��  �N�O���s��s�@�M 
		sprintf( song_modify , "%s\n" , list->srcData );
		fwrite( song_modify , strlen( song_modify ) , 1 , fp );
	}
	
	printf("�ק令�\\\n");
	fclose(fp);
}

void Search_song(alldata *s, int sum)
{
	int i;
	int select = 0;
	char songname[60];
	alldata selectlist[sum];
	printf("�п�J�q�W :\n");
	scanf("\n");
	gets(songname);
	for(i = 0 ; i < sum ; i++)
	{
		if(strcmp(songname,s[i].Song) == 0)
		{
			strcpy(selectlist[select].Song, s[i].Song);
			strcpy(selectlist[select].Singer, s[i].Singer);
			selectlist[select].Time = s[i].Time;
			selectlist[select].fav=s[i].fav;
			select++;
		}
	}

	if(select == 0)
	{
		return;
	}
	else
	{
		printlist(selectlist, select);
	}
}

void Search_singersortbysong(alldata *s, int sum)
{
	int i;
	int select = 0;
	char singername[60];
	alldata selectlist[sum];
	printf("�п�J�t�۪� :\n");
	scanf("\n");
	gets(singername);
	for(i = 0 ; i < sum ; i++)
	{
		if(strcmp(singername,s[i].Singer) == 0)
		{
			strcpy(selectlist[select].Song, s[i].Song);
			strcpy(selectlist[select].Singer, s[i].Singer); 
			selectlist[select].Time = s[i].Time;
			selectlist[select].fav=s[i].fav;
			select++;
		}
	}
	if(select == 0)
	{
		return;
	}
	else
	{
		quicksortsong(selectlist, 0, select-1);
		printlist(selectlist, select);
	}
}

void Search_singersortbytime(alldata *s, int sum)
{
	int i;
	int select = 0;
	char singername[60];
	alldata selectlist[sum];
	printf("�п�J�t�۪� :\n");
	scanf("\n");
	gets(singername);
	for(i = 0 ; i < sum ; i++)
	{
		if(strcmp(singername,s[i].Singer) == 0)
		{
			strcpy(selectlist[select].Song, s[i].Song);
			strcpy(selectlist[select].Singer, s[i].Singer);
			selectlist[select].Time = s[i].Time;
			selectlist[select].fav=s[i].fav;
			select++;
		}
	}

	if(select == 0)
	{
		return;
	}
	else
	{
		quicksorttime(selectlist, 0, select-1);
		printlist(selectlist, select);
	}
}

void Search_timesortbysong(alldata *s, int sum)
{
	int i, t1, t2;
	int select = 0;
	char songtime[60];
	alldata selectlist[sum];
	printf("�п�J�ɶ��Ϭq :\n");
	scanf("%d %d", &t1, &t2);
	for(i = 0 ; i < sum ; i++)
	{
		if(s[i].Time > t1 && s[i].Time < t2)
		{
			strcpy(selectlist[select].Song, s[i].Song);
			strcpy(selectlist[select].Singer, s[i].Singer);
			selectlist[select].Time = s[i].Time;
			selectlist[select].fav=s[i].fav;
			select++;
		}
	}

	if(select == 0)
	{
		return;
	}
	else
	{
		quicksortsong(selectlist, 0, select-1);
		printlist(selectlist, select);
	}
}

void Search_timesortbysinger(alldata *s, int sum)
{
	int i, t1, t2;
	int select = 0;
	char songtime[60];
	alldata selectlist[sum];
	printf("�п�J�ɶ��Ϭq :\n");
	scanf("%d %d", &t1, &t2);
	for(i = 0 ; i < sum ; i++)
	{
		if(s[i].Time > t1 && s[i].Time < t2)
		{
			strcpy(selectlist[select].Song, s[i].Song);
			strcpy(selectlist[select].Singer, s[i].Singer);
			selectlist[select].Time = s[i].Time;
			selectlist[select].fav=s[i].fav;
			select++;
		}
	}

	if(select == 0)
	{
		return;
	}
	else
	{
		quicksortsinger(selectlist, 0, select-1);
		printlist(selectlist, select);
	}
}

void Randomplay(alldata *s, int sum)
{
	int min,sec;
	srand(time(0));
	int i,j,randarr[sum];
	for(i = 0 ; i < sum ; i++)
	{
		do{
			randarr[i] = rand() % sum;
			for(j = 0 ; j < i ; j++)
			{
				if(randarr[i] == randarr[j])
				{
					break;
				}
			}
		} while(j != i);
		min = s[randarr[i]].Time / 60;
		sec = s[randarr[i]].Time % 60;
		if(sec >= 10)
			printf("Song[%3d]: Name:%-30s,Singer:%-30s,Time: %d : %d,fav: %c\n", randarr[i]+1, s[randarr[i]].Song, s[randarr[i]].Singer, min ,sec , s[randarr[i]].fav);
		else
			printf("Song[%3d]: Name:%-30s,Singer:%-30s,Time: %d : 0%d,fav: %c\n", randarr[i]+1, s[randarr[i]].Song, s[randarr[i]].Singer, min ,sec , s[randarr[i]].fav);
	}
}

void quicksortsong(alldata *s, int left, int right)
{
	int i, j;
	char pivot;
	alldata t;
	if (left < right)
	{
		i = left;
		j = right + 1;
		pivot = s[left].Song[0];
		do
		{
			do { i++; } while (s[i].Song[0] < pivot);
			do { j--; } while (s[j].Song[0] > pivot);
			if (i < j)
			{
				SWAP(s[i], s[j], t);
			}
		} while (i < j);

		SWAP(s[left], s[j], t);
		quicksortsong(s, left, j - 1);
		quicksortsong(s, j + 1, right);
	}
}

void quicksortsinger(alldata *s, int left, int right)
{
	int i, j;
	char pivot[70];
	alldata t;
	if (left < right)
	{
		i = left;
		j = right + 1;
		strcpy(pivot, s[left].Singer);
		do
		{
			do { i++; } while (strcmp(s[i].Singer , pivot) == -1);
			do { j--; } while (strcmp(s[j].Singer , pivot) == 1);
			if (i < j)
			{
				SWAP(s[i], s[j], t);
			}
		} while (i < j);

		SWAP(s[left], s[j], t);
		quicksortsinger(s, left, j - 1);
		quicksortsinger(s, j + 1, right);
	}
}

void quicksorttime(alldata *s, int left, int right)
{
	int i, j, pivot;
	alldata t;
	if (left < right)
	{
		i = left;
		j = right + 1;
		pivot = s[left].Time;
		do
		{
			do { i++; } while (s[i].Time < pivot);
			do { j--; } while (s[j].Time > pivot);
			if (i < j)
			{
				SWAP(s[i], s[j], t);
			}
		} while (i < j);

		SWAP(s[left], s[j], t);
		quicksorttime(s, left, j - 1);
		quicksorttime(s, j + 1, right);
	}
}

void printlist (alldata *s, int sum)
{
	int i, min, sec;
	for( i = 0 ; i < sum ; i++)
	{
		min = s[i].Time / 60;
		sec = s[i].Time % 60;
		
		if(sec >= 10)
			printf("Song[%3d]: Name:%-30s,Singer:%-30s,Time: %d : %d, fav: %c\n", i+1, s[i].Song, s[i].Singer, min,sec,s[i].fav);
		else
			printf("Song[%3d]: Name:%-30s,Singer:%-30s,Time: %d : 0%d, fav: %c\n", i+1, s[i].Song, s[i].Singer, min, sec,s[i].fav);
	}
}

void AddFavorite(alldata *s, int sum)
{
	char song[100];
	char favo[100];
	char time[5];
	int i;
	
	alldata favolist;
	printf("�п�J�n�[�J�̷R�M�檺�q��:");
	scanf("\n");
	gets(song);
	for(i = 0 ; i < sum ; i++)
	{
		if(strcmp(song, s[i].Song) == 0)
		{
			strcpy(favolist.Song, s[i].Song);
			strcpy(favolist.Singer, s[i].Singer);
			favolist.Time = s[i].Time;
			s[i].fav='Y';
		}
	}
	printf("�п�J�̷R�M��W:");
	scanf("%s", favo); 
	strcat(favo, ".csv");
	
	FILE *fp;	
	fp = fopen(favo, "a+");
    if(fp != NULL)
	{
		fputs(favolist.Song,fp);
		fprintf(fp,",");
		fputs(favolist.Singer,fp);
		fprintf(fp,",");
		fputs(itoa(favolist.Time, time, 10),fp);
		fprintf(fp,"\n");	
	}       
	else 
	{
		printf("File Error !\n");
	}
	fclose(fp);
	printf("%s�w�[�J�̷R�M��I\n\n", song, favo);
	
}

void SearchFavorite()
{
	char favo[100];
	alldata favodata[ROW];
	printf("�п�J�̷R�M��W:");
	scanf("%s", favo);
	strcat(favo, ".csv");
	
	FILE *fp;
	fp = fopen(favo, "r");
    if (fp == NULL) 
	{
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }

    char Row[80];
    char *RowData;
    int RowCount=0,index=0;
    
    while (fgets(Row, 80, fp) != NULL)
	{
		RowData = strtok(Row, ",");
		index=0;
		while(RowData!=NULL)
		{
			if(index==0)
			{
				strcpy(favodata[RowCount].Song,RowData);
            	index++;
			}
			else if(index==1)
			{
                strcpy(favodata[RowCount].Singer,RowData);
                index++;
            }
            else if(index==2)
			{
				favodata[RowCount].Time = atoi(RowData);
			}
			RowData = strtok(NULL, ",");
		}
		RowCount++;
    }
	printlist(favodata, RowCount);
	printf("\n");
}
