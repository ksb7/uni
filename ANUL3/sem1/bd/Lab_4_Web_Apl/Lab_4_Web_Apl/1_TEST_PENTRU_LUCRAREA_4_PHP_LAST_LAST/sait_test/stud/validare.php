<?php 
require_once('config.php');

/**
 * @author 
 * @copyright 2011
 */

$_SESSION['student'] = addentities($_POST['student']); $_SESSION['data_n'] = addentities($_POST['data_n']); $_SESSION['an_inscriere'] = addentities($_POST['an_inscriere']); $_SESSION['e-mail'] = addentities($_POST['e-mail']); $_SESSION['telefon'] = addentities($_POST['telefon']); $_SESSION['mobil'] = addentities($_POST['mobil']); $_SESSION['obs'] = addentities($_POST['obs']);
echo 'Student: '.$_SESSION['student'].'<br>
Data nasterii: '.$_SESSION['data_n'].'<br>
An inscriere: '.$_SESSION['an_inscriere'].'<br> Email: '.$_SESSION['e-mail'].'<br> Telefon: '.$_SESSION['telefon'].'<br> Mobil: '.$_SESSION['mobil'].'<br> Comentariu: '.$_SESSION['comentariu'].'<br><br> Daca datele sunt corecte, apasati <a href="prelucrare.php">aici</a> pentru a le valida <br>  si a le introduce in baza de date.'; 



?>