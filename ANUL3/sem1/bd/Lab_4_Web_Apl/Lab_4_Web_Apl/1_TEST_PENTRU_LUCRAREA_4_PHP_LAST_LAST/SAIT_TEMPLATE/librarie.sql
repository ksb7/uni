-- phpMyAdmin SQL Dump
-- version 5.0.3
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 05, 2021 at 02:05 PM
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
-- Database: `librarie`
--

-- --------------------------------------------------------

--
-- Table structure for table `autor`
--

CREATE TABLE `autor` (
  `id_autor` int(11) NOT NULL,
  `nume_autor` varchar(25) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `autor`
--

INSERT INTO `autor` (`id_autor`, `nume_autor`) VALUES
(1, 'Petru'),
(2, 'Diuma'),
(3, 'Vieru'),
(4, 'Lena'),
(5, 'Ioana'),
(6, 'Ghita'),
(7, 'Colea'),
(8, 'Nicu'),
(9, 'Valea');

-- --------------------------------------------------------

--
-- Table structure for table `carti`
--

CREATE TABLE `carti` (
  `idcarte` char(15) NOT NULL,
  `autor` varchar(32) DEFAULT NULL,
  `titlu` varchar(52) DEFAULT NULL,
  `pret` float(8,2) DEFAULT NULL,
  `cantitatea` tinyint(3) UNSIGNED DEFAULT NULL,
  `id_autor` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `carti`
--

INSERT INTO `carti` (`idcarte`, `autor`, `titlu`, `pret`, `cantitatea`, `id_autor`) VALUES
('2-2222-222-10', 'Petru  GFGF ', 'Laborator Mysql-Php vbvbvb', 950.00, 23, 1),
('2-2222-222-13', 'Vieru', 'MAMA', 2000.00, 200, 3),
('2-2222-2222-1', 'Diuma', 'Cei trei muschetari Php', 775.00, 10, 1),
('2-2222-2222-2', 'Diuma', 'Cei trei muschetari Php', 775.00, 10, 1),
('2-2222-2222-22', 'Eminescu', 'Ghid Php', 1000.00, 3, 2),
('2-2222-2222-23', 'Eminescu', 'Ghid Php', 1000.00, 3, 2),
('2-2222-2222-4', 'Petru', 'Cei trei muschetari Php', 155.00, 20, 1),
('2-2222-2222-5', 'Ion', 'Cei trei muschetari Php', 310.00, 5, 3),
('2-2222-2222-6', 'Vica', 'Cei trei muschetari Php', 930.00, 40, 4),
('2-2222-2222-7', 'Sandu', 'Cei trei muschetari Php', 465.00, 222, 2),
('2-2222-2222-8', 'Eminescu', 'Ghid Php', 1000.00, 3, 6),
('2-2222-2222-9', 'Eminescu', 'Ghid Php', 1000.00, 3, 2);

-- --------------------------------------------------------

--
-- Table structure for table `furnizor`
--

CREATE TABLE `furnizor` (
  `id_furn` int(11) NOT NULL,
  `nume_furn` char(10) NOT NULL,
  `id_tara` varchar(3) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `furnizor`
--

INSERT INTO `furnizor` (`id_furn`, `nume_furn`, `id_tara`) VALUES
(1, 'Alfa0', 'MD'),
(2, 'Alfa1', 'RO'),
(3, 'Beta', 'RU'),
(4, 'Gama0', 'MD'),
(5, 'Gama1', 'RO'),
(6, 'Gama2', 'SUA'),
(7, 'Eta', 'IT');

-- --------------------------------------------------------

--
-- Table structure for table `magazin`
--

CREATE TABLE `magazin` (
  `articol` int(11) NOT NULL,
  `furnizor` char(10) NOT NULL,
  `pret` double(5,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `magazin`
--

INSERT INTO `magazin` (`articol`, `furnizor`, `pret`) VALUES
(1, 'Alfa', 3.45),
(1, 'Alfa', 3.99),
(2, 'Beta', 10.99),
(3, 'Gama', 1.45),
(3, 'Gama', 1.69),
(3, 'Gama', 1.25),
(4, 'Eta', 19.95);

-- --------------------------------------------------------

--
-- Table structure for table `market`
--

CREATE TABLE `market` (
  `articol` int(11) NOT NULL,
  `furnizor` char(10) NOT NULL,
  `pret` double(5,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `market`
--

INSERT INTO `market` (`articol`, `furnizor`, `pret`) VALUES
(1, 'Alfa', 3.45),
(1, 'Alfa1', 3.99),
(2, 'Beta', 10.99),
(3, 'Gama', 1.45),
(3, 'Gama1', 1.69),
(3, 'Gama2', 1.25),
(4, 'Eta', 19.95);

-- --------------------------------------------------------

--
-- Table structure for table `producator`
--

CREATE TABLE `producator` (
  `id_pr` int(11) NOT NULL,
  `nume_pr` char(10) NOT NULL,
  `id_furn` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `producator`
--

INSERT INTO `producator` (`id_pr`, `nume_pr`, `id_furn`) VALUES
(1, 'Sssssss', 1),
(2, 'Tttttttttt', 1),
(3, 'Aaaaaa', 2),
(4, 'Bbbbb', 3),
(5, 'Ccccc', 4),
(6, 'Ddddd', 3),
(7, 'Eeeee', 3);

-- --------------------------------------------------------

--
-- Table structure for table `tara`
--

CREATE TABLE `tara` (
  `id_tara` char(3) NOT NULL,
  `nume_tara` varchar(25) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `tara`
--

INSERT INTO `tara` (`id_tara`, `nume_tara`) VALUES
('HN', 'Gama0'),
('IT', 'Eta'),
('MD', 'Alfa0'),
('NR', 'Gama1'),
('RO', 'Alfa1'),
('RU', 'Beta'),
('SUA', 'Gama2');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `autor`
--
ALTER TABLE `autor`
  ADD PRIMARY KEY (`id_autor`);

--
-- Indexes for table `carti`
--
ALTER TABLE `carti`
  ADD PRIMARY KEY (`idcarte`),
  ADD KEY `id_autor` (`id_autor`);

--
-- Indexes for table `furnizor`
--
ALTER TABLE `furnizor`
  ADD PRIMARY KEY (`id_furn`),
  ADD KEY `id_tara` (`id_tara`);

--
-- Indexes for table `market`
--
ALTER TABLE `market`
  ADD PRIMARY KEY (`articol`,`furnizor`);

--
-- Indexes for table `producator`
--
ALTER TABLE `producator`
  ADD PRIMARY KEY (`id_pr`),
  ADD KEY `id_furn` (`id_furn`);

--
-- Indexes for table `tara`
--
ALTER TABLE `tara`
  ADD PRIMARY KEY (`id_tara`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `autor`
--
ALTER TABLE `autor`
  MODIFY `id_autor` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- AUTO_INCREMENT for table `furnizor`
--
ALTER TABLE `furnizor`
  MODIFY `id_furn` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `producator`
--
ALTER TABLE `producator`
  MODIFY `id_pr` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `carti`
--
ALTER TABLE `carti`
  ADD CONSTRAINT `carti_ibfk_1` FOREIGN KEY (`id_autor`) REFERENCES `autor` (`id_autor`);

--
-- Constraints for table `furnizor`
--
ALTER TABLE `furnizor`
  ADD CONSTRAINT `furnizor_ibfk_1` FOREIGN KEY (`id_tara`) REFERENCES `tara` (`id_tara`);

--
-- Constraints for table `producator`
--
ALTER TABLE `producator`
  ADD CONSTRAINT `producator_ibfk_1` FOREIGN KEY (`id_furn`) REFERENCES `furnizor` (`id_furn`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
