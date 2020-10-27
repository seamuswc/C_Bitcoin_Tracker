#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <curl/curl.h>

const int MAX = 100;
int time_api_repeat;
int g_price; //the alert price


#include "user_input.h"         
#include "api.h"         
#include "alert.h"    
#include "data.h"       

int print_api(char * arg); 
int time_change(char * arg);
int play_alert();
int restart_thread(pthread_t newthread);
int print_api(char * arg);
int set_data();

int thread_number = 0;
pthread_t newthread;


void * price_thread(void * arg) {
  int cancel = thread_number;
  while(1) {
    sleep(time_api_repeat); 
    if(cancel != thread_number) {    //if a new thread that does the same thing, this one closes.
      pthread_exit(NULL);
    }
    print_api(NULL);
  }
  return NULL;
}


int time_change(char * arg) {
  if(arg == NULL) {printf("Time is currently set to %d\n" , time_api_repeat);} 
  if(arg != NULL) {
    int seconds = atoi(arg);
    if(seconds > 0){
      time_api_repeat=seconds;
      thread_number++;
      restart_thread(newthread);
    }
  }
  return 0;
}

int restart_thread(pthread_t newthread) {
  pthread_create(&newthread, NULL, price_thread, NULL);
  return 1;
}



int main(void) {

  set_data();

    print_api(NULL);
    restart_thread(newthread);

    while(1) {
        char * input_function_pointer = input();
     
        char * second = second_arg(input_function_pointer);
        char * first = first_arg(input_function_pointer);
        
        choose(first, second);

        free(input_function_pointer);   
        input_function_pointer = NULL;  
    }
    pthread_join(newthread, NULL);
  return 0;
}


