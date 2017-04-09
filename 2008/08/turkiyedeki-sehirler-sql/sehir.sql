-- phpMyAdmin SQL Dump
-- http://www.phpmyadmin.net
--
-- Türkiye'deki Şehirler
-- Umut Benzer 
-- http://www.ubenzer.com/
--

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

CREATE TABLE IF NOT EXISTS `sehirler` (
  `ID` int(3) unsigned NOT NULL default '0' COMMENT 'Plaka Numarası',
  `name` tinytext NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

INSERT INTO `sehirler` (`ID`, `name`) VALUES
(1, 'Adana'),
(2, 'Adıyaman'),
(3, 'Afyonkarahisar'),
(4, 'Ağrı'),
(68, 'Aksaray'),
(5, 'Amasya'),
(6, 'Ankara'),
(7, 'Antalya'),
(75, 'Ardahan'),
(8, 'Artvin'),
(9, 'Aydın'),
(10, 'Balıkesir'),
(74, 'Bartın'),
(72, 'Batman'),
(69, 'Bayburt'),
(11, 'Bilecik'),
(12, 'Bingöl'),
(14, 'Bolu'),
(15, 'Burdur'),
(13, 'Bitlis'),
(16, 'Bursa'),
(17, 'Çanakkale'),
(18, 'Çankırı'),
(19, 'Çorum'),
(20, 'Denizli'),
(21, 'Diyarbakır'),
(81, 'Düzce'),
(22, 'Edirne'),
(23, 'Elazığ'),
(24, 'Erzincan'),
(25, 'Erzurum'),
(26, 'Eskişehir'),
(27, 'Gaziantep'),
(28, 'Giresun'),
(44, 'Malatya'),
(0, '(belirtilmedi)'),
(67, 'Zonguldak'),
(66, 'Yozgat'),
(77, 'Yalova'),
(65, 'Van'),
(64, 'Uşak'),
(62, 'Tunceli'),
(61, 'Trabzon'),
(60, 'Tokat'),
(59, 'Tekirdağ'),
(73, 'Şırnak'),
(63, 'Şanlıurfa'),
(58, 'Sivas'),
(57, 'Sinop'),
(56, 'Siirt'),
(55, 'Samsun'),
(54, 'Sakarya'),
(53, 'Rize'),
(80, 'Osmaniye'),
(52, 'Ordu'),
(51, 'Niğde'),
(50, 'Nevşehir'),
(49, 'Muş'),
(48, 'Muğla'),
(47, 'Mardin'),
(45, 'Manisa'),
(29, 'Gümüşhane'),
(30, 'Hakkari'),
(31, 'Hatay'),
(76, 'Iğdır'),
(32, 'Isparta'),
(33, 'İçel'),
(34, 'İstanbul'),
(35, 'İzmir'),
(46, 'Kahramanmaraş'),
(78, 'Karabük'),
(70, 'Karaman'),
(36, 'Kars'),
(37, 'Kastamonu'),
(38, 'Kayseri'),
(71, 'Kırıkkale'),
(39, 'Kırklareli'),
(40, 'Kırşehir'),
(79, 'Kilis'),
(41, 'Kocaeli'),
(42, 'Konya'),
(43, 'Kütahya');
