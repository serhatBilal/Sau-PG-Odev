/****************************************************************************
**					SAKARYA ÜNİVERSİTESİ
**			        BİLGİSAYAR ve BİLİŞİM BİLİMLERİ FAKÜLTESİ
**				    BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**				    PROGRAMLAMAYA GİRİŞİ DERSİ
**
**				    ÖDEV NUMARASI…...:1.(Proje ödevi)
**				    ÖĞRENCİ ADI......:Serhat BİLAL
**				    ÖĞRENCİ NUMARASI.:B191210309
**				    DERS GRUBU.......:1/B
****************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<string>
#include<clocale>
#include<ctime>

using namespace std;

class Kitap { // Kitap classimiz.
public:
	string sorguISBN; // kitap degiskenlerini private yapmaya gerek duymadigimdan public yaptim.
	Kitap();
	void kitapDegerAlma(); // fonksiyonlarimiz.
	void kitapEkle();
	void deleteBook();
	void updateTheBook();
	int kitapVarMi;
	string ISBN, kitapAdi, yazarAdi, yazarSoyadi, kitapKonu, kitapTur, sayfaSayisi;
	string alisTarihi, donusTarihi;
};
Kitap::Kitap() { // kurucu fonksiyonlda integer degiskenimize 0 atiyoruz default olarak
	kitapVarMi = 0;
}
void Kitap::kitapEkle() { // kitap ekleyen fonksiyonumuz
	cout << "Kitabin ISBN Numarasi";
	cin >> sorguISBN;
	kitapDegerAlma();
	int varMi = 0;
	char cevap = 'e';
	ifstream readFile("kitaplar.txt");
	while (readFile >> sorguISBN)
	{
		if (sorguISBN == ISBN) // eger girilen ISBN esitse kayita 1'e esitliyoruz degiskenimizi.
		{
			varMi = 1;
			break;
		}
	}
	readFile.close();
	if (varMi == 1) // degiskenimiz 1'e esitse kayit var demektir kitap kaydi yapmiyoruz.
	{
		cout << "Boyle bir kayit bulunmaktadir..!";
		cout << "Baska bir kayit yapmak istiyor musunuz..:(e/h)";
		cin >> cevap;
		if (cevap == 'E' || cevap == 'e') // eger kullanici bir daha kayit yapmak isterse kaydi yapiyoruz.
		{
			ofstream insertFile("kitaplar.txt", ios::app);
			kitapDegerAlma(); // kitap degiskenlerini alan fonksiyon
			insertFile << ISBN << " " << kitapAdi << " " << yazarAdi << " " << yazarSoyadi << " " << kitapKonu << " " << kitapTur << " " << sayfaSayisi << endl; //dosyaya yazdik.
			insertFile.close();
		}
		else
		{
			cout << "Iyi gunler dileriz..";
		}
	}
	else // eger varMi=0 ise yani 1 degilse sistemde kayit yok demektir o zaman kitabimizi sistemimize ekleyebiliriz.
	{
		ofstream insertFile("kitaplar.txt", ios::app);
		insertFile << ISBN << " " << kitapAdi << " " << yazarAdi << " " << yazarSoyadi << " " << kitapKonu << " " << kitapTur << " " << sayfaSayisi << endl;
		insertFile.close();
	}
}
void Kitap::kitapDegerAlma() { // kitap degiskenlerinin degerlerini alan fonksiyonumuz.

	cout << "Kitabin Ismi :";
	cin >> kitapAdi;

	cout << "Yazarin Adi :";
	cin >> yazarAdi;

	cout << "Yazarin Soyadi :";
	cin >> yazarSoyadi;

	cout << "Konusu :";
	cin >> kitapKonu;

	cout << "Turu :";
	cin >> kitapTur;

	cout << "Sayfa Sayisi :";
	cin >> sayfaSayisi;
}
void Kitap::deleteBook() { // kitap silecek fonksiyonumuz.

	int sayac = 0;
	int dosyaSayac = 0;

	char cevap = 'e';

	do
	{
		cout << "Lutfen silinecek kitap ISBN numarasi giriniz..";
		cin >> sorguISBN;
		ifstream readFile;
		readFile.open("kitaplar.txt");
		ofstream temp;
		temp.open("temp.txt");
		if (readFile.is_open() && temp.is_open())
		{
			while (readFile >> ISBN >> kitapAdi >> yazarAdi >> yazarSoyadi >> kitapKonu >> kitapTur >> sayfaSayisi)
			{
				if (!(ISBN == sorguISBN)) // kullanicidan aldigimiz sorguISBN'ye göre sistemde kayit eslesmeyen degerleri yeni dosyaya yazdiriyoruz.
				{
					sayac++;// silinmesi gereken kayit harici yazilan kayitlarin sayisini tutan sayac
					temp << ISBN << " " << kitapAdi << " " << yazarAdi << " " << yazarSoyadi << " " << kitapKonu << " " << kitapTur << " " << sayfaSayisi << endl;
				}
				dosyaSayac++;// dosyamizdaki tum kayitlarin sayisini tutan sayac
			}
		}
		if (dosyaSayac == sayac) // eger iki sayacimiz esitse kayit bulunamamistir anlamina gelir.
		{
			cout << "Kayit bulunamadi.." << endl;;
		}
		cout << "Baska bir kayit silmek istiyor musunuz.....(e/h)";
		cin >> cevap;
		if (!(cevap == 'h' || cevap == 'H' || cevap == 'e' || cevap == 'E'))
		{
			cout << "PROGRAM HATA!";
			exit(1);
		}
		readFile.close();
		temp.close();
	} while (!(cevap == 'h' || cevap == 'H'));

	remove("kitaplar.txt");
	(void)rename("temp.txt", "kitaplar.txt");
}
void Kitap::updateTheBook() {

	char cevap = 'e';
	kitapVarMi = 0;

	do
	{
		cout << "Lutfen guncellenecek kitap ISBN numarasi giriniz..";
		cin >> sorguISBN;
		ifstream readFile("kitaplar.txt");
		ofstream temp;
		temp.open("temp.txt");
		if (readFile.is_open() && temp.is_open())
		{
			while (readFile >> ISBN >> kitapAdi >> yazarAdi >> yazarSoyadi >> kitapKonu >> kitapTur >> sayfaSayisi) // kitaplar.txt dosyamizi okuyoruz.
			{
				if (sorguISBN == ISBN) // eger sistemle eslesiyorsa
				{
					kitapVarMi = 1; // kitabimiz var demektir
					kitapDegerAlma(); // yeni deger aliyoruz.
					temp << sorguISBN << " " << kitapAdi << " " << yazarAdi << " " << yazarSoyadi << " " << kitapKonu << " " << kitapTur << " " << sayfaSayisi << endl;
				}
				else // diger kayitlari yazdiriyoruz.
				{

					temp << ISBN << " " << kitapAdi << " " << yazarAdi << " " << yazarSoyadi << " " << kitapKonu << " " << kitapTur << " " << sayfaSayisi << endl;
				}

			}

		}
		if (kitapVarMi == 0) // default olarak kaldiysa degiskenimiz kayit yok demektir.
		{
			cout << "Kitap sistemde kayitli degildir..";
		}
		cout << "Baska bir guncelleme yapmak istiyor musunuz..(e/h)";
		cin >> cevap;
		if (!(cevap == 'h' || cevap == 'H' || cevap == 'e' || cevap == 'E'))
		{
			cout << "PROGRAM HATA!";
			exit(1);
		}
		readFile.close();
		temp.close();
	} while (!(cevap == 'h' || cevap == 'H'));

	remove("kitaplar.txt");
	(void)rename("temp.txt", "kitaplar.txt");

}

class okuyucu : Kitap // okuyucu classimiz kitapdan kalitim aliyoruz erisebilmek icin.
{
public:
	string sorguTc;
	int kullaniciVarMi;
	okuyucu();
	~okuyucu();
	void okuyucuDegerAlma();
	void okuyucuKayit();
	void okuyucuKayitGuncelle();
	void okuyucuKayitSil();
	void okuyucuKitapOduncAlma();
	void okuyucuKitapIade();
	void okuyucununKitaplari();
private: // private alanimiz.
	string tcNumarasi, okuyucuAdi, okuyucuSoyadi, okuyucuGorevi, uyeNo, telefonNo, okuyucuDogumTarihi;
	int alabilecegiKitapSayisi;
};
okuyucu::okuyucu() // kurucu fonksiyonumuzda integer degiskenlerimizin baslangic degerlerini atiyoruz.
{
	kullaniciVarMi = 0;
	alabilecegiKitapSayisi = 0;
}
okuyucu::~okuyucu() // yikici fonksiyonumuz.
{
}
void okuyucu::okuyucununKitaplari() {
	kullaniciVarMi = 0; // default olarak 0' atıyoruz.
	kitapVarMi = 0;
	cout << "Lutfen tc numarasi giriniz...";
	cin >> sorguTc;
	ifstream dosyaOku("okuyucu.txt");
	if (dosyaOku.is_open())
	{
		while (dosyaOku >> tcNumarasi >> okuyucuAdi >> okuyucuSoyadi >> uyeNo >> telefonNo >> okuyucuDogumTarihi >> okuyucuGorevi >> alabilecegiKitapSayisi) // okuyucu.txt dosya okumamız.
		{
			if (sorguTc == tcNumarasi) // eger kayıtlar eslestiyse ISBN numarasi istiyoruz.
			{
				cout << "Lutfen ISBN Numarasi giriniz..";
				cin >> sorguISBN;
				kullaniciVarMi = 1; // Kayitlar eslesti yani kullanicimiz kayitli 1 atıyoruz.
				ifstream dosyaOku2("odunc.txt");
				if (dosyaOku2.is_open())
				{
					while (dosyaOku2 >> ISBN >> tcNumarasi >> alisTarihi >> donusTarihi) // odunc.txt dosyasini okuyoruz.
					{
						if (sorguISBN == ISBN && tcNumarasi == sorguTc) // ISBN ve TC numaraları eslesti
						{
							kitapVarMi = 1;//okuyucu uzerine kitap var demektir,1 atiyoruz.
							cout << "Kullanici uzerindeki kitaplar..:" << endl;// ekrana kitap bilgilerini basiyoruz.
							cout << "ISBN no..:" << ISBN << endl;
							cout << "Odunc Tarihi..:" << alisTarihi << endl;
							cout << "Donus Tarihi...:" << donusTarihi << endl;

						}
					}
				}
				dosyaOku2.close();
			}
		}
	}
	dosyaOku.close();
	if (kullaniciVarMi == 0) // eger kayitlar eslesmediyse default degerimiz kaliyor yani kullanici yok
	{
		cout << "Sistemde kayitli kullanicimiz yoktur..!";
	}
	else if (kullaniciVarMi == 1 && kitapVarMi == 0) // tc kayiti var ama odunc kitabi yoksa ekrana bilgisini yaziyoruz.
	{
		cout << "Maalesef kullanici üzerinde kitap gözükmemektedir.";
	}

}
void okuyucu::okuyucuDegerAlma() { // okuyucunun degerlerini alan fonksiyon.
	cout << "Ad giriniz..:";
	cin >> okuyucuAdi;
	cout << "Soyadi giriniz..:";
	cin >> okuyucuSoyadi;
	cout << "Gorevi giriniz..:";
	cin >> okuyucuGorevi;
	cout << "Dogum tarihi giriniz..";
	cin >> okuyucuDogumTarihi;
	cout << "Uye No giriniz..";
	cin >> uyeNo;
	cout << "Telefon no giriniz..";
	cin >> telefonNo;
	cout << "Alabilecegi kitap sayisi giriniz..:";
	cin >> alabilecegiKitapSayisi;

}
void okuyucu::okuyucuKayitSil() {
	kullaniciVarMi = 0;
	char cevap = 'e';
	do
	{
		ifstream readFile;
		readFile.open("okuyucu.txt");
		ofstream temp;
		temp.open("temp.txt");
		cout << "Silinecek tc giriniz...";
		cin >> sorguTc;
		if (readFile.is_open() && temp.is_open())
		{
			while (readFile >> tcNumarasi >> okuyucuAdi >> okuyucuSoyadi >> uyeNo >> telefonNo >> okuyucuDogumTarihi >> okuyucuGorevi >> alabilecegiKitapSayisi)
			{
				if (tcNumarasi == sorguTc) // eger okuyucu sorgutc eslestiyse sistemle
				{
					kullaniciVarMi = 1; // degiskene 1 atiyoruz.
					cout << "Gercekten silme islemi yapmak istiyor musunuz..(e/h)";
					cin >> cevap;
					if ((cevap == 'e') || (cevap == 'E')) // onayladiysa silme islemini kullanici
					{
						cout << "Kayit silindi..!" << endl; // silme islemini yeni dosyaya yazdirmayarak yapiyoruz
						ifstream odunc("odunc.txt");
						ofstream temp2("temp2.txt");
						while (odunc >> ISBN >> tcNumarasi >> alisTarihi >> donusTarihi) //eger kullanicinin odunc almis kitabi varsa geri donus yapiyoruz
						{
							if (sorguTc == tcNumarasi) //
							{
								cout << "Kullanici oduncleri geri donduruldu!" << endl;
							}
							else
							{
								temp2 << ISBN << " " << tcNumarasi << " " << alisTarihi << " "
									<< donusTarihi << "\n";
							}
						}
						odunc.close();
						temp2.close();
						remove("odunc.txt");
						(void)rename("temp2.txt", "odunc.txt");
					}
					else // kullanici eger silme islemini onaylamadiysa kaydi silmiyoruz.
					{
						temp << tcNumarasi << " " << okuyucuAdi << " " << okuyucuSoyadi << " " << uyeNo << " " << telefonNo
							<< " " << okuyucuDogumTarihi << " " << okuyucuGorevi << " " << alabilecegiKitapSayisi << "\n";
					}
				}
				else// kullanicidan istenilen tc disindaki kayitlari yazdiriyoruz.
				{
					temp << tcNumarasi << " " << okuyucuAdi << " " << okuyucuSoyadi << " " << uyeNo << " " << telefonNo
						<< " " << okuyucuDogumTarihi << " " << okuyucuGorevi << " " << alabilecegiKitapSayisi << "\n";
				}

			}

		}
		if (kullaniciVarMi == 0) // degisken 0 olarak kaldiysa kullanici yok demektir.
		{
			cout << "Boyle bir kullanici kaydimiz yoktur." << endl;
		}
		cout << "Baska bir kullanici guncellemesi yapmak istiyor musunuz.(e/h)";
		cin >> cevap;
		if (!(cevap == 'h' || cevap == 'H' || cevap == 'e' || cevap == 'E'))
		{
			cout << "PROGRAM HATA!";
			exit(1);
		}
		readFile.close();
		temp.close();

	} while (!(cevap == 'h' || cevap == 'H'));
	remove("okuyucu.txt");
	(void)rename("temp.txt", "okuyucu.txt");

}
void okuyucu::okuyucuKitapOduncAlma() {
	kullaniciVarMi = 0; // default degerlerimizi atıyoruz,0
	kitapVarMi = 0;
	cout << "Lutfen kitap alacak kullanicimizin TC'sini giriniz..";
	cin >> sorguTc;
	ifstream dosyaOku("okuyucu.txt");
	ofstream dosyaYaz("odunc.txt", ios::app);
	while (dosyaOku >> tcNumarasi >> okuyucuAdi >> okuyucuSoyadi >> uyeNo >> telefonNo >> okuyucuDogumTarihi >> okuyucuGorevi >> alabilecegiKitapSayisi) // okuyucu.txt dosyası kayitlarini okuyoruz
	{
		if (sorguTc == tcNumarasi) // eger input aldigimiz tc eslesirse kayitla
		{
			kullaniciVarMi = 1; // kullanicimiz var demektir 1 atıyoruz.
			if (alabilecegiKitapSayisi == 0) // ilk basta alabilecegi kitap sayisina bakiyoruz 0'sa programı sonlandiriyoruz.
			{
				cout << "Maalesef alabileceginiz kitap sayisi 0'dir...";
				exit(1);
			}
			else // 0 degilse kitap alabilir demektir.
			{
				cout << "Almak istediginiz kitap ISBN numarasini giriniz..";
				cin >> sorguISBN;
				ifstream dosyaOku2("kitaplar.txt");
				try
				{
					if (dosyaOku2.is_open())
					{
						while (dosyaOku2 >> ISBN >> kitapAdi >> yazarAdi >> yazarSoyadi >> kitapTur >> kitapKonu >> sayfaSayisi) // kitaplar.txt dosyasini okuyoruz.
						{
							if (sorguISBN == ISBN) // eger input aldigimiz ISBN eslestiyse kayitla
							{
								kitapVarMi = 1; // kitapVarMi'ya 1 atiyoruz yani kitap odunc aldi ve kitap sistemde var
								cout << "Kitap odunc aliniyor!!" << endl;
								cout << "Alis ve donus tarihi giriniz..";
								cin >> alisTarihi;
								cout << "Donus tarihi giriniz..";
								cin >> donusTarihi;
								dosyaYaz << sorguISBN << " " << sorguTc << " " << alisTarihi << " " << donusTarihi << "\n"; // odunc.txt'ye bilgilerini yaziyoruz kitap alan okuyucunun
							}
						}
					}
				}
				catch (const std::exception&)
				{
					cout << "YANLIS ISLEM!!";
					exit(1);
				}
				dosyaOku2.close();

			}
		}
	}
	dosyaOku.close();
	dosyaYaz.close();
	if (kullaniciVarMi == 0) // eger default degerimiz 0 kaldıysa kullanicimiz yoktur.
	{
		cout << "Boyle bir kullanici bulunmamaktadir";
	}
	else if (kitapVarMi == 0) // eger 0'sa kullanicinin almak istedigi kitap sisstemde kayitli degildir.
	{
		cout << "Boyle bir kitap bulunmamaktadir";
	}
	else if (kitapVarMi == 1 && kullaniciVarMi == 1) // ikisi de 1 olursa hem kitap var hem de kullanici vardir ve odunc alinmistir.
	{
		ifstream okuyucuDosyaOku("okuyucu.txt");
		ofstream temp("temp.txt");
		while (okuyucuDosyaOku >> tcNumarasi >> okuyucuAdi >> okuyucuSoyadi >> uyeNo >> telefonNo >> okuyucuDogumTarihi >> okuyucuGorevi >> alabilecegiKitapSayisi) // okuyucu.txt dosyamizi okuyoruz.
		{
			if (sorguTc == tcNumarasi) // kitap alan kullanicimizi belirleyen kosulumuz
			{
				temp << tcNumarasi << " " << okuyucuAdi << " " << okuyucuSoyadi << " " << okuyucuGorevi << " " << okuyucuDogumTarihi
					<< " " << uyeNo << " " << telefonNo << " " << (alabilecegiKitapSayisi - 1) << endl; // ONEMLİ NOKTA alabilecegi kitap sayisini 1 azaltiyoruz.
			}
			else
			{
				temp << tcNumarasi << " " << okuyucuAdi << " " << okuyucuSoyadi << " " << okuyucuGorevi << " " << okuyucuDogumTarihi // diger kayitlari yazdiriyoruz.
					<< " " << uyeNo << " " << telefonNo << " " << alabilecegiKitapSayisi << endl;
			}
		}
		cout << "Odunc alinmistir!";
		okuyucuDosyaOku.close();
		temp.close();
		remove("okuyucu.txt");
		(void)rename("temp.txt", "okuyucu.txt");
	}

}
void  okuyucu::okuyucuKayit() {

	char cevap = '0';
	ifstream okuyucuDosya("okuyucu.txt");
	while (okuyucuDosya >> tcNumarasi >> okuyucuAdi >> okuyucuSoyadi >> uyeNo >> telefonNo >> okuyucuDogumTarihi >> okuyucuGorevi >> alabilecegiKitapSayisi)
	{
		if (tcNumarasi == sorguTc) // eger kayitlar eslestiyse kullanici var demektir.
		{
			kullaniciVarMi = 1;
			cout << "Boyle bir kayit bulunmaktadir..." << endl;
			cout << "Baska bir kayit yapmak istiyor musunuz..:(e/h)";
			cin >> cevap;
			break;
		}
	}
	okuyucuDosya.close();

	if (kullaniciVarMi == 0)
	{
		okuyucuDegerAlma(); // okuyucu bilgilerini aliyoruz.
		ofstream dosyaKayit2("okuyucu.txt", ios::app);
		dosyaKayit2 << sorguTc << " " << okuyucuAdi << " " << okuyucuSoyadi << " " << uyeNo << " " << telefonNo // dosyaya kayit ediyoruz.
			<< " " << okuyucuDogumTarihi << " " << okuyucuGorevi << " " << alabilecegiKitapSayisi << "\n";
		dosyaKayit2.close();
	}

	if (cevap == 'e') // kullanici yeni kayit yapmak istedi.
	{
		ofstream dosyaKayit("okuyucu.txt", ios::app);
		cout << "\n" << "Yeni tc giriniz..:";
		cin >> tcNumarasi;
		okuyucuDegerAlma();// yeni bilgileri aliyoruz.
		dosyaKayit << tcNumarasi << " " << okuyucuAdi << " " << okuyucuSoyadi << " " << uyeNo << " " << telefonNo // dosyaya kayit ediyoruz.
			<< " " << okuyucuDogumTarihi << " " << okuyucuGorevi << " " << alabilecegiKitapSayisi << "\n";
		dosyaKayit.close();
	}
	else
	{
		cout << "Iyi gunler dileriz...";
		/*cout << ZAMAN;*/
	}

}
void okuyucu::okuyucuKayitGuncelle() {
	char cevap = 'e';
	do
	{
		ifstream readFile;
		readFile.open("okuyucu.txt");
		ofstream temp;
		temp.open("temp.txt");
		cout << "Guncellenecek tc giriniz...";
		cin >> sorguTc;
		if (readFile.is_open() && temp.is_open()) // dosyalar aciksa
		{
			while (readFile >> tcNumarasi >> okuyucuAdi >> okuyucuSoyadi >> uyeNo >> telefonNo >> okuyucuDogumTarihi >> okuyucuGorevi >> alabilecegiKitapSayisi) //dosyamizi okuyoruz.
			{
				if (tcNumarasi == sorguTc) //eger tcNumarasi esitse sorguTc'mize
				{
					kullaniciVarMi = 1;
					okuyucuDegerAlma(); // guncellenecek degerlerimizi alip yazdiriyoruz yeni dosyaya
					temp << tcNumarasi << " " << okuyucuAdi << " " << okuyucuSoyadi << " " << uyeNo << " " << telefonNo
						<< " " << okuyucuDogumTarihi << " " << okuyucuGorevi << " " << alabilecegiKitapSayisi << "\n";
				}
				else // diger kayitlarimiz yaziliyor
				{
					temp << tcNumarasi << " " << okuyucuAdi << " " << okuyucuSoyadi << " " << uyeNo << " " << telefonNo
						<< " " << okuyucuDogumTarihi << " " << okuyucuGorevi << " " << alabilecegiKitapSayisi << "\n";
				}

			}

		}
		if (kullaniciVarMi == 0) // default degeri kaldiysa kullanici yok demektir.
		{
			cout << "Boyle bir kullanicimiz yoktur.." << endl;
		}
		cout << "Baska bir kullanici guncellemesi yapmak istiyor musunuz.(e/h)";
		cin >> cevap;
		if (!(cevap == 'h' || cevap == 'H' || cevap == 'e' || cevap == 'E'))
		{
			cout << "PROGRAM HATA!";
			exit(1);
		}
		readFile.close();
		temp.close();
	} while (!(cevap == 'h' || cevap == 'H'));

	remove("okuyucu.txt");
	(void)rename("temp.txt", "okuyucu.txt");
}
void okuyucu::okuyucuKitapIade() {
	kullaniciVarMi = 0;
	kitapVarMi = 0;
	int oduncMu = 0;
	cout << "Lutfen kitap iade edecek kullanicimizin TC'sini giriniz..";
	cin >> sorguTc;
	ifstream dosyaOku("okuyucu.txt");
	while (dosyaOku >> tcNumarasi >> okuyucuAdi >> okuyucuSoyadi >> uyeNo >> telefonNo >> okuyucuDogumTarihi >> okuyucuGorevi >> alabilecegiKitapSayisi)
	{
		if (sorguTc == tcNumarasi) // sistemle eslesiyor mi diye kontrol ediyoruz.
		{
			kullaniciVarMi = 1;
			cout << "Lutfen iade edilecek kitap ISBN Numarasi giriniz...";
			cin >> sorguISBN; // eger tc numarasi sistemde varsa ISBN numarasi giriyoruz kullanici yoksa ISBN istememize gerek yok
			ifstream kitapDosyaOku("kitaplar.txt");
			while (kitapDosyaOku >> ISBN >> kitapAdi >> yazarAdi >> yazarSoyadi >> kitapTur >> kitapKonu >> sayfaSayisi)
			{
				if (ISBN == sorguISBN) // eger kullanicinin girdigi ISBN kitaplar.txt'mizde varsa
				{
					kitapVarMi = 1;
					string oduncTc;
					string oduncISBN;
					ifstream oduncDosyaOku("odunc.txt");
					ofstream temp("temp.txt");
					while (oduncDosyaOku >> oduncISBN >> oduncTc >> alisTarihi >> donusTarihi)
					{
						if (oduncISBN == sorguISBN) //eger odunc dosyamizda kullanicinin girdigi degerler eslesiyorsa
						{
							oduncMu = 1; // kullacinin geri verdigini belirten degiskenimize atiyoruz 1'i

						}
						else
						{
							temp << oduncTc << " " << oduncISBN << " " << alisTarihi << " " << donusTarihi << endl; // diger kayitlarimizi yazdiriyoruz.
						}
					}
					oduncDosyaOku.close();
					temp.close();
					remove("odunc.txt");
					(void)rename("temp.txt", "odunc.txt");
					break;
				}
			}
			kitapDosyaOku.close();
			break;

		}
	}
	dosyaOku.close();
	if (kullaniciVarMi == 0)  // sistemde eslesen kullanici yoksa
	{
		cout << "Maalesef sistemde boyle bir okuyucu yoktur." << endl;
	}
	else if (kitapVarMi == 0) // sistemde eslesen kitap yoksa
	{
		cout << "Maalesef sistemde boyle bir kitap yoktur." << endl;
	}
	else if (kullaniciVarMi == 1 && kitapVarMi == 1 && oduncMu == 0) // eger kullanici ve kitap varsa ama odunc degilse olan kosulumuz
	{
		cout << "Maalesef odunc kitabiniz gozukmemektedir." << endl;
	}
	else if (kullaniciVarMi == 1 && kitapVarMi == 1 && oduncMu == 1) // kullanici var kitap var ve odunc almissa kitabi olan kosulumuz
	{
		cout << "Kitabiniz iade edilmistir..";
	}



}

class Kullanici // kullanici classimiz.
{
public:
	string sorguUsername; // sorgulayacagimiz degiskenlerin private olmasina gerek duymadim
	string sorguPassword;
	int varMi;
	Kullanici();
	~Kullanici();
	void login(string username2, string password2); // login fonksiyonumuz
	void kullanicidegerAlma();//
private:
	string username;
	string password;
};
Kullanici::Kullanici()
{
	varMi = 0;
}
Kullanici::~Kullanici()
{
}
void Kullanici::kullanicidegerAlma() { // kullanicidan giris degerleri alan fonksiyonumuz
	cout << "Kullanici adi giriniz..;";
	cin >> sorguUsername;
	cout << "Password giriniz..:";
	cin >> sorguPassword;
}
void Kullanici::login(string username2, string password2) { // alınan parametreye gore dosyayi okuyan veya karsilastiran fonksiyonumuz.
	ifstream dosyaOku("kullanıcılar.txt");
	while (dosyaOku >> username >> password)
	{
		if (username2 == username && password2 == password)
		{
			varMi = 1; // eger eslestiyse kayitlar 1 donduruyoruz.
			break;

		}
	}
	dosyaOku.close();

}

class Menu { // menu classimiz
public:
	okuyucu Okuyucu; // nesnelerimizi olusturuyoruz.
	Kitap kitap;
	string sorgu;
	int secim;
	Menu();
	void menuGetir();


};
Menu::Menu() { // kurucu fonksiyonumuz.
	secim = 0;
}

void Menu::menuGetir() { // Kullanicinin onune cikacak menumuz.


	cout << "------Lutfen secim yapınız:--------" << endl;
	cout << "1-Okuyucu kaydi" << endl;
	cout << "2-Okuyucu kaydi guncelleme" << endl;
	cout << "3-Okuyucu silme" << endl;
	cout << "4-Okuyucu uzerindeki kitaplar listesi" << endl;
	cout << "5-Okuyucu kitap odunc alma" << endl;
	cout << "6-Okuyucu kitap geri dondurme" << endl;
	cout << "7-Kitap ekleme" << endl;
	cout << "8-Kitap silme" << endl;
	cout << "9-Kitap duzeltme" << endl;
	cin >> secim;

	if (secim == 1)
	{
		cout << "Eklenecek tc giriniz...";
		cin >> Okuyucu.sorguTc;

		Okuyucu.okuyucuKayit();
	}
	else if (secim == 2)
	{
		Okuyucu.okuyucuKayitGuncelle();
	}
	else if (secim == 3)
	{
		Okuyucu.okuyucuKayitSil();
	}
	else if (secim == 4)
	{
		Okuyucu.okuyucununKitaplari();
	}
	else if (secim == 5)
	{
		Okuyucu.okuyucuKitapOduncAlma();
	}
	else if (secim == 6)
	{
		Okuyucu.okuyucuKitapIade();
	}
	else if (secim == 7)
	{
		kitap.kitapEkle();
	}
	else if (secim == 8)
	{
		kitap.deleteBook();
	}
	else if (secim == 9)
	{
		kitap.updateTheBook();
	}
	else
	{
		system("cls");
		cout << "Hatali deger girdiniz.." << endl;;
		menuGetir();
	}
}




int main()
{

	time_t now = time(0); // ekrana giris ve cikis tarihlerini yazdirmak icin.
	char* dt = ctime(&now);


	Kullanici kullanici;
	Menu menu;
	kullanici.kullanicidegerAlma(); // kullanici giris degerleri aliyoruz.
	kullanici.login(kullanici.sorguUsername, kullanici.sorguPassword);
	while (kullanici.varMi != 1) // eger kullanici kayitl degilse dogru girene kadar istiyoruz.
	{
		kullanici.kullanicidegerAlma();
		kullanici.login(kullanici.sorguUsername, kullanici.sorguPassword);
	}
	system("cls");
	cout << dt << endl;

	menu.menuGetir();// kullanici dogru girdiyse degerlerini menuyu getiriyoruz.

	cout << endl << dt << endl;;

	return 0;
}
