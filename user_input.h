
int print_api(); 
int time_change(char * arg);
int set_alert(char * price);
int stop_alert();
int coin(char * arg);


char * input() {
  char * str = malloc(MAX);   
  if (fgets(str, MAX, stdin) != NULL) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
      str[--len] = '\0';
    }
  }
  return str;
}

char * first_arg(char * arg) {  
    char * j = strchr(arg, '-');
    if(j==NULL) {
        return arg;
    }
    *j = '\0';
    return arg;
}

char * second_arg(char * arg) {  
    char * j = strchr(arg, '-');
    if(j==NULL) {
        return NULL;
    }
    return ++j;
}


int choose(char * arg1, char *arg2) {

  if (strcmp(arg1, "now") == 0) {
    print_api(NULL);
  } else if (strcmp(arg1, "time") == 0) {
    time_change(arg2);
  } else if (strcmp(arg1, "coin") == 0) {
    coin(arg2);
  } else if (strcmp(arg1, "alert") == 0) {
    set_alert(arg2);
  } else if (strcmp(arg1, "stop") == 0) {
    stop_alert();
  }else if (strcmp(arg1, "exit") == 0) {
    exit(0);
  }else {
    puts("Command not Found");
  }
  return 0;
}
