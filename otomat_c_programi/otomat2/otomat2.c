#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "otomat.h"

void dosya(urun u1[5]);
void listeleme(urun u1[5]);
void satis(urun u1[5]);
int secim(urun u1[5]);
int stokKontrol(int rSecim, urun u1[5]);
void odeme(int rSecim, int rStok, urun u1[5]);


int main ()
{
    urun u1[5];
    dosya(u1); // !!
    int devamMi;
    do{
        listeleme(u1);
        satis(u1);
        printf("\n\nisleme devam etmek istiyor musunuz ? (1: Evet, 0: Hayir.) ");
        scanf("%d", &devamMi);
    }while(devamMi==1);
    return 0;
}

void dosya(urun u1[5])
{
    FILE *oku= fopen("urunler.dat","rb");
    if(oku==NULL){
        urun u0[5]={
            {1, "Cips", 10, 20},
            {2, "Kola", 15, 20},
            {3, "Su", 5, 50},
            {4, "Cikolata", 12, 30},
            {5, "Soda", 8, 40}
        };

        int i=0;
        while(i<5){
            u1[i]=u0[i];
            i++;
        }

        FILE *yaz= fopen("urunler.dat","wb");
        if(yaz!=NULL){
            fwrite(u1,sizeof(urun),5,yaz);
            fclose(yaz);
        }
    }
    else{
    fread(u1,sizeof(urun),5,oku);
    fclose(oku);
    }
}

void listeleme(urun u1[5])
{
    int i=0;
    printf("--------------------URUN LİSTESİ---------------------\n\n");
    printf("%-10s%-30s%-10s%-10s\n\n", "URUN NO","URUN ADI","FIYAT","STOK");
    while(i<5){
        printf("%-10d%-30s%-10d%-10d", u1[i].ID, u1[i].urunAdi, u1[i].fiyat, u1[i].stok);
        i++;
        printf("\n");
    }
}

void satis(urun u1[5])
{
    int rSecim=secim(u1);
    if(rSecim != -1){
        int rStok = stokKontrol(rSecim, u1);
        if(rStok != -1){
            odeme(rSecim, rStok, u1);
        }
    }
}

int secim(urun u1[5])
{
    int secim;
    int kontrol=0, i=0;
    printf("\n\nurun numarasi seciniz: ");
    scanf("%d", &secim);

    while(i<5){
        if(secim==u1[i].ID){
            kontrol=1;
            break;
        }
        i++;
    }

    if(kontrol==0){
        printf("%d numarali urun bulunmamaktadir.\n", secim);
        return -1;
    }
    else
    return secim;
}

int stokKontrol(int rSecim,urun u1[5])
{
    int adet;
    printf("\n\nurun adedi giriniz: ");
    scanf("%d", &adet);

    if(adet<=u1[rSecim-1].stok){
        return adet;
    }
    else{
        printf("%d numarali urunden kalmamistir.", rSecim);
        return -1;
    }
}

void odeme(int rSecim, int rStok, urun u1[5])
{
    int tutar = u1[rSecim-1].fiyat*rStok;
    printf("\nTOPLAM TUTAR: %d", tutar);
    int odenen;
    printf("\n\npara girisi yapiniz:");
    scanf("%d", &odenen);

    if(odenen<tutar){
        printf("\nYETERSİZ BAKİYE !");
        time_t t= time(NULL);
        printf("\nislem tarihi & saati : %s", ctime(&t));
    }
    else if(odenen==tutar){
        printf("\n\nİSLEM ONAYLANDI. URUNUNUZU ALABİLİRSİNİZ.");
        time_t t= time(NULL);
        printf("\nislem tarihi & saati : %s", ctime(&t));
        u1[rSecim-1].stok-=rStok;
    }
    else{
        printf("\n\nİSLEM ONAYLANDI. URUNUNUZU ALABİLİRSİNİZ.\n\nPARA USTU: %d",odenen-tutar);
        time_t t= time(NULL);
        printf("\nislem tarihi & saati : %s", ctime(&t));
        u1[rSecim-1].stok-=rStok;
    }
    FILE *yaz= fopen("urunler.dat","wb");
    if(yaz!=NULL){
        fwrite(u1,sizeof(urun),5,yaz);
        fclose(yaz);
    }
}