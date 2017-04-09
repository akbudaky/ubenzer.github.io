#include <stdio.h>
#include <stdlib.h>

struct ogrenci
{
    int ogr_no;
    char ad_soyad[25];
    char sinif[3];
    int basarili_ders_say;
    float not_ort;
};


int menu()
{
    int secim;
    printf("\n\n\n");
    printf("************************************MENU************************************\n\n");
    printf("    1.Ogrencilerin basarili olduklari derslerin eklenmesi.\n");
    printf("    2.Bir ogrencinin kaydinin silinmesi.\n");
    printf("    3.Bir ogrencinin bilgilerinin listelenmesi.\n");
    printf("    4.Bir ogrencinin bilgilerinin ve basarili olduklari derslerin listelenmesi.\n");
    printf("    5.Belirli bir not ortalamasi uzerindeki ogrencilerin listelenmesi.\n");
    printf("    6.Bir sinifta okuyan ogrencilerin listelenmesi.\n");
    printf("    7.Okulun basari istatistiklerinin listelenmesi.\n");
    printf("    8.Bir dersten basarili olan ogrencilerin listelenmesi.\n");
    printf("    9.Cikis.\n\n");
    printf("Seciminizi giriniz.\n\n");
    scanf("%d",&secim);
    return secim;
}

void ders_ekle()
{
    FILE *dosya;
    FILE *dosya2;
    char devam='E';
    int ek_no,ek_kod,ek_not;
    float yeni_not_ort;
    struct ogrenci bir_ogr=
        {
            0,"","",0,0.0
        };

    if((dosya=fopen("notlar.dat","a+"))== NULL)
    {
        printf("Notlar dosyasi acilamadi..\n\n");
    }
    else
    {
        if((dosya2=fopen("ogrenciler.dat","rb+"))== NULL)
        {
            printf("Ogrenciler dosyasi acilamadi..\n\n");
        }
        else
        {
            while(devam=='E')
            {
                do
                {
                    printf("Ogrencinin numarasini giriniz.\n");
                    scanf("%d",&ek_no);
                }
                while(ek_no>500 || ek_no<1);
                printf("Ders kodu ve ogrencinin gecme notunu aralarinda birer bosluk birakarak giriniz.\n\n");
                fscanf(stdin,"%d%d",&ek_kod,&ek_not);
                fseek(dosya2,(ek_no-1)*sizeof(struct ogrenci),SEEK_SET);
                fread(&bir_ogr,sizeof(struct ogrenci),1,dosya2);
                yeni_not_ort=(bir_ogr.not_ort*bir_ogr.basarili_ders_say+ek_not)/(++bir_ogr.basarili_ders_say);
                fprintf(dosya,"%d %d %d\n",ek_no,ek_kod,ek_not);
                bir_ogr.not_ort=yeni_not_ort;
                fseek(dosya2,(ek_no-1)*sizeof(struct ogrenci),SEEK_SET);
                fwrite(&bir_ogr,sizeof(struct ogrenci),1,dosya2);
                printf("Kayit eklenmistir.\nYeni bir ekleme yapmak istiyor musunuz?-E ya da H giriniz-\n");
                scanf("%s",&devam);
            }
            fclose(dosya2);
        }
        fclose(dosya);
    }
    return;
}

void kayit_sil()
{
    FILE *dosya;
    FILE *dosya2;
    FILE *dosya3;
    int silinecek_no;
    int no,kod,not;
    struct ogrenci bir_ogr,bos_ogr=
        {
            0,"","",0,0.0
        };

    if((dosya=fopen("notlar.dat","r"))== NULL)
    {
        printf("Notlar dosyasi acilamadi..\n\n");
    }
    else
    {
        if((dosya2=fopen("ogrenciler.dat","rb+"))== NULL)
        {
            printf("Ogrenciler dosyasi acilamadi..\n\n");
        }
        else
        {
            dosya3=fopen("gecici.dat","a");
            do
            {
                printf("Silinecek ogrencinin numarasini giriniz.\n");
                scanf("%d",&silinecek_no);
            }
            while(silinecek_no>500 || silinecek_no<1);
            fseek(dosya2,(silinecek_no-1)*sizeof(struct ogrenci),SEEK_SET);
            fread(&bir_ogr,sizeof(struct ogrenci),1,dosya2);
            if(bir_ogr.ogr_no==0)
            {
                printf("Uzgunuz boyle bir ogrenci yoktur.\n");
            }
            else
            {
                fseek(dosya2,(silinecek_no-1)*sizeof(struct ogrenci),SEEK_SET);
                fwrite(&bos_ogr,sizeof(struct ogrenci),1,dosya2);
                fscanf(dosya,"%d %d %d",&no,&kod,&not);
                while(!feof(dosya))
                {
                    if(silinecek_no!=no)
                    {
                        fprintf(dosya3,"%d %d %d\n",no,kod,not);
                    }
                    fscanf(dosya,"%d %d %d",&no,&kod,&not);
                }
            }
            fclose(dosya2);
        }
        fclose(dosya);
        fclose(dosya3);
        remove("notlar.dat")
        ;
        rename("gecici.dat","notlar.dat");
        printf("Kayit silinmistir.\n");
    }
    return;
}

void ogr_listele(int kontrol)
{
    FILE *dosya;
    FILE *dosya2;
    int listelenecek_no;
    int no,kod,not;
    int bulundu=0;
    struct ogrenci bir_ogr;

    if((dosya=fopen("notlar.dat","a+"))== NULL)
    {
        printf("Notlar dosyasi acilamadi..\n\n");
    }
    else
    {
        if((dosya2=fopen("ogrenciler.dat","rb+"))== NULL)
        {
            printf("Ogrenciler dosyasi acilamadi..\n\n");
        }
        else
        {
            do
            {
                printf("Listelenecek ogrencinin numarasini giriniz.\n");
                scanf("%d",&listelenecek_no);
            }
            while(listelenecek_no>500 || listelenecek_no<1);
            fseek(dosya2,(listelenecek_no-1)*sizeof(struct ogrenci),SEEK_SET);
            fread(&bir_ogr,sizeof(struct ogrenci),1,dosya2);

            printf("Ogr no\tAd Soyad\tSinif\tBasarili Ders Say\tNot Ort\n");
            printf("------\t--------\t-----\t-----------------\t-------\n");
            printf("%d\t%s\t%s\t%d\t\t\t%.2f\n\n",bir_ogr.ogr_no,bir_ogr.ad_soyad,bir_ogr.sinif,bir_ogr.basarili_ders_say,bir_ogr.not_ort);
            if(kontrol==1)
            {
                printf("Basarili oldugu dersler:\n");
                printf("Basarili ders kodu\tGecme Notu\n");
                printf("------------------\t----------\n");
                fscanf(dosya,"%d %d %d",&no,&kod,&not);
                while(!feof(dosya))
                {
                    if(no==bir_ogr.ogr_no)
                    {
                        printf("%d\t\t\t%d\n",kod,not);
                        bulundu=1;
                    }
                    fscanf(dosya,"%d %d %d",&no,&kod,&not);
                }
                if(bulundu==0)
                {
                    printf("Bu ogrenci tembel.\n\n");
                }
            }

            fclose(dosya2);
        }
        fclose(dosya);
    }
    return;
}


void ortalamaya_gore_listele()
{
    FILE *dosya;
    FILE *dosya2;
    float sinir;
    int i=0;
    long yer;
    struct ogrenci bir_ogr=
        {
            0,"","",0,0.0
        };

    if((dosya=fopen("notlar.dat","a+"))== NULL)
    {
        printf("Notlar dosyasi acilamadi..\n\n");
    }
    else
    {
        if((dosya2=fopen("ogrenciler.dat","rb+"))== NULL)
        {
            printf("Ogrenciler dosyasi acilamadi..\n\n");
        }
        else
        {
            printf("Ortalamayi giriniz.\n");
            scanf("%f",&sinir);
            printf("Ogr No\tAd Soyad\tSinif\tBasarili Ders Say\tNot Ort\n");
            printf("------\t--------\t-----\t-----------------\t-------\n");

            fseek(dosya2,0,SEEK_END);
            yer=ftell(dosya2);
            yer/=sizeof(struct ogrenci);
            while(i<yer)
            {

                fseek(dosya2,i*sizeof(struct ogrenci),SEEK_SET);
                fread(&bir_ogr,sizeof(struct ogrenci),1,dosya2);
                if(bir_ogr.not_ort>sinir)
                {
                    printf("%d\t%s\t%s\t%d\t\t\t%.2f\n",bir_ogr.ogr_no,bir_ogr.ad_soyad,bir_ogr.sinif,bir_ogr.basarili_ders_say,bir_ogr.not_ort);
                }
                i++;
            }
            fclose(dosya2);
        }
        fclose(dosya);
    }
    return;
}

void bubble_sort(struct ogrenci gelen[])
{
    int   i, j;
    struct ogrenci temp;
    for (i = 0; i < 49; i++)
        for (j = 0; j < 50 - i - 1; j++)
            if (gelen[j].not_ort > gelen[j + 1].not_ort)
            {
                temp = gelen[j];
                gelen[j] = gelen[j + 1];
                gelen[j + 1] = temp;
            }
            else if(gelen[j].not_ort == gelen[j + 1].not_ort)
            {
                if (gelen[j].basarili_ders_say > gelen[j + 1].basarili_ders_say)
                {
                    temp = gelen[j];
                    gelen[j] = gelen[j + 1];
                    gelen[j + 1] = temp;
                }
            }
    return;
}

void sinifa_gore_listele(void)
{
    FILE *dosya;
    char sinif_ad[3];
    int i=0,j=0,k;
    long yer;
    struct ogrenci ogrenciler[50]=
        {
            0,"","",0,0.0
        };
    struct ogrenci bir_ogr=
        {
            0,"","",0,-1.0
        };

    if((dosya=fopen("ogrenciler.dat","rb+"))== NULL)
    {
        printf("Ogrenciler dosyasi acilamadi..\n\n");
    }
    else
    {
        printf("Sinifin adini giriniz.\n");
        scanf("%s",sinif_ad);
        printf("Sira\tOgr no\tAd Soyad\tBasarili Ders Say\tNot Ort\n");
        printf("----\t------\t--------\t-----------------\t-------\n");
        fseek(dosya,0,SEEK_END);
        yer=ftell(dosya);
        yer/=sizeof(struct ogrenci);
        while(i<yer)
        {

            fseek(dosya,i*sizeof(struct ogrenci),SEEK_SET);
            fread(&bir_ogr,sizeof(struct ogrenci),1,dosya);

            if(strcmp(bir_ogr.sinif,sinif_ad)==0)
            {
                if(bir_ogr.not_ort==0)
                {
                    ogrenciler[j].ogr_no=bir_ogr.ogr_no;
                    ogrenciler[j].basarili_ders_say=bir_ogr.basarili_ders_say;
                    ogrenciler[j].not_ort=-1;
                    for(k=0;k<24;k++)
                    {
                        ogrenciler[j].ad_soyad[k]=bir_ogr.ad_soyad[k];
                    }
                    j++;
                }
                ogrenciler[j].ogr_no=bir_ogr.ogr_no;
                ogrenciler[j].basarili_ders_say=bir_ogr.basarili_ders_say;
                ogrenciler[j].not_ort=bir_ogr.not_ort;
                for(k=0;k<24;k++)
                {
                    ogrenciler[j].ad_soyad[k]=bir_ogr.ad_soyad[k];
                }
                j++;
            }
            i++;
        }
        bubble_sort(ogrenciler);
        k=0;
        for(i=49;i>=0;i--)
        {
            if(ogrenciler[i].sinif!=NULL && ogrenciler[i].not_ort!=0)
            {
                if(ogrenciler[i].not_ort==-1){
                    ogrenciler[i].not_ort=0;
                }
                printf("%d\t%d\t%s\t%d\t\t\t%.2f\n",++k,ogrenciler[i].ogr_no,ogrenciler[i].ad_soyad,ogrenciler[i].basarili_ders_say,ogrenciler[i].not_ort);
            }
        }

        fclose(dosya);
    }
    return;
}

int aralik_bul(int not)
{
    int i;
    if(not<9.5)
        i=0;
    else if(not<19.5)
        i=1;
    else if(not<29.5)
        i=2;
    else if(not<39.5)
        i=3;
    else if(not<49.5)
        i=4;
    else if(not<59.5)
        i=5;
    else if(not<69.5)
        i=6;
    else if(not<79.5)
        i=7;
    else if(not<89.5)
        i=8;
    else if(not<101)
        i=9;
    return i;

}

void istatistik(void)
{
    FILE *dosya;
    int toplam=0,ilk=90,son=99;
    int i=0;
    int j,indis;
    long yer;
    int ogr_sayisi[10]=
        {
            0
        };
    float ogr_yuzdesi[10];
    struct ogrenci bir_ogr=
        {
            0,"","",0,0.0
        };
    if((dosya=fopen("ogrenciler.dat","rb+"))== NULL)
    {
        printf("Ogrenciler dosyasi acilamadi..\n\n");
    }
    else
    {
        printf("Not araligi\tOgrenci Sayisi\tOgrenci Yuzdesi\n");
        printf("-----------\t--------------\t---------------\n");
        fseek(dosya,0,SEEK_END);
        yer=ftell(dosya);
        yer/=sizeof(struct ogrenci);
        while(i<yer)
        {
            fseek(dosya,i*sizeof(struct ogrenci),SEEK_SET);
            fread(&bir_ogr,sizeof(struct ogrenci),1,dosya);
            if(bir_ogr.not_ort!=0 || bir_ogr.ogr_no!=0)
            {
                indis=aralik_bul(bir_ogr.not_ort);
                ogr_sayisi[indis]=ogr_sayisi[indis]+1;
            }
            i++;
        }
        for(i=0;i<10;i++)
        {
            toplam=toplam+ogr_sayisi[i];
        }
        j=0;
        while(j<10)
        {
            ogr_yuzdesi[j]=(float)ogr_sayisi[j]/toplam*100;
            j++;
        }
        printf("90-100\t\t\t");
        for(i=9;i>0;i--)
        {
            ilk-=10;
            son-=10;
            printf("%d\t\t",ogr_sayisi[i]);
            printf("%.2f\n",ogr_yuzdesi[i]);
            printf("%d-%d\t\t\t",ilk,son);
        }
        printf("%d\t\t",ogr_sayisi[i]);
        printf("%.2f\n",ogr_yuzdesi[i]);
        fclose(dosya);
    }
    return;
}

void derse_gore_listele(void)
{
    FILE *dosya;
    FILE *dosya2;
    int aranan_ders;
    int no,kod,not;
    int toplam=0,bulundu=0;
    int sayac=0;
    float ortalama;
    struct ogrenci bir_ogr=
        {
            0,"","",0,0.0
        };

    if((dosya=fopen("notlar.dat","r"))== NULL)
    {
        printf("Notlar dosyasi acilamadi..\n\n");
    }
    else
    {
        if((dosya2=fopen("ogrenciler.dat","rb+"))== NULL)
        {
            printf("Ogrenciler dosyasi acilamadi..\n\n");
        }
        else
        {
            printf("Dersin kodunu giriniz.\n");
            scanf("%d",&aranan_ders);
            printf("Ogr No\tAd Soyad\tSinif\tGecme Notu\n");
            printf("------\t--------\t-----\t----------\n");
            fscanf(dosya,"%d %d %d",&no,&kod,&not);
            while(!feof(dosya))
            {
                if(aranan_ders==kod)
                {
                    fseek(dosya2,(no-1)*sizeof(struct ogrenci),SEEK_SET);
                    fread(&bir_ogr,sizeof(struct ogrenci),1,dosya2);
                    printf("%d\t%s\t%s\t%d\n",bir_ogr.ogr_no,bir_ogr.ad_soyad,bir_ogr.sinif,not);
                    toplam+=not;
                    sayac++;
                    bulundu=1;
                }
                fscanf(dosya,"%d %d %d",&no,&kod,&not);
            }
            if(bulundu==0)
            {
                printf("Okulumuzda boyle bir sinif yoktur.\n\n");
                return;
            }

            ortalama=toplam/sayac;
            printf("Dersin genel not ortalamasi:%.2f",ortalama);

            fclose(dosya2);
        }
        fclose(dosya2);
    }
    return;
}

int main()
{
    int gelen;
    do
    {
        gelen=menu();
        switch(gelen)
        {
            case 1:
            ders_ekle();
            break;
            case 2:
            kayit_sil();
            break;
            case 3:
            ogr_listele(0);
            break;
            case 4:
            ogr_listele(1);
            break;
            case 5:
            ortalamaya_gore_listele();
            break;
            case 6:
            sinifa_gore_listele();
            break;
            case 7:
            istatistik();
            break;
            case 8:
            derse_gore_listele();
            break;
        }
    }
    while(gelen!=9);
    printf("Esen kalin..");
    return 0;
}
