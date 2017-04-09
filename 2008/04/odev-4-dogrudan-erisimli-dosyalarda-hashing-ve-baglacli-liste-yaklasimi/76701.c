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
/* URUN_NO_MIN      : Ürün numarasýnýn alabileceði en düþük deðer. (negatif deðeler özel parametre-
                      lere karþýlýk gelebileceði için tercih edilmemelidir.)
   KAYIT_SAY        : Hash fonksiyonu ile gidilecek, ilk baþta yaratýlan kýsým. Bu deðer oynanarak
                      ilk baþta ne kadar boþ kayýt olacaðý deðiþtirilebilir.
                      DÝKKAT: Dosyalar yaratýldýktan sonra bunu deðiþtirmeniz sorun çýkartýr.
   STOK_LIMIT_MIN   : Stok deðerinin alabileceði minimum deðerdir. Programda depoda olmayan bir ürünün
                      satýlamayacaðý düþünülerek bu sabit 0 alýnmýþtýr. Ancak stok deðerinin - deðer-
                      lere de düþmesi isteniyorsa bu deðer deðiþtirilebilir.
   ALIS_FIYAT_MIN   : Birim alýþ/satýþ fiyatlarýnýn alabileceði minimum deðeri belirler. Bir ürünün
                      en fazla bedava satýlacaðý (o da nedense) düþünülmüþ ve programda 0 ayarlanmýþtýr.
                      Ama eðer ürünü satýp üstüne de para verilmesi isteniyorsa bu deðiþken her türlü
                      sayý yapýlabilir.
   LINK_AYNI        : urun_duzenle fonksiyonuna deðiþtirilen girdideki link deðerinin deðiþtirilmemesi
                      gerektiðini söyleyen sembolik sabittir.
   LINK_GONDER      : urun_duzenle fonksiyonuna gönderildiðinde fonksyinonun urun_kodu ile gönderilen
                      ürüne ait link deðerini geri döndürmesini saðlar.

*/

/* Yapýlar */
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

/* Kullanýcý tanýmlý tipler */
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

    /* Ürünün olup olmadýðýný kontrol eder. Aþaðýdaki deðerlerden birini dönüdürür. */

    /*  0: Urun yok.        */
    /* -1: Dosya açýlamadý. */
    /* -2: Urun var.        */

    FILE *fp;
    URUN oku;

    if ((fp=fopen ("urunler.dat","rb+"))== NULL) {
        printf("Urunler.dat acilamadi. Gidiyorum ben.");
        return -1;
    }

    if (kayit_no == -1) { /* Eðer fonksiyona ilk defa geldiysek hash ile asýl kaydý kontrol etmeliyiz. */
        fseek(fp,(hash(urun_kodu) - 1) * sizeof(URUN),0);
    } else {
        fseek(fp,(kayit_no) * sizeof(URUN),0); /* Eðer fonksiyon kendini çaðýrdýysa dosya sonuna gidip baðlayacaðýz. */
    }

    fread(&oku,sizeof(URUN),1,fp);

    if (oku.urun_kodu == urun_kodu) {

        fclose(fp);
        if (link_yolla == 0) { /* Eðer link numarasýný gönderme parametresiyse çaðrýldýysa */
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

    /* Adý üstünde: Ürün ekler */
    /*  0: Baþarýlý. */
    /* -1: Dosya açýlamadý. */

    FILE *fp;
    URUN oku;
    int sayac;
    int gecici_konum;

    if ((fp=fopen ("urunler.dat","rb+"))== NULL) {
        printf("Urunler.dat acilamadi. Gidiyorum ben.");
        return -1;
    }

    if (kayit_no == -1) { /* Eðer fonksiyona ilk defa geliysek hash ile asýl kaydý kontrol etmeliyiz. */
        fseek(fp,(hash(urun_kodu) - 1) * sizeof(URUN),0);
    } else {
        fseek(fp,kayit_no * sizeof(URUN),0); /* Eðer fonksiyon kendini çaðýrdýysa dosya sonuna gidip baðlayacaðýz. */
    }

    fread(&oku,sizeof(URUN),1,fp);

    if (oku.urun_kodu == -1) {
        /* Burasý boþ, yazabiliriz. */

        /* Gerekli atamalar */
        oku.urun_kodu = urun_kodu;

        for (sayac=0;sayac<20;sayac++) {
            oku.urun_adi[sayac] = urun_adi[sayac];
        }

        oku.birim_alis_fiyati = birim_alis_fiyati;
        oku.stok_miktari = stok_miktari;
        oku.sonraki = -1;
        oku.link = -1;

        fseek(fp,-sizeof(URUN),1); // Denetlemek için ileri gitmiþtik, dön geri.
        fwrite(&oku,sizeof(URUN),1,fp); // ve büyülü satýr...
        fclose(fp);

    } else {
        /* Bu kayýt dolu, hadi baþka bulalým. */

        /* Eðer bu kayýt baðlý listenin son kaydýysa bu kaydý sonraki kýsmýný deðiþtirerek yeniden yaz. */
        if (oku.sonraki == -1) {
            gecici_konum = ftell(fp);
            fseek(fp,0,2);
            oku.sonraki = ftell(fp)/sizeof(URUN);
            fseek(fp,gecici_konum,0);

            fseek(fp,-sizeof(URUN),1);
            fwrite(&oku,sizeof(URUN),1,fp);

            /* Sonra yeni ekleneceði ekleyelim. */
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

        } else { /* eðer baðlý listenin son elemaný deðilse onu bulana kadar ayný algoritmayý tekrarla */
            fclose(fp);
            return urun_ekle(urun_kodu, urun_adi[20], birim_alis_fiyati, stok_miktari, oku.sonraki);
        }
    }

    return 0;
}

int urun_guncelle(int urun_kodu, float birim_alis_fiyati, int stok_miktari, int kayit_no, int link) {

    /*  0: Baþarýlý. */
    /* -1: Dosya açýlamadý. */

    FILE *fp;
    URUN oku;

    if ((fp=fopen ("urunler.dat","rb+"))== NULL) {
        printf("Urunler.dat acilamadi. Gidiyorum ben.");
        return -1;
    }

    if (kayit_no == -1) { /* Eðer fonksiyona ilk defa geliysek hash ile asýl kaydý kontrol etmeliyiz. */
        fseek(fp,(hash(urun_kodu) - 1) * sizeof(URUN),0);
    } else {
        fseek(fp,kayit_no * sizeof(URUN),0); /* Eðer fonksiyon kendini çaðýrdýysa dosya sonuna gidip baðlayacaðýz. */
    }

    fread(&oku,sizeof(URUN),1,fp);

    if (oku.urun_kodu == urun_kodu) { /* Ýþte düzenlenecek ürünümüzü bulduk, mutluyuz biz. :) */

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

            fseek(fp,-sizeof(URUN),1); // Denetlemek için ileri gitmiþtik, dön geri.
            fwrite(&oku,sizeof(URUN),1,fp); // ve büyülü satýr...
            fclose(fp);

        }

    } else {
        /* Bu kayýt dolu, hadi baþka bulalým. */
        fclose(fp);
        return urun_guncelle(urun_kodu, birim_alis_fiyati, stok_miktari, oku.sonraki, link);
    }

    return 0;
}

int satis_ekle(int urun_kodu, char fatura_no[6], char satis_tarihi[6], int satis_miktari, float birim_satis_fiyati, int sonraki, int simdiki) {

    /*  0: Sorunsuz tamam */
    /* -1: Dosya hatasý */

    FILE *fp;
    SATIS oku;
    int link_konum;
    int sayac;

    /* Önce urune bakalým... Eðer üründeki link -1 ise bu ürüne
       daha önce satýþ eklenmemiþtir ki, ilk olduðu için iþimiz
       çoooook basit olur. */

    if (sonraki == -2) { /* Eðer fonksiyon kendini çaðýrmadýysa */

        link_konum = urun_var_mi(urun_kodu,-1,0);
        if (link_konum == -1) { /* O zaman linki yaratacaðýz. */

            if ((fp=fopen ("satislar.dat","rb+"))== NULL) {
                return -1;
            }

            fseek(fp,0,2); /* Dosya sonuna uç, ciiiik */
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

            fwrite(&oku,sizeof(SATIS),1,fp); // ve büyülü satýr...
            fclose(fp);

            urun_guncelle(urun_kodu, ALIS_FIYAT_MIN - 1, STOK_LIMIT_MIN - 1, -2, link_konum);
            /* Þu hayatta zaten ne oluyorsa iletiþimsizlikten kaynaklanýyor.
               Baðlantýyý koparmamak lazým. urunler.dat ile satislar.dat
               da yukarýdaki satýrla birbirine baðlanacak. */
        } else {

        /* Eðer o ürüne dair daha önceden bir satýþ kaydý varsa bu biraz uðraþtýrýcý...
           Tüm kayýtlarý sýradan gezmeye baþlayalým, uygun olan baðý bulalým ve hooop
           yeni satýþ bilgilerini yazalým.
        */
            return satis_ekle(urun_kodu, fatura_no, satis_tarihi, satis_miktari, birim_satis_fiyati, link_konum, simdiki);

        }

    } else {

        if ((fp=fopen ("satislar.dat","rb+"))== NULL) {
            return -1;
        }

        fseek(fp,(sonraki-1) * sizeof(SATIS),0);
        fread(&oku, sizeof(SATIS),1,fp);

        if (sonraki == -1 || strncmp(oku.satis_tarihi,satis_tarihi,6) < 0) { /* Eðer girilen kayýt dosyadakinden daha büyükse iþlem yapýlacak */

            /* Eðer sonraki != 0 AMA simdiki == -1 ise o zaman urunler.dat'dan ulaþýlan ilk satýþdayýz demektir.
               Eðer yeni kaydedeceðimiz satýþ bu satýþtan önce gelecekse o zaman urunler.dat'daki bað da deðiþicek
               demektir ki iþte bunun için bu özel þartý yerine getiren bir kod parçasý yazacaðým þimdi. */

            for (sayac=0;sayac<6;sayac++) {
                oku.fatura_no[sayac] = fatura_no[sayac];
            }

            for (sayac=0;sayac<6;sayac++) {
                oku.satis_tarihi[sayac] = satis_tarihi[sayac];
            }

            oku.satis_miktari = satis_miktari;
            oku.birim_satis_fiyati = birim_satis_fiyati;
            oku.sonraki = sonraki;

            fseek(fp,0,2); /* Dosya sonuna ýþýnlan */
            link_konum = (ftell(fp) / sizeof(SATIS)) + 1;
            fwrite(&oku,sizeof(SATIS),1,fp);

            if (simdiki == -1) {
                /* Önceki bað düzelt */

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

        } else { /* Yok girilen kayýt dosyadakinden daha büyük deðilse bir sýkýntý yok, taramaya devam... */

            return satis_ekle(urun_kodu, fatura_no, satis_tarihi, satis_miktari, birim_satis_fiyati, oku.sonraki, sonraki);
        }
    }

    return 0;
}

int satis_listele(int urun_kodu, char ust_limit[6], char alt_limit[6]) {

    /*  0: Baþarýlý. */
    /* -1: Dosya açýlamadý. */

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

    /*  1: Öyle bir fatura no yok */
    /*  0: Baþarýlý. */
    /* -1: Dosya açýlamadý. */

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

        if (strncmp(oku.fatura_no,fatura_no,6) == 0) { /* EVET! Silinecek faturayý bulduk!!!!! */
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

    /* Bu fonksiyon kontrol için, asýl programda iþe yaramaz. */
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

    /* Bu fonksiyon kontrol için, asýl programda iþe yaramaz. */

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
       farkli farkli bir sürü amaçla kullanýldýðý için
       özel isimler vermedim. */

    /* Dosyayi sifirdan yaratalim */
    /* Odev kontrolunde kolaylik saglamasi acisindan dosyanin
       her acilista silinmesi ve tekrar yaratilmasi istendi.
       Programin gerceginde bunun iptal edilmesini saglamak icin
       asagidaki satirlar comment yapilabilir. */

    FILE *fp;
    URUN yaz={-1,"",0,0,-1,-1};

    remove ("urunler.dat");  // Eðer dosyalar varsa silinir.
    remove ("satislar.dat"); // Eðer dosyalar varsa silinir.

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

    /* Dosyayi sifirdan yaratalim kýsmýnnýn SONU */


    /* Ana döngü */
    while (sag_serbest==-1) {

         // Eðer her baþlangýçta ürüner.dat'ýn içerðini görmek istiyorsanýz commenti kaldýrýn.

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

        /* secenek getche ile alýndýðý için ASCII koduna göre switch yapýsýna sokulabilir. */

        /* Her CASE için aþaðýdaki not geçerlidir. */

        /* Gerekli saçma sapan veri kontrolleri ve doðru girdi
           için ilgili fonksiyonlarýn çaðýrýlmasý, fonksiyon-
           lardan cevap alýnmasý ve bunlarýn iþlenmesi.

           Ayrýntýlý bilgi için her fonksiyona ayrý ayrý baka-
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

                    case 0: /* Hayýr, yok. */

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

                    case 0: /* Hayýr, yok */
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
                            /* Ödevin asýl amacýnýn tarihlerle deðil de
                               dosyalamayla uðraþmak olduðu bilindiðinden
                               2000 öncesi yýllar için sýralama sorunu
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

                    case 0: /* Hayýr, yok */
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

                    case 0: /* Hayýr, yok */
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

                    case 0: /* Hayýr, yok */
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

                    case 0: /* Hayýr, yok */
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
