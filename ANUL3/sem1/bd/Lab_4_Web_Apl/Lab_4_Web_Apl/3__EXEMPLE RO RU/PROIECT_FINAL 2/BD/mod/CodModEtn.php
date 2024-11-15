<?php
	include_once '../conect.php';


	$id = $_POST['id'];
	$etn = $_POST['Etnie'];
	$an = $_POST['anul'];
	$pop = $_POST['pop'];
	$idloc = $_POST['idloc'];

	$sql = "UPDATE popetnii
			SET idEtnie = '$etn',Populatie = '$pop', idAn = '$an',idLocalitate='$idloc'
			WHERE idPopEtnie = '$id' ";
	mysqli_query($conn,$sql);
	
	header("refresh:0.5; url=modetnie.php");   	

?>