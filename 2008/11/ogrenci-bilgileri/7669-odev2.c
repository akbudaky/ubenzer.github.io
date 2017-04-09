#include <stdio.h>
#include <stdlib.h>

int main()
{
    int ogrno;
    float notort;
    char ikamet;
    char cinsiyet;
    float burs, kizort,okulort, erkekort,yuzdekiz, yuzdeerkek,yuzdeokul;
    int basarilikiz=0;
    int basarilier=0;
    float kiznotort=0;
    float erkeknotort=0;
    int kizsay=0;
    int erkeksay=0;
    int maxogrno;
    float maxnotort=0;
    float maxburs=0;
    int zenginogrno;
    float zenginnotort=0;
    int zenginogr=0;
    int evdekiz=0;
    int evdeerkek=0;
    float topburs=0;
    int basarisizev=0;
    int basarisizaile=0;
    int basarisizyurt=0;
    int a=0;

    while (ogrno!=0)
    {
        printf("ogrenci numarasini giriniz. <cikis icin 0 a basiniz> \n");
        scanf("%d",&ogrno);
        a=a+1;

        if ((a==1) && (ogrno==0))
        {
            return 0;
        }
        //ilk girilen ogrenci numarasinin 0 olmasi durumunda programdan cikisi saglar.

        if (ogrno<0)
        {
            printf("hatali girdi\n");
            continue;
        }
        //hatali veri girisi halinde bir bildiri vererek dongunun icindeki sonraki asamalari atlar ve basa doner.

        if (ogrno==0)
        {
            break;
        }
        //ogrenci numarasinin 0 girilmesi halinde donguden cikarak sonucu listelemeye gider.

        printf("cinsiyetini giriniz.(e/E/k/K)\n");
        fflush(stdin);
        cinsiyet=getchar();
        if (cinsiyet!='e' && cinsiyet!='E' && cinsiyet!='k' && cinsiyet!='K')
        {
            printf("hatali girdi\n");
            continue;
        }
        //hatali veri girisi halinde bir bildiri vererek dongunun icindeki sonraki asamalari atlar ve basa doner.

        printf("ikamet giriniz.(a/A/y/Y/e/E)\n");
        fflush(stdin);
        ikamet=getchar();
        if (ikamet!='a' && ikamet!='A' && ikamet!='y' && ikamet!='Y' && ikamet!='e' && ikamet!='E')
        {
            printf("hatali girdi\n");
            continue;
        }
        //hatali veri girisi halinde bir bildiri vererek dongunun icindeki sonraki asamalari atlar ve basa doner.
        printf("not ortalamasini giriniz.(0 ile 4 arasinda ondalikli sayi)\n");
        scanf("%f",&notort);
        if (notort<0||notort>4)
        {
            printf("hatali girdi\n");
            continue;
        }
        //hatali veri girisi halinde bir bildiri vererek dongunun icindeki sonraki asamalari atlar ve basa doner.

        if (ikamet=='a'||ikamet=='A')
        {
            if (notort<2)
            {
                burs=100;
                basarisizaile=basarisizaile+1;
            }
            if (notort<3 && notort>=2)
            {
                burs=(notort*50)+100;
            }
            if (notort>=3)
            {
                burs=(notort*60)+150;
            }
            //ailesiyle kalan ogrencilerin burslarini hesaplar, basarisiz ogrecilere ait bir sayac tutar.
        }

        if (ikamet=='Y'||ikamet=='y')
        {
            if (notort<2)
            {
                burs=130;
                basarisizyurt=basarisizyurt+1;
            }
            if (notort<3 && notort>=2)
            {
                burs=((notort*50)+100)*1.3;
            }

            if (notort>=3)
            {
                burs=((notort*60)+150)*1.3;
            }
            //yurtta kalan ogrencilerin burslarini hesaplar, basarisiz ogrecilere ait bir sayac tutar.
        }

        if (ikamet=='E'||ikamet=='e')
        {
            if (notort<2)
            {
                burs=130;
                basarisizev=basarisizev+1;
            }
            if (notort<3 && notort>=2)
            {
                burs=((notort*50)+100)*1.5;
            }
            if (notort>=3)
            {
                burs=((notort*60)+150)*1.5;
            }
            //evde kalan ogrencilerin burslarini hesaplar, basarisiz ogrecilere ait bir sayac tutar.
        }

        printf("ogrenci no:%d\n",ogrno);
        printf("ogrencinin not ortalamasi:%.2f\n",notort);
        printf("aldigi burs:%.2f YTL\n\n",burs);
        //bir ogrencinin veri girisi tamamlandiktan sonra bilgileri yazdidir.

        if (cinsiyet=='k'||cinsiyet=='K')
        {
            kiznotort=kiznotort+notort;
            kizsay=kizsay+1;
            if (notort>=2)
            {
                basarilikiz=basarilikiz+1;
            }
            if (ikamet=='e'||ikamet=='E')
            {
                evdekiz=evdekiz+1;
            }
            //toplam kiz, basarili kiz ve evde kalan kizlari sayar.
        }

        if (cinsiyet=='e'||cinsiyet=='E')
        {
            erkeknotort=erkeknotort+notort;
            erkeksay=erkeksay+1;
            if (notort>=2)
            {
                basarilier=basarilier+1;
            }
            if (ikamet=='e'||ikamet=='E')
            {
                evdeerkek=evdeerkek+1;
            }
            //toplam erkek, basarili erkek ve evde kalan erkeleri sayar.
        }

        if (notort>maxnotort)
        {
            maxnotort=notort;
            maxogrno=ogrno;
            //okul birincisinin verilerini tutar.
        }

        if (burs>maxburs)
        {
            maxburs=burs;
            zenginogrno=ogrno;
            zenginnotort=notort;
            //en cok burs alan ogrencinin verilerini tutar.
        }

        if (burs>500)
        {
            zenginogr=zenginogr+1;
            //500 den fazla burs alan ogrencileri sayar.
        }
        topburs=topburs+burs;
        //toplam burs miktarini hesaplar.
    }

    if (kizsay>0)
    {
        printf("\n\nbasarili kizlarin sayisi:%d\n",basarilikiz);
        yuzdekiz=(basarilikiz*100)/kizsay;
        printf("basarili kiz yuzdesi:%.2f\n",yuzdekiz);
    }
    else
    {
        printf("\n\nKiz ogrenci girisi yapilmadi.\n");
    }
    //varsa kizlarin basari yuzdesini hesaplar, yoksa islem yapmadan bildiri verir.

    if (erkeksay>0)
    {
        printf("basarili erkeklerin sayisi:%d\n",basarilier);
        yuzdeerkek=(basarilier*100)/erkeksay;
        printf("basarili erkek yuzdesi:%.2f\n",yuzdeerkek);
    }
    else
    {
        printf("erkek ogrenci girisi yapilmadi.\n");
    }
    //varsa erkek ogrenci basari yuzdesini hesaplar, yoksa islem yapmadan bildiri verir.

    yuzdeokul=((basarilikiz+basarilier)*100)/(kizsay+erkeksay);
    printf("okul basari yuzdesi:%.2f\n",yuzdeokul);
    //okulun basari yuzdesini hesaplar.

    if (kizsay>0)
    {
        kizort=kiznotort/kizsay;
        printf("kizlarin not ortalamasi:%.2f\n",kizort);
    }
    else
    {
        printf("Kiz ogrenci girisi yapilmadi.\n");
    }
    /*kiz ogrenci yoksa 0a bolunme hatasi vermemesi icin islem yapmaz ve bir bildiri yazar.
    Varsa kizlarin ortalamasini hesaplar*/

    if (erkeksay>0)
    {
        erkekort=erkeknotort/erkeksay;
        printf("erkeklerin not ortalamasi:%.2f\n",erkekort);
    }
    else
    {
        printf("erkek ogrenci girisi yapilmadi.\n");
    }
    /*Erkek ogrenci yoksa 0a bolunme hatasi vermemesi icin islem yapmaz ve bir bildiri yazar.
    Varsa erkeklerin ortalamasini hesaplar*/

    okulort=(kiznotort+erkeknotort)/(kizsay+erkeksay);
    printf("okulun not ortalamasi:%.2f\n\n",okulort);
    //okul ortalamasini hesaplar.

    printf("okul birincisinin ogrenci numarasi:%d\n",maxogrno);
    printf("okul birincisinin not ortalamasi:%.2f\n\n",maxnotort);
    printf("odenen toplam burs:%.2f\n\n",topburs);
    printf("en cok burs alan ogrencinin numarasi:%d\n",zenginogrno);
    printf("en cok burs alan ogrencinin not ortlamasi:%.2f\n",zenginnotort);
    printf("en cok burs alan ogrencinin aldigi burs:%.2f Ytl\n\n",maxburs);
    printf("500 ytlden fazla burs alan ogrenci sayisi:%d\n\n",zenginogr);
    printf("evde kalan kiz:%d\n",evdekiz);
    printf("evde kalan erkek:%d\n\n",evdeerkek);

    if (basarisizaile!=0&&basarisizyurt!=0&&basarisizev!=0)
    {

        if ((basarisizev>basarisizyurt)&&(basarisizev>basarisizaile))
        {
            printf("en dusuk basari yuzdesine sahip ogrenciler evde kalmaktadir.\n");
        }
        else if ((basarisizyurt>basarisizev)&&(basarisizyurt>basarisizaile))
        {
            printf("en dusuk basari yuzdesine sahip ogrenciler yurtta kalmaktadir.\n ");
        }
        else
        {
            printf("en dusuk basari yuzdesine sahip ogrenciler aileleriyle kalmaktadir.\n ");
        }
    }
    else
    {
        printf("ikamete gore basari yuzdesi hesaplayabilmek icin yeterli veri girisi yapilmadi.\n");
    }
    /*eger yurtta, evde ve ailesiyle kalan en az bir ogrenci varsa en dusuk basari yuzdesinin ikamet
    adresini ekrana yazdirir. ancak bunlardan herhangi birinde kalan bir ogranci yoksa bu hesaplamayi yapmaz.
    aksi halde, diyelim ki tum ogrenciler evde kaliyor olarak girildi, o zaman en dusuk basari yuzdesi
    evde kalan ogrenciye ait oluyor. bu nedenle boylesi bu durumda program hesaplama yapmiyor.*/
}
