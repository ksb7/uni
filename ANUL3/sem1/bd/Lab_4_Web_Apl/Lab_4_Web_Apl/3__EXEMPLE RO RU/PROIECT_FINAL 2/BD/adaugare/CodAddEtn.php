<?php
    include_once '../conect.php';


    $etn = $_POST['Etnie'];
    $pop = $_POST['pop'];
    $an = $_POST['anul'];
    $loc = $_POST['loc'];

    $sql = "INSERT INTO popetnii(idEtnie,Populatie,idAn,idLocalitate)
            VALUES ('$etn','$pop','$an','$loc')";
    mysqli_query($conn,$sql);
    
    header("refresh:0.5; url=adaugareetnie.php");     

?>
