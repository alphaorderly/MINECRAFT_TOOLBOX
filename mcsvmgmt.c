#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>
#include <curses.h>
#include <string.h>
#include <sys/time.h>

void getInput(int sig);
void setAsync(int i);
void setCurses(int i);
void printMainMenu();
void getMenuInput(int sig);
void printPluginMenu();
void getPluginInput(int sig);
void printRestoreMenu();
void getRestoreInput(int sig);
void runMinecraft();

#define MAINMENU_HEIGHT 10

char* mainMenu[] = {
"====================================================================",
"|                                                                  |",
"|        1. Edit server properties       | PRESS Q                 |",
"|        2. Get plugin                   | PRESS P                 |",
"|        3. Clear all setting            | PRESS C                 |",
"|        4. Run server                   | PRESS R                 |",
"|        6. Backup World                 | PRESS B                 |",
"|        5. EXIT Program                 | PRESS X                 |",
"|                                                                  |",
"===================================================================="
};

#define PLUGINMENU_HEIGHT 8

char* pluginMenu[] = {
"====================================================================",
"|                                                                  |",
"|        1. Install World Edit            | Press 1                |",
"|        2. Install Grief Prevention      | Press 2                |",
"|        3. Install LuckPerm              | Press 3                |",
"|        3. Back                          | Press X                |",
"|                                                                  |",
"===================================================================="
};

#define RESTORE_HEIGHT 7

char* restoreMenu[] = {
"====================================================================",
"|                                                                  |",
"|     ALL SETTINGS ARE GOING TO ERASED                             |",
"|     PRESS Q | ERASE                                              |",
"|     PRESS ANY OTHER KEY | BACK                                   |",
"|                                                                  |",
"===================================================================="
};

void getMenuInput(int sig) {
    char input = getchar();

    if(input == 'X' || input == 'x') {
        clear();
        setAsync(0);
        setCurses(0);
        exit(0);
    } else if(input == 'Q' || input == 'q') {
        int pid;
        if((pid = fork()) == -1) {
            perror("fork");
            exit(1);
        } else if(pid == 0) {
            execlp("gedit", "gedit", "server.properties", NULL);
        } else {
            wait(NULL);
        }
    } else if(input == 'P' || input == 'p') {
        printPluginMenu();
        pause();
    } else if(input == 'C' || input == 'c') {
        printRestoreMenu();
        pause();
    } else if(input == 'R' || input == 'r') {
        runMinecraft();
    } else if(input == 'B' || input == 'b') {
        int pid;
        if((pid = fork()) == -1) {
            perror("fork");
            exit(1);
        } else if(pid == 0) {
            execlp("sh", "sh", "backup.sh", NULL);
        } else {
            wait(NULL);
        }
    }
}

void getPluginInput(int sig) {
    char input = getchar();

    if(input == '1') {
        int pid;
        if((pid = fork()) == -1) {
            perror("fork");
            exit(1);
        } else if(pid == 0) {
            execlp("wget", "wget", "-O", "./plugins/worldEdit.jar", "https://media.forgecdn.net/files/3502/100/worldedit-mod-7.2.7.jar", NULL);
        } else {
            wait(NULL);
        }
    } else if (input == '2') {
        int pid;
        if((pid = fork()) == -1) {
            perror("fork");
            exit(1);
        } else if(pid == 0) {
            execlp("wget", "wget", "-O", "./plugins/GriefPrevention.jar", "https://media.forgecdn.net/files/3173/411/GriefPrevention.jar", NULL);
        } else {
            wait(NULL);
        }
    } else if (input == '3') {
        int pid;
        if((pid = fork()) == -1) {
            perror("fork");
            exit(1);
        } else if(pid == 0) {
            execlp("wget", "wget", "-O", "./plugins/luckPerm.jar", "https://ci.lucko.me/job/LuckPerms/1382/artifact/bukkit/loader/build/libs/LuckPerms-Bukkit-5.3.83.jar", NULL);
        } else {
            wait(NULL);
        }
    }
}

void getRestoreInput(int sig) {
    char input = getchar();

    if(input == 'Q' | input == 'q') {
        int pid;
        if((pid = fork()) == -1) {
            perror("fork");
            exit(1);
        } else if(pid == 0) {
            execlp("sh", "sh", "restore.sh", NULL);
        } else {
            wait(NULL);
        }
    }
}
/*
    Async input ENABLE (1) / DISABLE (0)
*/
void setAsync(int i) {
    if(i) {
        fcntl(0, F_SETOWN, getpid());
        int save = fcntl(0, F_GETFL);
        fcntl(0, F_SETFL, save | O_ASYNC);
    } else {
        signal(SIGIO, SIG_IGN);
        int save = fcntl(0, F_GETFL);
        fcntl(0, F_SETFL, save &~ O_ASYNC);
    }
}

/*
    Set curses ENABLE (1) / DISABLE (0)
*/
void setCurses(int i) {
    if(i) {
        initscr();
        noecho();
        crmode();
    } else {
        echo();
        nocbreak();
        endwin();
    }
}

/*
    print main program menu
*/
void printMainMenu() {

    struct sigaction sig;
    sig.sa_flags = SA_NODEFER;
    sig.sa_handler = getMenuInput;
    sigaction(SIGIO, &sig, 0);
    clear();
    for(int prt = 0;prt < MAINMENU_HEIGHT;prt++) {
        mvaddstr(prt, 0, mainMenu[prt]);
    }
    refresh();

}

void printPluginMenu() {

    struct sigaction sig;
    sig.sa_flags = SA_NODEFER;
    sig.sa_handler = getPluginInput;
    sigaction(SIGIO, &sig, 0);
    clear();
    for(int prt = 0;prt < PLUGINMENU_HEIGHT;prt++) {
        mvaddstr(prt, 0, pluginMenu[prt]);
    }
    refresh();

}

void printRestoreMenu() {
    struct sigaction sig;
    sig.sa_flags = SA_NODEFER;
    sig.sa_handler = getRestoreInput;
    sigaction(SIGIO, &sig, 0);
    clear();
    for(int prt = 0;prt < RESTORE_HEIGHT;prt++) {
        mvaddstr(prt, 0, restoreMenu[prt]);
    }
    refresh();
}

int main(int argc, char* argv[]) {
    setCurses(1);
    setAsync(1);

    // In menu, we ignore interrupt - quit signal.
    while(1) {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        printMainMenu();
        pause();
    }

    setAsync(0);
    setCurses(0);
}

char* getString(char* front) {
    char* getString = (char*)calloc(BUFSIZ, sizeof(char));
    char* addString = (char*)calloc(BUFSIZ, sizeof(char));
    strcat(getString, front);
    fgets(addString, BUFSIZ, stdin);
    strcat(getString, addString);
    getString[strlen(getString) - 1] = 0;
    return getString;
}

int minecraftPid;

int tick = 0;
const int required = 80;

void printtop(int sig) {

    if(waitpid(minecraftPid, NULL, WNOHANG)) return;

    if(tick < required) {
        tick++;
        return;
    }

    tick %= required;

    int pid;
    printf("\n");
    if((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        execlp("sh", "sh", "top.sh", NULL);
    } else {
        wait(NULL);
    }
}

void runMinecraft() {
    struct sigaction sig;
    sig.sa_flags = SA_NODEFER;
    sig.sa_handler = SIG_IGN;
    sigaction(SIGIO, &sig, 0);

    clear();
    char* a[20] = {0, };
    int ac = 0;
    a[ac++] = "java";
    setCurses(0);
    setAsync(0);
    printf("Maximum Ram limit ( Ex. 1G / 512M ) : ");
    a[ac++] = getString("-Xmx");
    printf("Minumum Ram limit ( Ex. 1G / 512M ) : ");
    a[ac++] = getString("-Xms");
    a[ac++] = "-jar";
    a[ac++] = "server.jar";
    a[ac++] = "nogui";

    if((minecraftPid = fork()) == -1) {
        perror("fork");
        exit(1);
    } else if (minecraftPid == 0) {
        execvp("java", a);
    } else {
        struct sigaction sigalrm;
        sigalrm.sa_flags = SA_NODEFER;
        sigalrm.sa_handler = printtop;
        sigaction(SIGALRM, &sigalrm, 0);
        struct itimerval time;
        time.it_interval.tv_sec = 0;
        time.it_interval.tv_usec = 250000;
        time.it_value.tv_sec = 0;
        time.it_value.tv_usec = 250000;
        setitimer(ITIMER_REAL, &time, NULL);


        while(!waitpid(minecraftPid, NULL, WNOHANG)) {
            pause();
        }

        time.it_interval.tv_sec = 0;
        time.it_interval.tv_usec = 0;
        time.it_value.tv_sec = 0;
        time.it_value.tv_usec = 0;
        setitimer(ITIMER_REAL, &time, NULL);
        sigalrm.sa_handler = SIG_IGN;
        sigaction(SIGALRM, &sigalrm, 0);

        setCurses(1);
        setAsync(1);

        int newPid;
        if((newPid = fork()) == -1) {
            perror("fork");
            exit(1);
        } else if(newPid == 0) {
            execlp("sh", "sh", "save.sh", NULL);
        } else {
            wait(NULL);
        }        
    }
}