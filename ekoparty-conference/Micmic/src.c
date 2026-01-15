#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <linux/limits.h>

#if defined(__linux__)
#define IS_LINUX 1
#else
#define IS_LINUX 0
#endif

#define MM "MIC MIC"
void escape();
void display_micmic(char* flg);
char MM2[9] = "TOO LATE";

void *race_condition(void *arg) {
    char input[2000];
    printf("MIC MIC? ");
    fgets(input, sizeof(input), stdin);
    usleep(10000000);
    if (strcmp(input, MM) == 0){ //Si frenaron la race condition
        char *flg = (char *)malloc(28);

        //Escritura de flag en memoria
        strcpy(&(flg[3]),"7");strcpy(&(flg[16]),"$");strcpy(&(flg[21]),"U");strcpy(&(flg[6]),"K");strcpy(&(flg[15]),"4");strcpy(&(flg[4]),"_");strcpy(&(flg[18]),"3");strcpy(&(flg[11]),"_");strcpy(&(flg[20]),"0");
        strcpy(&(flg[8]),"2");strcpy(&(flg[14]),"f");strcpy(&(flg[1]),"s");strcpy(&(flg[9]),"3");strcpy(&(flg[10]),"!");strcpy(&(flg[5]),"E");strcpy(&(flg[24]),"?");strcpy(&(flg[2]),"E");strcpy(&(flg[19]),"N");
        strcpy(&(flg[7]),"0");strcpy(&(flg[12]),"R");strcpy(&(flg[0]),"3");strcpy(&(flg[13]),"U");strcpy(&(flg[25]),"!");strcpy(&(flg[22]),"G");strcpy(&(flg[23]),"H");strcpy(&(flg[17]),"t");flg[26] ='\0';
        
        //Impresion de la direccion de memoria de la flag
        display_micmic(flg);

        free(flg);

    } else {escape();}
    return NULL;
}

void escape(){
    //Apertura de video en youtube
    const char *youtube_url = "https://www.youtube.com/watch?v=Ay70ALo4UIs"; 
    char command[256];
    snprintf(command, sizeof(command), "xdg-open \"%s\"", youtube_url);
    int ret = system(command);
    
    //Eliminacion del binario
    char self_path[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", self_path, sizeof(self_path) - 1);
    self_path[count] = '\0';
    remove(self_path);
    return;
}

void display_micmic(char *flg){
    char* flg2 = (char *)malloc(28);
    printf("              .==,_ \n");
    printf("             .===,_\\`\\ \n");
    printf("           .====,_ \\` \\      .====,__ \n");
    printf("     ---     .==-,\\`~. \\           \\`:\\`.__, \n");
    printf("      ---      \\`~~=-.  \\           /^^^   ...%p \n",flg2);
    printf("        ---       \\`~~=. \\         / \n");
    printf("                     \\`~. \\       / \n");
    printf("                       ~. \\____./ \n");
    printf("                         \\`.=====) \n");
    printf("                      ___.--~~~--.__ \n");
    printf("            ___\\.--~~~              ~~~---.._|/ \n");
    printf("            ~~~\"                             / \n");
    return;
}


int main() {
    if (!IS_LINUX){ 
        //Verificar que este corriendo en Linux
        printf("NO LINUX NO PARTY! \n");
        char self_path[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", self_path, sizeof(self_path) - 1);
        self_path[count] = '\0';
        remove(self_path);
    } else {
        pthread_t thread;
        //Creacion del hilo
        pthread_create(&thread, NULL, race_condition, NULL)
        //Pisa la string a verificar
        strcpy(MM2, MM);
        pthread_join(thread, NULL);
    }
    return 0;
}