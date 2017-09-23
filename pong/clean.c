//get the tabs out of the file and replace them with spaces
#include <stdio.h>

int main(int argc, char *argv[])
{
 FILE *fr, //file to read from
      *fw; //file to write to
 char clean_file[20]; //name of the file to write
 
 char ch;  //character being copied
 int num_spaces,
     done = 0;
 
 if(argc != 3)
 {
  printf("Remove the TAB character and replace with spaces.\n");
  printf("usage: %s <file>.c <num of spaces>\n", argv[0]);
  return 0;
 }

 num_spaces = atoi(argv[2]);

 /* open the file to read from */
 fr = fopen(argv[1], "r");
 if(fr == NULL)
 {
  printf("Error: %s not found.\n", argv[1]);
  return 0;
 }

 strcpy(clean_file, argv[1]);
 strcat(clean_file, "CF"); /* CF for clean file */
 
 /* open the file to write to */
 fw = fopen(clean_file, "w");
 if(fw == NULL)
 {
  printf("Error: Cannot open output file.\n");
  return 0;
 }

 while(!done)
 {
  ch = fgetc(fr);
  if(ch == EOF)
  {
   done = 1;
  }
  else
  {
   if(ch == '\t')
   {
    int i;
    for(i = 0; i < num_spaces; i++)
    {
     fputc(' ', fw); //replace the tab with spaces
    }
   }
   else
   {
    fputc(ch, fw);
   }
  }
 }

 /* close the files */
 fclose(fw);
 fclose(fr);
 printf("All Clean!\n");
 return 0;
}
 
 
