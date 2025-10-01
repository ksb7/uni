<?php
	include_once '../conect.php';


	$id = $_POST['Id'];

	$sql = "DELETE FROM popsex WHERE popsex.idPopSex = '$id'";
	mysqli_query($conn,$sql);
	
	header("refresh:0.5; url=DelGen.php");	

?>