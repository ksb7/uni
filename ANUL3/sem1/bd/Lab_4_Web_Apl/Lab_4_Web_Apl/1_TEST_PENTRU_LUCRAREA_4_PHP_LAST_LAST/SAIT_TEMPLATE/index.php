<?php
/* Sesiunile, reprezinta o functionalitate prin care anumite informatii sunt mentinute de la o pagina la alta. O sesiune dureaza atat timp cat utilizatorul acceseaza un site si se incheie odata cu inchiderea browserului.
In momentul in care un script apeleaza functia session_start() pentru prima data intr-o sesiune de lucru, se transmite un cookie catre browserul clientului (un header de tipul 'Set-Cookie', vezi lectia Cookie-uri). Fiind vorba de un cookie, este necesar ca functia session_start() sa fie apelata inaintea oricarei instructiuni ce afiseaza ceva (print, echo, etc) si inaintea oricarui cod HTML. Cookie-ul transmis contine un identificator ce poarta numele de Session ID, pe baza caruia se poate face distinctie intre sesiunea curenta si alte sesiuni ale altor utilizatori ce acceseaza site-ul in acel moment. */
session_start();
//FISIERUL DE CONFIGURARE A UNEI BD CONCRETE
require_once('config.sql.php');
// require_once('functions.php');
/* 
error_reporting — Stabilește ce erori PHP vor fi raportate   (PHP 4, PHP 5, PHP 7)
Funcția error_reporting() stabilește directiva error_reporting în timpul rulării. PHP posedă multe nivele de erori, iar utilizarea acestei funcții vă permite să stabiliți nivelul ce va fi activ pe durata execuției script-ului dumneavoastră. Dacă parametrul opțional level nu este stabilit, error_reporting() va întoarce doar nivelul curent de raportare a erorilor.
Sfat
Transmiterea valorii -1 va afișa toate erorile posibile, chiar și atunci când vor fi adăugate nivele și constante noi în versiunile viitoare ale PHP. Constanta E_ALL se comportă în același mod începând cu PHP 
 */
error_reporting(E_ALL); 
// se include antetul
if (file_exists('antet.html'))
{     
include_once('antet.html');   
} 
else
{     
die("<br>Eroare: Nu se gaseste fisierul antet.html"); 
}
if (file_exists('corp.php'))
{     
include_once('corp.php');     
} 
else
{     
die("<br>Eroare: Nu se gaseste fisierul corp.php");   
} 
if (file_exists('subsol.html'))
{     
include_once('subsol.html');  
} 
else
{   
die("<br>Eroare: Nu se gaseste fisierul subsol.html");  
} 
?>
