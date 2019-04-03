#include<stdio.h>
#include<stdlib.h>//malloc用
#define NODATA 0//データ無し
#define EXISTDATA 1//データあり

/*
int型データを保持するセル
デクで用いる
自己参照構造体
 */
struct intCell{
  int data;             //データ部
  struct intCell * prev;//前へのポインタ部
  struct intCell * next;//後ろへのポインタ部
};

typedef struct intCell IntCell ;
typedef IntCell* Cell_P; //セル型

struct intDeque{
  IntCell * head;//先頭ポインタ
  IntCell * tail;//末尾ポインタ
};

typedef struct intDeque IntDeque;//デク型

IntDeque makeDeque();//デクの作成

void head_in(IntDeque *deque,int data);//先頭からデータ挿入
int head_out(IntDeque *deque);//先頭からデータ削除
void tail_in(IntDeque *deque,int data);//末尾からデータ挿入
int tail_out(IntDeque *deque);//末尾からデータ削除

int isEmpty(IntDeque *deque);//空のテスト
void printDeque(IntDeque *deque);//デク表示
void copyDeque(IntDeque *deque1,IntDeque *deque2);//デク１をデク２に複製

void fscanToDeque(FILE*fp,IntDeque *deque);//ファイルからのデータ入力
void forward_fprint(FILE*fp,IntDeque *deque);//ファイルへ順方向に出力
void reverse_fprint(FILE*fp,IntDeque *deque);//ファイルへ逆方向に出力

Cell_P makeCell(int n);//セル作成

int main(){
  //デクの動作
  IntDeque deque1,deque2;
  IntDeque *d_p1,*d_p2;
  FILE *fp_in,*fp_out;

  deque1=makeDeque();//デク１の生成
  d_p1=&deque1;
  deque2=makeDeque();//デク２の生成
  d_p2=&deque2;

  printf("デク用意\n");
  printf("デク１を表示します、\n");
  printDeque(d_p1);
  printf("デク２を表示します。");
  printDeque(d_p2);
  
  fp_in=fopen("IntData","r");
  fscanToDeque(fp_in,d_p1);
  fclose(fp_in);

  printf("ファイル入力\n");
  printf("デク１を表示します。\n");
  printDeque(d_p1);
  printf("デク２を表示します。\n");
  printDeque(d_p2);

  copyDeque(d_p1,d_p2);
  printf("デクの複製\n");
  printf("デク１を表示します。\n");
  printDeque(d_p1);
  printf("デク２を表示します。\n");
  printDeque(d_p2);

  printf("ファイルへ順に出力します。\n");
  fp_out=fopen("Mirror","w");
  forward_fprint(fp_out,d_p1);//ファイルへ順に出力
  printf("ファイルへ逆に出力します。\n");
  reverse_fprint(fp_out,d_p2);//ファイルへ逆順に出力
  fclose(fp_out);

  printf("デク１を表示します。\n");
  printDeque(d_p1);

  printf("デク２を表示します。\n");
  printDeque(d_p2);

  return 0;
}

IntDeque makeDeque(){
  IntDeque deque;
  deque.head=NULL;
  deque.tail=NULL;
  return deque;
  }

int isEmpty(IntDeque *deque){
  if(deque->head==NULL){
    return NODATA;
  }else{
    return EXISTDATA;
  }
}


Cell_P makeCell(int n){
  Cell_P new =(Cell_P)malloc(sizeof(IntCell));
  new->data=n;
  return new;
}

void head_in(IntDeque *deque,int data){
  Cell_P new_cell=makeCell(data);
  if(isEmpty(deque)==NODATA){
    deque->head=new_cell;
    deque->tail=new_cell;
  }else{
  new_cell->prev=NULL;
  new_cell->next=deque->head;
  deque->head->prev=new_cell;
  deque->head=new_cell;
  }
  return;
}

int head_out(IntDeque *deque){
  int idata;
  Cell_P remove;
  if(deque->head!=deque->tail){
    remove=deque->head;
    idata=remove->data;
    deque->head=deque->head->next;
    deque->head->prev=NULL;
    free(remove);
    return idata;
  }else if(deque->head==deque->tail){//最後の一個の削除
    remove=deque->head;
    idata=remove->data;
    deque->head=NULL;
    deque->tail=NULL;
    free(remove);
    return idata;
  }else{
    printf("No data\n");
    return -1;
  }
}

void tail_in(IntDeque *deque ,int data){
  Cell_P new_cell=makeCell(data);
  if(isEmpty(deque)==NODATA){
    deque->head=new_cell;
    deque->tail=new_cell;
  }else{
    new_cell->next=NULL;
    new_cell->prev=deque->tail;
    deque->tail->next=new_cell;
    deque->tail=new_cell;
  }
  return ;
}

int tail_out(IntDeque *deque){
  int idata;
  Cell_P remove;
  if(deque->tail!=deque->head){
    remove=deque->tail;
    idata=remove->data;
    deque->tail=deque->tail->prev;
    deque->head->next=NULL;
    free(remove);
    return idata;
  }else if(deque->tail==deque->head){//最後の一個の削除
    remove=deque->tail;
    idata=remove->data;
    deque->head=NULL;
    deque->tail=NULL;
    free(remove);
    return idata;
  }else{
    printf("No data\n");
    return -1;
  }
}

void copyDeque(IntDeque *deque1,IntDeque *deque2){
  Cell_P p1=deque1->head;
  if(deque1->head!=NULL){
    while(p1!=deque1->tail){
      tail_in(deque2,p1->data);
      p1=p1->next;
    }
    tail_in(deque2,p1->data);
  }
  return ;
}

void printDeque(IntDeque *deque){
  Cell_P  p=deque->head;
  if(deque->head==NULL){
    printf("()\n");
  }else{
    printf("(");
    while(p!=deque->tail){
      printf("%3d,",p->data);
      p=p->next;
    }
    printf("%3d,",p->data);
    printf(")\n");
  }
  return;
}
void fscanToDeque(FILE *fp,IntDeque *deque){
  int idata;
  while(fscanf(fp,"%d",&idata)!=EOF){
    head_in(deque,idata);
  }
  return;
}

void forward_fprint(FILE*fp,IntDeque *deque){
  int idata;
  while(isEmpty(deque)==EXISTDATA){
    idata=tail_out(deque);
    fprintf(fp,"%3d",idata);
  }
  return ;
}

void reverse_fprint(FILE*fp,IntDeque *deque){
  int idata;
  while(isEmpty(deque)==EXISTDATA){
    idata=head_out(deque);
    fprintf(fp,"%3d",idata);
  }
  return ;
}


  
  
