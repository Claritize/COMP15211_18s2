// Fetch data from a URL, separating header and body
// Adapted from an example on https://curl.haxx.se/
// Written by Daniel Sternberg
// Modified by John Shepherd
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
 
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
   size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
   return written;
}
 
int main(int argc, char **argv)
{
   CURL *cp;
   char *headFileName = "head.txt";
   FILE *headf;
   char *bodyFileName = "body.txt";
   FILE *bodyf;
 
   // check that they gave us a URL
   if (argc < 2) {
      fprintf(stderr, "Usage %s URL\n", argv[0]);
      exit(1);
   }
   // init the curl session 
   curl_global_init(CURL_GLOBAL_ALL);
   cp = curl_easy_init();
   // set URL to get 
   curl_easy_setopt(cp, CURLOPT_URL, argv[1]);
   // no progress meter please 
   curl_easy_setopt(cp, CURLOPT_NOPROGRESS, 1L);
   // send all data to this function   
   curl_easy_setopt(cp, CURLOPT_WRITEFUNCTION, write_data);
   // open the header file 
   headf = fopen(headFileName, "wb");
   if (!headf) {
      perror(headFileName);
      curl_easy_cleanup(cp);
      exit(1);
   }
   // open the body file 
   bodyf = fopen(bodyFileName, "wb");
   if (!bodyf) {
      perror(bodyFileName);
      curl_easy_cleanup(cp);
      fclose(headf);
      exit(1);
   }
   // we want the headers be written to this file instead of stdout 
   curl_easy_setopt(cp, CURLOPT_HEADERDATA, headf);
   // we want the body be written to this file instead of stdout 
   curl_easy_setopt(cp, CURLOPT_WRITEDATA, bodyf);
   // get it! 
   curl_easy_perform(cp);
   fclose(headf);
   fclose(bodyf);
   // cleanup curl stuff 
   curl_easy_cleanup(cp);
   return 0;
}