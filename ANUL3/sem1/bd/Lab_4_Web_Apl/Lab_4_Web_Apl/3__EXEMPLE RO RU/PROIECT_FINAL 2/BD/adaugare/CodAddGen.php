<?php
    include_once '../conect.php';


    $etn = $_POST['gen'];
    $pop = $_POST['pop'];
    $an = $_POST['anul'];
    $loc = $_POST['loc'];

    $sql = "INSERT INTO popsex(idSex,Populatie,idAn,idLocalitate)
            VALUES ('$etn','$pop','$an','$loc')";
    mysqli_query($conn,$sql);
    
    header("refresh:0.5; url=adaugaregen.php");     

?>
