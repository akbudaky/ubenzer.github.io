#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Umut BENZER\n");
    printf("05-06-7670\n");
    printf("IZSU Aylik Su Tuketim Faturasi Duzenleme\n\n");

    int abonetipi;
    int okuay;
    int okugun;
    int guncelsayac;
    int oncekigun;
    int oncekisayac;

    int aydakigun=31;       // Girilen ayda kac gun oldugunu tutacak. Varsayilan olarak 31 atali.
    int oncekiay;           // Bunun nedeni bir yildaki aylarin cogunun 31 cekmesi. Etkilik acisindan
    int oncekiaydakigun=31; // ay sadece 31 cekmiyorsa ileride case dongusunde bir sarta girilecek.

    int kacgungecti;
    int tuketim;

    float kademe1;
    float kademe2;
    float kademe3;

    float kademe1fiyat;
    float kademe2fiyat;
    float kademe3fiyat;
    float kademe4fiyat;

    float fiyat;
    float kalan;            // Ileride kalan = tuketim gececek. Bunun nedeni ekrana bu ay 0.000 ton harcadiniz yerine
                            // 0 ton harcadiniz yazdirmak. Yoksa tek float degiskeni de kullanabilirdim.

    printf("Abone tipi kodunu giriniz:\n");
    scanf("%d",&abonetipi);
    if (abonetipi>4 || abonetipi<1)
    {
        printf("Abone tipi hatali. Program sonlanacak.");
        return 0;
    }

    printf("Sayacin okundugu ay:\n");
    scanf("%d",&okuay);
    if (okuay>12 || okuay<1)
    {
        printf("Ay girdisi hatali. Program sonlanacak.");
        return 0;
    }

    printf("Sayacin okundugu gun:\n");
    scanf("%d",&okugun);
    switch (okuay)                    // 1  OC 31
    {                                 // 2  SU 28
        case 4:                       // 3  MA 31
        case 6:                       // 4  NI 30
        case 9:                       // 5  MA 31
        case 11:                      // 6  HA 30
            aydakigun = 30;           // 7  TE 31
            break;                    // 8  AG 31
        case 2:                       // 9  EY 30
            aydakigun = 28;           // 10 EK 31
    }                                 // 11 KA 30
                                      // 12 AR 31
    if (okugun<1 || okugun>aydakigun)
    {
        printf("%d. ayda %d. gun yok. Program sonlanacak.",okuay,okugun);
        return 0;
    }

    printf("Guncel sayac degeri:\n");
    scanf("%d",&guncelsayac);

    // ve sayac 0'dan az olamaz degil mi? En azindan bizim evdeki sayacda yok :)
    if (guncelsayac<0)
    {
        printf("Sayac eksi deger almaz. Sizi sistemden atiyoruz.");
        return 0;
    }

    printf("Bir onceki ay sayacin okundugu gun:\n");
    scanf("%d",&oncekigun);

    oncekiay = okuay - 1;
    if (oncekiay==0) oncekiay = 12;  // Eger güncel ay ocaksa, bir onceki ay araliktir.
    switch (oncekiay)                 // 1  OC 31
    {                                 // 2  SU 28
        case 4:                       // 3  MA 31
        case 6:                       // 4  NI 30
        case 9:                       // 5  MA 31
        case 11:                      // 6  HA 30
            oncekiaydakigun = 30;     // 7  TE 31
            break;                    // 8  AG 31
        case 2:                       // 9  EY 30
            oncekiaydakigun = 28;     // 10 EK 31
    }                                 // 11 KA 30
                                      // 12 AR 31
    if (oncekigun<1 || oncekigun>oncekiaydakigun)
    {
        printf("%d. ayda %d. gun yok. Program sonlanacak.",oncekiay,oncekigun);
        return 0;
    }

    printf("Eski sayac degeri:\n");
    scanf("%d",&oncekisayac);

    if (oncekisayac>guncelsayac)
    {
        printf("Gecen ayin sayac degeri simdikinden buyuk. Program sonlancak.");
        return 0;
    }

    // ve sayac 0'dan az olamaz degil mi? En azindan bizim evdeki sayacda yok :)
    if (oncekisayac<0)
    {
        printf("Sayac eksi deger almaz. Sizi sistemden atiyoruz.");
        return 0;
    }

    printf("\n*** Ciktilar ***\nAbone tipi: ");
    switch (abonetipi)
    {
        case 1:
            printf("Konut");    //Oncelikle ev kullanicilarini yazalim, cunku en cok onlardan var. Etkinlik meselesi.
            kademe1 = 13.0/30.0;
            kademe2 = 7.0/30.0;
            kademe3 = 8.0/3.0;

            kademe1fiyat = 1.19;
            kademe2fiyat = 3.09;
            kademe3fiyat = 5.00;
            kademe4fiyat = 6.13;
            break;
        case 2:
            printf("Konut disi");
            kademe1 = 0;
            kademe2 = 1.0/3.0;
            kademe3 = 1.0/3.0;

            kademe2fiyat = 4.13;
            kademe3fiyat = 4.75;
            kademe4fiyat = 6.53;
            break;
        case 3:
            printf("Resmi daire");
            kademe1 = 0;
            kademe2 = 0;
            kademe3 = 0;

            kademe4fiyat = 3.55;
            break;
        case 4:
            printf("Okul-Hastane");
            kademe1 = 0;
            kademe2 = 0;
            kademe3 = 0;

            kademe4fiyat = 2.84;
            break;
    }

    printf("\n\nOnceki sayac okuma bilgileri\n AY: %d, GUN: %d, SAYAC DEGERI: %d\n",oncekiay,oncekigun,oncekisayac);
    printf("\nSimdiki sayac okuma bilgileri\n AY: %d, GUN: %d, SAYAC DEGERI: %d\n\n",okuay,okugun,guncelsayac);

    kacgungecti = oncekiaydakigun - oncekigun + okugun;
    printf("Son sayac okunmasindan bu yana %d gun gecti.\n",kacgungecti);

    tuketim = guncelsayac - oncekisayac;
    printf("Bu ayin tuketim miktari: %d ton.\n",tuketim);
    // kalan degiskeni float tuketim int, cunku ekranda x.0000 ton yazmasini istemiyorum.

    kalan = tuketim;

    kademe1=kademe1*kacgungecti;
    kademe2=kademe2*kacgungecti;
    kademe3=kademe3*kacgungecti;

    if (kalan>kademe1) {
      // Eger program buraya geliyorsa demek ki bir kismi kademe1'den ucretlendirilecek, kalani 2'ye aktarilacak.
      fiyat = kademe1 * kademe1fiyat;
      kalan = kalan - kademe1;        // Kalan kismi kademe 2'ye gonder
      if (kalan>kademe2) {  // Odeme kademe 3'e de sarkacak.
          fiyat = fiyat + kademe2 * kademe2fiyat;
          kalan = kalan - kademe2; // Kalan kismi kademe 3'e gonder.
          if (kalan>kademe3) { // Odeme kademe 4'e de sarkacak, aboooo
              fiyat = fiyat + kademe3 * kademe3fiyat + (kalan - kademe3) * kademe4fiyat;
          } else {
              fiyat = fiyat + kalan * kademe3fiyat;
          }
      } else { // Odeme kademe 2 de tamamlaniyor.
            fiyat = fiyat + kalan * kademe2fiyat;
      }
    } else {   // Burada parantez olmasina gerek yok, farkindayim ama diger turlu kafam karisiyor.
        fiyat = kalan * kademe1fiyat; // Odemenin tamami 1.Kademeden gerceklesitiriyor...
    }

    float kdv;
    kdv = fiyat*8.0/108.0;
    printf ("KDV %8: %f\n",kdv);
    printf ("KDV DAHIL %f YTL ODENMESI GEREKIYOR.",fiyat);

    return 0;
}

