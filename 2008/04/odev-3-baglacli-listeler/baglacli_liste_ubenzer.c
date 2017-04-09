#include <stdio.h>
#include <stdlib.h>

#define NO 1
#define AD 2
#define STOK_LIMIT_YOK -1

/* Sabitler ve Anlamlari */
/* --------------------- */
/* NO               : urun_baglanacak fonksiyonun neye g�re geriye veri g�nderece�ini belirten sa-
                      bitlerden bir tanesi. AD ile ayn� olmamak ko�uluyla her �ey olabilir.
   AD               : urun_baglanacak fonksiyonun neye g�re geriye veri g�nderece�ini belirten sa-
                      bitlerden bir tanesi. NO ile ayn� olmamak ko�uluyla her �ey olabilir.
   STOK_LIMIT_YOK   : �lgili fonksiyonun parametresindeki stok limiti k�sm�n� g�z ard� etmesini sa�layan
                      sabit. Negatif herhangi bir say� ile de�i�tirilebilir.
*/

/* Yap�lar */
struct URUN_YAPI {
    int urun_kodu;
    char urun_adi[20];
    float birim_alis_fiyati;
    int stok_miktari;
    struct URUN_YAPI *sonraki;
    struct URUN_YAPI *sonraki_ad;
    struct SATIS_YAPI *link;
};

struct SATIS_YAPI {
    char fatura_no[6];
    char satis_tarihi[6];
    int satis_miktari;
    float birim_satis_fiyati;
    struct SATIS_YAPI *sonraki;
};

/* Kullan�c� tan�ml� tipler */
typedef struct URUN_YAPI URUN;
typedef struct SATIS_YAPI SATIS;

void beklet() {
    /* Bu fonksiyonun tek amaci kullaniciyi bir tusa basana kadar
       bekletmek, ve sonra ekrani silmektir. */
    printf("\nDevam etmek icin bir tusa basin.");
    getche();
    system ("cls");
}

void urun_baglanacak(URUN *liste_basi, int urun_kodu, char urun_adi[20], int ne, URUN **gonderilecek) {

    /* Ne parametresinde ald��� bilgiye g�re urun_kodu ya da urun_adi'ne g�re guncel listede
       arama yapar ve �r�n kodu/ad�'ndan bir k���k koda/ada sahip �r�n�n bellekteki adresini g�nderir.
       (yoksa listeba��) */

    URUN *guncel;

    if (ne == NO) { /* �r�n koduna g�re s�ralayacak ve bir adres g�nderece�iz. */

        guncel = liste_basi->sonraki; /* G�ncel en ba�ta 1.kay�t olsun */
        *gonderilecek = liste_basi;

        /* Dikkat: Yukar�daki sat�ra dikkat edilirse, e�er liste bo�sa while d�ng�s�ne girilmeyecektir. */

        while(guncel != liste_basi) { /* Ba�tan ba�la geriye d�nene kadar u� */

            if (guncel->urun_kodu >= urun_kodu) {
                return 0;
            }

            *gonderilecek = guncel; /* Bir �ncekini g�nderece�imiz i�in bir yerde tutmak laz�m geliyor. */
            guncel = guncel->sonraki; /* Bir sonraki kay�da u�al�m. */

        }

        return 0; /* E�er buraya geldiyse e�le�me yok demektir. */

    } else { /* �sme g�re s�ralayacak ve bir adres g�nderece�iz. */

        guncel = liste_basi->sonraki_ad; /* G�ncel en ba�ta 1.kay�t olsun */
        *gonderilecek = liste_basi;

        /* Dikkat: Yukar�daki sat�ra dikkat edilirse, e�er liste bo�sa while d�ng�s�ne girilmeyecektir. */

        while(guncel != liste_basi) { /* Ba�tan ba�la geriye d�nene kadar u� */

            if (strncmp(guncel->urun_adi,urun_adi,20) >=0) {
                return 0;
            }

            *gonderilecek = guncel; /* Bir �ncekini g�nderece�imiz i�in bir yerde tutmak laz�m geliyor. */
            guncel = guncel->sonraki_ad; /* Bir sonraki kay�da u�al�m. */

        }

        return 0; /* E�er buraya geldiyse e�le�me yok demektir. */

    }

}

void urun_ekle(URUN *liste_basi, int urun_kodu, char urun_adi[20], float birim_alis_fiyati, int stok_miktari) {

    URUN *adres;
    int sayac;
    URUN *onceki_urun;

    adres=malloc(sizeof(URUN)); /* Az�c�k bellek tahsis edelim kendimize. */

    /* ��ine gerekli verileri yazal�m. */
    adres->urun_kodu = urun_kodu;
    for (sayac=0;sayac<20;sayac++) {
        adres->urun_adi[sayac] = urun_adi[sayac];
    }
    adres->birim_alis_fiyati = birim_alis_fiyati;
    adres->stok_miktari = stok_miktari;
    adres->link = NULL;
    /* Yazd�k. */

    /* �imdi �ncesini sonras�n� ayarlayal�m ki dairesel bir ba�la� olu�sun. */

    /* Numaraya g�re */
    urun_baglanacak(liste_basi,urun_kodu,urun_adi,NO,&onceki_urun);

    adres->sonraki = onceki_urun->sonraki;
    onceki_urun->sonraki = adres;
    /* Ada g�re */

    urun_baglanacak(liste_basi,urun_kodu,urun_adi,AD,&onceki_urun);

    adres->sonraki_ad = onceki_urun->sonraki_ad;
    onceki_urun->sonraki_ad = adres;

    /* Burada da ba�lant�lar ayarlanacak ama �imdi diil */

}

int urun_var_mi(URUN *liste_basi, int urun_kodu) {

    /* 1: �r�n var
       0: �r�n yok */

    URUN *guncel;

    guncel = liste_basi->sonraki; /* G�ncel en ba�ta 1.kay�t olsun */
    /* Dikkat: Yukar�daki sat�ra dikkat edilirse, e�er liste bo�sa while d�ng�s�ne girilmeyecektir. */

    while(guncel != liste_basi || guncel->urun_kodu > urun_kodu) { /* Ba�tan ba�la geriye d�nene kadar u� */

        if (guncel->urun_kodu == urun_kodu) {
            return 1;
        }

        guncel = guncel->sonraki; /* Bir sonraki kay�da u�al�m. */

    }

    return 0; /* E�er buraya geldiyse e�le�me yok demektir. */

}

void urun_duzenle(URUN *liste_basi, int urun_kodu, float birim_alis_fiyati, int stok_miktari) {

    URUN *guncel;

    guncel = liste_basi->sonraki; /* G�ncel en ba�ta 1.kay�t olsun */
    /* Dikkat: Yukar�daki sat�ra dikkat edilirse, e�er liste bo�sa while d�ng�s�ne girilmeyecektir. */

    while(guncel != liste_basi) { /* Ba�tan ba�la geriye d�nene kadar u� */

        if (guncel->urun_kodu == urun_kodu) {

            guncel->birim_alis_fiyati = birim_alis_fiyati;
            guncel->stok_miktari = stok_miktari;
            return 0;
        }

        guncel = guncel->sonraki; /* Bir sonraki kay�da u�al�m. */
    }
}

void urun_listele(URUN *liste_basi, int stok_miktari,int ne) {

    URUN *guncel;

    printf("Urun Kodu        Urun Adi      Stok Miktari Bilim Alis Fiyati\n");
    printf("--------- -------------------- ------------ -----------------\n");

    if (ne == NO) { /* Liste numaraya g�re s�ral� g�sterilecek */

        guncel = liste_basi->sonraki; /* G�ncel en ba�ta 1.kay�t olsun */
        /* Dikkat: Yukar�daki sat�ra dikkat edilirse, e�er liste bo�sa while d�ng�s�ne girilmeyecektir. */

        while(guncel != liste_basi) { /* Ba�tan ba�la geriye d�nene kadar u� */

            if (stok_miktari == STOK_LIMIT_YOK || guncel->stok_miktari <= stok_miktari) {
                printf("%9d %20s %12d %17.2f %p %p %p\n",guncel->urun_kodu,guncel->urun_adi,guncel->stok_miktari,guncel->birim_alis_fiyati, guncel, guncel->sonraki, guncel->sonraki_ad);
            }
            guncel = guncel->sonraki; /* Bir sonraki kay�da u�al�m. */
        }

    } else { /* Liste ada g�re s�ral� g�sterilecek. */

        guncel = liste_basi->sonraki_ad; /* G�ncel en ba�ta 1.kay�t olsun */
        /* Dikkat: Yukar�daki sat�ra dikkat edilirse, e�er liste bo�sa while d�ng�s�ne girilmeyecektir. */

        while(guncel != liste_basi) { /* Ba�tan ba�la geriye d�nene kadar u� */

            if (stok_miktari == STOK_LIMIT_YOK || guncel->stok_miktari <= stok_miktari) {
                printf("%9d %20s %12d %17.2f\n",guncel->urun_kodu,guncel->urun_adi,guncel->stok_miktari,guncel->birim_alis_fiyati);
            }
            guncel = guncel->sonraki_ad; /* Bir sonraki kay�da u�al�m. */
        }

    }
}

void urun_sil(URUN *liste_basi, int urun_kodu) {

    URUN *guncel;
    URUN *onceki_urun;
    SATIS *sil_konum;

    guncel = liste_basi->sonraki; /* G�ncel en ba�ta 1.kay�t olsun */
    /* Dikkat: Yukar�daki sat�ra dikkat edilirse, e�er liste bo�sa while d�ng�s�ne girilmeyecektir. */

    while(guncel != liste_basi) { /* Ba�tan ba�la silenecek ��eyi bulana kadar u� */

        if (guncel->urun_kodu == urun_kodu) { /* ��e silinecek ��e! Silece�im seni nhahahaha! */

            /* �r�ne ba�l� sat��lar� silelim */

            sil_konum = guncel->link;
            while(sil_konum!=NULL) {
                sil_konum = sil_konum->sonraki;
                free(sil_konum);
            }

            /* Silmeden �nce �nceki kayd�n ba��n� sonrakine almal�y�z.*/

            /* Numaraya g�re bir �nceki �r�n� bul*/
            urun_baglanacak(liste_basi,urun_kodu,guncel->urun_adi,NO,&onceki_urun);
            onceki_urun->sonraki = guncel->sonraki;

            /* Ada g�re bir �nceki �r�n� bul */
            urun_baglanacak(liste_basi,urun_kodu,guncel->urun_adi,AD,&onceki_urun);
            onceki_urun->sonraki_ad = guncel->sonraki_ad;

            /* Sil gitsin */
            free(guncel);

            return 0;
        }

        guncel = guncel->sonraki; /* Bir sonraki kay�da u�al�m. */

    }

}

void satis_ekle(URUN *liste_basi, int urun_kodu, char fatura_no[6], char satis_tarihi[6], int satis_miktari, float birim_satis_fiyati) {

    URUN *guncel;
    SATIS *gezinti;
    SATIS *adres;
    SATIS *onceki;
    int sayac;
    adres=malloc(sizeof(SATIS)); /* Az�c�k bellek tahsis edelim kendimize. */

    /* ��ine gerekli verileri yazal�m. */
    for (sayac=0;sayac<6;sayac++) {
        adres->fatura_no[sayac] = fatura_no[sayac];
    }

    for (sayac=0;sayac<6;sayac++) {
        adres->satis_tarihi[sayac] = satis_tarihi[sayac];
    }
    adres->satis_miktari = satis_miktari;
    adres->birim_satis_fiyati = birim_satis_fiyati;
    /* Yazd�k. */

    guncel = liste_basi->sonraki; /* G�ncel en ba�ta 1.kay�t olsun */
    /* Dikkat: Yukar�daki sat�ra dikkat edilirse, e�er liste bo�sa while d�ng�s�ne girilmeyecektir. */

    while(guncel != liste_basi || guncel->urun_kodu > urun_kodu) {

        if (guncel->urun_kodu == urun_kodu) { /* �r�n� bulduk, hadi neymi� inceleyelim. */

            /* Durum 1: Daha �nce sat�� eklenmemi� olabilir. */

            if (guncel->link == NULL) { /* daha �nce �r�n eklemesi yap�lmam��. hemen ekliyoruz. */
                adres->sonraki = NULL;
                guncel->link = adres;
            } else {

                /* Durum 2: Yeni eklenen sat�� �imdiye kadarkilerin en b�y��� olabilir ki
                   �r�nler k�sm�nda de�i�iklik gerekir. */
                if(strncmp(satis_tarihi,(guncel->link)->satis_tarihi,6)>0) { /* Bu satirda hata yoksa hi�bir sat�rda yoktur art�k :) */
                    adres->sonraki = guncel->link;
                    guncel->link = adres;
                } else {
                    /* Durum 3: Yeni eklenen herhangi bir arada ya da en sonra olabilir. */
                    gezinti = guncel->link; /* Gezintiye ilk kayd�n adresini ata */

                    do  { /* Son kayda kadar */

                        if(strncmp(satis_tarihi,gezinti->satis_tarihi,6) > 0) {

                            adres->sonraki = gezinti;
                            onceki->sonraki = adres;
                            return 0;
                        }

                        onceki = gezinti;
                        gezinti = gezinti->sonraki;

                    } while (gezinti != NULL);

                    adres->sonraki = gezinti;
                    onceki->sonraki = adres;
                }
            }
        }
        guncel = guncel->sonraki; /* Bir sonraki kay�da u�al�m. */
    }
}

void satis_listele(URUN *liste_basi, int urun_kodu) {

    URUN *guncel;
    SATIS *gezinti;

    printf("%d numarali urunun satis listesi\n",urun_kodu);
    printf("\n");
    printf("FATURA NO SATIS TARIHI SATIS MIKTARI BIRIM SATIS FIYATI\n");
    printf("--------- ------------ ------------- ------------------\n");

    guncel = liste_basi->sonraki; /* G�ncel en ba�ta 1.kay�t olsun */
    /* Dikkat: Yukar�daki sat�ra dikkat edilirse, e�er liste bo�sa while d�ng�s�ne girilmeyecektir. */

    while(guncel != liste_basi) {

        if (guncel->urun_kodu == urun_kodu) { /* �r�n� bulduk, hadi ekrana sat��lar� yazal�m. */

            if (guncel->link == NULL) { /* heheee ��kertemezsiniz */

                printf("(satis kaydi yok)\n");
                return 0;

            } else {

                gezinti = guncel->link;
                while (gezinti != NULL) {
                    printf("   %c%c%c%c%c%c       %c%c%c%c%c%c %13d %18.4f \n",gezinti->fatura_no[0],gezinti->fatura_no[1],gezinti->fatura_no[2],gezinti->fatura_no[3],gezinti->fatura_no[4],gezinti->fatura_no[5],gezinti->satis_tarihi[0],gezinti->satis_tarihi[1],gezinti->satis_tarihi[2],gezinti->satis_tarihi[3],gezinti->satis_tarihi[4],gezinti->satis_tarihi[5],gezinti->satis_miktari,gezinti->birim_satis_fiyati);
                    gezinti = gezinti->sonraki;
               }
            }
            return 0;
        }
        guncel = guncel->sonraki; /* Bir sonraki kay�da u�al�m. */
    }

}

void tum_urun_top_satis(URUN *liste_basi) {

    URUN *guncel;
    SATIS *gezinti;

    int satis_urun;
    int satis_top=0;
    float ciro_urun;
    float ciro_top=0L;

    printf("Urun Kodu      Urun Adi        Toplam Satis Miktari Toplam Ciro\n");
    printf("--------- -------------------- -------------------- -----------\n");

    guncel = liste_basi->sonraki; /* G�ncel en ba�ta 1.kay�t olsun */
    /* Dikkat: Yukar�daki sat�ra dikkat edilirse, e�er liste bo�sa while d�ng�s�ne girilmeyecektir. */

    while(guncel != liste_basi) { /* Ba�tan ba�la geriye d�nene kadar u� */

        /* Sat��larla ilgili gerekli hesaplamalar� yapal�m */
        satis_urun = 0;
        ciro_urun = 0L;
        if (guncel->link != NULL) { /* heheee ��kertemezsiniz */
            gezinti = guncel->link;
            while (gezinti != NULL) {
                satis_urun += gezinti->satis_miktari;
                ciro_urun += gezinti->satis_miktari * gezinti->birim_satis_fiyati;

                gezinti = gezinti->sonraki;
           }
        }

        printf("%9d %20s %20d %11.4f\n",guncel->urun_kodu,guncel->urun_adi,satis_urun,ciro_urun);

        ciro_top += ciro_urun;
        satis_top += satis_urun;

        guncel = guncel->sonraki; /* Bir sonraki kay�da u�al�m. */
    }

    printf("---------------------------------------------------------------\n");
    printf("Toplam:                      %22d %11.4f\n",satis_top,ciro_top);

}

int main() {

    /* Acilis yazilari BASLANGICI */
    printf("Umut BENZER\n");
    printf("05-06-7670\n");
    printf("Ege Universitesi Bilgisayar Muhendisligi 1. Sinif\n");
    printf("http://www.ubenzer.com\n");
    printf("Odev 3\n\n");
    /* Acilis yazilari SONU */

    /* Verilerin tutalaca�� YAPILAR */

    URUN liste_basi;

    /* Verilerin tutulaca�� YAPILAR SONU */

    int sag_serbest=-1;
    int sayac;
    int girdi;
    char girdi2[20];
    float girdi3;
    int girdi4;
    char girdi5[6];
    char girdi6[6];
    char secenek;
    /* Girdi degiskenleri main fonksiyonun her bir yerinde
       farkli farkli bir s�r� ama�la kullan�ld��� i�in
       �zel isimler vermedim. */

    liste_basi.urun_kodu = -1;
    for (sayac=0;sayac<20;sayac++) {
        liste_basi.urun_adi[sayac] = '_';
    }
    liste_basi.birim_alis_fiyati = 0.0;
    liste_basi.stok_miktari = 0;
    liste_basi.sonraki = &liste_basi;
    liste_basi.sonraki_ad = &liste_basi;
    liste_basi.link = NULL;

    /* Ana d�ng� */
    while (sag_serbest==-1) {

        /* menu BASLANGICI */
        printf("*** Menu *** \n\n");
        printf("1. Yeni bir urunun eklenmesi \n");
        printf("2. Bir urunun birim alis fiyatinin ve stok miktarinin guncellenmesi \n");
        printf("3. Bir urune iliskin satis eklenmesi \n");
        printf("4. Bir urunun silinmesi \n");
        printf("5. Bir urunden yapilan tum satislarin listelenmesi \n");
        printf("6. Tum urunlerin koda gore sirali olarak listelenmesi \n");
        printf("7. Tum urunlerin ada gore sirali olarak listelenmesi \n");
        printf("8. Belirli bir stok miktarinin altinda urunlerin listelenmesi \n");
        printf("9. Tum urunlerden yapilan toplam satislarin listelenmesi \n");
        printf("C. Cikis \n");

        printf("Lutfen istediginiz islemin numarasini giriniz.\n");
        /*menu BITIMI */

        secenek=getche();
        system ("cls");

        /* secenek getche ile al�nd��� i�in ASCII koduna g�re switch yap�s�na sokulabilir. */

        /* Her CASE i�in a�a��daki not ge�erlidir. */

        /* Gerekli sa�ma sapan veri kontrolleri ve do�ru girdi
           i�in ilgili fonksiyonlar�n �a��r�lmas�, fonksiyon-
           lardan cevap al�nmas� ve bunlar�n i�lenmesi.

           Ayr�nt�l� bilgi i�in her fonksiyona ayr� ayr� baka-
           bilirsiniz.
        */

        switch(secenek) {
            case 49: //1

                system ("cls");
                printf("Yeni bir urun kodu giriniz: \n");
                scanf("%d",&girdi);
                system ("cls");

                switch (urun_var_mi(&liste_basi,girdi)) {

                    case 0: /* Ya�as�n do�ru girmi�ler. */

                        for (sayac=0;sayac<20;sayac++) {
                            girdi2[sayac] = NULL;
                        }

                        while (girdi2[0] == NULL) {
                            fflush(stdin);
                            printf("Yeni urunun adini giriniz: ");
                            gets(girdi2);
                        }

                        printf("Urunun alis fiyatini giriniz: ");
                        scanf("%f",&girdi3);

                        printf("Urunun stok durumunu giriniz: ");
                        scanf("%d",&girdi4);

                        urun_ekle(&liste_basi, girdi, girdi2, girdi3, girdi4);
                        printf("Islem tamam. ;)\n");
                        break;

                    case 1:
                        printf("Girdiginiz urun kodu daha once alinmis.\n");
                        break;
                }
                beklet();
                break;
            case 50: //2
                system ("cls");
                printf("Duzenlenecek urun kodunu giriniz: \n");
                scanf("%d",&girdi);
                system ("cls");

                switch (urun_var_mi(&liste_basi,girdi)) {

                    case 1: /* Ya�as�n do�ru girmi�ler. */

                        printf("Urunun yeni alis fiyatini giriniz: ");
                        scanf("%f",&girdi3);

                        printf("Urunun yeni stok durumunu giriniz: ");
                        scanf("%d",&girdi4);

                        urun_duzenle(&liste_basi, girdi, girdi3, girdi4);
                        printf("Islem tamam. ;)\n");
                        break;

                    case 0:
                        printf("Boyle bir urun yok. Bohuuu...\n");
                        break;
                }
                beklet();
                break;
            case 51: //3

                system ("cls");
                printf("Satis eklenecek urun kodunu giriniz: \n");
                scanf("%d",&girdi);
                system ("cls");

                switch (urun_var_mi(&liste_basi,girdi)) {

                    case 1: /* Evet var. */

                        for (sayac=0;sayac<6;sayac++) {
                            girdi5[sayac] = NULL;
                        }

                        while (girdi5[0] == NULL) {
                            fflush(stdin);
                            printf("Fatura kodunu giriniz (6 karakter): ");
                            gets(girdi5);
                        }


                        for (sayac=0;sayac<6;sayac++) {
                            girdi6[sayac] = NULL;
                        }

                        while (girdi6[0] == NULL) {
                            fflush(stdin);
                            /* �devin as�l amac�n�n tarihlerle de�il de
                               bellekle u�ra�mak oldu�u bilindi�inden
                               2000 �ncesi y�llar i�in s�ralama sorunu
                               ihmal edildi.
                            */
                            printf("Satis tarihini giriniz (YYAAGG): ");
                            gets(girdi6);
                        }

                        printf("Urunun satis miktarini giriniz: ");
                        scanf("%d",&girdi4);

                        printf("Birim satis fiyatini giriniz: ");
                        scanf("%f",&girdi3);

                        satis_ekle(&liste_basi, girdi, girdi5, girdi6, girdi4, girdi3);
                        printf("Islem tamam.");
                        break;

                    case 0: /* Hay�r, yok */
                        printf("Boyle bir urun yok.");
                        break;
                }
                beklet();
                break;
            case 52: //4

                system ("cls");
                printf("Silinecek urun kodunu giriniz: \n");
                scanf("%d",&girdi);
                system ("cls");

                switch (urun_var_mi(&liste_basi,girdi)) {

                    case 1: /* Ya�as�n do�ru girmi�ler. */
                        urun_sil(&liste_basi, girdi);
                        printf("Sildim bile.");
                        break;
                    case 0:
                        printf("Boyle bir urun zaten yok ki. :)\n");
                        break;
                }

                beklet();
                break;
            case 53: //5
                system ("cls");
                printf("Satislari listelenecek urun kodunu giriniz: \n");
                scanf("%d",&girdi);
                system ("cls");

                switch (urun_var_mi(&liste_basi,girdi)) {

                    case 1: /* Ya�as�n do�ru girmi�ler. */

                        satis_listele(&liste_basi, girdi);
                        break;

                    case 0:
                        printf("Boyle bir urun yok. Bohuuu...\n");
                        break;
                }
                beklet();
                break;
            case 54: //6
                urun_listele(&liste_basi, STOK_LIMIT_YOK, NO);
                beklet();
                break;
            case 55: //7
                urun_listele(&liste_basi, STOK_LIMIT_YOK, AD);
                beklet();
                break;

            case 56: //8
                girdi = STOK_LIMIT_YOK;
                while(girdi == STOK_LIMIT_YOK) {
                    system("cls");
                    printf("Kactan kucuk olsun istiyorsunuz? ");
                    scanf("%d",&girdi);
                }

                /* Dikkat: �devde istenmeyen ek �zelliktir. */

                system("cls");
                printf("Neye gore sirali istersiniz? (%d urun koduna gore, %d ada gore)",NO,AD);
                scanf("%d",&girdi4);

                urun_listele(&liste_basi, girdi, girdi4);
                beklet();
                break;

            case 57: //9

                tum_urun_top_satis(&liste_basi);
                beklet();
                break;
            case 99: //c
            case 67: //C
                /* E e H h ve disinda girdi kabul etmeyen cikmak istiyor musunuz sorusu BASLANGICI */
                do {
                    printf ("\nCidden cikmak istiyor musunuz? (E/H) ");
                    secenek = getche();
                    if (secenek == 'E' || secenek == 'e') {
                        sag_serbest = 0;
                        secenek = 'H';
                    }
                } while (secenek != 'H' && secenek != 'h');
                /* E e H h ve disinda girdi kabul etmeyen cikmak istiyor musunuz sorusu SONU */
                system ("cls");
                break;
            case 65:
                printf("There are no choices. Nothing but a straight line.  The  illusion\n");
                printf("comes afterwards, when you ask 'Why me?' and 'What if?'. When you\n");
                printf("look  back  and  see  the branches, like a pruned bonsai tree, or\n");
                printf("forked lightning. If  you  had  done  something  differently,  it\n");
                printf("wouldn't  be you. It would be someone else looking back, asking a\n");
                printf("different set of questions.              (a quote from Max Payne)\n");
                printf("\n\n");
                printf("Press any key to continue...");
                getche();
                system("cls");
                printf("Supriz Yumurta | Easter Egg\n");
                printf("Tebrikler, bu programin gizli ozelligini buldunuz. :)\n");
                printf("\n");
                printf("http://www.imdb.com/title/tt0366758/quotes\n");
                beklet();
                break;
            default:
                /* Elleri yanlis tusa basan kullanicilar icin yazilan bolum BASLANGICI */
                printf("Bir zahmet 1'den 9'a kadar bir secim yapin.");
                beklet();
                /* Elleri yanlis tusa basan kullanicilar icin yazilan bolum SONU */
                break;
        }
    }

    printf("O halde hoscakalin. :)\n\n\n");
    return 0;
}
