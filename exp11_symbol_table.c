// #192411237
/*
 Exp 11 - Simple symbol table operations (insert, search, display, modify)
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct sym { char label[32]; int addr; } sy[100];
int cnt = 0;

int find_index(const char *lab){
    for(int i=0;i<cnt;i++) if(strcmp(sy[i].label, lab)==0) return i;
    return -1;
}

void insert_symbol(){
    char lab[32];
    int addr;
    printf("Enter label: "); if(scanf("%31s", lab)!=1) return;
    if(find_index(lab)!=-1){ printf("Duplicate symbol\n"); return; }
    printf("Enter address: "); if(scanf("%d", &addr)!=1) return;
    strcpy(sy[cnt].label, lab); sy[cnt].addr = addr; cnt++;
}

void display(){ for(int i=0;i<cnt;i++) printf("%s\t%d\n", sy[i].label, sy[i].addr); }
void modify_symbol(){ char lab[32]; int addr;
    printf("Enter label to modify: "); if(scanf("%31s", lab)!=1) return;
    int idx = find_index(lab); if(idx==-1){ printf("No such symbol\n"); return; }
    printf("Enter new address: "); if(scanf("%d", &addr)!=1) return;
    sy[idx].addr = addr;
}

int main(void){
    int ch;
    do{
        printf("\\n1.insert\\n2.display\\n3.search\\n4.modify\\n5.exit\\n");
        if(scanf("%d", &ch)!=1) break;
        if(ch==1) insert_symbol();
        else if(ch==2) display();
        else if(ch==3){ char lab[32]; printf("Enter label to search: "); scanf("%31s", lab); if(find_index(lab)!=-1) printf("label is found\\n"); else printf("label not found\\n"); }
        else if(ch==4) modify_symbol();
    }while(ch!=5);
    return 0;
}
