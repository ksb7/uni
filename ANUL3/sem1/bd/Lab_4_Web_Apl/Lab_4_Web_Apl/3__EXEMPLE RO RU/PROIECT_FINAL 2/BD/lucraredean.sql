-- phpMyAdmin SQL Dump
-- version 4.9.2
-- https://www.phpmyadmin.net/
--
-- Хост: 127.0.0.1
-- Время создания: Янв 18 2020 г., 13:32
-- Версия сервера: 10.4.11-MariaDB
-- Версия PHP: 7.4.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `lucraredean`
--

-- --------------------------------------------------------

--
-- Структура таблицы `an`
--

CREATE TABLE `an` (
  `idAn` int(11) NOT NULL,
  `Anul` year(4) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Дамп данных таблицы `an`
--

INSERT INTO `an` (`idAn`, `Anul`) VALUES
(1, 2004),
(2, 2014);

-- --------------------------------------------------------

--
-- Структура таблицы `etnii`
--

CREATE TABLE `etnii` (
  `idEtnie` int(11) NOT NULL,
  `Etnie` varchar(30) COLLATE utf8_bin DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Дамп данных таблицы `etnii`
--

INSERT INTO `etnii` (`idEtnie`, `Etnie`) VALUES
(1, 'Rusi'),
(2, 'Ukraineni'),
(3, 'Romani'),
(4, 'Moldoveni'),
(5, 'Gagauzi'),
(6, 'Bulgari');

-- --------------------------------------------------------

--
-- Структура таблицы `localitate`
--

CREATE TABLE `localitate` (
  `idLocalitate` int(11) NOT NULL,
  `Localitate` varchar(40) COLLATE utf8_bin DEFAULT NULL,
  `idMediu` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Дамп данных таблицы `localitate`
--

INSERT INTO `localitate` (`idLocalitate`, `Localitate`, `idMediu`) VALUES
(1, 'Chisinau', 2),
(2, 'Orhei', 2),
(3, 'Bacioi', 1),
(4, 'Frumusica', 1),
(5, 'Balti', 2),
(6, 'Anenii Noi', 2),
(7, 'Basarabeasca', 1),
(8, 'Briceni', 1),
(9, 'Cahul', 2),
(10, 'Cantemir', 2),
(11, 'Calarasi', 2),
(12, 'Causeni', 2),
(13, 'Cimislia', 2),
(14, 'Criuleni', 2),
(15, 'Donduseni', 2),
(16, 'Dubasari', 2),
(17, 'Soroca', 2),
(18, 'Razeni', 1);

-- --------------------------------------------------------

--
-- Структура таблицы `mediul`
--

CREATE TABLE `mediul` (
  `idMediu` int(11) NOT NULL,
  `Mediul` varchar(5) COLLATE utf8_bin DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Дамп данных таблицы `mediul`
--

INSERT INTO `mediul` (`idMediu`, `Mediul`) VALUES
(1, 'Rural'),
(2, 'Urban');

-- --------------------------------------------------------

--
-- Структура таблицы `popetnii`
--

CREATE TABLE `popetnii` (
  `idPopEtnie` int(11) NOT NULL,
  `idEtnie` int(11) DEFAULT NULL,
  `Populatie` int(11) NOT NULL,
  `idAn` int(11) DEFAULT NULL,
  `idLocalitate` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Дамп данных таблицы `popetnii`
--

INSERT INTO `popetnii` (`idPopEtnie`, `idEtnie`, `Populatie`, `idAn`, `idLocalitate`) VALUES
(23, 4, 481626, 1, 1),
(24, 2, 58945, 1, 1),
(26, 1, 99149, 1, 1),
(27, 5, 6446, 1, 1),
(28, 3, 31984, 1, 1),
(29, 6, 8868, 1, 1),
(30, 4, 116271, 1, 2),
(32, 2, 4520, 1, 2),
(33, 1, 2216, 1, 2),
(34, 5, 113, 1, 2),
(35, 3, 8253, 1, 2),
(36, 6, 90, 1, 2),
(37, 4, 66877, 1, 5),
(38, 2, 30288, 1, 5),
(39, 1, 24526, 1, 5),
(40, 5, 243, 1, 5),
(41, 3, 2258, 1, 5),
(42, 6, 297, 1, 5),
(43, 4, 55123, 1, 8),
(44, 2, 19939, 1, 8),
(45, 1, 2061, 1, 8),
(46, 5, 59, 1, 8),
(48, 3, 314, 1, 8),
(49, 6, 45, 1, 8),
(50, 4, 91001, 1, 9),
(51, 2, 7842, 1, 9),
(52, 1, 7702, 1, 9),
(53, 5, 3665, 1, 9),
(54, 3, 2095, 1, 9),
(55, 6, 5816, 1, 9),
(56, 4, 68761, 1, 6),
(57, 2, 6526, 1, 6),
(58, 1, 4135, 1, 6),
(59, 5, 235, 1, 6),
(60, 3, 857, 1, 6),
(61, 6, 481, 1, 6),
(62, 4, 84728, 1, 17),
(63, 2, 4752, 1, 17),
(64, 1, 2601, 1, 17),
(65, 5, 53, 1, 17),
(66, 3, 931, 1, 17),
(67, 6, 48, 1, 17),
(68, 4, 304860, 2, 1),
(70, 1, 42174, 2, 1),
(71, 3, 65800, 2, 1),
(72, 2, 26774, 2, 1),
(73, 5, 3176, 2, 1),
(74, 6, 4991, 2, 1),
(75, 4, 83598, 2, 2),
(76, 3, 8917, 2, 2),
(77, 2, 3039, 2, 2),
(78, 1, 1317, 2, 2),
(79, 5, 101, 2, 2),
(80, 6, 100, 2, 2),
(81, 4, 66622, 2, 17),
(82, 3, 3154, 2, 17),
(83, 2, 2854, 2, 17),
(84, 1, 1502, 2, 17),
(85, 5, 35, 2, 17),
(86, 6, 37, 2, 17),
(87, 4, 64440, 2, 6),
(88, 3, 4379, 2, 6),
(89, 2, 4692, 2, 6),
(90, 1, 3519, 2, 6),
(91, 5, 245, 2, 6),
(92, 6, 469, 2, 6),
(93, 4, 57222, 2, 5),
(94, 3, 2738, 2, 5),
(95, 2, 17468, 2, 5),
(96, 1, 15108, 2, 5),
(97, 5, 139, 2, 5),
(98, 6, 188, 2, 5);

-- --------------------------------------------------------

--
-- Структура таблицы `popsex`
--

CREATE TABLE `popsex` (
  `idPopSex` int(11) NOT NULL,
  `idLocalitate` int(11) NOT NULL,
  `idSex` int(11) DEFAULT NULL,
  `Populatie` int(11) DEFAULT NULL,
  `idAn` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Дамп данных таблицы `popsex`
--

INSERT INTO `popsex` (`idPopSex`, `idLocalitate`, `idSex`, `Populatie`, `idAn`) VALUES
(17, 1, 1, 235478, 1),
(18, 1, 2, 245372, 1),
(19, 1, 3, 480840, 1);

-- --------------------------------------------------------

--
-- Структура таблицы `sex`
--

CREATE TABLE `sex` (
  `idSex` int(11) NOT NULL,
  `Gen` varchar(2) COLLATE utf8_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Дамп данных таблицы `sex`
--

INSERT INTO `sex` (`idSex`, `Gen`) VALUES
(1, 'F'),
(2, 'M'),
(3, 'B');

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `an`
--
ALTER TABLE `an`
  ADD PRIMARY KEY (`idAn`);

--
-- Индексы таблицы `etnii`
--
ALTER TABLE `etnii`
  ADD PRIMARY KEY (`idEtnie`);

--
-- Индексы таблицы `localitate`
--
ALTER TABLE `localitate`
  ADD PRIMARY KEY (`idLocalitate`),
  ADD UNIQUE KEY `Localitate` (`Localitate`),
  ADD KEY `idMediu` (`idMediu`);

--
-- Индексы таблицы `mediul`
--
ALTER TABLE `mediul`
  ADD PRIMARY KEY (`idMediu`);

--
-- Индексы таблицы `popetnii`
--
ALTER TABLE `popetnii`
  ADD PRIMARY KEY (`idPopEtnie`),
  ADD UNIQUE KEY `unique_index` (`idLocalitate`,`idEtnie`,`idAn`),
  ADD KEY `idEtnie` (`idEtnie`),
  ADD KEY `idAn` (`idAn`);

--
-- Индексы таблицы `popsex`
--
ALTER TABLE `popsex`
  ADD PRIMARY KEY (`idPopSex`),
  ADD UNIQUE KEY `unique_index` (`idLocalitate`,`idSex`,`idAn`),
  ADD KEY `fk_nm` (`idSex`),
  ADD KEY `fk_nl` (`idAn`);

--
-- Индексы таблицы `sex`
--
ALTER TABLE `sex`
  ADD PRIMARY KEY (`idSex`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `an`
--
ALTER TABLE `an`
  MODIFY `idAn` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT для таблицы `etnii`
--
ALTER TABLE `etnii`
  MODIFY `idEtnie` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT для таблицы `localitate`
--
ALTER TABLE `localitate`
  MODIFY `idLocalitate` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=40;

--
-- AUTO_INCREMENT для таблицы `mediul`
--
ALTER TABLE `mediul`
  MODIFY `idMediu` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT для таблицы `popetnii`
--
ALTER TABLE `popetnii`
  MODIFY `idPopEtnie` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=99;

--
-- AUTO_INCREMENT для таблицы `popsex`
--
ALTER TABLE `popsex`
  MODIFY `idPopSex` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=21;

--
-- AUTO_INCREMENT для таблицы `sex`
--
ALTER TABLE `sex`
  MODIFY `idSex` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- Ограничения внешнего ключа сохраненных таблиц
--

--
-- Ограничения внешнего ключа таблицы `localitate`
--
ALTER TABLE `localitate`
  ADD CONSTRAINT `localitate_ibfk_1` FOREIGN KEY (`idMediu`) REFERENCES `mediul` (`idMediu`);

--
-- Ограничения внешнего ключа таблицы `popetnii`
--
ALTER TABLE `popetnii`
  ADD CONSTRAINT `popetnii_ibfk_1` FOREIGN KEY (`idEtnie`) REFERENCES `etnii` (`idEtnie`) ON DELETE CASCADE,
  ADD CONSTRAINT `popetnii_ibfk_2` FOREIGN KEY (`idAn`) REFERENCES `an` (`idAn`) ON DELETE CASCADE,
  ADD CONSTRAINT `popetnii_ibfk_3` FOREIGN KEY (`idLocalitate`) REFERENCES `localitate` (`idLocalitate`) ON DELETE CASCADE;

--
-- Ограничения внешнего ключа таблицы `popsex`
--
ALTER TABLE `popsex`
  ADD CONSTRAINT `fk_nl` FOREIGN KEY (`idAn`) REFERENCES `an` (`idAn`) ON DELETE CASCADE,
  ADD CONSTRAINT `fk_nm` FOREIGN KEY (`idSex`) REFERENCES `sex` (`idSex`) ON DELETE CASCADE,
  ADD CONSTRAINT `fk_nn` FOREIGN KEY (`idLocalitate`) REFERENCES `localitate` (`idLocalitate`) ON DELETE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
