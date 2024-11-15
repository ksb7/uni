<?php
// se verifica daca se cere o pagina 
if (isset($_GET['ID'])) 
{
// daca se cere o pagina se verifica daca variabila nu este goala 
if (!empty($_GET['ID']))
         {     $ID = $_GET['ID'];  } 
    // daca este goala se ia pagina principala
    else
         {  $ID = 'index';  };}
// daca nu se cere nici o pagina inseamna ca trebuie afisata pagina principala
else
    {   $ID = 'index';  } 
// in continuare se prelucreaza pagina pentru afisare
switch ($ID)
//STUDENTI
{
case 'stud':
if (file_exists("studenti.html"))
{
include_once("studenti.html");
$afisare = '';
} else
{ $afisare  = '<br>Eroare: Nu se gaseste fisierul studenti.html';
} break; 
//CATALOG
case 'cat':
if (file_exists("catalog.html")) {
include_once("catalog.html"); $afisare = ''; } else
{ $afisare  = '<br>Eroare: Nu se gaseste fisierul catalog.html';
} break; 
//PROIECTE
case 'pro':
if (file_exists("proiecte.html")) { include_once("proiecte.html"); $afisare = ''; } else { $afisare  = '<br>Eroare: Nu se gaseste fisierul proiecte.html'; } break;
//CONTACT
case 'contact':
if (file_exists("contact.html"))
{
$afisare  = '';
include_once("contact.html");
} else
{ $afisare  = '<br>Eroare: Nu se gaseste fisierul contact.html';
} break;
case 'index':
if (file_exists("primapagina.html")) { include_once("primapagina.html");
$afisare  = '';
} else
{ $afisare  = '<br>Eroare: Nu se gaseste fisierul primapagina.html';
} break;
default:
$afisare = '<br>Eroare: A fost ceruta pagina care nu exista pe server.';
}
// se afiseaza codul html pentru pagina
echo $afisare;
?>
