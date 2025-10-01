<?php
        include_once '../conect.php';

        if (isset($_POST['localitate'])) 
        {
                
        

        $searchq1 = $_POST['localitate'];
        $searchq2 = $_POST['gen'];
        $searchq3 = $_POST['mediu'];
        $searchq4 = $_POST['an'];
        $searchq1 = preg_replace("#^0-9a-z#i", "", $searchq1);
        $searchq2 = preg_replace("#^0-9a-z#i", "", $searchq2);
        $searchq3 = preg_replace("#^0-9a-z#i", "", $searchq3);
        $searchq4 = preg_replace("#^0-9a-z#i", "", $searchq4);

        $sql = "SELECT Localitate,Gen,Populatie,Anul,Mediul FROM popsex INNER JOIN localitate on popsex.idLocalitate=localitate.idLocalitate INNER JOIN sex on popsex.idSex=sex.idSex INNER JOIN an ON popsex.idAn-an.idAn INNER JOIN mediul ON localitate.idMediu=mediul.idMediu WHERE Localitate LIKE '%$searchq1%' AND Gen LIKE '%$searchq2%' AND Mediul LIKE '%$searchq3%' AND Anul LIKE '%$searchq4%' ORDER by Localitate";
        $result = mysqli_query($conn, $sql);
        $resultCheck = mysqli_num_rows($result);


        if ($resultCheck >= 0) 
        {
                while ($row = mysqli_fetch_assoc($result)) 
                {
                        echo "<tr><td>" . $row['Localitate'] . "</td><td>" . $row['Gen'] . "</td><td>" . $row['Mediul'] . "</td><td>" . $row['Populatie'] . "</td><td>" . $row['Anul'] . "</td></tr>";
                }
                        echo '</table>';
        }

        }
 
?>