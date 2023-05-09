#include<stdio.h>
#include<windows.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
typedef struct articol{

char titlu[30],continut[400];
int fav;
}articol;
void resetBuffer(){


    while(_kbhit())
        _getch();
}
int is_substr(char str[], char sub[])
{
  int num_matches = 0;
  int sub_size = 0;
  int i=0;
  while (sub[i] != '\0') {
    sub_size++;
    i++;

  }

  i=0;
  int j=0;
  while (str[i] != '\0') {
    while (sub[j] == str[i] && sub[j] != '\0') {
      num_matches++;
      j++;
      i++;
    }
    if (num_matches == sub_size) {
      return 1;
    }
    num_matches = 0;
    i++;
  }
  return 0;
}
void menu(int n)
{
//if(n==0)


}
void filtrare(){
short y=2, ymax,ok=1,sag=0,ymin=2,i,ct=0;
char* ret;
FILE *p;
p=fopen("nrarticole.txt","r");
fscanf(p,"%d",&ymax);
fclose(p);
p=fopen("io.txt","r");
articol opt[ymax];
for(i=0;i<ymax;i++){
    if (!fgets(opt[i].titlu, 30, p)) {
        exit(1);
}
    opt[i].titlu[strcspn(opt[i].titlu, "\n")] = '\0';
    fgets(opt[i].continut,400,p);
    fscanf(p,"%d",&opt[i].fav);

}
fclose(p);
int max=0;
char in[30];
while(GetAsyncKeyState(VK_RETURN)){}
while(1==1)
{
    resetBuffer();
    printf("Filtreaza articolele\n\n");
    printf("Introduceti textul dupa care se filtreaza -->");
    if (!fgets(in, 30, stdin)) {
    exit(1);
}
    in[strcspn(in, "\n")] = '\0';
    for(int i=0;i<ymax;i++)
    {
       ret=is_substr(opt[i].titlu,in);

        if(ret!=0)
            max+=1;
    }
    if(max!=0)
        break;
}
    short poz[ymax];
    for(int i=0;i<ymax;i++)
    {
        poz[i]=-1;
    }
    articol* temp = malloc(max*sizeof(articol));
    for(int i=0;i<ymax;i++)
    {
     ret=is_substr(opt[i].titlu,in);

    if(ret!=0)
        {
            strcpy(temp[ct].titlu,opt[i].titlu);
            strcpy(temp[ct].continut,opt[i].continut);
            temp[ct].fav=opt[i].fav;
            poz[i]=ct;
            ct+=1;
        }
    }
     while (GetAsyncKeyState(VK_RETURN)) {}
     resetBuffer();
while(ok==1){
    system("cls");
    printf("Acestea sunt articolele care contin filtrul introdus\n\n");

    for(short i=0;i<max;i++){
        if(sag==i)
            printf(">>%s\n",temp[i].titlu);


        else printf("%s\n",temp[i].titlu);
    }
    if(sag==max)
    printf(">>Inapoi\n");
    else printf("Inapoi\n");
    gotoxy(0,y);
    while(1==1){
     if(GetAsyncKeyState(0x57))//w
     {
         y--;
         sag--;
         if(y<=ymin){
            y=2;
            sag=0;}

     break;
     }
    if(GetAsyncKeyState(0x53))//s
    {
        y++;
        sag++;

        if(y>=max+2){
            y=max+2;
            sag=max;
        }
        break;
    }
     if (GetAsyncKeyState(VK_RETURN))
            {


                while (GetAsyncKeyState(VK_RETURN)) {}
                if(sag<max){
                        int v;
                        v=viz(&temp[sag],&opt);
                        if(v==0){
                            temp[sag].fav=0;
                            for(i=0;i<ymax;i++)
                                if(poz[i]==sag){
                                opt[i].fav=0;
                                update(i,0);
                                break;
                                }

                            viz(&temp[sag],&opt);
                            return 0;
                        }
                        else if(v==1){
                                temp[sag].fav=1;
                                for(i=0;i<ymax;i++)
                                if(poz[i]==sag){
                                opt[i].fav=1;
                                update(i,1);
                                break;
                                }
                            viz(&temp[sag],&opt);
                            return 0;
                        }
                        system("cls");

                        ok=0;
                        break;}

                else if(sag==max){
                    system("cls");
                    meniu();
                    ok=0;
                    break;
            }


    }

    }
  Sleep(25);

    }system("cls");
}
void update(short poz,short f){
    FILE *ptr;
    short ymax;
    ptr=fopen("nrarticole.txt","r");
    fscanf(ptr,"%d",&ymax);
    fclose(ptr);
    ptr=fopen("io.txt","r");
    articol opt[ymax];
    for(int i=0;i<ymax;i++){
    fgets(opt[i].titlu,30,ptr);
    fgets(opt[i].continut,400,ptr);
    fscanf(ptr,"%d",&opt[i].fav);

}
fclose(ptr);
    fclose(fopen("io.txt","w"));
    for(int i=0;i<ymax;i++)
        if(i==poz){
        if(f==0){
        opt[i].fav=0;}
        else opt[i].fav=1;}
    fopen("io.txt","a");
    for(int i=0;i<ymax;i++){
    fputs(opt[i].titlu,ptr);
    fputs(opt[i].continut,ptr);
    fprintf(ptr,"%d",opt[i].fav);
    }
    fclose(ptr);

 }
void show(short r,short sag,short n)
{
    char opt[4][30]={"Vizualizare articole", "Scrie un articol","Favorite","Iesire Aplicatie"};
    if(n==0)
    for(short i=0;i<r;i++){
        if(sag==i)
            printf(">>%s\n",opt[i]);

        else printf("%s\n",opt[i]);
    }


}
void gotoxy(short x, short y){

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(h, coord);
}
int viz(articol *x,articol* z[]){

articol aux;
short y=2, ymax=3,ok=1,sag=0,ymin=3;
while(ok==1){
    system("cls");
    if(x->fav==0){
    printf("Lista de articole\n\n");
    if(sag==0){
    printf(">>Inapoi\n");
    printf("Adauga la favorite\n");}
    else{ printf("Inapoi\n");
    printf(">>Adauga la favorite\n");
    }
    printf("%s\n%s",x->titlu,x->continut);
    }
    else{

    printf("Lista de articole\n\n");
    if(sag==0){
    printf(">>Inapoi\n");
    printf("Elimina de la favorite\n");}
    else{ printf("Inapoi\n");
    printf(">>Elimina de la favorite\n");
    }
    printf("%s\n%s",x->titlu,x->continut);

    }
    gotoxy(0,y);
    while(1==1){
     if(GetAsyncKeyState(0x57))//w
     {
         y--;
         sag--;
         if(y<=ymin){
            y=2;
            sag=0;}

     break;
     }
    if(GetAsyncKeyState(0x53))//s
    {
        y++;
        sag++;

        if(y>=ymax){
            y=3;
            sag=1;
        }
        break;
    }
     if (GetAsyncKeyState(VK_RETURN))
            {


                while (GetAsyncKeyState(VK_RETURN)) {}
                if(y==2){
                        system("cls");
                        meniu();
                        ok=0;
                        return 0;
                        break;}

                if(y==3){
                    system("cls");
                    if(x->fav==0){
                        x->fav=1;
                    return 1;}
                    else{ x->fav=0;
                    return 0;}

                    ok=0;
                    break;
                }
            }


    }
    Sleep(25);
    }
    system("cls");

    }
void meniu(){
short y=2, ymax=6,ok=1,sag=0,ymin=3;


while(ok==1){
    system("cls");
    printf("News Reading\n\n");
    show(4,sag,0);
    gotoxy(0,y);

    while(1==1){
        if(GetAsyncKeyState(0x57))//w
        {
            y--;
            sag--;

            if(y<=ymin){
                y=2;
                sag=0;}

            break;}

        if(GetAsyncKeyState(0x53))//s
    {
            y++;
            sag++;

            if(y>=ymax){
                y=5;
                sag=3;}

                break;
    }
        if (GetAsyncKeyState(VK_RETURN))
            {
            while (GetAsyncKeyState(VK_RETURN)) {}
                if(y==2){
                    system("cls");
                    meniuviz();
                    ok=0;
                    break;}

                else if(y==3){
                    system("cls");
                    scriere();
                    ok=0;
                    return;
                    break;}

                else if(y==4){
                    system("cls");
                    favorite();
                    ok=0;
                    break;}

                else if(y==5){
                    system("cls");
                    ok=0;
                    return 0;
                    break;}


            }

        }

    Sleep(25);

    }

system("cls");
}
void meniuviz(){

short y=2, ymax,ok=1,sag=0,ymin=3,i;
FILE* ptr;
ptr=fopen("nrarticole.txt","r");
fscanf(ptr,"%d",&ymax);
fclose(ptr);
ptr=fopen("io.txt","r");
articol opt[ymax];
for(i=0;i<ymax;i++){
    fgets(opt[i].titlu,30,ptr);
    fgets(opt[i].continut,400,ptr);
    fscanf(ptr,"%d",&opt[i].fav);

}
fclose(ptr);
while(ok==1){
    system("cls");
    printf("Lista de articole\n\n");
    for(short i=0;i<ymax;i++){
        if(sag==i)
            printf(">>%s",opt[i].titlu);

        else printf("%s",opt[i].titlu);
    }
    if(sag==ymax)
    printf(">>Filtrare\n");
    else printf("Filtrare\n");
    if(sag==ymax+1)
    printf(">>Inapoi\n");
    else printf("Inapoi\n");
    gotoxy(0,y);
    while(1==1){
     if(GetAsyncKeyState(0x57))//w
     {
         y--;
         sag--;
         if(y<=ymin){
            y=2;
            sag=0;}

     break;
     }
    if(GetAsyncKeyState(0x53))//s
    {
        y++;
        sag++;

        if(y>=ymax+3){
            y=ymax+3;
            sag=ymax+1;
        }
        break;
    }
     if (GetAsyncKeyState(VK_RETURN))
            {


                while (GetAsyncKeyState(VK_RETURN)) {}
                if(sag<ymax){
                        system("cls");
                        int v;
                        v=viz(&opt[sag],&opt);
                        if(v==0){
                            opt[sag].fav=0;
                            update(sag,0);
                            viz(&opt[sag],&opt);
                            return 0;
                        }
                        else if(v==1){
                            opt[sag].fav=1;
                            update(sag,1);
                            viz(&opt[sag],&opt);
                            return 0;
                        }
                        }
                else if(sag==ymax){
                    system("cls");
                    filtrare();
                ok=0;
                break;}
                else if(sag==ymax+1){
                    system("cls");
                    meniu();
                    ok=0;
                    break;
            }}


    }
  Sleep(25);
    }

       system("cls");
    }
void succes(){

    resetBuffer();
  short y=2, ymax=4,ok=1,sag=0,ymin=2;
char opt[3][30]={"Scrie un alt articol","Meniu","Iesi din aplicatie"};
while(ok==1){
    system("cls");
    printf("Articolul a fost publicat cu succes\n\n");
    for(short i=0;i<3;i++){
        if(sag==i)
            printf(">>%s\n",opt[i]);

        else printf("%s\n",opt[i]);
    }
    gotoxy(0,y);
    while(1==1){
     if(GetAsyncKeyState(0x57))//w
     {
         y--;
         sag--;
         if(y<=ymin){
            y=2;
            sag=0;}

     break;
     }
    if(GetAsyncKeyState(0x53))//s
    {
        y++;
        sag++;

        if(y>=ymax){
            y=4;
            sag=2;
        }
        break;
    }
     if (GetAsyncKeyState(VK_RETURN))
            {


                while (GetAsyncKeyState(VK_RETURN)) {}
                if(y==2){
                        system("cls");
                        scriere();
                        while (GetAsyncKeyState(VK_RETURN)) {}
                        ok=0;
                        return ;
                        break;}

                else if(y==3)
                {
                    system("cls");
                    meniu();
                    ok=0;
                    break;
                }
                else if(y==4)
                {
                    system("cls");
                    ok=0;
                    break;
                }
            }


    }
    Sleep(25);
    }
    system("cls");

    }
void scriere(){

    while(GetAsyncKeyState(VK_RETURN)) {}
    int ok=0,ymax;
    while(ok==0){
        resetBuffer();
        FILE *fp;
        articol c;
        fp=fopen("io.txt", "a");
        printf("Scrie un articol\n\n");
        printf("Introduceti titlul articolului -> ");
        fgets(c.titlu,30,stdin);
        resetBuffer();
        system("cls");
        printf("Scrie un articol\n\n");
        printf("Introduceti continutul articolului ->");
        fgets(c.continut,400,stdin);
        resetBuffer();
        c.fav=0;
        fputs(c.titlu,fp);
        fputs(c.continut,fp);
        fprintf(fp,"%d",c.fav);
        fclose(fp);
        FILE* ptr;
        ptr=fopen("nrarticole.txt","r");
        fscanf(ptr,"%d",&ymax);
        ymax+=1;
        fclose(ptr);
        ptr=fopen("nrarticole.txt","w");
        fprintf(ptr,"%d",ymax);
        fclose(ptr);
        ok=1;
        while (GetAsyncKeyState(VK_RETURN)) {}
        succes();
        system("cls");
        return 0;
    }
    }


void favorite()
{
short y=2, ymax,ok=1,sag=0,ymin=2,i;
FILE *p;
p=fopen("nrarticole.txt","r");
fscanf(p,"%d",&ymax);
fclose(p);
p=fopen("io.txt","r");
articol opt[ymax];
for(i=0;i<ymax;i++){
    fgets(opt[i].titlu,30,p);
    fgets(opt[i].continut,400,p);
    fscanf(p,"%d",&opt[i].fav);

}
fclose(p);
short max=0;
for(short i=0;i<ymax;i++){
        if(opt[i].fav==1)
            max+=1;

    }
    articol* temp = malloc(max*sizeof(articol));
    short ct=0;
    short poz[ymax];
    for(short i=0;i<ymax;i++)
    poz[i]=-1;


    for(short i=0;i<ymax;i++)
    {
        if(opt[i].fav==1){
            strcpy(temp[ct].titlu,opt[i].titlu);
            strcpy(temp[ct].continut,opt[i].continut);
            temp[ct].fav=opt[i].fav;
            poz[i]=ct;
            ct+=1;}
    }

while(ok==1){
    system("cls");
    printf("Lista de favorite\n\n");

    for(short i=0;i<max;i++){
        if(sag==i)
            printf(">>%s",temp[i].titlu);

        else printf("%s",temp[i].titlu);
    }
    if(sag==max)
    printf(">>Inapoi\n");
    else printf("Inapoi\n");
    gotoxy(0,y);
    while(1==1){
     if(GetAsyncKeyState(0x57))//w
     {
         y--;
         sag--;
         if(y<=ymin){
            y=2;
            sag=0;}

     break;
     }
    if(GetAsyncKeyState(0x53))//s
    {
        y++;
        sag++;

        if(y>=max+2){
            y=max+2;
            sag=max;
        }
        break;
    }
     if (GetAsyncKeyState(VK_RETURN))
            {


                while (GetAsyncKeyState(VK_RETURN)) {}
                if(sag<max){
                        int v;
                        v=viz(&temp[sag],&opt);
                        if(v==0){
                            temp[sag].fav=0;
                            for(i=0;i<ymax;i++)
                                if(poz[i]==sag){
                                opt[i].fav=0;
                                update(i,0);
                                break;
                                }

                            viz(&temp[sag],&opt);
                            return 0;
                        }
                        else if(v==1){
                                temp[sag].fav=1;
                                for(i=0;i<ymax;i++)
                                if(poz[i]==sag){
                                opt[i].fav=1;
                                update(i,1);
                                break;
                                }
                            viz(&temp[sag],&opt);
                            return 0;
                        }
                        system("cls");

                        ok=0;
                        break;}

                else if(sag==max){
                    system("cls");
                    meniu();
                    ok=0;
                    break;
            }


    }

    }
  Sleep(25);

    }system("cls");}
int main() {
meniu();
return 0;
}



