#include <unistd.h>
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

char buf[2048];
typedef struct {
    char* notDone;
    char* done;
    int amtDone;
    int length;
} word;

word* newWord(int size){
    word* ret = (word*) malloc(sizeof(word));
    ret->notDone = (char*) malloc(size);
    ret->done = (char*) malloc(size);
    ret->length = size;
    return ret;
}

int testChar(word* w, char c){
    if (w->notDone[w->amtDone] == c){
        w->done[w->amtDone] = c;
        w->amtDone++;
        return 1;
    }
    return 0;
}

void init(){
    initscr();
    raw();
    cbreak();
    noecho();
}

void loop(){
    word* w = newWord(2048);
    w->notDone = buf;
    printw("%s", w->notDone+w->amtDone);
    while(1){
        if(*(w->notDone+w->amtDone) == '\0')
            return;
        int ch = getch();
        switch(ch){
            case KEY_F(1):      
                printw("F1 Key pressed");
                return;
            default:
                if (testChar(w, ch)){
                    erase();
                    //attron(A_BOLD);
                    //printw("%s", w->done);
                    //attroff(A_BOLD);
                    printw("%s", w->notDone+w->amtDone);
                }
                break;
        }

    }
}
int main(int argc, char* argv[]){
    printf("%d\n", atoi(*(argv+1)+8));
    int displace = 0;
    int offset = 0;
    do {
        offset += displace;
        displace = read(atoi(*(argv+1)+8),buf + offset,2048);
    } while(displace != 0);
    init();
    loop();
    refresh();
    getch();
    endwin();
    return 0;
}
