<?php
	include_once '../conect.php';


	$id = $_POST['id'];
	$etn = $_POST['gen'];
	$an = $_POST['anul'];
	$pop = $_POST['pop'];
	$idloc = $_POST['idloc'];

	$sql = "UPDATE popsex
			SET idSex = '$etn',Populatie = '$pop', idAn = '$an',idLocalitate='$idloc'
			WHERE idPopSex = '$id'";
	mysqli_query($conn,$sql);
	
	header("refresh:0.5; url=modgen.php");   	

?>