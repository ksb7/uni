<?php

/**
 * @author 
 * @copyright 2011
 */


require_once('config.php');
if(($_SESSION['student'] == "") || ($_SESSION['data_n'] == "") ||
($_SESSION['an_inscriere'] == "") || ($_SESSION['e-mail'] == "") ||
($_SESSION['telefon'] == "")|| ($_SESSION['mobil'] == "")
||($_SESSION['obs'] == "") || (strlen($_SESSION['comentariu']) > 255)
)
{
echo 'Nu ai introdus date in formular sau cele introduse nu sunt
corecte. <br>
Apasa <a href="index1.html">aici</a> pentru a te intoarce la pagina
anterioara.';
}
else
{
echo 'Va multumim. <br>
Datele au fost introduse cu succes in baza de date. <br> Pentru vizualizare apasati <a href="vizualizare.php">aici</a>.';
$cerereSQL = "INSERT INTO `an1` (`student`, `datan`, `an_inscriere`, `e-mail`,`telefon`,`mobil`, `obs`)
VALUES ('".$_SESSION['student']."', '".$_SESSION['datan']."', '".$_SESSION['an_inscriere']."', '".$_SESSION['e-mail']."',
'".$_SESSION['telefon']."','".$_SESSION['mobil']."','".$_SESSION['obs' ]."');"; mysql_query($cerereSQL);
$_SESSION['student'] = ''; $_SESSION['data_n'] = ''; $_SESSION['an_inscriere'] = ''; $_SESSION['e-mail'] = ''; $_SESSION['telefon'] = ''; $_SESSION['mobil'] = ''; $_SESSION['obs'] = ''; }



?>