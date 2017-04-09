#include <stdio.h>
#include <stdlib.h>

#define URUN_NO_MIN 1
#define KAYIT_SAY 100
#define STOK_LIMIT_MIN 0
#define ALIS_FIYAT_MIN 0
#define LINK_AYNI -2
#define LINK_GONDER -3

/* Sabitler ve Anlamlari */
/* --------------------- */
/* URUN_NO_MIN      : �r�n numaras�n�n alabilece�i en d���k de�er. (negatif de�eler �zel parametre-
                      lere kar��l�k gelebilece�i i�in tercih edilmemelidir.)
   KAYIT_SAY        : Hash fonksiyonu ile gidilecek, ilk ba�ta yarat�lan k�s�m. Bu de�er oynanarak
                      ilk ba�ta ne kadar bo� kay�t olaca�� de�i�tirilebilir.
                      D�KKAT: Dosyalar yarat�ld�ktan sonra bunu de�i�tirmeniz sorun ��kart�r.
   STOK_LIMIT_MIN   : Stok de�erinin alabilece�i minimum de�erdir. Programda depoda olmayan bir �r�n�n
                      sat�lamayaca�� d���n�lerek bu sabit 0 al�nm��t�r. Ancak stok de�erinin - de�er-
                      lere de d��mesi isteniyorsa bu de�er de�i�tirilebilir.
   ALIS_FIYAT_MIN   : Birim al��/sat�� fiyatlar�n�n alabilece�i minimum de�eri belirler. Bir �r�n�n
                      en fazla bedava sat�laca�� (o da nedense) d���n�lm�� ve programda 0 ayarlanm��t�r.
                      Ama e�er �r�n� sat�p �st�ne de para verilmesi isteniyorsa bu de�i�ken her t�rl�
                      say� yap�labilir.
   LINK_AYNI        : urun_duzenle fonksiyonuna de�i�tirilen girdideki link de�erinin de�i�tirilmemesi
                      gerekti�ini s�yleyen sembolik sabittir.
   LINK_GONDER      : urun_duzenle fonksiyonuna g�nderildi�inde fonksyinonun urun_kodu ile g�nderilen
                      �r�ne ait link de�erini geri d�nd�rmesini sa�lar.

*/

/* Yap�lar */
struct URUN_YAPI {
    int urun_kodu;
    char urun_adi[20];
    float birim_alis_fiyati;
    int stok_miktari;
    int sonraki;
    int link;
};

struct SATIS_YAPI {
    char fatura_no[6];
    char satis_tarihi[6];
    int satis_miktari;
    float birim_satis_fiyati;
    int sonraki;
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

int hash(int urun_kodu) {
    return (urun_kodu % KAYIT_SAY) + 1;
}

int urun_var_mi(int urun_kodu,int kayit_no, int link_yolla) {

    /* �r�n�n olup olmad���n� kontrol eder. A�a��daki de�erlerden birini d�n�d�r�r. */

    /*  0: Urun yok.        */
    /* -1: Dosya a��lamad�. */
    /* -2: Urun var.        */

    FILE *fp;
    URUN oku;

    if ((fp=fopen ("urunler.dat","rb+"))== NULL) {
        printf("Urunler.dat acilamadi. Gidiyorum ben.");
        return -1;
    }

    if (kayit_no == -1) { /* E�er fonksiyona ilk defa geldiysek hash ile as�l kayd� kontrol etmeliyiz. */
        fseek(fp,(hash(urun_kodu) - 1) * sizeof(URUN),0);
    } else {
        fseek(fp,(kayit_no) * sizeof(URUN),0); /* E�er fonksiyon kendini �a��rd�ysa dosya sonuna gidip ba�layaca��z. */
    }

    fread(&oku,sizeof(URUN),1,fp);

    if (oku.urun_kodu == urun_kodu) {

        fclose(fp);
        if (link_yolla == 0) { /* E�er link numaras�n� g�nderme parametresiyse �a�r�ld�ysa */
            return oku.link;
        } else {
            return -2;
        }
    }

    if (oku.urun_kodu == -1) {
        fclose(fp);
        return 0;
    } else {
        if (oku.sonraki == -1) {
            fclose(fp);
            return 0;
        } else {
            fclose(fp);
            return urun_var_mi(urun_kodu, oku.sonraki, link_yolla);
        }
    }
}

int urun_ekle(int urun_kodu, char urun_adi[20], float birim_alis_fiyati, int stok_miktari, int kayit_no) {

    /* Ad� �st�nde: �r�n ekler */
    /*  0: Ba�ar�l�. */
    /* -1: Dosya a��lamad�. */

    FILE *fp;
    URUN oku;
    int sayac;
    int gecici_konum;

    if ((fp=fopen ("urunler.dat","rb+"))== NULL) {
        printf("Urunler.dat acilamadi. Gidiyorum ben.");
        return -1;
    }

    if (kayit_no == -1) { /* E�er fonksiyona ilk defa geliysek hash ile as�l kayd� kontrol etmeliyiz. */
        fseek(fp,(hash(urun_kodu) - 1) * sizeof(URUN),0);
    } else {
        fseek(fp,kayit_no * sizeof(URUN),0); /* E�er fonksiyon kendini �a��rd�ysa dosya sonuna gidip ba�layaca��z. */
    }

    fread(&oku,sizeof(URUN),1,fp);

    if (oku.urun_kodu == -1) {
        /* Buras� bo�, yazabiliriz. */

        /* Gerekli atamalar */
        oku.urun_kodu = urun_kodu;

        for (sayac=0;sayac<20;sayac++) {
            oku.urun_adi[sayac] = urun_adi[sayac];
        }

        oku.birim_alis_fiyati = birim_alis_fiyati;
        oku.stok_miktari = stok_miktari;
        oku.sonraki = -1;
        oku.link = -1;

        fseek(fp,-sizeof(URUN),1); // Denetlemek i�in ileri gitmi�tik, d�n geri.
        fwrite(&oku,sizeof(URUN),1,fp); // ve b�y�l� sat�r...
        fclose(fp);

    } else {
        /* Bu kay�t dolu, hadi ba�ka bulal�m. */

        /* E�er bu kay�t ba�l� listenin son kayd�ysa bu kayd� sonraki k�sm�n� de�i�tirerek yeniden yaz. */
        if (oku.sonraki == -1) {
            gecici_konum = ftell(fp);
            fseek(fp,0,2);
            oku.sonraki = ftell(fp)/sizeof(URUN);
            fseek(fp,gecici_konum,0);

            fseek(fp,-sizeof(URUN),1);
            fwrite(&oku,sizeof(URUN),1,fp);

            /* Sonra yeni eklenece�i ekleyelim. */
            fseek(fp,0,2);
            oku.sonraki = -1;
            oku.link = -1;
            oku.birim_alis_fiyati = birim_alis_fiyati;
            oku.stok_miktari = stok_miktari;
            oku.urun_kodu = urun_kodu;
            for (sayac=0;sayac<20;sayac++) {
                oku.urun_adi[sayac] = urun_adi[sayac];
            }

            fwrite(&oku,sizeof(URUN),1,fp);
            fclose(fp);

        } else { /* e�er ba�l� listenin son eleman� de�ilse onu bulana kadar ayn� algoritmay� tekrarla */
            fclose(fp);
            return urun_ekle(urun_kodu, urun_adi[20], birim_alis_fiyati, stok_miktari, oku.sonraki);
        }
    }

    return 0;
}

int urun_guncelle(int urun_kodu, float birim_alis_fiyati, int stok_miktari, int kayit_no, int link) {

    /*  0: Ba�ar�l�. */
    /* -1: Dosya a��lamad�. */

    FILE *fp;
    URUN oku;

    if ((fp=fopen ("urunler.dat","rb+"))== NULL) {
        printf("Urunler.dat acilamadi. Gidiyorum ben.");
        return -1;
    }

    if (kayit_no == -1) { /* E�er fonksiyona ilk defa geliysek hash ile as�l kayd� kontrol etmeliyiz. */
        fseek(fp,(hash(urun_kodu) - 1) * sizeof(URUN),0);
    } else {
        fseek(fp,kayit_no * sizeof(URUN),0); /* E�er fonksiyon kendini �a��rd�ysa dosya sonuna gidip ba�layaca��z. */
    }

    fread(&oku,sizeof(URUN),1,fp);

    if (oku.urun_kodu == urun_kodu) { /* ��te d�zenlenecek �r�n�m�z� bulduk, mutluyuz biz. :) */

        if (link == LINK_GONDER) {

            fclose(fp);
            return oku.link;

        } else {


            if (birim_alis_fiyati != ALIS_FIYAT_MIN - 1) {
                oku.birim_alis_fiyati = birim_alis_fiyati;
            }

            if (stok_miktari != STOK_LIMIT_MIN - 1) {
                oku.stok_miktari = stok_miktari;
            }

            if (link != LINK_AYNI) {
                oku.link = link;
            }

            fseek(fp,-sizeof(URUN),1); // Denetlemek i�in ileri gitmi�tik, d�n geri.
            fwrite(&oku,sizeof(URUN),1,fp); // ve b�y�l� sat�r...
            fclose(fp);

        }

    } else {
        /* Bu kay�t dolu, hadi ba�ka bulal�m. */
        fclose(fp);
        return urun_guncelle(urun_kodu, birim_alis_fiyati, stok_miktari, oku.sonraki, link);
    }

    return 0;
}

int satis_ekle(int urun_kodu, char fatura_no[6], char satis_tarihi[6], int satis_miktari, float birim_satis_fiyati, int sonraki, int simdiki) {

    /*  0: Sorunsuz tamam */
    /* -1: Dosya hatas� */

    FILE *fp;
    SATIS oku;
    int link_konum;
    int sayac;

    /* �nce urune bakal�m... E�er �r�ndeki link -1 ise bu �r�ne
       daha �nce sat�� eklenmemi�tir ki, ilk oldu�u i�in i�imiz
       �oooook basit olur. */

    if (sonraki == -2) { /* E�er fonksiyon kendini �a��rmad�ysa */

        link_konum = urun_var_mi(urun_kodu,-1,0);
        if (link_konum == -1) { /* O zaman linki yarataca��z. */

            if ((fp=fopen ("satislar.dat","rb+"))== NULL) {
                return -1;
            }

            fseek(fp,0,2); /* Dosya sonuna u�, ciiiik */
            link_konum = (ftell(fp) / sizeof(SATIS)) + 1;

            for (sayac=0;sayac<6;sayac++) {
                oku.fatura_no[sayac] = fatura_no[sayac];
            }

            for (sayac=0;sayac<6;sayac++) {
                oku.satis_tarihi[sayac] = satis_tarihi[sayac];
            }

            oku.satis_miktari = satis_miktari;
            oku.birim_satis_fiyati = birim_satis_fiyati;
            oku.sonraki = -1;

            fwrite(&oku,sizeof(SATIS),1,fp); // ve b�y�l� sat�r...
            fclose(fp);

            urun_guncelle(urun_kodu, ALIS_FIYAT_MIN - 1, STOK_LIMIT_MIN - 1, -2, link_konum);
            /* �u hayatta zaten ne oluyorsa ileti�imsizlikten kaynaklan�yor.
               Ba�lant�y� koparmamak laz�m. urunler.dat ile satislar.dat
               da yukar�daki sat�rla birbirine ba�lanacak. */
        } else {

        /* E�er o �r�ne dair daha �nceden bir sat�� kayd� varsa bu biraz u�ra�t�r�c�...
           T�m kay�tlar� s�radan gezmeye ba�layal�m, uygun olan ba�� bulal�m ve hooop
           yeni sat�� bilgilerini yazal�m.
        */
            return satis_ekle(urun_kodu, fatura_no, satis_tarihi, satis_miktari, birim_satis_fiyati, link_konum, simdiki);

        }

    } else {

        if ((fp=fopen ("satislar.dat","rb+"))== NULL) {
            return -1;
        }

        fseek(fp,(sonraki-1) * sizeof(SATIS),0);
        fread(&oku, sizeof(SATIS),1,fp);

        if (sonraki == -1 || strncmp(oku.satis_tarihi,satis_tarihi,6) < 0) { /* E�er girilen kay�t dosyadakinden daha b�y�kse i�lem yap�lacak */

            /* E�er sonraki != 0 AMA simdiki == -1 ise o zaman urunler.dat'dan ula��lan ilk sat��day�z demektir.
               E�er yeni kaydedece�imiz sat�� bu sat��tan �nce gelecekse o zaman urunler.dat'daki ba� da de�i�icek
               demektir ki i�te bunun i�in bu �zel �art� yerine getiren bir kod par�as� yazaca��m �imdi. */

            for (sayac=0;sayac<6;sayac++) {
                oku.fatura_no[sayac] = fatura_no[sayac];
            }

            for (sayac=0;sayac<6;sayac++) {
                oku.satis_tarihi[sayac] = satis_tarihi[sayac];
            }

            oku.satis_miktari = satis_miktari;
            oku.birim_satis_fiyati = birim_satis_fiyati;
            oku.sonraki = sonraki;

            fseek(fp,0,2); /* Dosya sonuna ���nlan */
            link_konum = (ftell(fp) / sizeof(SATIS)) + 1;
            fwrite(&oku,sizeof(SATIS),1,fp);

            if (simdiki == -1) {
                /* �nceki ba� d�zelt */

                fclose(fp);
                urun_guncelle(urun_kodu, ALIS_FIYAT_MIN - 1, STOK_LIMIT_MIN - 1, -2, link_konum);

            } else {

                fseek(fp,(simdiki-1) * sizeof(SATIS),0);
                fread(&oku, sizeof(SATIS),1,fp);
                fseek(fp,-sizeof(SATIS),1);
                oku.sonraki = link_konum;
                fwrite(&oku,sizeof(SATIS),1,fp);

                fclose(fp);
            }

        } else { /* Yok girilen kay�t dosyadakinden daha b�y�k de�ilse bir s�k�nt� yok, taramaya devam... */

            return satis_ekle(urun_kodu, fatura_no, satis_tarihi, satis_miktari, birim_satis_fiyati, oku.sonraki, sonraki);
        }
    }

    return 0;
}

int satis_listele(int urun_kodu, char ust_limit[6], char alt_limit[6]) {

    /*  0: Ba�ar�l�. */
    /* -1: Dosya a��lamad�. */

    FILE *fp;
    SATIS oku;
    int sayac=0;
    int konum;

    printf("%d numarali urunun satis listesi\n",urun_kodu);
    printf("\n");
    printf(" NO  FATURA NO SATIS TARIHI SATIS MIKTARI BIRIM SATIS FIYATI\n");
    printf("---- --------- ------------ ------------- ------------------\n");

    konum = urun_guncelle(urun_kodu, ALIS_FIYAT_MIN-1,STOK_LIMIT_MIN-1,-1,LINK_GONDER);
    if (konum == -1) {
        printf("(hic satis kaydi yok.)\n");
        return 0;
    }

    if ((fp=fopen ("satislar.dat","rb+"))== NULL) {
        return -1;
    }

    while (konum != -1) {
        fseek(fp,(konum-1) * sizeof(SATIS),0);
        fread(&oku,sizeof(SATIS),1,fp);
        konum = oku.sonraki;

        if (strncmp(oku.satis_tarihi,alt_limit,6) >= 0 && strncmp(oku.satis_tarihi,ust_limit,6) <= 0 && oku.fatura_no[0] != '|') {
            sayac++;
            printf("%4d    %c%c%c%c%c%c       %c%c%c%c%c%c %13d %18.4f \n",sayac,oku.fatura_no[0],oku.fatura_no[1],oku.fatura_no[2],oku.fatura_no[3],oku.fatura_no[4],oku.fatura_no[5],oku.satis_tarihi[0],oku.satis_tarihi[1],oku.satis_tarihi[2],oku.satis_tarihi[3],oku.satis_tarihi[4],oku.satis_tarihi[5],oku.satis_miktari,oku.birim_satis_fiyati);
        }
    }

    fclose(fp);

}

int satis_sil(int urun_kodu, char fatura_no[6]) {

    /*  1: �yle bir fatura no yok */
    /*  0: Ba�ar�l�. */
    /* -1: Dosya a��lamad�. */

    FILE *fp;
    SATIS oku;
    int konum;

    konum = urun_guncelle(urun_kodu, ALIS_FIYAT_MIN-1,STOK_LIMIT_MIN-1,-1,LINK_GONDER);
    if (konum == -1) {
        return 1;
    }

    if ((fp=fopen ("satislar.dat","rb+"))== NULL) {
        return -1;
    }

    while (konum != -1) {
        fseek(fp,(konum-1) * sizeof(SATIS),0);
        fread(&oku,sizeof(SATIS),1,fp);
        konum = oku.sonraki;

        if (strncmp(oku.fatura_no,fatura_no,6) == 0) { /* EVET! Silinecek faturay� bulduk!!!!! */
            fseek(fp,-sizeof(SATIS),1);
            oku.fatura_no[0] = '|';
            fwrite(&oku,sizeof(SATIS),1,fp);
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);
    return 1;
}

void listele() {

    /* Bu fonksiyon kontrol i�in, as�l programda i�e yaramaz. */
    FILE *fp;
    URUN urun;
    int sayac=0;
    int gecici;
    if ((fp=fopen ("urunler.dat","rb+"))== NULL) {
        printf("Urunler.dat acilamadi. Gidiyorum ben.");
        return -1;
    }

    fseek(fp,0,2);
    gecici = ftell(fp)/sizeof(URUN);
    printf("Kayit sayisi: %d\n\n", gecici);
    fseek(fp,0,0);

    for (sayac=1;sayac<=gecici;sayac++) {
        fread(&urun,sizeof(URUN),1,fp);
        printf("%3d %4d %20s %6.2f %2d %4d %2d\n",sayac,urun.urun_kodu,urun.urun_adi,urun.birim_alis_fiyati,urun.stok_miktari, urun.sonraki, urun.link);
    }

    fclose(fp);
}

void listele2() {

    /* Bu fonksiyon kontrol i�in, as�l programda i�e yaramaz. */

    FILE *fp;
    SATIS urun;
    int sayac=0;
    int gecici;
    if ((fp=fopen ("satislar.dat","rb+"))== NULL) {
        printf("satislar.dat acilamadi.");
        return -1;
    }

    fseek(fp,0,2);
    gecici = ftell(fp)/sizeof(SATIS);
    printf("Kayit sayisi: %d\n\n", gecici);
    fseek(fp,0,0);

    for (sayac=1;sayac<=gecici;sayac++) {
        fread(&urun,sizeof(SATIS),1,fp);
        printf("%3d %c%c%c%c%c%c %c%c%c%c%c%c %5d %6.2f %2d\n",sayac,urun.fatura_no[0],urun.fatura_no[1],urun.fatura_no[2],urun.fatura_no[3],urun.fatura_no[4],urun.fatura_no[5],urun.satis_tarihi[0],urun.satis_tarihi[1],urun.satis_tarihi[2],urun.satis_tarihi[3],urun.satis_tarihi[4],urun.satis_tarihi[5],urun.satis_miktari,urun.birim_satis_fiyati,urun.sonraki);
    }

    fclose(fp);
}

int main() {

    /* Acilis yazilari BASLANGICI */
    printf("Umut BENZER\n");
    printf("05-06-7670\n");
    printf("Ege Universitesi Bilgisayar Muhendisligi 1. Sinif\n");
    printf("http://www.ubenzer.com\n");
    printf("Odev 4 (0.1)\n\n");
    /* Acilis yazilari SONU */

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

    /* Dosyayi sifirdan yaratalim */
    /* Odev kontrolunde kolaylik saglamasi acisindan dosyanin
       her acilista silinmesi ve tekrar yaratilmasi istendi.
       Programin gerceginde bunun iptal edilmesini saglamak icin
       asagidaki satirlar comment yapilabilir. */

    FILE *fp;
    URUN yaz={-1,"",0,0,-1,-1};

    remove ("urunler.dat");  // E�er dosyalar varsa silinir.
    remove ("satislar.dat"); // E�er dosyalar varsa silinir.

    if ((fp=fopen ("urunler.dat","w+b"))== NULL) {
        printf("Urunler.dat yaratilamadi. Gidiyorum ben.");
        return 0;
    }

    for (sayac=0;sayac<KAYIT_SAY;sayac++) {
        fwrite(&yaz,sizeof(URUN),1,fp);
    }

    fclose(fp);

    if ((fp=fopen ("satislar.dat","w+b"))== NULL) {
        printf("Satislar.dat yaratilamadi. Gidiyorum ben.");
        return 0;
    }

    fclose(fp);

    /* Dosyayi sifirdan yaratalim k�sm�nn�n SONU */


    /* Ana d�ng� */
    while (sag_serbest==-1) {

         // E�er her ba�lang��ta �r�ner.dat'�n i�er�ini g�rmek istiyorsan�z commenti kald�r�n.

        /*
        listele();
        beklet();
        listele2();
        beklet();


        /* menu BASLANGICI */
        printf("*** Menu *** \n\n");
        printf("1. Yeni bir urunun eklenmesi \n");
        printf("2. Bir urunun birim alis fiyatinin ve stok miktarinin guncellenmesi \n");
        printf("3. Bir urune iliskin satis eklenmesi \n");
        printf("4. Bir urune iliskin satisin silinmesi \n");
        printf("5. Bir urunden yapilan tum satislarin listelenmesi \n");
        printf("6. Bir urunden iki tarih arasinda yapilen tum satislarin listelenmesi \n");
        printf("7. Cikis \n");

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

                girdi = -1;
                while (girdi < URUN_NO_MIN) {
                    system ("cls");
                    printf("Yeni bir urun kodu giriniz: \n");
                    printf("Zaten var olan bir urunun ustune\n");
                    printf("yazmaya calisirsaniz uyarilacaksiniz.)\n");
                    scanf("%d",&girdi);
                }
                system ("cls");

                switch (urun_var_mi(girdi,-1,-1)) {

                    case 0: /* Hay�r, yok. */

                        for (sayac=0;sayac<20;sayac++) {
                            girdi2[sayac] = NULL;
                        }

                        while (girdi2[0] == NULL) {
                            fflush(stdin);
                            printf("Yeni urunun adini giriniz: ");
                            gets(girdi2);
                        }

                        girdi3 = ALIS_FIYAT_MIN - 1;
                        while (girdi3 < ALIS_FIYAT_MIN) {
                            printf("Urunun alis fiyatini giriniz: ");
                            scanf("%f",&girdi3);
                        }

                        girdi4 = STOK_LIMIT_MIN-1;
                        while (girdi4 < STOK_LIMIT_MIN) {
                            printf("Urunun stok durumunu giriniz: ");
                            scanf("%d",&girdi4);
                        }

                        switch (urun_ekle(girdi,girdi2,girdi3,girdi4,-1)) {
                            case -1:
                                printf("Dosya acilamadi. :(");
                                break;
                            case 0:
                                printf("Ekleme basarili. Tebrik ederim. :)");
                                break;
                        }
                        break;

                    case -1:
                        printf("Dosya acilamadi. :(");
                        break;

                    case -2:
                        printf("Girdiginiz urun kodu daha once alinmis.");
                        break;
                }

                beklet();
                break;
            case 50: //2

                girdi = -1;
                while (girdi < URUN_NO_MIN) {
                    system ("cls");
                    printf("Duzenlenecek urun kodunu giriniz: \n");
                    scanf("%d",&girdi);
                }
                system ("cls");

                switch (urun_var_mi(girdi,-1,-1)) {

                    case -2: /* Evet var. */

                        girdi3 = ALIS_FIYAT_MIN - 1;
                        while (girdi3 < ALIS_FIYAT_MIN) {
                            printf("Urunun yeni alis fiyatini giriniz: ");
                            scanf("%f",&girdi3);
                        }

                        girdi4 = STOK_LIMIT_MIN-1;
                        while (girdi4 < STOK_LIMIT_MIN) {
                            printf("Urunun yeni stok durumunu giriniz: ");
                            scanf("%d",&girdi4);
                        }

                        switch (urun_guncelle(girdi,girdi3,girdi4,-1,LINK_AYNI)) {
                            case -1:
                                printf("Dosya acilamadi. :(");
                                break;
                            case 0:
                                printf("Duzenleme basarili. Tebrik ederim. :)");
                                break;
                        }
                        break;

                    case -1:
                        printf("Dosya acilamadi. :(");
                        break;

                    case 0: /* Hay�r, yok */
                        printf("Boyle bir urun yok.");
                        break;
                }
                beklet();
                break;

            case 51: //3

                girdi = -1;
                while (girdi < URUN_NO_MIN) {
                    system ("cls");
                    printf("Satis eklenecek urun kodunu giriniz: \n");
                    scanf("%d",&girdi);
                }
                system ("cls");

                switch (urun_var_mi(girdi,-1,-1)) {

                    case -2: /* Evet var. */

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
                               dosyalamayla u�ra�mak oldu�u bilindi�inden
                               2000 �ncesi y�llar i�in s�ralama sorunu
                               ihmal edildi.
                            */
                            printf("Satis tarihini giriniz (YYAAGG): ");
                            gets(girdi6);
                        }

                        girdi4 = STOK_LIMIT_MIN-1;
                        while (girdi4 < STOK_LIMIT_MIN) {
                            printf("Urunun satis miktarini giriniz: ");
                            scanf("%d",&girdi4);
                        }

                        girdi3 = ALIS_FIYAT_MIN - 1;
                        while (girdi3 < ALIS_FIYAT_MIN) {
                            printf("Birim satis fiyatini giriniz: ");
                            scanf("%f",&girdi3);
                        }

                        switch (satis_ekle(girdi, girdi5, girdi6, girdi4, girdi3,-2,-1)) {
                            case -1:
                                printf("Dosya acilamadi. :(");
                                break;
                            case 0:
                                printf("Satis eklendi. Oleeey!");
                                break;
                        }

                        break;
                    case -1:
                        printf("Dosya acilamadi. :(");
                        break;

                    case 0: /* Hay�r, yok */
                        printf("Boyle bir urun yok.");
                        break;
                }
                beklet();
                break;
            case 52: //4

               girdi = -1;
                while (girdi < URUN_NO_MIN) {
                    system ("cls");
                    printf("Ilgili urun kodunu giriniz: \n");
                    scanf("%d",&girdi);
                }
                system ("cls");

                switch (urun_var_mi(girdi,-1,-1)) {

                    case -2: /* Evet var. */

                        for (sayac=0;sayac<6;sayac++) {
                            girdi5[sayac] = NULL;
                        }

                        while (girdi5[0] == NULL) {
                            fflush(stdin);
                            printf("Silinecek fatura kodunu giriniz (6 karakter): ");
                            gets(girdi5);
                        }


                        switch (satis_sil(girdi, girdi5)) {
                            case -1:
                                printf("Dosya acilamadi. :(");
                                break;
                            case 0:
                                printf("Satis bilgisi silindi.");
                                break;
                            case 1:
                                printf("Boyle bir fatura yok. Silinemedi.");
                                break;
                        }

                        break;
                    case -1:
                        printf("Dosya acilamadi. :(");
                        break;

                    case 0: /* Hay�r, yok */
                        printf("Boyle bir urun yok.");
                        break;
                }
                beklet();
                break;
            case 53: //5
                girdi = -1;
                while (girdi < URUN_NO_MIN) {
                    system ("cls");
                    printf("Satis listesi gosterilecek urun kodunu giriniz: \n");
                    scanf("%d",&girdi);
                }
                system ("cls");

                switch (urun_var_mi(girdi,-1,-1)) {

                    case -2: /* Evet var. */
                        satis_listele(girdi, "999999", "000000");
                        break;
                    case -1:
                        printf("Dosya acilamadi. :(");
                        break;

                    case 0: /* Hay�r, yok */
                        printf("Boyle bir urun yok.");
                        break;
                }
                beklet();
                break;
            case 54: //6

                girdi = -1;
                while (girdi < URUN_NO_MIN) {
                    system ("cls");
                    printf("Satis listesi gosterilecek urun kodunu giriniz: \n");
                    scanf("%d",&girdi);
                }
                system ("cls");

                switch (urun_var_mi(girdi,-1,-1)) {

                    case -2: /* Evet var. */

                        for (sayac=0;sayac<6;sayac++) {
                            girdi5[sayac] = NULL;
                        }

                        while (girdi5[0] == NULL) {
                            fflush(stdin);
                            printf("Ust limiti girin (yyaagg): ");
                            gets(girdi5);
                        }
                        system ("cls");

                        for (sayac=0;sayac<6;sayac++) {
                            girdi6[sayac] = NULL;
                        }

                        while (girdi6[0] == NULL) {
                            fflush(stdin);
                            printf("Alt limiti girin (yyaagg): ");
                            gets(girdi6);
                        }
                        system ("cls");

                        satis_listele(girdi, girdi5, girdi6);
                        break;
                    case -1:
                        printf("Dosya acilamadi. :(");
                        break;

                    case 0: /* Hay�r, yok */
                        printf("Boyle bir urun yok.");
                        break;
                }
                beklet();
                break;
            case 55: //7
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
            default:
                /* Elleri yanlis tusa basan kullanicilar icin yazilan bolum BASLANGICI */
                printf("Bir zahmet 1'den 7'ye kadar bir secim yapin.");
                beklet();
                /* Elleri yanlis tusa basan kullanicilar icin yazilan bolum SONU */
                break;
        }
    }

    printf("O halde hoscakalin. :)\n\n\n");
    return 0;
}
