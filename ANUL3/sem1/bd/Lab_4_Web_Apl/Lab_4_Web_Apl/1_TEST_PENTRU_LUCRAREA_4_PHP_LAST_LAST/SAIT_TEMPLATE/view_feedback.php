<?php 
$con=mysqli_connect("localhost","root","","contact") or die(mysqli_error());
//require_once('functions.php');
// Perform query
$cerereSQL = 'SELECT name, email, phone,comments FROM `contactatus`';
/* prezentare catalogul cu note */
$rezultat = mysqli_query($con, $cerereSQL);
if($result)
	{
    die ("EROARE: nu pot executa interogarea $cerereSQL"."<br/>". mysqli_error($con));
    }
    else
	{  
echo'<table align="center" border="1"><caption align="top"><h1>Lista Feedback</h1>
<tr bgcolor="bleu">
<th>Nume</th>
<th>E-mail</th>
<th>Telefon</th>
<th>Comentarii</th> </tr>' ;
/* Afisarea datelor din masivul de date in care a fost transferat 
rezultatul comenzii SELECT. */
	while($rand=mysqli_fetch_array($rezultat))// Alegem din masiv cite un rind
	{
/* echo; */
/* Plasam rindul ales in tabelul prezentat in HTML*/
echo '<tr>
<td bgcolor="bleu">'.$rand['name'].'</td>
<td align="center">'.$rand['email'].'</td>
<td align="center">'.$rand['phone'].'</td>
<td align="center">'.$rand['comments'].'</td> </tr>';
     }
	echo "</TABLE>";
	 }
/* inchidere conectare BD */
	mysqli_close($con);
?>
