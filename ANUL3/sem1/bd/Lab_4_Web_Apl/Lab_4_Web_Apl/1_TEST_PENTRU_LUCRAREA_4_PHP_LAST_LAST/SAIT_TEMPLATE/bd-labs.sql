-- phpMyAdmin SQL Dump
-- version 3.2.4
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Oct 27, 2011 at 08:06 PM
-- Server version: 5.1.44
-- PHP Version: 5.3.1

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `bd-labs`
--

-- --------------------------------------------------------

--
-- Table structure for table `info_students`
--

CREATE TABLE IF NOT EXISTS `info_students` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `Nume_prenume` varchar(35) NOT NULL,
  `grupa` varchar(10) NOT NULL,
  `echipa` text NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=10 ;

--
-- Dumping data for table `info_students`
--

INSERT INTO `info_students` (`ID`, `Nume_prenume`, `grupa`, `echipa`) VALUES
(1, 'Brumaru Ion', 'MI-100', 'e3'),
(2, 'Brumaru Ion', 'MI-100', 'e3'),
(3, 'Maimescu Alex', 'MI-100', 'Echipa #1: Analiza Riscului'),
(4, 'Zubco Pavel', 'MI-100', 'Echipa #3: Analiza Factoriala'),
(5, 'Semion', 'MI-101', 'Echipa #2: Metode Matematice'),
(6, 'Maimescu Alex', 'MI-101', 'Echipa #1: Analiza Riscului'),
(7, 'Inglis Semion', 'MI-101', 'Echipa #3: Analiza Factoriala'),
(8, 'Ursu Ion', 'MI-101', 'Echipa #3: Analiza Factoriala'),
(9, 'Halca Eugen', 'MI-101', 'Echipa #2: Metode Matematice');
