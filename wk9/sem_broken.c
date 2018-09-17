#include <unistd.h>
#include <stdio.h>
 
int main(void)
{
   void delay(int);
   int pid;
 
   setbuf(stdout, NULL);
   if ((pid = fork()) != 0) {
      for (int i = 0; i < 5; i++) {
         for (int j = 0; j < 26; j++) putchar('a'+j);
         putchar('\n');
         delay(100000);
      }
   }
   else {
      for (int i = 0; i < 5; i++) {
         for (int j = 0; j < 26; j++) putchar('A'+j);
         putchar('\n');
         delay(100000);
      }
   }
   return 0;
}
 
void delay(int max)
{
   for (int i = 0; i < max; i++) /* waste time */;
}