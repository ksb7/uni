<?php
//session_start();
// set_time_limit(0);
// error_reporting(E_ALL);
Error_Reporting(E_ALL & ~E_NOTICE);
// Informatii baza de date
$AdresaBazaDate = "localhost";
$UtilizatorBazaDate = "root"; //numele utilizatorului
$ParolaBazaDate = ""; //parola de conectare la baza de date
$NumeBazaDate = "studenti_mi"; //numele bazei de date
$conexiune = mysqli_connect($AdresaBazaDate,$UtilizatorBazaDate,$ParolaBazaDate,$NumeBazaDate);
// Check connection
if (mysqli_connect_errno()) 
{
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  exit();
}
//CHECK TIME-ZONE
// SHOW GLOBAL VARIABLES LIKE 'time_zone';
if (function_exists('date_default_timezone_set'))
date_default_timezone_set('Europe/Moscow');
function addentities($data)
{
if(trim($data) != '')
{
$data = htmlentities($data, ENT_QUOTES);
return str_replace('\\', '&#92;', $data);
} 
else 
	return $data;
} 
// End addentities() --------------
?>