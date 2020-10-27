



void freeAllocatedMemory(char ***strings, int n)
{
    for (int i = 0; i < n; i++)
    {
        free((*strings)[i]); // free allocated memory
        (*strings)[i] = NULL;
    }
    free(*strings);
    *strings=NULL;
}

int get_length(char * str) {
      int len = strlen(str);
      if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
      }
      len = strlen(str) +1;
  return len;
}

int read_file(FILE* file, char *** strings) {
  char str[MAX];
  int n = 0;
  while(fgets(str, MAX, file)) {
      if(n > 0) {
        *strings = realloc(*strings, (n+1) * sizeof(char*)); 
      }
      int len = get_length(str);
      (*strings)[n] = malloc(len * sizeof(char));
      strcpy((*strings)[n], str);
      n++;
  }

return n;
}


int print_strings(char *** strings, int n) {
  for(int i = 0; i < n; i++) {
    puts((*strings)[i]);
  }
  return 1;
}

int set_data() {
  FILE *file;
  file = fopen("data.txt", "r");

  char ** strings = malloc(sizeof(char*));

  int n = read_file(file, &strings);
  fclose(file);
  
  time_api_repeat = atoi(strings[0]);
  g_price = atoi(strings[1]);
  
  //print_strings(&strings, n);

  freeAllocatedMemory(&strings, n);
  return 1;
}



