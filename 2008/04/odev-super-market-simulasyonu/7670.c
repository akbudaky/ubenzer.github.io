#include <stdio.h>
#include <stdlib.h>

#define KUYRUK_UZ 1000
#define EKRAN_BOYUTU 22
#define DURSUN_MU 1

/* Sabitler ve Anlamlari */
/* --------------------- */
/* KUYRUK_UZ        : Kuyruðun uzunluðunu ayarlayabilmenize imkan tanýr. (eðer kuyruk yeterli gel-
                      mezs program çalýþma zamanýnda sizi uyaracaktýr.)
                      lere karþýlýk gelebileceði için tercih edilmemelidir.)
   EKRAN_BOYUTU     : Simülasyonun gidiþatýný izlediðiniz pencerenin satýr sayýsý boyutunun bir eksiði
   DURSUN_MU        : Eðer 1 yapýlýrsa ekran doluduðunda simülasyon durdurularak kullanýcdan bir tuþa
                      basmasý istenir. Böylece kullanýcý tüm simülasyonu takip edebilir.
*/

int kuyruga_ekle(int kuyruk_bilgi[], int kuyruk[]) {

    // Kuyruða 0 bekleme süreli yeni bir kiþi ekler.
    // Kuyruktaki son kiþinin sahip olduðu indis de ayarlanýr.
    // Kuyruk dolduysa -1 döndürür.

    if (kuyruk_bilgi[1] == KUYRUK_UZ) {
        return -1;
    }

    kuyruk_bilgi[1]++;
    kuyruk[kuyruk_bilgi[1]+1] = 0;

    return 0;
}

void beklet() {
    /* Bu fonksiyonun tek amaci kullaniciyi bir tusa basana kadar
       bekletmek, ve sonra ekrani silmektir. */
    printf("\nDevam etmek icin bir tusa basin.");
    getche();
    system ("cls");
}

void insanlari_beklet(int kuyruk_bilgi[],int kuyruk[]) {

    // Kuyrukta bulunan tüm insanlarý bir dakika bekletir.

    int sayac;

    for (sayac=kuyruk_bilgi[0];sayac<=kuyruk_bilgi[1];sayac++) {
        kuyruk[sayac]++;
    }
}

int max(int son_indis, int dizi[]) {

    // 0'dan son_indis'e kadar olan dizi elemanlarýndan en büyüðünü geri gönderir.

    int sayac;
    int eb=0;
    for (sayac = 0;sayac<=son_indis;sayac++) {
        if (dizi[sayac] > eb) {
            eb = dizi[sayac];
        }
    }
    return eb;

}

float ortalama(int son_indis, int dizi[]) {

    // 0'dan son_indis'e kadar olan dizi elemanlarýnýn ortalamasýný gönderir.

    int sayac;
    float temp=0;
    for (sayac = 0;sayac<=son_indis;sayac++) {
        temp += dizi[sayac];
    }
    if (son_indis < 0) {
        return 0;
    } else {
        return temp / (son_indis + 1);
    }

}

int main() {
    /* Acilis yazilari BASLANGICI */
    printf("Umut BENZER\n");
    printf("05-06-7670\n");
    printf("Ege Universitesi Bilgisayar Muhendisligi 1. Sinif\n");
    printf("http://www.ubenzer.com\n");
    printf("Super Market Simulasyonu 1.0 beta\n\n");
    /* Acilis yazilari SONU */

    int cekirdek;
    int simulasyon_sure;
    int sayac;
    int kuyruk[KUYRUK_UZ];
    int kuyruk_bilgi[2]={0,-1};
    /* BU DÝZÝNÝN ANLAMI
        BÝRÝNCÝ ÝNDÝS: Kuyrukta iþlem gören ilk eleman indisi.
        ÝKÝNCÝ ÝNDÝS : Kuyrukta iþlem gören son eleman indisi.
    */
    int en_son_gelen_dakika = 0;
    int kasadaki_sure = 0;
    int kuyruktaki_kisi_max = 0;
    int satirsay = 0;

    printf("Cekirdek sayiyi girin: ");
    scanf("%d",&cekirdek);
    srand(&cekirdek);

    printf("Toplam simulasyon suresini girin: ");
    scanf("%d",&simulasyon_sure);

    printf("\n\nDukkan acildi. Ilk musteri alisverisini yapmaya basladi.\n");
    satirsay++;

    for (sayac=1;sayac<=(simulasyon_sure+4);sayac++) { //Niye simulasyon_sure + 4? Malum 4 dakika boyunca odeme yapabilir.

        // Geçen HER dakika için
        // ACABA YENÝ MÜÞTERÝ GELMÝÞ MÝ? GELDÝYSE KUYRUÐA AT
        // Eðer 4 dakikadýr yeni müþteri gelmediyse, ödevin kuralýna göre mecburn gelmek zorunda.
        if (sayac < simulasyon_sure) { // Dükkan kapanmadýysa

            if (sayac - en_son_gelen_dakika >= 4) {
                if (kuyruga_ekle(kuyruk_bilgi,kuyruk) == -1) {
                    printf("\nKuyruk doldu. Program su noktada coker.\nKUYRUK_UZ sabitinin degerini yukseltip tekrar deneyin.");
                    beklet();
                    return 0;
                }
                en_son_gelen_dakika = sayac;
                printf("%d. dakikada Musteri#%d geldi.\n",sayac,kuyruk_bilgi[1]+1);
                satirsay++;
                //printf("(4 dakikada bir musteri gelemek zorunda kuralindan dolayi.)\n");
                //satir_say++;
                //Ayrintili bilgi için ust satiradki commenti kaldýrýn.
                if (satirsay >= EKRAN_BOYUTU && DURSUN_MU == 1) {
                    satirsay = 0;
                    printf("Sayfa doldu. Simulasyona devam etmek icin bir tusa basin.\n");
                    getche();
                    system("cls");
                }

            } else {
                if (rand()%2 == 1) { // Daha az müþteri gelmesini istiyorsanýz rand()%2 --> rand()%3 yapýlabilir.
                    if (kuyruga_ekle(kuyruk_bilgi,kuyruk) == -1) {
                        printf("\nKuyruk doldu. Program su noktada coker.\nKUYRUK_UZ sabitinin degerini yukseltip tekrar deneyin.");
                        beklet();
                        return 0;
                    }
                    en_son_gelen_dakika = sayac;
                    printf("%d. dakikada Musteri#%d geldi.\n",sayac,kuyruk_bilgi[1]+1);
                    satirsay++;
                    if (satirsay >= EKRAN_BOYUTU && DURSUN_MU == 1) {
                        satirsay = 0;
                        printf("Sayfa doldu. Simulasyona devam etmek icin bir tusa basin.\n");
                        getche();
                        system("cls");
                    }
                }
            }

        }

        // PEKÝ YA GÝDENLER? MÜÞTERÝ ACABA BU DAKÝKADA MI KASADAN AYRILACAK?
        // 4 dakika boyunca kasadaysa ödev kuralý gereði mecburen gitsin.

        if (kasadaki_sure == 4 || (rand()%2 == 1 && kasadaki_sure != 0)) {
            kuyruk_bilgi[0]++;
            kasadaki_sure = 0;
            printf("%d. dakikada Musteri#%d gitti.\n",sayac,kuyruk_bilgi[0]);
            satirsay++;
            if (satirsay >= EKRAN_BOYUTU && DURSUN_MU == 1) {
                satirsay = 0;
                printf("Sayfa doldu. Simulasyona devam etmek icin bir tusa basin.\n");
                getche();
                system("cls");
            }

        }

        // Ýnsanlar bekliyor!
        if (kuyruk_bilgi[1] - kuyruk_bilgi[0] >= 0) { //Eðer kuyrukta müþteri varsa
            kasadaki_sure++;
        }
        insanlari_beklet(kuyruk_bilgi,kuyruk);

        if (kuyruk_bilgi[1] - kuyruk_bilgi[0] > kuyruktaki_kisi_max) {
            kuyruktaki_kisi_max = kuyruk_bilgi[1] - kuyruk_bilgi[0];
        }

    }

    /* Mutlu son */

    printf("\nDukkan kapandi, herkes gitti. Iste bazi sonuclar:\n");
    printf("Herhangi bir zamanda kuyrukta bulunan max kisi sayisi: %d\n",kuyruktaki_kisi_max);
    printf("Kuyrukta en uzun sure bekleyen musterinin bekleme suresi: %d\n",max(kuyruk_bilgi[1],kuyruk));
    printf("Bir musterinin kuyrukta ortalama bekleme suresi: %.2f\n",ortalama(kuyruk_bilgi[1],kuyruk));

    beklet();
    return 0;

}
