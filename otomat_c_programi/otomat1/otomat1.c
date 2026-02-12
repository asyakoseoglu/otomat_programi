#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void listeleme(int urunNo[5], char urunler[5][20],int fiyatlar[5], int stoklar[5]);
void satis(int urunNo[5], int fiyatlar[5], int stoklar[5]);
int secim(int urunNo[5]);
int stokKontrol(int rSecim, int stoklar[5]);
int odeme(int rSecim, int rStok, int fiyatlar[5], int stoklar[5]);

void stokYukle(int stoklar[5],char urunler[5][20]); // !!
void stokKaydet(int stoklar[5]); // !!

int main()
{
    int i=0;
    int urunNo[5];
    while(i<5){
        urunNo[i]=i+1;
        i++;
    }
    
    char urunler[5][20] = {"Cips", "Soda", "Cikolata", "Sakiz", "Biskuvi"};
    int fiyatlar[5] = {50, 30, 25, 10, 40};
    int stoklar[5] = {0, 0, 0, 0, 0}; // !!

    stokYukle(stoklar,urunler); // !!

    int devamMi;
    do{
        listeleme(urunNo, urunler, fiyatlar, stoklar);
        satis(urunNo, fiyatlar, stoklar);
        printf("\n\nisleme devam etmek istiyor musunuz ? (1: Evet, 0: Hayir.) ");
        scanf("%d", &devamMi);
    }while(devamMi==1);
    return 0;
}

void listeleme(int urunNo[5],char urunler[5][20],int fiyatlar[5], int stoklar[5])
{
    int i=0;
    printf("--------------------URUN LİSTESİ---------------------\n\n");
    printf("%-10s%-30s%-10s%-10s\n\n", "URUN NO","URUN ADI","FIYAT","STOK");
    while(i<5){
        printf("%-10d%-30s%-10d%-10d", urunNo[i],urunler[i],fiyatlar[i],stoklar[i]);
        i++;
        printf("\n");
    }
}

void satis(int urunNo[5], int fiyatlar[5], int stoklar[5])
{
    int rSecim = secim(urunNo);
    if(rSecim != -1){
        int rStok = stokKontrol(rSecim,stoklar);
        if(rStok != -1){
            odeme(rSecim,rStok,fiyatlar,stoklar);
        }
    }
}

int secim(int urunNo[5])
{
    int secim;
    int kontrol=0, i=0;
    printf("\n\nurun numarasi seciniz: ");
    scanf("%d", &secim);

    while(i<5){
        if(secim==urunNo[i]){
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

int stokKontrol(int rSecim, int stoklar[5])
{
        int adet;
        printf("\nurun adedi giriniz: ");
        scanf("%d", &adet);
        
        if(adet<=stoklar[rSecim-1]){
            return adet;
        }
        else{
            printf("%d numarali urunden kalmamistir.", rSecim);
            return -1;
        }
}

int odeme(int rSecim, int rStok, int fiyatlar[5],int stoklar[5])
{
    printf("\ntoplam tutar: %d", fiyatlar[rSecim-1]*rStok);
    int odenen;
    printf("\n\npara girisi yapiniz:");
    scanf("%d", &odenen);

    if(odenen<fiyatlar[rSecim-1]*rStok){
        printf("\nYETERSİZ BAKİYE !");
        time_t t= time(NULL);
        printf("\nislem tarihi & saati : %s", ctime(&t));
    }
    else if(odenen==fiyatlar[rSecim-1]*rStok){
        printf("\n\nİSLEM ONAYLANDI. URUNUNUZU ALABİLİRSİNİZ.");
        time_t t= time(NULL);
        printf("\nislem tarihi & saati : %s", ctime(&t));
        stoklar[rSecim-1]-=rStok;
    }
    else{
        printf("\n\nİSLEM ONAYLANDI. URUNUNUZU ALABİLİRSİNİZ.\n\nPARA USTU: %d",odenen-fiyatlar[rSecim-1]*rStok);
        time_t t= time(NULL);
        printf("\nislem tarihi & saati : %s", ctime(&t));
        stoklar[rSecim-1]-=rStok;
    }
    stokKaydet(stoklar); // !!
    return 0;
}

void stokYukle(int stoklar[5], char urunler[5][20]) // !!
{
    FILE *ptr= fopen("stoklar.txt", "r");
    int i=0;
    if(ptr==NULL){
        printf("\n");
        while(i<5){
            printf("%d. urun \"%s\" icin stok giriniz: ", i+1, urunler[i]);
            scanf("%d", &stoklar[i]);
            i++;
        }
        stokKaydet(stoklar); // !!
    }
    else{
        while(i<5){
            fscanf(ptr, "%d", &stoklar[i]);
            i++;
        }
        fclose(ptr); // !!
    }
}

void stokKaydet(int stoklar[5]) // !!
{
    FILE *ptr= fopen("stoklar.txt", "w");
    int i=0;
    while(i<5){
        fprintf(ptr, "%d ", stoklar[i]);
        i++;
    }
    fclose(ptr);
}