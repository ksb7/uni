<?php
	// se verifica daca se cere o pagina 
	/* Bazarea pe valoarea implicită a unei variabile neinitializate este problematică în cazul includerii unui fișier într-un alt care utilizează același nume de variabilă. Este, de asemenea, un risc major de securitate cu register_globals activat. Eroarea de nivel E_NOTICE este emisă în cazul în care se lucrează cu variabile neinițializate, însă nu în cazul adăugării de elemente la matricea neinițializată. isset () constructul de limbă poate fi folosit pentru a detecta dacă o variabilă a fost deja inițializată. În plus și mai ideală este soluția de empty() deoarece nu generează un mesaj de avertizare sau de eroare dacă variabila nu este inițializată. */
Error_Reporting(E_ALL & ~E_NOTICE);
if (isset($_GET['ID'])) 
{
    // daca se cere o pagina se verifica daca variabila nu este goala/null-a 
	if (!empty($_GET['ID']))
        {     
			$ID = $_GET['ID'];  
		} 
    // daca este goala se ia pagina principala
		else
		{  
			$ID = 'index';  
		};
}
	// daca nu se cere nici o pagina inseamna ca trebuie afisata pagina principala
		else
		{   
			$ID = 'index';  
		} 
	// IN CONTINUARE SE PRELUCREAZA PAGINA PENTRU AFISARE
	
SWITCH ($ID)

//STUDENTI
{
CASE 'stud':
if (file_exists("vizualizare.php"))
{
include_once("vizualizare.php");
$afisare = '';
}
	else
	{ 
		$afisare  = '<br>Eroare: Nu se gaseste fisierul studenti.html';
	} 
break; 

//ADMIN
CASE 'admin';
if (file_exists("Admin.php")) 
{
include_once("Admin.php"); $afisare = ''; 
} 
else
{ 
$afisare  = '<br>Eroare: Nu se gaseste fisierul admin.php';
} 
break; 

//CAUT
CASE 'caut':
if (file_exists("cauta.php"))
{
$afisare  = '';
include_once("cauta.php");
} 
else
{ 
$afisare  = '<br>Eroare: Nu se gaseste fisierul cauta.php';
} 
break;

//CATALOG
CASE 'cat':
if (file_exists("catalog_meniu.php")) 
{
include_once("catalog_meniu.php"); $afisare = ''; 
} 
else
{ 
$afisare  = '<br>Eroare: Nu se gaseste fisierul catalog_meniu.php';
} 
break; 

//PROIECTE
CASE 'pro':
if (file_exists("proiecte.html")) 
{ 
include_once("proiecte.html"); 
$afisare = ''; 
} 
else 
{ 
$afisare  = '<br>Eroare: Nu se gaseste fisierul proiecte.html'; 
} 
break;

//CONTACT
CASE 'contact':
if (file_exists("contact.html"))
{
$afisare  = '';
include_once("contact.html");
} 
else
{ 
$afisare  = '<br>Eroare: Nu se gaseste fisierul contact.html';
} 
break;

//FEEDBACK
CASE 'feedback':
if (file_exists("feedback.html"))
{
$afisare  = '';
include_once("feedback.html");
} 
else
{ 
$afisare  = '<br>Eroare: Nu se gaseste fisierul feedback.html';
} 
break;
// VIEW_feedback
CASE 'view_feedback':
if (file_exists("view_feedback.php"))
{
$afisare  = '';
include_once("view_feedback.php");
} 
else
{ 
$afisare  = '<br>Eroare: Nu se gaseste fisierul view_feedback.php';
} 
break;

CASE 'index':
if (file_exists("primapagina.html")) 
{ 
include_once("primapagina.html");
$afisare  = '';
} 
else
{ 
$afisare  = '<br>Eroare: Nu se gaseste fisierul primapagina.html';
} 
break;

default:
$afisare = '<br>Eroare: A fost ceruta pagina care nu exista pe server.';
}
// se afiseaza codul html pentru pagina
echo $afisare;
?>
