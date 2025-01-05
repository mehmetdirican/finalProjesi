#include <stdio.h>
#include <string.h>

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"

void mnScreen();

int main(int argc, char *argv[]) {
	
	FILE *fp = fopen("veriler.txt","a");
	
    int toplam = 0;
    int sac_kesim = 450;
    int sakal_kesim = 250;
    int sac_boya = 500;
    int cilt_bakimi = 300;
    int i = 0;

    char yapilan_islemler[100][100];
    int islem_sayisi = 0;

    // Randevularýn saatlerini saklayacak dizi
    int randevular[100];
    int randevu_sayisi = 0;

    while (1) {
        mnScreen();
        int randevu_saati;
        int menu_secim;

        printf(CYAN "Seciminizi giriniz: " RESET);
        scanf("%d", &menu_secim);

        switch (menu_secim) {
            case 1: {
                char musteri_no[12];
                while (1) {
                    printf(YELLOW "Lutfen telefon numaranizi 11 haneli olarak giriniz (Orn: 05355415569): " RESET);
                    scanf("%s", musteri_no);

                    if (strlen(musteri_no) == 11) {
                        break;
                    } else {
                        printf(RED "Gecersiz telefon numarasi. Lutfen tekrar deneyin.\n" RESET);
                    }
                }

                while (1) {
                    printf(BLUE "\n*** Hizmet Secimi ***\n" RESET);
                    printf(GREEN "1. Sac kesimi (450 TL)\n");
                    printf("2. Sakal kesimi (250 TL)\n");
                    printf("3. Sac boyama (500 TL)\n");
                    printf("4. Cilt bakimi (300 TL)\n");
                    printf(RED "5. Ana menuye don\n" RESET);

                    int hizmet_secim;
                    printf(CYAN "Seciminizi giriniz: " RESET);
                    scanf("%d", &hizmet_secim);

                    if (hizmet_secim == 5) {
                        break;
                    }

                    printf(YELLOW "Lutfen randevu saatini giriniz (8-21): " RESET);
                    scanf("%d", &randevu_saati);

                    if (randevu_saati >= 8 && randevu_saati <= 21) {
                        int is_cakisma = 0;

                        // Çakýþan bir randevu olup olmadýðýný kontrol ediyor eðer çakýlan bir randevu varsa red veriyor ve yeni bir saat seçtiriyor.//
                        int j = 0;
                        for (j = 0; j < randevu_sayisi; j++) {
                            if (randevular[j] == randevu_saati) {
                                is_cakisma = 1;
                                break;
                            }
                        }

                        if (is_cakisma) {
                            printf(RED "Bu saatte daha onceden bir randevu alinmis. Lutfen baska bir saat secin.\n" RESET);
                        } else {
                            switch (hizmet_secim) {
                                case 1:
                                    toplam += sac_kesim;
                                    printf(GREEN "Saat %d'ye sac kesimi randevunuz onaylandi.\n" RESET, randevu_saati);
                                    sprintf(yapilan_islemler[islem_sayisi++], "Telefon: %s - Sac kesimi - Saat: %d", musteri_no, randevu_saati);
                                    randevular[randevu_sayisi++] = randevu_saati;  
                                    break;
                                case 2:
                                    toplam += sakal_kesim;
                                    printf(GREEN "Saat %d'ye sakal kesimi randevunuz onaylandi.\n" RESET, randevu_saati);
                                    sprintf(yapilan_islemler[islem_sayisi++], "Telefon: %s - Sakal kesimi - Saat: %d", musteri_no, randevu_saati);
                                    randevular[randevu_sayisi++] = randevu_saati;  
                                    break;
                                case 3:
                                    toplam += sac_boya;
                                    printf(GREEN "Saat %d'ye sac boyama randevunuz onaylandi.\n" RESET, randevu_saati);
                                    sprintf(yapilan_islemler[islem_sayisi++], "Telefon: %s - Sac boyama - Saat: %d", musteri_no, randevu_saati);
                                    randevular[randevu_sayisi++] = randevu_saati;  
                                    break;
                                case 4:
                                    toplam += cilt_bakimi;
                                    printf(GREEN "Saat %d'ye cilt bakimi randevunuz onaylandi.\n" RESET, randevu_saati);
                                    sprintf(yapilan_islemler[islem_sayisi++], "Telefon: %s - Cilt bakimi - Saat: %d", musteri_no, randevu_saati);
                                    randevular[randevu_sayisi++] = randevu_saati; 
                                    break;
                                default:
                                    printf(RED "Gecersiz secim. Lutfen tekrar deneyin.\n" RESET);
                            }
                        }
                    } else {
                        printf(RED "Gecersiz saat. Lutfen 8:00 ile 21:00 arasinda bir saat secin.\n" RESET);
                    }

                    printf(YELLOW "Baska bir islem yapmak ister misiniz? (Evet: 1, Hayir: 0): " RESET);
                    int devam;
                    scanf("%d", &devam);
                    if (devam == 0) {
                        break;
                    }
                }

                printf(GREEN "Toplam tutar: %d TL\n" RESET, toplam);
                printf(CYAN "Secilen hizmetleri onayliyor musunuz? (Evet: 1, Hayir: 0): " RESET);
                int tutar_onay;
                scanf("%d", &tutar_onay);

                if (tutar_onay == 1) {
                    printf(GREEN "Randevunuz basari ile onaylandi!\n" RESET);
                } else {
                    printf(RED "Islemler iptal edildi.\n" RESET);
                }
                break;
            }
            case 2: {
                char kullaniciadi[20];
                char sifre[10];

                printf(CYAN "Kullanici adi giriniz: " RESET);
                scanf("%s", kullaniciadi);
                printf(CYAN "Sifre giriniz: " RESET);
                scanf("%s", sifre);

                if (strcmp(kullaniciadi, "admin") == 0 && strcmp(sifre, "sifre") == 0) {
                    printf(GREEN "Giris basarili\n" RESET);
                    printf(YELLOW "Toplam alinmis islemler tutari: %d TL\n" RESET, toplam);
                    printf(CYAN "Yapilan islemler:\n" RESET);
                    for (i = 0; i < islem_sayisi; i++) {
                        printf("%d. %s\n", i + 1, yapilan_islemler[i]);
                        fprintf(fp,yapilan_islemler[i]);
                        fclose(fp);
                    }
                } else {
                    printf(RED "Kullanici adi veya sifre hatali\n" RESET);
                }
                break;
            }
            case 3:
                printf(RED "Sistemden cikiliyor...\n" RESET);
                return 0;
            default:
                printf(RED "Gecersiz secim. Lutfen tekrar deneyin.\n" RESET);
        }
    }
	
    return 0;
}

void mnScreen() {
    printf(BOLD "\n====================\n" RESET);
    printf(BLUE "*** ANA MENU ***\n" RESET);
    printf(BOLD "====================\n" RESET);
    printf(GREEN "1. Musteri girisi\n");
    printf("2. Calisan girisi\n");
    printf(RED "3. Cikis\n" RESET);
    printf(BOLD "====================\n\n" RESET);
}

