-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 20, 2025 at 05:42 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `alegeri`
--

-- --------------------------------------------------------

--
-- Table structure for table `consilieri`
--

CREATE TABLE `consilieri` (
  `id` int(11) NOT NULL,
  `nume` varchar(255) DEFAULT NULL,
  `prenume` varchar(255) DEFAULT NULL,
  `id_localitate` int(11) DEFAULT NULL,
  `id_partid` int(11) DEFAULT NULL,
  `id_functie` int(11) DEFAULT NULL,
  `id_gen` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `consilieri`
--

INSERT INTO `consilieri` (`id`, `nume`, `prenume`, `id_localitate`, `id_partid`, `id_functie`, `id_gen`) VALUES
(1, 'Olga', 'Ursu', 1, 1, 2, 2),
(2, 'Lilian', 'Carp', 1, 5, 2, 1),
(3, 'Irina', 'Gutnic', 1, 1, 2, 2),
(4, 'Zinaida', 'Popa', 1, 5, 2, 2),
(5, 'Angela', 'Cutasevici', 1, 1, 2, 2),
(7, 'Dunas', 'Nicolae', 4, 5, 2, 1),
(8, 'Pascal', 'Cătălina', 4, 5, 2, 2),
(9, 'Goncearov', 'Tatiana', 4, 5, 2, 2),
(10, 'Grigoriță', 'Maria', 4, 5, 2, 2);

-- --------------------------------------------------------

--
-- Table structure for table `functii`
--

CREATE TABLE `functii` (
  `id_functie` int(11) NOT NULL,
  `nume_functie` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `functii`
--

INSERT INTO `functii` (`id_functie`, `nume_functie`) VALUES
(1, 'Primar'),
(2, 'Consilier'),
(3, 'Secretar');

-- --------------------------------------------------------

--
-- Table structure for table `genuri`
--

CREATE TABLE `genuri` (
  `id_gen` int(11) NOT NULL,
  `nume_gen` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `genuri`
--

INSERT INTO `genuri` (`id_gen`, `nume_gen`) VALUES
(1, 'Masculin'),
(2, 'Feminin');

-- --------------------------------------------------------

--
-- Table structure for table `localitati`
--

CREATE TABLE `localitati` (
  `id_localitate` int(11) NOT NULL,
  `nume_localitate` varchar(100) NOT NULL,
  `id_unitate` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `localitati`
--

INSERT INTO `localitati` (`id_localitate`, `nume_localitate`, `id_unitate`) VALUES
(1, 'Chișinău', 5),
(2, 'Anenii Noi', 3),
(3, 'Briceni', 3),
(4, 'Cahul', 5),
(5, 'Căușeni', 3),
(6, 'Cimișlia', 3),
(7, 'Criuleni', 3),
(8, 'Dondușeni', 3),
(9, 'Drochia', 3),
(10, 'Fălești', 3),
(11, 'Glodeni', 3),
(12, 'Hîncești', 5),
(13, 'Ialoveni', 3),
(14, 'Leova', 3),
(15, 'Ocnița', 3),
(16, 'Orhei', 5),
(17, 'Rezina', 3),
(18, 'Sîngerei', 3),
(19, 'Soroca', 5),
(20, 'Strășeni', 5),
(21, 'Ștefan Vodă', 3),
(22, 'Taraclia', 3),
(23, 'Telenești', 3),
(24, 'Bubuieci', 2),
(25, 'Tohatin', 2),
(26, 'Trușeni', 2),
(27, 'Alexanderfeld', 4),
(28, 'Roșu', 4),
(29, 'Manta', 2),
(30, 'Zîrnești', 2);

-- --------------------------------------------------------

--
-- Table structure for table `partide`
--

CREATE TABLE `partide` (
  `id_partid` int(11) NOT NULL,
  `nume_partid` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `partide`
--

INSERT INTO `partide` (`id_partid`, `nume_partid`) VALUES
(1, 'MAN'),
(2, 'PSRM'),
(3, 'CI'),
(4, 'PPPDA'),
(5, 'PAS'),
(6, 'PN'),
(7, 'PDCM'),
(8, 'LOC'),
(9, 'FASM'),
(10, 'PS'),
(11, 'MAN'),
(12, 'PSRM'),
(13, 'CI'),
(14, 'PPPDA'),
(15, 'PAS'),
(16, 'PN'),
(17, 'PDCM'),
(18, 'LOC'),
(19, 'FASM'),
(20, 'PS'),
(21, 'PLDM'),
(22, 'ACUM'),
(23, 'PDM');

-- --------------------------------------------------------

--
-- Table structure for table `primari`
--

CREATE TABLE `primari` (
  `id` int(11) NOT NULL,
  `nume` varchar(100) NOT NULL,
  `prenume` varchar(100) NOT NULL,
  `id_localitate` int(11) NOT NULL,
  `id_partid` int(11) NOT NULL,
  `id_functie` int(11) NOT NULL,
  `id_gen` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `primari`
--

INSERT INTO `primari` (`id`, `nume`, `prenume`, `id_localitate`, `id_partid`, `id_functie`, `id_gen`) VALUES
(47, 'Ion', 'Ceban', 1, 1, 1, 1),
(48, 'Alexandr', 'Mațarin', 2, 2, 1, 1),
(49, 'Vitalii', 'Gorodinschii', 3, 2, 1, 1),
(50, 'Nicolae', 'Dandiș', 4, 3, 1, 1),
(51, 'Anatolie', 'Donțu', 5, 4, 1, 1),
(52, 'Sergiu', 'Andronachi', 6, 5, 1, 1),
(53, 'Mihail', 'Sclifos', 7, 2, 1, 2),
(54, 'Ion', 'Zloi', 8, 2, 1, 1),
(55, 'Nina', 'Cereteu', 9, 6, 1, 2),
(56, 'Alexandr', 'Severin', 10, 6, 1, 1),
(57, 'Stela', 'Onuțu', 11, 6, 1, 2),
(58, 'Alexandru', 'Botnari', 12, 7, 1, 1),
(59, 'Sergiu', 'Armașu', 13, 5, 1, 1),
(60, 'Alexandru', 'Bujoren', 14, 8, 1, 1),
(61, 'Victor', 'Artamaniuc', 15, 2, 1, 1),
(62, 'Tatiana', 'Cociu', 16, 9, 1, 1),
(63, 'Simion', 'Tatarov', 17, 10, 1, 1),
(64, 'Arcadie', 'Covaliov', 18, 5, 1, 1),
(65, 'Lilia', 'Pilipețchi', 19, 2, 1, 2),
(66, 'Valentina', 'Casian', 20, 3, 1, 2),
(67, 'Vladislav', 'Cociu', 21, 8, 1, 1),
(68, 'Veaceslav', 'Lupov', 22, 3, 1, 1),
(69, 'Vadim', 'Lelic', 23, 10, 1, 1),
(70, 'Leonid', 'Umaneț', 24, 1, 1, 1),
(71, 'Olga', 'Caraman', 25, 4, 1, 2),
(72, 'Viorica', 'Beregoi', 26, 5, 1, 2),
(85, 'Liubov', 'Arnautova', 27, 3, 1, 2),
(86, 'Nicolae', 'Savilencu', 28, 3, 1, 1),
(87, 'Violeta', 'Hîncu', 29, 22, 1, 2),
(88, 'Nicolae', 'Beju', 30, 23, 1, 1);

-- --------------------------------------------------------

--
-- Table structure for table `unitate`
--

CREATE TABLE `unitate` (
  `id_unitate` int(11) NOT NULL,
  `nume` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `unitate`
--

INSERT INTO `unitate` (`id_unitate`, `nume`) VALUES
(2, 'Comuna'),
(3, 'Oras'),
(4, 'Sat'),
(5, 'Municipiu');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `consilieri`
--
ALTER TABLE `consilieri`
  ADD PRIMARY KEY (`id`),
  ADD KEY `id_localitate` (`id_localitate`),
  ADD KEY `id_partid` (`id_partid`),
  ADD KEY `id_functie` (`id_functie`),
  ADD KEY `fk_consilieri_genuri` (`id_gen`);

--
-- Indexes for table `functii`
--
ALTER TABLE `functii`
  ADD PRIMARY KEY (`id_functie`);

--
-- Indexes for table `genuri`
--
ALTER TABLE `genuri`
  ADD PRIMARY KEY (`id_gen`);

--
-- Indexes for table `localitati`
--
ALTER TABLE `localitati`
  ADD PRIMARY KEY (`id_localitate`),
  ADD KEY `id_unitate` (`id_unitate`);

--
-- Indexes for table `partide`
--
ALTER TABLE `partide`
  ADD PRIMARY KEY (`id_partid`);

--
-- Indexes for table `primari`
--
ALTER TABLE `primari`
  ADD PRIMARY KEY (`id`),
  ADD KEY `id_localitate` (`id_localitate`),
  ADD KEY `id_partid` (`id_partid`),
  ADD KEY `id_functie` (`id_functie`),
  ADD KEY `fk_primari_genuri` (`id_gen`);

--
-- Indexes for table `unitate`
--
ALTER TABLE `unitate`
  ADD PRIMARY KEY (`id_unitate`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `consilieri`
--
ALTER TABLE `consilieri`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=18;

--
-- AUTO_INCREMENT for table `functii`
--
ALTER TABLE `functii`
  MODIFY `id_functie` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `genuri`
--
ALTER TABLE `genuri`
  MODIFY `id_gen` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `localitati`
--
ALTER TABLE `localitati`
  MODIFY `id_localitate` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=31;

--
-- AUTO_INCREMENT for table `partide`
--
ALTER TABLE `partide`
  MODIFY `id_partid` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=24;

--
-- AUTO_INCREMENT for table `primari`
--
ALTER TABLE `primari`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=96;

--
-- AUTO_INCREMENT for table `unitate`
--
ALTER TABLE `unitate`
  MODIFY `id_unitate` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `consilieri`
--
ALTER TABLE `consilieri`
  ADD CONSTRAINT `consilieri_ibfk_1` FOREIGN KEY (`id_localitate`) REFERENCES `localitati` (`id_localitate`),
  ADD CONSTRAINT `consilieri_ibfk_2` FOREIGN KEY (`id_partid`) REFERENCES `partide` (`id_partid`),
  ADD CONSTRAINT `consilieri_ibfk_3` FOREIGN KEY (`id_functie`) REFERENCES `functii` (`id_functie`),
  ADD CONSTRAINT `fk_consilieri_genuri` FOREIGN KEY (`id_gen`) REFERENCES `genuri` (`id_gen`);

--
-- Constraints for table `localitati`
--
ALTER TABLE `localitati`
  ADD CONSTRAINT `localitati_ibfk_1` FOREIGN KEY (`id_unitate`) REFERENCES `unitate` (`id_unitate`);

--
-- Constraints for table `primari`
--
ALTER TABLE `primari`
  ADD CONSTRAINT `fk_primari_genuri` FOREIGN KEY (`id_gen`) REFERENCES `genuri` (`id_gen`),
  ADD CONSTRAINT `primari_ibfk_1` FOREIGN KEY (`id_localitate`) REFERENCES `localitati` (`id_localitate`),
  ADD CONSTRAINT `primari_ibfk_2` FOREIGN KEY (`id_partid`) REFERENCES `partide` (`id_partid`),
  ADD CONSTRAINT `primari_ibfk_3` FOREIGN KEY (`id_functie`) REFERENCES `functii` (`id_functie`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
