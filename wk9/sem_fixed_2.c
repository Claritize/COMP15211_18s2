#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <semaphore.h>
 
int main(void)
{
   void delay(int);
   int pid;
   sem_t *exclusion;
 
   exclusion = sem_open("mysemaphore", O_CREAT, 0644, 1);
   if (exclusion == SEM_FAILED) {
      perror("sem_init");
      exit(1);
   }
   setbuf(stdout, NULL);
   if ((pid = fork()) != 0) {
      for (int i = 0; i < 5; i++) {
         sem_wait(exclusion);
         for (int j = 0; j < 26; j++) putchar('a'+j);
         putchar('\n');
         sem_post(exclusion);
         delay(100000);
      }
   }
   else {
      for (int i = 0; i < 5; i++) {
         sem_wait(exclusion);
         for (int j = 0; j < 26; j++) putchar('A'+j);
         putchar('\n');
         sem_post(exclusion);
         delay(100000);
      }
   }
   sem_destroy(exclusion);
   return 0;
}
 
void delay(int max)
{
   for (int i = 0; i < max; i++) /* waste time */;
}