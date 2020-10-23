
int print_api(); 
int time_change(char * arg);
int set_alert(char * price);
int stop_alert();

const int MAX = 100;

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

int coin(char * arg) {
    if(arg == NULL) {puts("Command not complete");}
    print_api(arg);
return 0;
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
  }else {
    puts("Command not Found");
  }
  return 0;
}
