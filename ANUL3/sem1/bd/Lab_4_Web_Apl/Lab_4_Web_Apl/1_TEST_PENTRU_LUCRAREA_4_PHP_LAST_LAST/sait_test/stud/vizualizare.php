<?php 
require_once('config.php');

/**
 * @author 
 * @copyright 2011
 */

$cerereSQL = 'SELECT * FROM `an1`';
$rezultat = mysql_query($cerereSQL); while($rand = mysql_fetch_array($rezultat)) { echo '<b>Student:</b> '.$rand['student'].' <br>
<b>Data nasterii:</b> '.$rand['datan'].' <br>
<b>An inscriere:</b> '.$rand['an_inscriere'].'<br> <b>E-mail:</b> '.$rand['e-mail'].' <br> <b>Telefon:</b> '.$rand['telefon'].' <br> <b>Mobil:</b> '.$rand['mobil'].' <br> <b>Observatii:</b> '.$rand['obs'].' <br><br>'; } 



?>