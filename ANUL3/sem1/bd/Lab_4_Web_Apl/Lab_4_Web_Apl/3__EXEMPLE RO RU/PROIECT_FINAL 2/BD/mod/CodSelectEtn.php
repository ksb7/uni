<?php
        include_once '../conect.php';

        $sql = "SELECT idPopEtnie,Etnie,Populatie,Anul,Localitate FROM popetnii INNER JOIN etnii on popetnii.idEtnie=etnii.idEtnie INNER JOIN an on popetnii.idAn=an.idAn INNER JOIN localitate on popetnii.idLocalitate=localitate.idLocalitate ORDER BY idPopEtnie;";
        $result = mysqli_query($conn, $sql);
        $resultCheck = mysqli_num_rows($result);


        if ($resultCheck > 0) 
        {
                while ($row = mysqli_fetch_assoc($result)) 
                {
                        echo "<tr><td>" . $row['idPopEtnie'] . "</td><td>" . $row['Etnie'] . "</td><td>" . $row['Populatie'] . "</td><td>" . $row['Anul'] . "</td><td>" . $row['Localitate'] . "</td></tr>";
                }
                        echo '</table>';
        }
?>
