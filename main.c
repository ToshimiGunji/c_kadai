#include  <stdio.h>
#include <string.h>
#include <limits.h>
#define MAX  10

/*--- int 型スタックを実現する構造体 ---*/
typedef struct {
    double vision;
    int height;
}Body;

typedef struct {
    Body body;
    char name[20];
}PhysCheck;

typedef struct {
    int max;
    int ptr;

    PhysCheck stk[MAX];
}PhysCheckStack;

/*--- スタックの初期化 ---*/
int Initialize(PhysCheckStack *s, int max){
    s->ptr = 0;
    s->max = max;
    return 0;
}

/*--- スタックにデータをプッシュ ---*/
int Push(PhysCheckStack *s, double vision, int height, char *name){
    if (s->ptr >= s->max) return -1;/* スタック満杯 */
    s->stk[s->ptr].body.vision = vision;
    s->stk[s->ptr].body.height = height;
    strcpy(s->stk[s->ptr].name,name);

    s->ptr++;
    return 0;
}

/*--- スタックからデータをポップ ---*/
int Pop(PhysCheckStack *s, double *vision, int *height, char *name){
    if (s->ptr <= 0) return -1;/* スタックは空 */
    s->ptr--;
    *vision = s->stk[s->ptr].body.vision;
    *height = s->stk[s->ptr].body.height;
    *name   = s->stk[s->ptr].name[0];
    return (0);
}

/*--- スタックからデータをピーク ---*/
int Peek(PhysCheckStack *s, double *vision, int *height, char *name){
    if (s->ptr <= 0) return -1;
    *vision = s->stk[s->ptr-1].body.vision;
    *height = s->stk[s->ptr-1].body.height;
    *name   = s->stk[s->ptr-1].name[0];
    return 0; }

/*--- スタックの容量 ---*/
int Capacity(const PhysCheckStack *s){
    return s->max;
}

/*--- スタックに積まれているデータ数 ---*/
int Size(const PhysCheckStack *s){
    return s->ptr;
}

/*--- スタックの全データの表示 ---*/
void Print(const PhysCheckStack *s) {
    int i;
    for (i = 0; i < s->ptr; i++) {
        printf("%f,%d,%s", s->stk[i].body.vision, s->stk[i].body.height, s->stk[i].name);
        putchar('\n');
    }
}


char *bm_match(char *pat , char *txt){
    char  *pt;   /* txt をなぞるカーソル */
    char  *pp;  /* pat をなぞるカーソル */
    int  txt_len = strlen(txt);   /* txt の文字数 */
    int  pat_len = strlen(pat);    /* pat の文字数 */
    int  skip[UCHAR_MAX + 1]; /* スキップテーブル */
    int  i;

    for (i = 0; i <= UCHAR_MAX; i++) /* スキップテーブルの作成 */
        skip[i] = pat_len;
    for (pp = pat; *pp != '\0'; pp++)
        skip[*pp] =  strlen(pp) - 1;
    skip[*(pp - 1)] = pat_len;
    /* パターンの最後文字の移動距離はパターンの文字数 */
    pt = txt + pat_len - 1;
    /* pat の末尾と比較する txt の文字を決定 */
    while ( pt < txt + txt_len) {
        /* txt の比較する文字の位置が txt の末尾を越えるまで */
        pp = pat + pat_len - 1; /* pat の最後の文字に着目 */
        while (*pt == *pp) {
            if (pp == pat) return (pt);
            /* 一致した文字がパターンの最初の文字になれば終了 */
            pp--;
            pt--;
        }
        pt += (skip[*pt]> strlen(pp)) ? skip[*pt] : strlen(pp);
    }
    return (NULL);
}

int Count(PhysCheckStack *s, PhysCheck *x){
    int i, counter = 0;
    char *txt;
    char *pat = x->name;

    for(i = 0; i < s->ptr ; i++){
        txt = s->stk[i].name;
        while((txt = bm_match(pat, txt)) != NULL){
            counter ++;
            txt ++;
        }
    }
    return counter;
}


int main(void) {
    PhysCheckStack s;
    Initialize(&s, MAX);

    while (1) {
        PhysCheck x;
        double vision;
        int height;
        char name[20];
        int menu,counter;

        printf("現在のデータ数：%d/%d\n", Size(&s), Capacity(&s));
        printf("(1) プッシュ  (2) ポップ (3) ピーク  (4) 表示  (0) 終了：");
        scanf("%d", &menu);

        if (menu == 0) break;

        switch (menu) {

            case 1: /* プッシュ */
                printf("視力：");
                scanf("%lf", &vision);
                printf("身長：");
                scanf("%d", &height);
                printf("名前：");
                scanf("%s", name);
                if (Push(&s, vision, height, name) == -1)
                    puts("\a エラー：プッシュに失敗しました。");
                break;

            case 2: /* ポップ */
                if (Pop(&s, &vision, &height, name) == -1)
                    puts("\a エラー：ポップに失敗しました。");
                else
                    printf("ポップしたデータは%lf%d%s です。\n", vision, height, name);
                break;

            case 3: /* ピーク */
                if (Peek(&s, &vision, &height, name) == -1)
                    puts("\a エラー：ピークに失敗しました。");
                else
                    printf("ピークしたデータは%lf%d%s です。\n", vision, height, name);
                break;

            case 4: /* 表示 */
                Print(&s);
                break;
            case 5: /* 計数 */
                printf("パターン:");
                scanf("%s",  x.name);
                if ((counter = Count(&s, &x)) >0)
                    printf("パターン数は，%d 個です\n",counter);
                else
                    puts("\a パターンは存在しません。\n ");

                break;

            default:
                break;
        }
    }
    return 0;
}