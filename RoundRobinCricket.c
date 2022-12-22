#include <stdio.h>
#include<string.h>
#include<math.h>
#define size 50

struct player
{
    int player_id;
    int match_id;
    int previous_total_score;
    int previous_avg;
    int previous_total_wickets;
    int previous_wicket_avg;
    int total_runs_in_last_five_matches;
    int total_wickets_in_last_five_matches; 
    int century;
    int present_match_score;
    int present_match_wicket;
    char player_role[11];
    char out_or_not_out[7];
    int matches_played;
};

struct team
{
    char team_name[50];
    int player_id[15];
    char player_name[15][100];
    char player_role[15][11];
    int mom_counter[15];
    int points;
};

struct match_played
{
    int match_id; 
    char team1[50]; 
    char team2[50];
    int higest_run; 
    char man_of_the_match[100]; 
    int wicket_taken_by_pacer;
    char match_result[50];
};

struct player update( struct player player_details[], int array[] , char O_NO[] , int index )
{
	struct player details;
	int i=0,status=0;
	details.player_id = array[0];
	details.match_id = array[1];
	details.present_match_score = array[3];
	details.present_match_wicket = array[4];
	for(i=index-1;i>=0 && status==0;i--)
	{
		if(details.player_id==player_details[i].player_id)
		{
			status=1;
			details.matches_played=player_details[i].matches_played+1;
			details.century=player_details[i].century+array[2];
			strcpy(details.player_role,player_details[i].player_role);
			details.previous_total_score = player_details[i].previous_total_score+player_details[i].present_match_score;
			details.previous_total_wickets = player_details[i].previous_total_wickets+player_details[i].present_match_wicket;
			if (player_details[i].matches_played!=0)
			{
				details.previous_avg=details.previous_total_score/player_details[i].matches_played;
				details.previous_wicket_avg=details.previous_total_wickets/player_details[i].matches_played;
			}
			else
			{
				details.previous_avg=0;
				details.previous_wicket_avg=0;
			}
			details.total_runs_in_last_five_matches = player_details[i].total_runs_in_last_five_matches+player_details[i].present_match_score;
			details.total_wickets_in_last_five_matches = player_details[i].total_wickets_in_last_five_matches+player_details[i].present_match_wicket;
			if(player_details[i].matches_played>5)
			{
				int check=0,j;
				for(j=i-1;check==0;j--)
				{
					if(details.player_id==player_details[j].player_id && player_details[i].matches_played-player_details[j].matches_played==5)
					{
						details.total_runs_in_last_five_matches-=player_details[j].present_match_score;
						details.total_wickets_in_last_five_matches-=player_details[j].present_match_wicket;
						check=1;
					}
				}
			}
		}
	}
	strcpy(details.out_or_not_out , O_NO);	
	return details;
}

void sort(struct team arr[], int highest_pid[], int h_pid_index, int n)
{
	char name[h_pid_index][100];
	int z=0,a,b,c;
	for(a=0;a<n;a++)
	{
		for(b=0;b<15;b++)
		{
			for(c=0;c<h_pid_index;c++)
			{
				if(arr[a].player_id[b]==highest_pid[c])
				{
					strcpy(name[z],arr[a].player_name[b]);
					z++;
				}
			}	
		}
	}
	int d,e,sorted=0;
	for(d=0;d<h_pid_index-1 && sorted==0;d++)
	{
		sorted=1;
		for(e=0;e<h_pid_index-d-1 ;e++)
		{
			if(strcmp(name[e],name[e+1])>0)
			{
				char temp[100];
				strcpy(temp,name[e]);
				strcpy(name[e],name[e+1]);
				strcpy(name[e+1],temp);
				sorted=0;
			}
		}
	}
	int i;
	for(i=0;i<h_pid_index;i++)
	{
		printf("%s",name[i]);
	}
 } 
 
void combinationUtil(struct team a[], int arr[], int data[], int start, int end, int index, int r, int n1);

void printCombination(struct team a[], int arr[], int n, int r, int n1)
{
    int data[r]; 	// A temporary array to store all combination one by one
    combinationUtil(a, arr, data, 2, n-1, 0, r, n1);
}
/* 
arr[]  ---> Input Array
data[] ---> Temporary array to store current combination
start & end ---> Starting and Ending indexes in arr[]
index  ---> Current index in data[]
r ---> Size of a combination to be printed 
*/
void combinationUtil(struct team a[],int arr[], int data[], int start, int end,int index, int r, int n1)
{
    if (index == r)		// Current combination is ready to be printed, print it
    {
    	int j,k,l;
        for (j=0; j<r; j++)
        {
        	for(k=0;k<n1;k++)
        	{
        		for(l=0;l<15;l++)
        		{
        			if(a[k].player_id[l]==data[j])
        			{
        				printf("%s,",a[k].player_name[l]);
					}
				}
			}
		}
		printf("\n");
        return;
    }
 
    // replace index with all possible elements. The condition "end-i+1 >= r-index" makes sure that including one element at index will make a combination with remaining elements at remaining positions
    int i;
	for (i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(a, arr, data, i+1, end, index+1, r, n1);
    }
}
 
int main() 
{
	int n;		//n is number of teams
	int i,j,k=0;
	printf("Enter no. of teams: ");
	scanf("%d" , &n);
	int m=n/2;
	struct team arr[size];
	struct player player_details[15*size+(3+(size/2)*((size/2)-1))*22]; //based on initializing and number of matches
	//taking id, name and player role as input
	for(i=0;i<n;i++)
	{
		fflush(stdin);
		char team_name[50];
		printf("Enter team name: ");
		scanf("%[^\n]%*c", team_name);
		strcpy(arr[i].team_name,team_name);
		arr[i].points=0;
		for(j=0;j<15;j++)
		{
			int id;
			printf("Enter player id: ");
			scanf("%d" , &id);
			arr[i].player_id[j]=id;
			player_details[k].player_id=id;
			char player_name[100];
			fflush(stdin); 
			printf("Enter player name: ");
			scanf("%[^\n]%*c",player_name);
			strcpy(arr[i].player_name[j],player_name);
			char player_role[11];
			fflush(stdin);
			printf("Enter player role: ");
			scanf("%[^\n]%*c" , player_role);
			strcpy(arr[i].player_role[j],player_role);
			strcpy(player_details[k].player_role,player_role);
			arr[i].mom_counter[j]=0;
			k++;
		}fflush(stdin);	
	}
	
	// printing team name and player name with id and role
	for(i=0;i<n;i++)
	{	
		printf("--------------------------------\n");
		printf("Team name: %s\n" , arr[i].team_name);
		for(j=0;j<15;j++)
		{
			printf("%d\t" ,arr[i].player_id[j] );
			printf("%s\t" ,arr[i].player_name[j] );
			printf("%s\n" ,arr[i].player_role[j] );
		}
		printf("--------------------------------\n");
	}

	//intialization of details of every player
	for(i=0;i<15*n;i++)
	{
		player_details[i].match_id=0; 
		player_details[i].previous_total_score=0;
		player_details[i].previous_avg =0;  
		player_details[i].previous_total_wickets=0;
		player_details[i].previous_wicket_avg=0;
		player_details[i].total_runs_in_last_five_matches=0; 
		player_details[i].total_wickets_in_last_five_matches=0;
		player_details[i].century=0;
		player_details[i].present_match_score=0;
		player_details[i].present_match_wicket=0;
		strcpy( player_details[i].out_or_not_out,"not out");
		player_details[i].matches_played=0;
	}
	
	//details of all the players
	k=0;
	for(i=0;i<15*n;i++)
	{
		if (i%15==0 && i!=0)
		{
			k++;
		}
		printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\t%s\t%d\n", player_details[i].player_id, arr[k].player_name[i%15], player_details[i].match_id, player_details[i].previous_total_score, player_details[i].previous_avg, player_details[i].previous_total_wickets, player_details[i].previous_wicket_avg, player_details[i].total_runs_in_last_five_matches, player_details[i].total_wickets_in_last_five_matches, player_details[i].century, player_details[i].present_match_score, player_details[i].present_match_wicket, player_details[i].player_role, player_details[i].out_or_not_out, player_details[i].matches_played);
	}
	
	//group-1 with groups assumed 
	int index = 15*n;
	struct match_played group1[(size/2)*((size/2)-1)/2];
	for(i=0;i<m*(m-1)/2;i++)
	{
		printf("Enter match id:\n");
		scanf("%d" , &group1[i].match_id);
		printf("Enter name of team1 and team2:\n");
		fflush(stdin);
		char team_name1[50];
		scanf("%[^\n]%*c", team_name1);
		strcpy(group1[i].team1 , team_name1);
    	char team_name2[50];
    	fflush(stdin);
		scanf("%[^\n]%*c", team_name2);
		strcpy(group1[i].team2 , team_name2);
		
		char man_of_the_match[100];
		printf("Enter the name of man of the  match");
		fflush(stdin);
		scanf("%[^\n]%*c", man_of_the_match);
		strcpy(group1[i].man_of_the_match , man_of_the_match);
		
		int flag=0,a,b;
		for(a=0;a<n/2 && flag==0;a++)
		{
			for(b=0;b<15 && flag==0;b++)
			{
				if(strcmp(group1[i].man_of_the_match,arr[a].player_name[b])==0)
				{
					arr[a].mom_counter[b]+=1;
					flag=1;
				}
			}
		}
		printf("Enter the number of wickets taken by pacer : \n");
		scanf("%d" , &group1[i].wicket_taken_by_pacer);
		
		printf("Enter the highest runs:\n");
		scanf("%d" , &group1[i].higest_run);
		
		char match_result[50];
		
		printf("Enter match result : \n");
		fflush(stdin);
		scanf("%[^\n]%*c", match_result);
		strcpy(group1[i].match_result , match_result);
		
		int z;
		if(strcmp(match_result , "no result")==0 || strcmp(match_result , "tie")==0)
		{
			for(z=0 ; z<n ; z++)
			{
				if(strcmp(group1[i].team1,arr[z].team_name)==0)
				{
					arr[z].points+=1;
				}
				if(strcmp(group1[i].team2,arr[z].team_name)==0)
				{
					arr[z].points+=1;
				}
			}
		}
		else
		{
			for(z=0 ; z<n ; z++)
			{
				if(strcmp(group1[i].match_result,arr[z].team_name)==0)
				{
					arr[z].points+=2;
				}
			}
		}
		int x,y;
		for(x=0 ; x<22 ; x++)
		{
			printf("Enter the player id , match id , number of centuries , runs scored in presenet match , wickets taken in present match :\n");
			int a[5];
			for(y=0 ; y<5 ; y++)
			{
				scanf("%d" , &a[y]);
			}
			char O_NO[7];
			printf("Enter if the player was out or not out : \n");
			fflush(stdin);
			scanf("%[^\n]%*c", O_NO);
			player_details[index]= update( player_details, a , O_NO , index );
			index++;
		}
	}
	int f_points=0,s_points=0;
	char first1[50],second1[50];
	if(n==4)
	{
		if(arr[0].points>arr[1].points)
		{
			strcpy(first1,arr[0].team_name);
			strcpy(second1,arr[1].team_name);
		}
		else
		{
			strcpy(first1,arr[1].team_name);
			strcpy(second1,arr[0].team_name);
		}
	}
	else
	{
		for(i=0;i<n/2;i++)
		{
			if(arr[i].points>f_points)
			{
				f_points=arr[i].points;
				strcpy(first1,arr[i].team_name);
				s_points=f_points;
				strcpy(second1,arr[i].team_name);
			}
			else if(arr[i].points>s_points && arr[i].points<f_points)
			{
				s_points=arr[i].points;
				strcpy(second1,arr[i].team_name);
			}
		}
	}

	//group-2 with groups assumed
	printf("Enter details of group 2: \n");
	struct match_played group2[(size/2)*((size/2)-1)/2];
	for(i=0;i<m*(m-1)/2;i++)
	{	printf("Enter match id:\n");
		scanf("%d" , &group2[i].match_id);
		
		printf("Enter the names of team1 and team2: \n");
		fflush(stdin);
		char team_name1[50];
		scanf("%[^\n]%*c", team_name1);
		strcpy(group2[i].team1 , team_name1);
    	char team_name2[50];
    	fflush(stdin);
		scanf("%[^\n]%*c", team_name2);
		strcpy(group2[i].team2 , team_name2);
		
		char man_of_the_match[100];
		printf("Enter the name of man of the match:\n");
		fflush(stdin);
		scanf("%[^\n]%*c", man_of_the_match);
		strcpy(group2[i].man_of_the_match , man_of_the_match);
		
		int flag=0,a,b;
		for(a=n/2;a<n && flag==0;a++)
		{
			for(b=0;b<15 && flag==0;b++)
			{
				if(strcmp(group2[i].man_of_the_match,arr[a].player_name[b])==0)
				{
					arr[a].mom_counter[b]+=1;
					flag=1;
				}
			}
		}
		printf("Enter the number of wickets taken by pacer:\n");
		scanf("%d" , &group2[i].wicket_taken_by_pacer);
		printf("Enter the highest runs:\n");
		scanf("%d" , &group2[i].higest_run);
		
		char match_result[50];
		printf("Enter the result of the match:\n");
		fflush(stdin);
		scanf("%[^\n]%*c", match_result);
		strcpy(group2[i].match_result , match_result);
		
		int z;
		if(strcmp(match_result , "no result")==0 || strcmp(match_result , "tie")==0)
		{
			for(z=0 ; z<n ; z++)
			{
				if(strcmp(group2[i].team1,arr[z].team_name)==0)
				{
					arr[z].points+=1;
				}
				if(strcmp(group2[i].team2,arr[z].team_name)==0)
				{
					arr[z].points+=1;
				}
			}
		}
		else
		{
			for(z=0 ; z<n ; z++)
			{
				if(strcmp(group2[i].match_result,arr[z].team_name)==0)
				{
					arr[z].points+=2;
				}
			}
		}
		int x,y;
		for(x=0 ; x<22 ; x++)
		{
			printf("Enter the player id , match id , number of centuries , score in present match , wickets taken in present match:\n");
			int a[5];
			for(y=0 ; y<5 ; y++)
			{
				scanf("%d" , &a[y]);
			}
			char O_NO[7];
			printf("Enter if the player was ouit or not out:\n");
			fflush(stdin);
			scanf("%[^\n]%*c", O_NO);
			player_details[index]= update( player_details, a , O_NO , index );
			index++;
		}
	}
	f_points=0,s_points=0;
	char first2[50],second2[50];
	if(n==4)
	{
		if(arr[2].points>arr[3].points)
		{
			strcpy(first2,arr[2].team_name);
			strcpy(second2,arr[3].team_name);
		}
		else
		{
			strcpy(first2,arr[3].team_name);
			strcpy(second2,arr[2].team_name);
		}
	}
	else
	{
		for(i=n/2;i<n;i++)
		{
			if(arr[i].points>f_points)
			{
				f_points=arr[i].points;
				strcpy(first2,arr[i].team_name);
				s_points=f_points;
				strcpy(second2,arr[i].team_name);
			}
			else if(arr[i].points>s_points && arr[i].points<f_points)
			{
				s_points=arr[i].points;
				strcpy(second2,arr[i].team_name);
			}
		}
	}

	//part 2
	printf("\nQ2\n");
	int highest_run=0;
	int highest_pid[15*size];
	int h_pid_index=0;
	for(i=15*n;i<index;i++)
	{
		if(player_details[i].previous_total_score+player_details[i].present_match_score>highest_run)
		{
			
			highest_run=player_details[i].previous_total_score+player_details[i].present_match_score;
			highest_pid[0]=player_details[i].player_id;
			
			int a;
			for(a=1;a<h_pid_index;a++)
			{
				highest_pid[a]=0;
			}
			h_pid_index=1;
		}
		else if(player_details[i].previous_total_score+player_details[i].present_match_score==highest_run)
		{
			highest_pid[h_pid_index]=player_details[i].player_id;
			h_pid_index++;
		}
	}
	sort(arr, highest_pid, h_pid_index, n);

	
	//knockout
	printf("Semi-1 between %s and %s\n", first1, second2);
	struct match_played knockout[3];
	printf("Enter the match id:\n");
	scanf("%d" , &knockout[0].match_id);
	
	fflush(stdin);
	strcpy(knockout[0].team1 , first1);
	strcpy(knockout[0].team2 , second2);
	
	char man_of_the_match[100];
	printf("Enter the man of the match:\n");
	fflush(stdin);
	scanf("%[^\n]%*c", man_of_the_match);
	strcpy(knockout[0].man_of_the_match , man_of_the_match);
	int flag=0,a,b;
	for(a=0;a<n && flag==0;a++)
	{
		for(b=0;b<15 && flag==0;b++)
		{
			if(strcmp(knockout[0].man_of_the_match,arr[a].player_name[b])==0)
			{
				arr[a].mom_counter[b]+=1;
				flag=1;
			}
		}
	}
	printf("Enter the wickets taken by pacer:\n");
	scanf("%d" , &knockout[0].wicket_taken_by_pacer);
	printf("Enter the hoghest runs :\n");
	scanf("%d" , &knockout[0].higest_run);
		
	char match_result[50];
	printf("Enter the match result :\n");
	fflush(stdin);
	scanf("%[^\n]%*c", match_result);
	strcpy(knockout[0].match_result , match_result);
	char final1[50];
	strcpy(final1,match_result);	
	int x,y;
	for(x=0 ; x<22 ; x++)
	{
		printf("Enter the player id , match id , number of centuries , score in present match , wickets taken in present match:\n");
		int a[5];
		for(y=0 ; y<5 ; y++)
		{
			scanf("%d" , &a[y]);
		}
		char O_NO[7];
		printf("Enter if the player was out or not out:\n");
		fflush(stdin);
		scanf("%[^\n]%*c", O_NO);
		player_details[index]= update( player_details, a , O_NO , index );
		index++;
	}
		
	printf("Semi-2 between %s and %s\n", first2, second1);
	fflush(stdin);
	strcpy(knockout[1].team1 , first2);
	strcpy(knockout[1].team2 , second1);
	
	printf("Enter match id:");
	scanf("%d" , &knockout[1].match_id);
	fflush(stdin);
	printf("Enter the man of the match:\n");
	scanf("%[^\n]%*c", man_of_the_match);
	strcpy(knockout[1].man_of_the_match , man_of_the_match);
	flag=0;
	for(a=0;a<n && flag==0;a++)
	{
		for(b=0;b<15 && flag==0;b++)
		{
			if(strcmp(knockout[1].man_of_the_match,arr[a].player_name[b])==0)
			{
				arr[a].mom_counter[b]+=1;
				flag=1;
			}
		}
	}
	printf("Enter the wickets taken by pacer:\n");
	scanf("%d" , &knockout[1].wicket_taken_by_pacer);
	printf("Enter the highest run:\n");
	scanf("%d" , &knockout[1].higest_run);
	printf("Enter the match result:\n");
	fflush(stdin);
	scanf("%[^\n]%*c", match_result);
	strcpy(knockout[1].match_result , match_result);
	char final2[50];
	strcpy(final2,match_result);	
	for(x=0 ; x<22 ; x++)
	{
		printf("Enter the player id , match id , number of centuries , score in present match , wickets taken in present match:\n");
		int a[5];
		for(y=0 ; y<5 ; y++)
		{
			scanf("%d" , &a[y]);
		}
		char O_NO[7];
		printf("Enter if the player was out or not out:");
		fflush(stdin);
		scanf("%[^\n]%*c", O_NO);
		player_details[index]= update( player_details, a , O_NO , index );
		index++;
	}
	
	printf("Final betwen %s and %s\n", final1, final2);
	printf("Enter match id:\n");
	scanf("%d" , &knockout[2].match_id);
	fflush(stdin);
	strcpy(knockout[2].team1 , final1);
	strcpy(knockout[2].team2 , final2);
	printf("Enter the man of the match:\n");
	fflush(stdin);
	scanf("%[^\n]%*c", man_of_the_match);
	strcpy(knockout[2].man_of_the_match , man_of_the_match);
	flag=0;
	for(a=0;a<n && flag==0;a++)
	{
		for(b=0;b<15 && flag==0;b++)
		{
			if(strcmp(knockout[2].man_of_the_match,arr[a].player_name[b])==0)
			{
				arr[a].mom_counter[b]+=1;
				flag=1;
			}
		}
	}
	printf("Enter the wickets taken by pacer:\n");
	scanf("%d" , &knockout[2].wicket_taken_by_pacer);
	printf("Enter the hoghest runs :\n");
	scanf("%d" , &knockout[2].higest_run);

	printf("Enter the match result:\n");
	fflush(stdin);
	scanf("%[^\n]%*c", match_result);
	strcpy(knockout[2].match_result , match_result);
	printf("Winner of the tournament is %s\n", match_result);	
	for(x=0 ; x<22 ; x++)
	{
		printf("Enter the player id , match id , number of centuries , score in present match , wickets taken in present match:\n");
		int a[5];
		for(y=0 ; y<5 ; y++)
		{
			scanf("%d" , &a[y]);
		}
		char O_NO[7];
		printf("Enter if the player was out or not out:\n");
		fflush(stdin);
		scanf("%[^\n]%*c", O_NO);
		player_details[index]= update( player_details, a , O_NO , index );
		index++;
	}

	//part 1
	printf("\nQ1\n");
	int bat[15*size];
	int pts[15*size];
	int bavg[15*size];
	char bat_name[15*size][100];
	int bowl[15*size];
	int ptw[15*size];
	int wavg[15*size];
	char bowl_name[15*size][100];
	int all_round[15*size];
	char all_name[15*size][100];
	int count_bat=0, count_bowl=0, count_all_round=0;
	for(i=0;i<15*n;i++)
	{
		if(strcmp(player_details[i].player_role, "batsman")==0)
		{
			bat[count_bat]=player_details[i].player_id;
			int flag=0;
			for(k=index-1;k>15*n && flag==0;k--)
			{
				if(player_details[i].player_id==player_details[k].player_id)
				{
					pts[count_bat]=player_details[k].previous_total_score+player_details[k].present_match_score;
					if(player_details[k].matches_played!=0)
					{
						bavg[count_bat]=(player_details[k].previous_total_score+player_details[k].present_match_score)/player_details[k].matches_played;
					}
					else
					{
						bavg[count_bat]=0;
					}
					flag=1;
				}
			}
			count_bat++;
		}
		else if(strcmp(player_details[i].player_role, "bowler")==0)
		{
			bowl[count_bowl]=player_details[i].player_id;
			int flag=0;
			for(k=index-1;k>15*n && flag==0;k--)
			{
				if(player_details[i].player_id==player_details[k].player_id)
				{
					ptw[count_bowl]=player_details[k].previous_total_wickets+player_details[k].present_match_wicket;
					if(player_details[k].matches_played!=0)
					{
						wavg[count_bat]=(player_details[k].previous_total_wickets+player_details[k].present_match_wicket)/player_details[k].matches_played;
					}
					else
					{
						wavg[count_bowl]=0;
					}
					flag=1;
				}
			}
			count_bowl++;
		}
		else
		{
			all_round[count_all_round]=player_details[i].player_id;
			count_all_round++;
		}
	}
	int sorted=0;
	for(i=0;i<count_bat && sorted==0;i++)
	{
		sorted=1;
		for(j=0;j<count_bat-i-1 ;j++)
		{
			if(pts[j]<pts[j+1])
			{
				int temp=pts[j];
				pts[j]=pts[j+1];
				pts[j+1]=temp;
				temp=bat[j];
				bat[j]=bat[j+1];
				bat[j+1]=temp;
				sorted=0;
			}
			else if(pts[j]==pts[j+1])
			{
				if(bavg[j]<bavg[j+1])
				{
					int temp=pts[j];
					pts[j]=pts[j+1];
					pts[j+1]=temp;
					temp=bat[j];
					bat[j]=bat[j+1];
					bat[j+1]=temp;
					sorted=0;
				}
			}
		}
	}
	
	for(i=0;i<count_bowl && sorted==0;i++)
	{
		sorted=1;
		for(j=0;j<count_bowl-i-1 ;j++)
		{
			if(ptw[j]<ptw[j+1])
			{
				int temp=ptw[j];
				ptw[j]=ptw[j+1];
				ptw[j+1]=temp;
				temp=bowl[j];
				bowl[j]=bowl[j+1];
				bowl[j+1]=temp;
				sorted=0;
			}
			else if(ptw[j]==ptw[j+1])
			{
				if(wavg[j]<wavg[j+1])
				{
					int temp=ptw[j];
					ptw[j]=ptw[j+1];
					ptw[j+1]=temp;
					temp=bowl[j];
					bowl[j]=bowl[j+1];
					bowl[j+1]=temp;
					sorted=0;
				}
			}
		}
	}
	
	for(i=0;i<count_bat;i++)
	{
		for(j=0;j<n;j++)
		{
			for(k=0;k<15;k++)
			{
				if(bat[i]==arr[j].player_id[k])
				{
					strcpy( bat_name[i], arr[j].player_name[k]);
				}
			}
				
		}
		
	}

	for(i=0;i<count_bowl;i++)
	{
		for(j=0;j<n;j++)
		{
			for(k=0;k<15;k++)
			{
				if(bowl[i]==arr[j].player_id[k])
				{
					strcpy( bowl_name[i], arr[j].player_name[k]);
				}	
			}
				
		}
		
	}
	
	for(i=0;i<count_all_round;i++)
	{
		for(j=0;j<n;j++)
		{
			for(k=0;k<15;k++)
			{
				if(all_round[i]==arr[j].player_id[k])
				{
					strcpy( all_name[i], arr[j].player_name[k]);
				}	
			}
				
		}
		
	}
	
	printf("The fixed 4 players in each combination are:\n");	
	printf("The best two batsmen:/n");
	for(i=0;i<2;i++)
	{
		printf("%s\n", bat_name[i]);
	}
	printf("The best two bowlers:/n");
	for(i=0;i<2;i++)
	{
		printf("%s\n", bowl_name[i]);
	}
	
	printf("\nOther combination of players-1:\n");
	printf("Combinations of batsmen\n");
	printCombination(arr,bat,count_bat,5,n);
	printf("Combinations of bowlers\n");
	printCombination(arr,bowl,count_bowl,2,n);
	printf("No allrounders\n");
	
	printf("\nOther combination of players-2:\n");
	printf("Combinations of batsmen\n");
	printCombination(arr,bat,count_bat,4,n);
	printf("Combinations of bowlers\n");
	printCombination(arr,bowl,count_bowl,3,n);
	printf("No allrounders\n");
	
	printf("\nOther combination of players-3:\n");
	printf("Combinations of batsmen\n");
	printCombination(arr,bat,count_bat,4,n);
	printf("Combinations of bowlers\n");
	printCombination(arr,bowl,count_bowl,2,n);
	printf("Combinations of all rounders\n");
	printCombination(arr,all_round,count_all_round,1,n);
	
	printf("\nOther combination of players-4:\n");
	printf("Combinations of batsmen\n");
	printCombination(arr,bat,count_bat,3,n);
	printf("Combinations of bowlers\n");
	printCombination(arr,bowl,count_bowl,4,n);
	printf("No allrounders\n");
	
	printf("\nOther combination of players-5:\n");
	printf("Combinations of batsmen\n");
	printCombination(arr,bat,count_bat,3,n);
	printf("Combinations of bowlers\n");
	printCombination(arr,bowl,count_bowl,3,n);
	printf("Combinations of all rounders\n");
	printCombination(arr,all_round,count_all_round,1,n);
	
	printf("\nOther combination of players-6:\n");
	printf("Combinations of batsmen\n");
	printCombination(arr,bat,count_bat,3,n);
	printf("Combinations of bowlers\n");
	printCombination(arr,bowl,count_bowl,2,n);
	printf("Combinations of all rounders\n");
	printCombination(arr,all_round,count_all_round,2,n);
	
	//part 3
	printf("\nQ3\n");
	int h_mom=0;
	int mom_pid[15*size];
	int mom_pid_index=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<15;j++)
		{

			if(arr[i].mom_counter[j]>h_mom)
			{
				h_mom=arr[i].mom_counter[j];
				mom_pid[0]=arr[i].player_id[j];
				int a;
				for(a=1;a<mom_pid_index;a++)
				{
					mom_pid[a]=0;
				}
				mom_pid_index=1;
			}
			else if(arr[i].mom_counter[j]==h_mom)
			{
				mom_pid[mom_pid_index]=player_details[i].player_id;
				mom_pid_index++;
			}
		}	
	}
	sort(arr, mom_pid, mom_pid_index, n);
	
	
	//part 4
	printf("\nQ4\n");
	flag=0;
	for(i=0;i<h_pid_index && flag==0;i++)
	{
		int check=0;
		for(j=0;j<mom_pid_index && check==0;j++)
		{
			if(mom_pid[j]==highest_pid[i])
			{
				check=1;	
			}			
		}
		if (check==0)
		{
			printf("The results are not same\n");
			flag=1;
		}
	}
	if(flag==0)
	{
		printf("The results are same\n");
	}
	
	//part 5
	printf("\nQ5\n");
	int ha=0;
	int ha_arr[15*size];
	for(i=0;i<15*n;i++)
	{
		ha_arr[i]=0;
	}
	int count=0;
	for(i=index-1;i>=15*n  && count<15*n;i--)
	{
		if(ha_arr[player_details[i].player_id]==0)
		{
			ha_arr[player_details[i].player_id]=(player_details[i].previous_total_score+player_details[i].present_match_score)/player_details[i].matches_played;
			count++;
		}
	}
	for(i=0;i<15*n;i++)
	{
		if(ha_arr[i]>ha)
		{
			ha=ha_arr[i];
		}
	}
	printf("Highest average is %d\n",ha);
	
	//part6
	printf("\nQ6\n");
	int tw=0;
	for(i=15*n;i<index;i++)
	{
		tw+=player_details[i].present_match_wicket;
	}
	int twp=0;
	for(i=0;i<m*(m-1)/2;i++)
	{
		twp+=group1[i].wicket_taken_by_pacer+group2[i].wicket_taken_by_pacer;
	}
	for(i=0;i<3;i++)
	{
		twp+=knockout[i].wicket_taken_by_pacer;
	}
	printf("Difference in total wickets taken by all spinners and pacers is %d\n",abs(tw-twp-twp));
			
	//part 7
	printf("\nQ7\n");
	int max_cent=0;
	int cent[15*size];
	int z=0;
	scanf("%d",&k);
	for(i=0;i<n;i++)
	{
		for(j=0;j<15;j++)
		{
			if(arr[i].mom_counter[j]>=k)
			{
				cent[z]=arr[i].player_id[j];
				z++;
			}
		}
	}
	int cent_arr[15*size];
	for(i=0;i<15*n;i++)
	{
		cent_arr[i]=0;
	}
	count=0;
	for(i=index-1;i>=15*n  && count<z;i--)
	{
		for(j=0;j<z;j++)
		{
			if(cent_arr[player_details[i].player_id]==0 && cent[j]==player_details[i].player_id)
			{
				cent_arr[player_details[i].player_id]=player_details[i].century;
				count++;
			}	
		}
	}
	for(i=0;i<15*n;i++)
	{
		if(cent_arr[i]>max_cent)
		{
			max_cent=cent_arr[i];
		}
	}
	int part7_arr[15*size];
	int part7_index=0;
	for(i=0;i<15*n;i++)
	{
		if(cent_arr[i]==max_cent)
		{
			part7_arr[part7_index]=i;
			part7_index++;
		}
	}
	sort(arr, part7_arr, part7_index, n);
	

	
	return 0;
}

