#include <stdio.h>
#include <stdlib.h>

int main() {
    int sayi,basamak1,basamak2,basamak3,basamak4;
    //kullanicidan alinacak sayi ve islemlerde kullanilacak degiskenler
    printf("Lutfen -9999 ile +9999 arasinda bir tamsayi giriniz!\n");
    scanf("%d",&sayi);
    //kullanicidan alinan sayiyi sayi degiskenine atiyor.
    if(sayi==0) {
        printf("Sifir");
        return 0;
        //sayi sifir ise islemlere girmeden yaziyor ve programdan cikiyor.
    } if((sayi<-9999)||(sayi>9999)) {
        printf("Hatali Girdi!");
        return 0;
        //sayi -9999dan kucuk ya da 9999dan buyukse hata verip programdan cikiyor.
    } else if((sayi<0)&&(sayi>=-9999)) {
        sayi=sayi*-1;
        printf("eksi");
        //sayi negatif ise sayiyi pozitif tamsayiya cevirip, basina eksi yazdýrýyor.
    }
    /*buradan itiaren sayimiz artýk her sekilde pozitif ve hata kontrollerinin en basinda yapilmis
    olmasindan dolayi 0 ile 10000 arasinda. */
    basamak1=sayi%10;
    basamak2=(sayi%100)/10;
    basamak3=(sayi%1000)/100;
    basamak4=sayi/1000;
    /*bize lazim olan basamak degerlerini veren islemler dizisi. basamak1 icin yalnizca 10a gore
    mod aliniyor, boylece birler basamagi elde ediliyor. basamak2 icin 100e gore mod alinip 10 a
    kalansiz bolunme yapiliyor ki birler basamagi islem disi kalsin. diger basamaklar icin de
    benzeri sekilde devam ediyor. */
    switch(basamak4){
        case 1: printf("bin");
                break;
        case 2: printf("ikibin");
                break;
        case 3: printf("ucbin");
                break;
        case 4: printf("dortbin");
                break;
        case 5: printf("besbin");
                break;
        case 6: printf("altibin");
                break;
        case 7: printf("yedibin");
                break;
        case 8: printf("sekizbin");
                break;
        case 9: printf("dokuzbin");
                break;
        default: printf("");
                break;
        //binler basamagi varsa degerini yaziyor, yoksa yazmadan geciyor.
    }
    switch(basamak3){
        case 1: printf("yuz");
                break;
        case 2: printf("ikiyuz");
                break;
        case 3: printf("ucyuz");
                break;
        case 4: printf("dortyuz");
                break;
        case 5: printf("besyuz");
                break;
        case 6: printf("altiyuz");
                break;
        case 7: printf("yediyuz");
                break;
        case 8: printf("sekizyuz");
                break;
        case 9: printf("dokuzyuz");
                break;
        default: printf("");
                break;
        //yuzler basamagi varsa degerini yaziyor, yoksa atlayýp geciyor.
    }
    switch(basamak2){
        case 1: printf("on");
                break;
        case 2: printf("yirmi");
                break;
        case 3: printf("otuz");
                break;
        case 4: printf("kirk");
                break;
        case 5: printf("elli");
                break;
        case 6: printf("altmis");
                break;
        case 7: printf("yetmis");
                break;
        case 8: printf("seksen");
                break;
        case 9: printf("doksan");
                break;
        default: printf("");
                break;
        //onlar basamagini kontrol ediyor, varsa yaziyor, yoksa atliyor.
    }
    switch(basamak1){
        case 1: printf("bir");
                break;
        case 2: printf("iki");
                break;
        case 3: printf("uc");
                break;
        case 4: printf("dort");
                break;
        case 5: printf("bes");
                break;
        case 6: printf("alti");
                break;
        case 7: printf("yedi");
                break;
        case 8: printf("sekiz");
                break;
        case 9: printf("dokuz");
                break;
        default: printf("");
                break;
        //son olarak birler basamagini kontrol ediyor ve yazdiriyor.
    }
    return 0;
}
