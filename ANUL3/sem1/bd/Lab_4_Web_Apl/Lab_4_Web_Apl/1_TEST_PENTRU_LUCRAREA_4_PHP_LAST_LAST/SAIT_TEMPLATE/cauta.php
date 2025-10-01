<?php
session_start();
require_once('config.sql.php');

if(!isset($_GET['pag'])) $_GET['pag'] = '';

SWITCH($_GET['pag'])
{
	
CASE '':
echo '<form name="cauta" action="cauta.php?pag=cauta" method="post"> Nume student: <input type="text" name="cauta" value=""> <input type="submit" name="Cauta" value="Cauta"> <br>
</form>'; 
BREAK;

CASE 'cauta':
if($_POST['cauta'] == '') 
	{
		echo 'Introdu un Nume pentru a cauta in baza de date. <br>
		Apasa <a href="cauta.php">aici</a> pentru a te intoarce.'; 
	} 
elseif(strlen($_POST['cauta']) < 2) 
	{ 
		echo 'Cuvantul trebuie sa contina cel putin 2 caractere. <br>
		Apasa <a href="cauta.php">aici</a> pentru a te intoarce.'; 
	} 
else
{
	$cerereSQL = 'SELECT * FROM `an2` WHERE `nume` LIKE "%'.addentities($_POST['cauta']).'%"'; 

	$rezultat = mysqli_query($conexiune,$cerereSQL);
 
	if(mysqli_num_rows($rezultat) > 0)
	{
		echo 'Rezultatle cautarii dupa <b>'.$_POST['cauta'].'</b><br><br>'; 
		while($rand=mysqli_fetch_array($rezultat))
		{
		echo'<b>'.$_POST['cauta'].'</b><br><br>'; 
		echo '<b>'.$rand['nume'].' '.$rand['prenume'].'</b> 
		'.$rand['adresa'].'<br> <i>'.$rand['PG'].' , '.$rand['MS'].' , '.$rand['BD2'].', '.$rand['TI'].'</i> <br>';
		}
	echo'<br> <a href="cauta.php"> Cautare noua</a>';
	echo ("<div style=\'text-align: center; margin-top: 10px;\'><a href=\SAIT_TEMPLATE\>Back</a></div>");
	} 
		else 
		{ 
		echo 'Nu au fost gasite rezultate pentru cautarea: <font color="red"><b><i>'.addentities($_POST['cauta']).'</i></b> </font> <br> Apasati <a href="cauta.php">aici</a> pentru a va intoarce';
		} 
}
BREAK;

$rezultat = mysqli_query($conexiune,$cerereSQL);

if(mysql_num_rows($rezultat) > 0) 
{
	echo 'Cautati in: <font color="red">'.$in.'</font> dupa: <font
	color="red"><b>'.addentities($_POST['cauta']).'</b></font><br><br>'; 
	while($rand=mysqli_fetch_array($rezultat))    
	{ 
	echo '<a href="'.$rand['prenume'].'">'.$rand['nume'].'</a> -'.$rand['prenume'].'<br> <i>'.$rand['descriere'].'</i> <br><br>'; 
	} 
}
else 
{
	echo 'Nu au fost gasite rezultate pentru cautarea: <font color="red"><b><i>'.addentities($_POST['cauta']).'
	</i></b></font> in <font color="red">'.$in.'</font><br>
	Apasati <a href="cauta.php?pag=cautare-avansata">aici</a> pentru a va intoarce';
} 
}
// echo ("<div style=\'text-align: center; margin-top: 10px;\'><a href=\SAIT_TEMPLATE\INDEX.html>Back</a></div>");
?>
