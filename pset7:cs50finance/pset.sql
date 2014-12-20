-- MySQL dump 10.13  Distrib 5.5.40, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.40-0ubuntu0.14.04.1-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `History`
--

DROP TABLE IF EXISTS `History`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `History` (
  `id` int(10) unsigned NOT NULL,
  `transaction` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `datetime` datetime NOT NULL,
  `symbol` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(11) NOT NULL,
  `price` decimal(10,4) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `History`
--

LOCK TABLES `History` WRITE;
/*!40000 ALTER TABLE `History` DISABLE KEYS */;
INSERT INTO `History` VALUES (6,'BUY','0000-00-00 00:00:00','aapl',10,1089.0000),(6,'SELL','0000-00-00 00:00:00','TGT',5,306.0000),(6,'SELL','2011-05-14 00:00:00','FB',50,3742.0000),(6,'SELL','0000-00-00 00:00:00','AAPL',20,2177.0000),(6,'SELL','2011-05-14 00:00:00','GOOG',10,5459.0000),(6,'BUY','2014-11-05 00:00:00','A',5,201.0000),(6,'BUY','2014-11-05 00:00:00','TGT',50,3056.0000),(6,'BUY','2014-11-05 00:00:00','FB',50,3742.0000),(6,'SELL','2014-11-05 00:00:00','A',5,201.0000),(6,'BUY','2014-11-05 23:06:58','GOOG',10,5459.2000),(13,'BUY','2014-11-06 01:13:34','GOOG',10,5459.2000),(13,'BUY','2014-11-06 01:19:03','TGT',40,2444.8000),(13,'BUY','2014-11-06 01:19:21','FB',10,748.3000),(13,'SELL','2014-11-06 01:20:02','FB',10,748.3000),(13,'SELL','2014-11-06 01:20:16','TGT',40,2444.8000),(19,'BUY','2014-11-06 01:39:48','FB',100,7483.0000),(19,'BUY','2014-11-06 01:41:51','A',30,1203.9000),(19,'BUY','2014-11-06 01:51:47','CMG',10,6425.9000),(19,'BUY','2014-11-06 01:52:02','FREE',50,7.4550),(19,'BUY','2014-11-06 01:52:27','A',30,1203.9000),(19,'BUY','2014-11-06 01:52:40','A',20,802.6000),(19,'SELL','2014-11-06 01:52:56','CMG',10,6425.9000),(19,'SELL','2014-11-06 01:53:03','FREE',50,7.4550),(19,'BUY','2014-11-06 02:05:05','GOOG',10,5459.2000),(13,'BUY','2014-11-06 02:11:29','A',50,2006.5000),(13,'BUY','2014-11-06 02:11:38','FREE',10,1.4910),(6,'BUY','2014-11-06 02:12:14','FREE',100,14.9100),(6,'BUY','2014-11-06 02:12:28','FREE',12,1.7892),(13,'BUY','2014-11-06 02:27:20','CMG',2,1285.1800),(13,'BUY','2014-11-06 02:27:47','CMG',1,642.5900),(13,'SELL','2014-11-06 02:27:57','GOOG',10,5459.2000),(13,'BUY','2014-11-06 02:29:34','A',50,2006.5000),(13,'SELL','2014-11-06 02:39:24','CMG',3,1927.7700),(13,'SELL','2014-11-06 02:39:51','A',100,4013.0000),(13,'BUY','2014-11-06 02:40:11','GOOG',10,5459.2000),(13,'BUY','2014-11-06 02:40:22','CMG',2,1285.1800),(20,'BUY','2014-11-06 02:55:11','CMG',1,642.5900),(20,'BUY','2014-11-06 02:58:09','B',1,36.3200),(20,'SELL','2014-11-06 02:58:15','B',1,36.3200),(20,'SELL','2014-11-06 02:58:23','CMG',1,642.5900);
/*!40000 ALTER TABLE `History` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Portfolio`
--

DROP TABLE IF EXISTS `Portfolio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Portfolio` (
  `id` int(10) unsigned NOT NULL,
  `symbol` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`,`symbol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Portfolio`
--

LOCK TABLES `Portfolio` WRITE;
/*!40000 ALTER TABLE `Portfolio` DISABLE KEYS */;
INSERT INTO `Portfolio` VALUES (1,'AAPL',50),(1,'MCD',25),(2,'AMZN',25),(2,'LNKD',25),(3,'CMG',10),(3,'NFLX',25),(4,'GRPN',100),(4,'MA',25),(4,'TGT',25),(5,'LULU',50),(5,'YELP',50),(6,'FB',50),(6,'FREE',112),(6,'GOOG',10),(6,'TGT',50),(13,'CMG',2),(13,'FREE',10),(13,'GOOG',10),(19,'A',80),(19,'FB',100),(19,'GOOG',10);
/*!40000 ALTER TABLE `Portfolio` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=21 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'belindazeng','$1$50$oxJEDBo9KDStnrhtnSzir0',10000.0000),(2,'caesar','$1$50$GHABNWBNE/o4VL7QjmQ6x0',10000.0000),(3,'jharvard','$1$50$RX3wnAMNrGIbgzbRYrxM1/',10000.0000),(4,'malan','$1$50$lJS9HiGK6sphej8c4bnbX.',10000.0000),(5,'rob','$1$HA$l5llES7AEaz8ndmSo5Ig41',10000.0000),(6,'skroob','$1$50$euBi4ugiJmbpIbvTTfmfI.',6931.3008),(7,'zamyla','$1$50$uwfqB45ANW.9.6qaQ.DcF.',10000.0000),(13,'fan','$1$ACxCBiOc$YlAEa4uZ1CUuNHucKv7cK/',5261.3285),(20,'fandy','$1$K6Wihqyn$mHInkLIc6L2SjFktRxGSU/',10000.0100);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-11-06  3:04:06
