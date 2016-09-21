/*
Author: Nadeem Jetha
CSCI 1730
W 11:15 Breakout
UGAID:810609087
This is a program designed to compare two text files using two different methods. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>

struct stat file1,file2;//File statistics that will be used by both functions
//Step 2 function reads files into array and writes out file 2 when the files differ
void step2(FILE *f1, FILE *f2){
  //variable declarations
        FILE *difference2=fopen("differencesFoundInFile2.txt","w");
	struct timeval timeStart,timeEnd;
	char *f1content=(char *)malloc(file1.st_size+1);
	char *f2content=(char *)malloc(file2.st_size+1);
	char *diff=(char *)malloc(file2.st_size);
	double milliseconds;
	int i=0,j=0;//i will be general counter, j will be counter for difference array

	gettimeofday(&timeStart, NULL);
	f1content[file1.st_size]=0;
	f2content[file2.st_size]=0;
	fread(f1content,file1.st_size,1,f1);//read files into arrays
	fread(f2content,file2.st_size,1,f2);
	while(f1content[i]!=0&&f2content[i]!=0){
	  if(f1content[i]!=f2content[i]){//comparing each element of the two files
	    diff[j]=f2content[i];//assign file2 element to difference array if different from file1
			j++;
		}	
		i++;
	}
	if(file1.st_size<file2.st_size){//if file1 is shorter copy the remaining part of file2 to difference array
		while(f2content[i]!=0){
			diff[j]=f2content[i];
			j++;
			i++;
		}
	}
	diff[j]=0;
	fwrite(diff,j,1,difference2);//write difference array into difference file
	gettimeofday(&timeEnd,NULL);
	
	milliseconds=(timeEnd.tv_sec-timeStart.tv_sec)*1000.0 -(timeEnd.tv_usec-timeStart.tv_usec)/1000.0;
      	printf("Step 2 took %f milliseconds\n",milliseconds);//calculate and print time
	//close files and free memory
	fclose(f1);
	fclose(f2);
	fclose(difference2);
	free(f1content);
	free(f2content);
	free(diff);
}

//Main function. Also contains step 1 of comparison
int main(int argc, char *argv[])
{
  //variable declarations
  double milliseconds=0.0;
  struct timeval start,end;
  FILE *f1=fopen(argv[1],"r");
  FILE *f2=fopen(argv[2],"r");
  FILE *difference1=fopen("differencesFoundInFile1.txt","w");
  int v1=stat(argv[1],&file1);//calculate stats for files
  int v2=stat(argv[2],&file2);
  char x,y;//used to compare files
  //verify command line arguments and files are correct
  if(argc!=3){
      printf("Usage: ./proj3.out <file name 1> <file name 2>\n");
      exit(0);
    }
  if(f1==NULL||f2==NULL||v1==-1||v2==-1){
      printf("Error reading a file");
      exit(0);
    }
  
  setbuf(f1,NULL);
  setbuf(f2,NULL);
  setbuf(difference1,NULL);
  
  gettimeofday(&start,NULL);
  while(fread(&x,1,1,f1)!=0&&fread(&y,1,1,f2)!=0){
      if(x!=y)
	  {fwrite(&x,sizeof(char),1,difference1);}
  }//compare files 
  fseek(f1,-1,SEEK_CUR);
  if(file1.st_size>file2.st_size){
      while(fread(&x,1,1,f1)!=0)
	  {fwrite(&x,sizeof(char),1,difference1);}
  }//if file 1 is bigger than 2 then write remaining to difference file
  gettimeofday(&end,NULL);
  //calculate and print time
  milliseconds=(end.tv_sec-start.tv_sec)*1000.0 -(end.tv_usec-start.tv_usec)/1000.0;
  printf("Step 1 took %f milliseconds\n",milliseconds);
  //close files and free memory
  fclose(f1);
  fclose(f2);
  fclose(difference1);
  f1=fopen(argv[1],"r");//re-open files for step 2
  f2=fopen(argv[2],"r");
  //call step 2
  step2(f1,f2);
  
  return 0;
}
