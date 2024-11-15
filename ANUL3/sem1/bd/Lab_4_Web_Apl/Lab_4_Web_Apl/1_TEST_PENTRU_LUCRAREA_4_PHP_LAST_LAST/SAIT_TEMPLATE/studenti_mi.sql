-- phpMyAdmin SQL Dump
-- version 5.0.3
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 05, 2021 at 02:06 PM
-- Server version: 10.4.14-MariaDB
-- PHP Version: 7.2.34

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `studenti_mi`
--

-- --------------------------------------------------------

--
-- Table structure for table `an2`
--

CREATE TABLE `an2` (
  `nume` varchar(20) NOT NULL,
  `data_n` date DEFAULT NULL,
  `an_inscriere` int(4) DEFAULT NULL,
  `email` varchar(20) DEFAULT NULL,
  `telefon` varchar(20) DEFAULT NULL,
  `mobil` varchar(20) DEFAULT NULL,
  `obs` int(4) DEFAULT NULL,
  `PG` int(2) DEFAULT NULL,
  `MS` int(2) DEFAULT NULL,
  `BD2` int(2) DEFAULT NULL,
  `TI` int(2) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `an2`
--

INSERT INTO `an2` (`nume`, `data_n`, `an_inscriere`, `email`, `telefon`, `mobil`, `obs`, `PG`, `MS`, `BD2`, `TI`) VALUES
('Petrov', '2012-12-12', 2020, 'aaaa@yahoo.com', '22-22-22', '693222222', 1, 7, 8, 7, 8),
('Sidorov', '2012-12-13', 2021, 'abaa@ygmail.com', '22-22-32', '693222222', 2, 5, 8, 8, 8),
('Borta', '2012-12-14', 2019, 'acaa@yahoo.com', '22-22-42', '693222222', 3, 6, 8, 9, 6),
('Covrig', '2012-12-15', 2018, 'adaa@gmail.com', '22-22-52', '693222222', 4, 6, 8, 8, 9),
('Mamaliga', '2012-12-16', 2018, 'aeaa@yahoo.com', '22-22-72', '693222222', 5, 5, 8, 7, 6),
('Furca', '2012-12-17', 2019, 'afaa@hotmail.com', '22-22-62', '693222222', 6, 7, 8, 7, 6),
('Boul', '2012-12-18', 2020, 'agaa@yahoo.com', '22-22-82', '693222222', 7, 5, 8, 7, 9);

-- --------------------------------------------------------

--
-- Table structure for table `info_students`
--

CREATE TABLE `info_students` (
  `ID` int(11) NOT NULL,
  `Nume_prenume` varchar(35) NOT NULL,
  `grupa` varchar(10) NOT NULL,
  `echipa` text NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

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
(9, 'Halca Eugen', 'MI-101', 'Echipa #2: Metode Matematice'),
(10, 'Mamaliga_mare', '#1', 'Alba ca Zaoada'),
(11, 'Mamaliga_mare', '#1', 'Alba ca Zaoada');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `info_students`
--
ALTER TABLE `info_students`
  ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `info_students`
--
ALTER TABLE `info_students`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
