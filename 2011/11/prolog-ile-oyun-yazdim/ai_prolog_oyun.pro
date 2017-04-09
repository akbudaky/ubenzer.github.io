DOMAINS
kare = symbol
kareno, zarsayisi, karepuan, oyuncuno = integer
isim,kareadi = string

PREDICATES
nondeterm kare(kareno, kareadi, karepuan)
oyunculari_al
nondeterm oyna(oyuncuno)
nondeterm oyuncu(oyuncuno, isim)
zarat(zarsayisi)
nondeterm bulunmaktadir(oyuncuno,kareno)
nondeterm oyuncuilerlet(oyuncuno,zarsayisi)
nondeterm kareilerletmekurali(kareno,integer)

DATABASE
xoyuncu(oyuncuno, isim)
xbulunmaktadir(oyuncuno,kareno)

CLAUSES
oyuncu(Oyuncuno, Isim) :- xoyuncu(Oyuncuno, Isim).
bulunmaktadir(Oyuncuno,Kareno) :- xbulunmaktadir(Oyuncuno,Kareno).

kare(0,   "BASLANGIC: Ege Bilgisayar Muhendisligi", 0).
kare(1,   "BORNOVA: IKEA",0).
kare(2,   "BORNOVA: Buyuk parkta guzel bir gun gecirdin.",2).
kare(3,   "BORNOVA: Forum Bornova",0).
kare(4,   "BORNOVA: Ozkanlar Migros",0).
kare(5,   "BORNOVA: Bornova Merkez",0).
kare(6,   "BORNOVA: Tez hocan aradi, cok acil okula cagirdi.",-10).
kare(7,   "BORNOVA: Askerlik Subesi",0).
kare(8,   "BORNOVA: Antakya Donercisi'nde super bir tavuk doner yedin.",5).
kare(9,   "BORNOVA: Evka-3",0).
kare(10,  "BORNOVA: Evka-4",0).
kare(11,  "BORNOVA: Cok yagmur yagdi ve etrafi sular kapladi. Bolumden cikip metroya giderken camur icinde kaldin.",-2).
kare(12,  "BORNOVA: Yesik Kosk",0).
kare(13,  "BORNOVA: Kis Bahcesi",0).
kare(14,  "BORNOVA: Buz Pateni Pisti",0).
kare(15,  "BORNOVA: Metroyu ucu ucuna kacirdin. Bir sonrakine 10 dakika var.",-1).
kare(16,  "BORNOVA: Kipa",0).
kare(17,  "BORNOVA: Cafe Deyim",0).
kare(18,  "BORNOVA: Teras Kafe'ye gittin, adam sana kufretti.",-1).
kare(19,  "BORNOVA: Buz patenine gittin, sosyal oldun.",+3).
kare(20,  "BORNOVA: 525",0).
kare(21,  "BORNOVA: Nufus subesine gidip ikametini tasitmamissin. 300TL ceza yedin.",-10).
kare(22,  "BORNOVA: Kayseri Manticisi",0).
kare(23,  "BORNOVA: Kampuse tur atmaya ciktin.",1).
kare(24,  "BORNOVA: Vatan Bilgisayar",0).
kare(25,  "BORNOVA: Osman Kibar Kavsagi",0).
kare(26,  "BORNOVA: Kutuphane",0).
kare(27,  "BORNOVA: Yapay zeka dersinden AA aldin. Aybars Hoca odeve 100 verdi.",10).

kare(28,  "KARSIYAKA: Bostanli",0).
kare(29,  "KARSIYAKA: Nergis",0).
kare(30,  "KARSIYAKA: IZBAN bos geldi. Oturacak yer buldun. (Impossible is nothing.)",4).
kare(31,  "KARSIYAKA: 06 Dondurmacisi",0).
kare(32,  "KARSIYAKA: Vapurda korfezin tadini cikarttin.",1).
kare(33,  "KARSIYAKA: Kiyida guzel bir yuruyus yaptin.",1).
kare(34,  "KARSIYAKA: Altinbalik",0).
kare(35,  "KARSIYAKA: Evlendirme Daires",0).
kare(36,  "KARSIYAKA: Girne Bulvari",0).
kare(37,  "KARSIYAKA: Dedebasi Mahallesi",-1).
kare(38,  "KARSIYAKA: Kariyaka carsida gezindin, dondurma yedin.",2).
kare(39,  "KARSIYAKA: Bahriye Ucok Bulvari",0).
kare(40,  "KARSIYAKA: Semikler",0).
kare(41,  "KARSIYAKA: Trafik sikisikligina yakalandin.",-3).
kare(42,  "KARSIYAKA: Demirkopru",0).

kare(43,  "KONAK: Saat kulesinin onunde fotograf cektirdin. (Turist misin?)",-1).
kare(44,  "KONAK: Konak'tan bisiklet kiralayip Urla'ya kadar surdun.",39).
kare(45,  "KONAK: Kordon'da yuruyus yaptin.",5).
kare(46,  "KONAK: Piu Pizza",0).
kare(47,  "KONAK: Alsancak",0).
kare(48,  "KONAK: Sevgi Yolu",0).
kare(49,  "KONAK: Hilton kral dairesinde bir gece kaldin.",3).
kare(50,  "KONAK: Cingeneler yuruyusu basti. 'Abe bi gul vereyim beya, bacim falina bakayim.' faland edi.",-2).
kare(51,  "KONAK: Balik tutanlarin iplerine takilip dustun. Bacagini kirdin. :/",-20).
kare(52,  "KONAK: Alsancak Iskele",0).
kare(53,  "KONAK: Pasaport Iskele",0).
kare(54,  "KONAK: Iskele",0).
kare(55,  "KONAK: Birinin yol tarifini cevapladin.",1).
kare(56,  "KONAK: Fuar, Kulturpark",0).
kare(57,  "KONAK: HP Yetkili Servisi",0).
kare(58,  "KONAK: Kibris Sehitler Cd",0).
kare(59,  "KONAK: Haslanmis misir alip yedin.",1).
kare(60,  "KONAK: Gun batimini seyrettin.",8).
kare(61,  "KONAK: Cankaya",0).
kare(62,  "KONAK: Kemeralti",0).

kare(63,  "BALCOVA: Inciralti'nda yuruyus yaptin.",2).
kare(64,  "BALCOVA: Teleferige ciktin",2).
kare(65,  "BALCOVA: Ekonomi Universitesi",0).
kare(66,  "BALCOVA: Teleferikten indin. :D",-1).
kare(67,  "BALCOVA: Balcova Termal",0).
kare(68,  "BALCOVA: Bisikletin lastigi patladi",-3).
kare(69,  "BALCOVA: Balova Merkez",0).
kare(70,  "BALCOVA: Kipa",0).
kare(71,  "BALCOVA: Agora",0).
kare(72,  "BALCOVA: Media Markt'i gezdin.",2).
kare(73,  "BALCOVA: Vatan Bilgisayar",0).
kare(74,  "BALCOVA: Narlidere'ye dogru uzunca bir yuruyus yaptin.",8).
kare(75,  "BALCOVA: 169 son duragi",0).
kare(76,  "BALCOVA: Ozdilek",0).


kare(77,  "NARLIDERE: Folkart",0).
kare(78,  "NARLIDERE: Yigitcan'dan bilgisayar kasasini alip, evine goturdun.",-17).
kare(79,  "NARLIDERE: Merkez'deki Tansas",0).
kare(80,  "NARLIDERE: Sahilevleri",0).
kare(81,  "NARLIDERE: Yanlis otobuse bindin, Narbel'e ciktin.",-4).
kare(82,  "NARLIDERE: Zeytinalani",0).
kare(83,  "NARLIDERE: Ordu",0).
kare(84,  "NARLIDERE: Otoyol sapagini kacirdin.",-1).
kare(85,  "NARLIDERE: Cok trafik var",-2).
kare(86,  "NARLIDERE: Trafik acik.",5).
kare(87,  "NARLIDERE: Yigitcan'larin evi",0).
kare(88,  "NARLIDERE: Otoyol gisesine geldin ama KGS kredisi bitmis. Gidip doldurman lazim.",-10).
kare(89,  "NARLIDERE: Ziraat Bankasi",0).
kare(90,  "NARLIDERE: 9 Eylul Hastanesi",0).

kare(91,  "URLA: Bindigin dolmus habire dur/kalk yapiyor.",-1).
kare(92,  "SON 9 KARE -- URLA: Iskele",0).
kare(93,  "SON 8 KARE -- URLA: Dolmuscu abi 150'yle gidiyor!!",6).
kare(94,  "SON 7 KARE -- URLA: Merkez",0).
kare(95,  "SON 6 KARE -- URLA: Otoyol",0).
kare(96,  "SON 5 KARE -- URLA: Karaburun Cikisi",0).
kare(97,  "SON 4 KARE -- URLA: Kampuste karsine yilan cikti. Odun b.kuna karisti.",-2).
kare(98,  "SON 3 KARE -- URLA: Netsis'in onu",0).
kare(99,  "SON 2 KARE -- URLA: Netsis'den Linovi'ye giden patika",0).
kare(100, "SON KARE -- URLA: Sofor uyuyakaldi. Kaza yaptiniz. Agir yaralisin. Ege Tip'a yolladilar.",-200).

kare(No,Ad,Puan) :- No<0,write("Amanin, eski karelere dustunuz eyvahlar olsun."),nl, 
 Ad="Eksiye dusenleri sifirinci kareye cekme yardimi aldiniz. (aka. Size kiyak gectik.)",Nopozitif = (-1) * No,Puan=Nopozitif,!.
 kare(_,_,_) :- write("TEBRIKLER. SONUNDA VARDIN. KAZANDIN. :))"),nl,exit.

zarat(Sayi) :- write("Zar atmak icin bir tusa basin..."),readchar(_),nl,write("Zariniz "),
 random(5, Tsayi),Sayi=Tsayi+1,write(Sayi),write(" geldi."),nl.

oyunculari_al :-
 write("Oyunumuza hos geldiniz."),nl,write("Birinci oyuncu adinizi girin"),nl,
 readln(Isim1),write("Hos geldin "),write(Isim1),asserta(xoyuncu(1,Isim1)),
 nl,nl,nl,write("Ikinci oyuncu adinizi girin"),nl,readln(Isim2),write("Hos geldin "),
 write(Isim2),asserta(xoyuncu(2,Isim2)),nl,nl,asserta(xbulunmaktadir(1,0)),
 asserta(xbulunmaktadir(2,0)).
 
oyuncuilerlet(_,0). 
oyuncuilerlet(Oyuncuno, Zarsayisi) :- 
 bulunmaktadir(Oyuncuno,Kareno),retract(xbulunmaktadir(Oyuncuno,Kareno)),
 Yenikare=Kareno+Zarsayisi,asserta(xbulunmaktadir(Oyuncuno,Yenikare)),
 kareilerletmekurali(Yenikare,HavMac),oyuncuilerlet(Oyuncuno,HavMac).
     
kareilerletmekurali(Sayi,HavMac):- nl,kare(Sayi,Hikaye,Puan),write("Bulundugunuz yeni kare "),write(Sayi),
 write(" puani: "),write(Puan),nl,write(Hikaye),nl,HavMac = Puan.

oyna(1) :-
 oyuncu(1, Isim), nl,nl,write("Siradaki oyuncu: "),write(Isim),nl,write("Bulundugunuz kare: "),bulunmaktadir(1,Kare),write(Kare),nl,zarat(Sayi),
 oyuncuilerlet(1, Sayi),nl,oyna(2).
 
oyna(2) :-
 oyuncu(2, Isim), nl,nl,write("Siradaki oyuncu: "),write(Isim),nl,write("Bulundugunuz kare: "),bulunmaktadir(2,Kare),write(Kare),nl,zarat(Sayi),
 oyuncuilerlet(2, Sayi),nl,oyna(1).
 
GOAL
write("Urla'ya teknokente gitmece."),nl,nl,write("Ilk kim varacak?"),nl,oyunculari_al, oyna(1).