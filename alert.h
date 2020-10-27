

bool alert_set = false;
bool alert_thread_exists = false;
void * music();
pthread_t musicthread;

int play_alert() {
    if(alert_thread_exists == false) {          //makes sure this thread isnt already running
        alert_thread_exists = true;
        pthread_create(&musicthread, NULL, music, NULL);
    }
    return 0;
}

void * music() {
    while(1) {
        if(alert_set == false) {           //shuts the thread down if user has asked it to stop
            pthread_exit(NULL); 
            alert_thread_exists = false;
        }
        system("say ALERT ALERT ALERT");
        sleep(5);
    }
    return NULL;
}

int set_alert(char * price) {
    if(price == NULL) {printf("Alert currently set to: %d\n", g_price);}
    if(price != NULL) {
        //check for , & . and let use know this doenst work
        int new_price = atoi(price);
        if (new_price < 1)
        {
            puts("Alert Command only accepts numbers as a parameter. Example: alert-100000");
            return 0;
        }
        g_price = new_price;
        alert_set = true;
    }
    return 0;
}

int stop_alert() {
    alert_set = false;
    g_price = 0;
    puts("Alert has been reset!");
return 0;
}