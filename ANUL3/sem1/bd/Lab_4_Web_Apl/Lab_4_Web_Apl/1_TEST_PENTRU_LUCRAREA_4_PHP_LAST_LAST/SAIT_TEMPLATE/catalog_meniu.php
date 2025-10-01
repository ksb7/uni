<?php 
$sql = "INSERT INTO logs (username, msg, color, Time) VALUES ('$uname', '$msg', '$color', '$time')";
//session_start();
//set_time_limit(0);
//require_once('functions.php');
// Perform query
$cerereSQL = 'SELECT nume, PG, MS,BD2,TI FROM `an2`';
/* prezentare catalogul cu note */
$rezultat = mysqli_query($conexiune, $cerereSQL);
if($result)
	{
    die ("EROARE: nu pot executa interogarea $cerereSQL"."<br/>". mysqli_error($conexiune));
    }
    else
	{  
echo'<table align="center" border="1"><caption align="top"><h1>Catalog
Note</h1>
<tr bgcolor="bleu">
<th>Student</th>
<th>Prelucrare Grafica</th>
<th>Modelare si Simulare</th>
<th>Baze de Date 2</th>
<th>Tehnologii Internet</th> </tr>' ;
/* Afisarea datelor din masivul de date in care a fost transferat 
rezultatul comenzii SELECT. */
	while($rand=mysqli_fetch_array($rezultat))// Alegem din masiv cite un rind
	{
/* echo; */
/* Plasam rindul ales in tabelul prezentat in HTML*/
echo '<tr>
<td bgcolor="bleu">'.$rand['nume'].'</td>
<td align="center">'.$rand['PG'].'</td>
<td align="center">'.$rand['MS'].'</td>
<td align="center">'.$rand['BD2'].'</td>
<td align="center">'.$rand['TI'].'</td> </tr>';
     }
	echo "</TABLE>";
	 }
/* inchidere conectare BD */
	mysqli_close($conexiune);
?>
