<html>
<head>
    <title>Programa gautare carte/carti </title>
</head>
<body>
<?php
/* 	require_once 'config_sql.php'; // script configurare server
	require_once 'connect_serv.php'; // script conectare server
	require_once 'connect_db.php'; // script conectare BD librarie */
echo '<form aсtion="cautare_carte.php" method="POST">
    Cautare dupa::<br>
    <select name="searchtype" size=3>
        <option value="autor" selected>AUTOR
        <option value="titlu">TITLU
        <option value="idcarte">COD CARTE
    </select> <br>
    Ce cautam:<br> <input name="searchterm"> <br>
    <input type=submit value="Cautare">
</form>';
	if(isset($_POST['searchterm']))
	{
    $searchterm=trim($_POST['searchterm']);
	echo $searchterm. "<br/>" . " Veti cauta dupa acest indicator";
	}
	else
	{
  // The user have not filled the <input name='name'> do something for empty
    echo "Nu este definit parametrul de cautare";
	echo "<br/>";
    die ("Nu toate datele sunt introduse <br/>
    continuati sa introduceti datele");
	}
$query = "SELECT * FROM carti WHERE "
    .$_POST['searchtype']." like '%".$searchterm."%'";
$result = mysqli_query ($conexiune, $query );
$n = mysqli_num_rows ( $result );
for ( $i=0; $i<$n; $i++ )
{
    $row = mysqli_fetch_array($result);
    echo "<p><b>".($i+1). $row['titlu']. "</b><br>";
    echo "AUTOR: ".$row['autor']."<br>";
    echo "COD CARTE: ".$row['idcarte']."<br>";
    echo "PRET: ".$row['pret']."<br>";
    echo "CANTITATE: ".$row['cantitatea']."</p>";
}
if ( $n == 0 ) echo "Mai mult nu va putem oferi. Scuzati";
mysqli_close ( $link );
?>
</body>
</html>

