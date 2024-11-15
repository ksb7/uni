<?php
error_reporting(E_ALL); 
// se include antetul
if (file_exists('antet.html'))
{     include_once('antet.html');   } else
{     die("<br>Eroare: Nu se gaseste fisierul antet.html"); }
if (file_exists('corp.php'))
{     include_once('corp.php');     } else
{     die("<br>Eroare: Nu se gaseste fisierul corp.php");   } if (file_exists('subsol.html'))
{     include_once('subsol.html');  } else
{   die("<br>Eroare: Nu se gaseste fisierul subsol.html");  } 
?>
