
struct MemoryStruct {
  char *memory;
  size_t size;
};

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
char * parse_api(char * str);
char * api_call(char * arg);
int write_to_file(struct MemoryStruct *chunk);



size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

return realsize;
}

char * parse_api(char * str) {
  char * needle;
  char * updated_needle;
  needle = strstr(str, "amount");

    if(needle == NULL) {
        puts("not valid coin");
        return NULL;
    }

  updated_needle = needle + 9;
  updated_needle[strlen(updated_needle)-3] = '\0';
  char * amount = (char *)malloc(strlen(updated_needle));
  strcpy(amount, updated_needle);
  return amount;
}

int write_to_file(struct MemoryStruct *chunk) {
  FILE *fp;
  fp = fopen( "file.txt" , "a" );
  fwrite(chunk->memory , 1 , chunk->size , fp );
  fwrite("\n" , 1 , sizeof("\n") , fp );
  fclose(fp);
  return 0;
}

char * api_call(char * arg) {
    
    char url[55];
    strcpy(url, "https://api.coinbase.com/v2/prices/BTC-USD/buy");
    if(arg != NULL) {
        int cx = snprintf ( url, 55, "https://api.coinbase.com/v2/prices/%s-USD/buy", arg );
        if(cx > 55) {
            puts("Too big an input");
            return NULL;
        }
    } 
    
    CURL *curl;
    CURLcode res;

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);  
    chunk.size = 0;    

    curl = curl_easy_init();

    if(curl) {
      curl_easy_setopt(curl, CURLOPT_URL, url);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
      res = curl_easy_perform(curl);

      if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
      } 
    }

    write_to_file(&chunk);
    char * amount = parse_api(chunk.memory);

    curl_easy_cleanup(curl);
    free(chunk.memory);
//cant send it back because I need to free it.
//maybe send the piuinter then free it later??? AHWHWHWHHH
return amount;
}