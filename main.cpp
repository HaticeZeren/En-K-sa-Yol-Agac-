#include <iostream>
#include <cmath>
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand ,qsort*/
#include <allegro.h>
using namespace std;
int renk=0;
class dugum{
  private:
    int x;
    int y;
    int renk;
   public:
    void deger_gir(int,int,int);
    void yaz();
    int getx();
    int gety();
    int get_renk();
    void set_renk(int);
};

class kenar{
friend void grafik(kenar *kisayol_kenarlar[],int kenar_sayisi);
friend int kruskal(kenar kenarlar[],dugum dugumler[],int kenar_sayisi,int dugum_sayisi,kenar *enkya_kenar[]);
friend int maliyet(kenar *enkya_kenar[],int enkya_ken_sayisi);
public:
    dugum d1;
    dugum d2;
    int uzaklik;
public:
   void kenar_degeri(dugum a,dugum b,int mesafe);
   void yaz();
   int get_uzaklik();
   void set_renk(int,int);
};
int kenar::get_uzaklik(){
return (this->uzaklik);
}
int dugum::get_renk(){
return (this->renk);
}
void dugum::set_renk(int a){
this->renk=a;
}
void kenar::set_renk(int d,int renk){//1:d1 dugumunun rengi 2:d2 dugumunun rengi
if(d==1) (this->d1).set_renk(renk);
if(d==2) (this->d2).set_renk(renk);
}
void kenar::yaz(){
cout<<"("<<d1.getx()<<","<<d1.gety()<<")"<<".dugum(rengi:"<<d1.get_renk()<<")-("<<d2.getx()<<","<<d2.gety()<<")"<<".dugum(rengi:"<<d2.get_renk()<<")komsu ve uzaklik:"<<uzaklik<<endl;
}
void kenar::kenar_degeri(dugum a,dugum b,int mesafe){
(this->d1)=a;
(this->d2)=b;
(this->uzaklik)=mesafe;
}
void mat_deg_ata(int *kom_mat,int N,dugum a[],kenar k[]){
int say=0;
for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
        if(kom_mat[i*N+j]!=0){
            k[say].kenar_degeri(a[i],a[j],kom_mat[i*N+j]);
            say++;
        }
    }
}
}

void dugum::yaz(){
    cout<<"x="<<x<<endl;
    cout<<"y="<<y<<endl;
}
void dugum::deger_gir(int x,int y,int renk){
this->x=x;
this->y=y;
this->renk=renk;
}

int dugum::getx(){
return (this->x);
}
int dugum::gety(){
return (this->y);
}
int mutlak(int sayi){
if(sayi<0) return (-1)*sayi;
else return sayi;
}
int maliyet(dugum a,dugum b){
int x=(a.getx()-b.getx());
x=mutlak(x);
int y=(a.gety()-b.gety());
y=mutlak(y);
return x+y;
}
int* komsuluk_matrisi(dugum a[],int N){
int *kom_matris=(int *)malloc(sizeof(int)*N*N);
for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
        if(i!=j){
            kom_matris[i*N+j]=maliyet(a[i],a[j]);
        }
        else
          kom_matris[i*N+j]=0;
    }
}
return kom_matris;
}
void kom_matris_yaz(int *kom_matris,int N){
cout<<"KOMSULUK MATRISI:"<<endl;
for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
       cout<<kom_matris[i*N+j]<<"  ";
    }
    cout<<endl;
}
}
void graf_girisi(int N,dugum a[]){
int x,y;
for(int i=0;i<N;i++){
cout<<"............................................"<<endl;
do{
cout<<i+1<<".dugumun x koordinatini giriniz:";
cin>>x;
if(x>20) cout<<"x degerini 20'den kucuk giriniz!"<<endl;
}while(x>20);
do{
cout<<endl<<i+1<<".dugumun y koordinatini giriniz:";
cin>>y;
if(y>20) cout<<"y degerini 20'den kucuk giriniz!"<<endl;
}while(y>20);
a[i].deger_gir(x,y,renk);
renk++;
}
}
int kenar_karsilastir(const void *kenar1,const void *kenar2){
kenar *K1=(kenar *)kenar1;
kenar *K2=(kenar *)kenar2;
return (K1->get_uzaklik()-K2->get_uzaklik());
}
void kenar_sirala(kenar k[],int N){
qsort(k,N,sizeof(kenar),kenar_karsilastir);
}
int kruskal(kenar kenarlar[],dugum dugumler[],int kenar_sayisi,int dugum_sayisi,kenar *enkya_kenar[]){
int enk_kenar_say=0;
for(int i=0;i<kenar_sayisi;i++){
    int d1_renk=kenarlar[i].d1.get_renk();
    int d2_renk=kenarlar[i].d2.get_renk();
    int cevrim=0;
    if(d1_renk==d2_renk){
        //cevrim var
        cevrim=1;
        cout<<"cevrim var eklenemedi!"<<endl;
    }
    if(!cevrim){
        enkya_kenar[enk_kenar_say]=&kenarlar[i];
        enk_kenar_say++;
        cout<<"cevrim yok "<<enk_kenar_say<<".kenar eklendi"<<endl;
        cout<<"("<<kenarlar[i].d1.getx()<<","<<kenarlar[i].d1.gety()<<")-"<<"("<<kenarlar[i].d2.getx()<<","<<kenarlar[i].d2.gety()<<")"<<endl;
        for(int j=0;j<kenar_sayisi;j++){
            if(kenarlar[j].d1.get_renk()==d2_renk) kenarlar[j].set_renk(1,d1_renk);//d2 ile ayni renkte olan dugume d1 rengini ver
            if(kenarlar[j].d2.get_renk()==d2_renk) kenarlar[j].set_renk(2,d1_renk);
        }
    }
}
return enk_kenar_say;
}
int maliyet(kenar *enkya_kenar[],int enkya_ken_sayisi){
int sayac=0;
for(int i=0;i<enkya_ken_sayisi;i++){
    sayac+=enkya_kenar[i]->uzaklik;
}
return sayac;
}
 void grafik(kenar *kisayol_kenarlar[],int kenar_sayisi){
allegro_init();
install_keyboard();
set_color_depth(32);
set_window_title("........KISA YOL AGACI..........");
set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
acquire_screen();
clear_to_color(screen,makecol( 255,255,255) );
  int x=160;
  while(x<=520){
  rect(screen,100,120,500,140,makecol(0,500,500));
  rect(screen,100,x,500,140,makecol(0,500,500));
  x+=20;
  }
  int y=120;
  while(y<=500){
  rect(screen,y,520,120,120,makecol(0,500,500));
   y+=20;
  }
  for(int i=0;i<=20;i++){
  textprintf_ex(screen,font,95+(i*20),100,makecol(0,0,0),makecol(255, 255, 255),"%d",i);//koordinat duzelmindeki x eksenindeki rakamlar
  }
  for(int j=1;j<=20;j++){
  textprintf_ex(screen,font,75,115+(j*20),makecol(0,0,0),makecol(255, 255, 255),"%d",j);//koordinat duzlemindeki y eksenindeki rakamlar
  }
  for(int i=0;i<kenar_sayisi;i++){
  int X1=kisayol_kenarlar[i]->d1.getx();
  int Y1=kisayol_kenarlar[i]->d1.gety();
  int X2=kisayol_kenarlar[i]->d2.getx();
  int Y2=kisayol_kenarlar[i]->d2.gety();
  circlefill(screen, 100+(20*X1),120+(20*Y1),5, makecol( 100, 0, 100) );//dugumun yerini nokta ile bildirir
  circlefill(screen,100+(20*X2),120+(20*Y2),5, makecol( 100, 0, 100) );//dugumun yerini nokta ile bildirir
  int uzaklik_x=X1-X2;//1. ve 2. kenarin dugumlerinin x koordinatlari farki
  int uzaklik_y=Y1-Y2;
/**1.kenarin  dugumlerini birlestirme*/
  if(X1<X2){
    uzaklik_x=(uzaklik_x<0)?(-1*uzaklik_x):uzaklik_x;
  }
  else{
    uzaklik_x=(uzaklik_x>0)?(-1*uzaklik_x):uzaklik_x;
  }
 /**(X1,Y1) noktasında UZAKLIK_X birim kadar x ekseninde cizgi cizdirmek icin asagidaki kod calistirilir*/

  rect(screen,100+(20*X1),120+(20*Y1),100+(20*X1)+20*uzaklik_x,120+(20*Y1),makecol(0,0,0));
if(Y1>Y2){
    uzaklik_y=(uzaklik_y<0)?(-1*uzaklik_y):uzaklik_y;
  }
  else{
    uzaklik_y=(uzaklik_y>0)?(-1*uzaklik_y):uzaklik_y;
  }
/**(X2,Y2) noktasında UZAKLIK_Y birim kadar y ekseninde cizgi cizdirmek icin asagidaki kod calistirilir*/
rect(screen,100+(20*X2),120+(20*Y2),100+(20*X2),120+(20*Y2)+20*uzaklik_y,makecol(0,0,0));
  }
  char yazi[100]="KISAYOL AGACININ MALIYETI=";
  int kisayol_maliyeti=maliyet(kisayol_kenarlar,kenar_sayisi);
  textprintf_ex(screen ,font ,160,540, makecol( 255, 0, 0) ,makecol( 500, 500, 500) ,"%s",yazi);
  textprintf_ex(screen ,font ,370,540, makecol( 255, 0, 0) ,makecol( 500, 500, 500) ,"%d",kisayol_maliyeti);
  release_screen();
  while(!key[KEY_ESC]){}//esc tusuna basildiginda olusturulan ekrandan cikilir
}
int main()
{
int N;
do{
cout<<"Olusturmak Istediginiz Graf Icin "<<endl<<"Girilecek Dugum Sayisi:"<<endl;
cin>>N;
if(N>400) cout<<"!!!!!!!20X20 TABLOYA 400 DUGUMDEN FAZLA GİRİLEMEZ!!!!!!!!!!!"<<endl;
}while(N>400);
dugum a[N];
graf_girisi(N,a);
int *matris=(int *)malloc(N*N*sizeof(int));
matris=komsuluk_matrisi(a,N);
kom_matris_yaz(matris,N);
kenar k[N*(N-1)];
mat_deg_ata(matris,N,a,k);
cout<<"GRAFLARIN KOMSULUGU VE MALIYETI:"<<endl;
for(int i=0;i<(N*N-N);i++){
    k[i].yaz();
    //komsuluk matrisinden graf kenarlarýna atamanýn dogrulugunu kontrol icin yapildi
}

kenar_sirala(k,N*(N-1));
cout<<"SIRALANMIS KENARLAR:"<<endl;
for(int i=0;i<(N*N-N);i++){
    k[i].yaz();
    //komsuluk matrisinden graf kenarlarina atamanin dogrulugunu kontrol icin yapildi
}

kenar *enkya_kenar[N*(N-1)];
cout<<"KISAYOL AGACI OLUSTURULUYOR:"<<endl;
int enkya_ken_sayisi=kruskal(k,a,N*(N-1),N,enkya_kenar);
cout<<"EN KISA YOL AGACI:"<<endl;
for(int i=0;i<enkya_ken_sayisi;i++){
        enkya_kenar[i]->yaz();
}
cout<<"Maliyeti:"<<maliyet(enkya_kenar,enkya_ken_sayisi);
grafik(enkya_kenar,enkya_ken_sayisi);

return 0;
}END_OF_MAIN();
