<?php
//session_start();
require_once('config.sql.php');
require_once('config.sql.php');
date_default_timezone_set('Europe/MOSCOW');
$time = date('d-m-Y H:i:s');
//require_once('functions.php');
//include_once("pas.php");
$cerereSQL= "SELECT nume,data_n,an_inscriere,email,telefon,mobil,obs FROM an2";
$rezultat = mysqli_query($conexiune, $cerereSQL);
//$result = mysqli_query($db, $sql) or die( mysqli_error($db));
if(!$rezultat)
	{
    die ("EROARE: nu pot executa interogarea $cerereSQL"."<br/>". mysqli_error($conexiune));
    }
    else
 {
echo "
<html>
<head>
<link rel=\"stylesheet\" href=\"../style.css\" type=\"text/css\" />
</head>
<body style=\"padding: 30px;\">
<h3>Studenti</h3>
<table class=\"studenti\" border=\"1\" width=\"100%\">
<tr style=\"background-color: #999999; color: #ffffff;\"><td>Student</td><td>Data nasterii</td><td>An inscriere</td><td>E-mail</td>
<td>Telefon</td><td>Mobil</td><td>Observatii</td></tr>";
/* Afisarea datelor din masivul de date in care a fost transferat 
rezultatul comenzii SELECT. */
//CHECK TIME-ZONE
// SHOW GLOBAL VARIABLES LIKE 'time_zone';
if (function_exists('date_default_timezone_set'))
date_default_timezone_set('Europe/Moscow');
define('TIMEZONE', 'Europe/Moscow');
date_default_timezone_set(TIMEZONE);
//
while($rand=mysqli_fetch_array($rezultat))// Alegem din masiv cite un rind
	{
/* echo; */
/* Plasam rindul ales in tabelul prezentat in HTML*/
echo '<tr><td>'.$rand['nume'].' '.$rand['prenume'].'</td>
<td>'.$rand['data_n'].'</td>
<td>'.$rand['an_inscriere'].'</td>
<td>'.$rand['email'].'</td>
<td>'.$rand['telefon'].'</td>
<td>'.$rand['mobil'].'</td>
<td>'.$rand['obs'].'</td></tr>';
}
	echo "</TABLE>";
}
/* inchidere conectare BD */
	mysqli_close($conexiune);
?>