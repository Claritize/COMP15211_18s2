#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
 
int main(void)
{
   void delay(int);
   int pid;
   sem_t exclusion;
 
   if (sem_init(&exclusion, 1, 1) < 0) {
      perror("sem_init");
      exit(1);
   }
   setbuf(stdout, NULL);
   if ((pid = fork()) != 0) {
      for (int i = 0; i < 5; i++) {
         sem_wait(&exclusion);
         for (int j = 0; j < 26; j++) putchar('a'+j);
         putchar('\n');
         sem_post(&exclusion);
         delay(100000);
      }
   }
   else {
      for (int i = 0; i < 5; i++) {
         sem_wait(&exclusion);
         for (int j = 0; j < 26; j++) putchar('A'+j);
         putchar('\n');
         sem_post(&exclusion);
         delay(100000);
      }
   }
   sem_destroy(&exclusion);
   return 0;
}
 
void delay(int max)
{
   for (int i = 0; i < max; i++) /* waste time */;
}