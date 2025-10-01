<?php
        include_once '../conect.php';

        if (isset($_POST['localitate'])) 
        {
                
        

        $searchq1 = $_POST['localitate'];
        $searchq2 = $_POST['etnie'];
        $searchq3 = $_POST['mediu'];
        $searchq4 = $_POST['an'];
        $searchq1 = preg_replace("#^0-9a-z#i", "", $searchq1);
        $searchq2 = preg_replace("#^0-9a-z#i", "", $searchq2);
        $searchq3 = preg_replace("#^0-9a-z#i", "", $searchq3);
        $searchq4 = preg_replace("#^0-9a-z#i", "", $searchq4);

        $sql = "SELECT Etnie,Localitate,Anul,Populatie,Mediul from popetnii INNER JOIN etnii ON popetnii.idEtnie=etnii.idEtnie INNER JOIN localitate ON popetnii.idLocalitate=localitate.idLocalitate INNER JOIN an ON popetnii.idAn=an.idAn INNER JOIN mediul ON localitate.idMediu=mediul.idMediu WHERE Localitate LIKE '%$searchq1%' AND Etnie LIKE '%$searchq2%' AND Mediul LIKE '%$searchq3%' AND Anul LIKE '%$searchq4%'";
        $result = mysqli_query($conn, $sql);
        $resultCheck = mysqli_num_rows($result);


        if ($resultCheck >= 0) 
        {
                while ($row = mysqli_fetch_assoc($result)) 
                {
                        echo "<tr><td>" . $row['Localitate'] . "</td><td>" . $row['Etnie'] . "</td><td>" . $row['Mediul'] . "</td><td>" . $row['Populatie'] . "</td><td>" . $row['Anul'] . "</td></tr>";
                }
                        echo '</table>';
        }

        }
 
?>